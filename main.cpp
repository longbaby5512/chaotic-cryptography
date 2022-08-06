#include "ChaoticCypher.h"
#include "AES.h"
#include "Example.h"

#include <random>
#include <memory>
#include <chrono>
#include <fstream>

std::vector<byte> randomBytes(int length) {
    std::vector<byte> result(length);
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    std::for_each(std::execution::par, result.begin(), result.end(), [&](byte& b) {
        b = dis(gen);
    });
    return result;
}

std::string printByteArray(std::vector<byte>& bytes) {
    std::string result = "[ ";
    std::for_each(bytes.begin(), bytes.end(), [&](byte b) {
        result += std::to_string(b) + " ";
    });
    return result + "]";
}

bytes chaotic(bytes data);
bytes aes(bytes data);

const size_t byteCount = 1024 * 1024 * 10; // 10 MB

std::vector<size_t> chaosEncryptTime;
std::vector<size_t> chaosDecryptTime;

std::vector<size_t> aesEncryptTime;
std::vector<size_t> aesDecryptTime;

void test1();

int main() {
    auto key = randomBytes(32);
    auto iv = randomBytes(16);
    auto cypher = AES();
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << noimage.length() << std::endl;
    auto encrypted = cypher.EncryptCBC(bytes(noimage.begin(), noimage.end()), key, iv);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << duration.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto decrypted = cypher.DecryptCBC(encrypted, key, iv);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << duration.count() << std::endl;

}

void test1() {

    for (int i = 0; i < 10; i++) {
        auto data = randomBytes(byteCount);
        std::cout << "Test " << i + 1 << std::endl;
        const bytes& data1 = data;
        const bytes& data2 = data;
        auto c = chaotic(data1);
        auto a = aes(data2);
        if (data != c) {
            std::cout << "Chaotic at Test " << i + 1 << "Fail" << std::endl;
        }
        if (data != a) {
            std::cout << "AES at Test " << i + 1 << "Fail" << std::endl;
        }

    }

    std::cout << "Chaotic cypher encrypt time: " << chaosEncryptTime << " with average " << std::accumulate(chaosEncryptTime.begin(), chaosEncryptTime.end(), 0) / chaosEncryptTime.size() << "ms" << std::endl;
    std::cout << "Chaotic cypher decrypt time: " << chaosDecryptTime << " with average " << std::accumulate(chaosDecryptTime.begin(), chaosDecryptTime.end(), 0) / chaosDecryptTime.size() << "ms" << std::endl;
    std::cout << "AES cypher encrypt time: " << aesEncryptTime << " with average " << std::accumulate(aesEncryptTime.begin(), aesEncryptTime.end(), 0) / aesEncryptTime.size() << "ms" << std::endl;
    std::cout << "AES cypher decrypt time: " << aesDecryptTime << " with average " << std::accumulate(aesDecryptTime.begin(), aesDecryptTime.end(), 0) / aesDecryptTime.size() << "ms" << std::endl;
}

bytes chaotic(bytes data) {
    auto key = randomBytes(32);
    auto cypher = ChaoticCypher();
    cypher.init(ChaoticCypher::ENCRYPT_MODE, key);
    auto start = std::chrono::high_resolution_clock::now();
    auto encrypted = cypher.doFinal(data);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    chaosEncryptTime.push_back(duration.count());

    cypher.init(ChaoticCypher::DECRYPT_MODE, key);
    start = std::chrono::high_resolution_clock::now();
    auto decrypted = cypher.doFinal(encrypted);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    chaosDecryptTime.push_back(duration.count());
    return decrypted;
}

bytes aes(bytes data ){
    auto key = randomBytes(32);
    auto iv = randomBytes(16);
    auto cypher = AES();
    auto start = std::chrono::high_resolution_clock::now();
    auto encrypted = cypher.EncryptCBC(data, key, iv);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    aesEncryptTime.push_back(duration.count());

    start = std::chrono::high_resolution_clock::now();
    auto decrypted = cypher.DecryptCBC(encrypted, key, iv);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    aesDecryptTime.push_back(duration.count());

    return decrypted;
}
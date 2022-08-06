#include "ChaoticCypher.h"

#include <random>
#include <chrono>
#include <fstream>

void test();

std::vector<byte> randomBytes(int length) {
    std::vector<byte> result(length);
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    std::for_each(result.begin(), result.end(), [&](byte &b) {
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

bool check(std::vector<byte>& bytes, std::vector<byte>& expected) {
    if (bytes.size() != expected.size()) {
        return false;
    }
    for (int i = 0; i < bytes.size(); i++) {
        if (bytes[i] != expected[i]) {
            return false;
        }
    }
    return true;
}



int main() {
    test();
}

void test() {
    std::vector<int> encryptTime;
    std::vector<int> decryptTime;
    int test_case = 10;
    std::ofstream out_chaos("time_chaos.txt");
    for (int i = 1; i <= test_case; ++i) {
        std::cout << "\nTest case " << i << std::endl;
        out_chaos << "\nTest case " << i << std::endl;
        auto plaintext = randomBytes(10'000'000);
        auto checktext = plaintext;
        auto key = randomBytes(16);

        auto cypher = ChaoticCypher();
        cypher.init(ChaoticCypher::ENCRYPT_MODE, key);
//        std::cout << "Cypher Info: " << cypher << std::endl;
        auto start = std::chrono::system_clock::now();
        auto ciphertext = cypher.doFinal(plaintext);
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Encryption time: " << duration.count() << " milliseconds" << std::endl;
        out_chaos << "Encryption time: " << duration.count() << " milliseconds" << std::endl;
        encryptTime.push_back(duration.count());

        cypher.init(ChaoticCypher::DECRYPT_MODE, key);
//        std::cout << "Cypher Info: " << cypher << std::endl;
        start = std::chrono::system_clock::now();
        auto decrypted = cypher.doFinal(ciphertext);
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Decryption time: " << duration.count() << " milliseconds" << std::endl;
        out_chaos << "Decryption time: " << duration.count() << " milliseconds" << std::endl;
        decryptTime.push_back(duration.count());

        if (!check(decrypted, checktext)) {
            std::cout << "Decrypted data is not the same as original data" << std::endl;
            out_chaos << "Decrypted data is not the same as original data" << std::endl;
        }

    }

    std::cout << "\nAverage encryption time: " << std::accumulate(encryptTime.begin(), encryptTime.end(), 0) / encryptTime.size() << " milliseconds" << std::endl;
    std::cout << "Average decryption time: " << std::accumulate(decryptTime.begin(), decryptTime.end(), 0) / decryptTime.size() << " milliseconds" << std::endl;
    out_chaos << "\nAverage encryption time: " << std::accumulate(encryptTime.begin(), encryptTime.end(), 0) / encryptTime.size() << " milliseconds" << std::endl;
    out_chaos << "Average decryption time: " << std::accumulate(decryptTime.begin(), decryptTime.end(), 0) / decryptTime.size() << " milliseconds" << std::endl;
    out_chaos.close();
}

#include "ChaoticCypher.h"
#include "LFSR.h"

#include <random>
#include <chrono>
#include <fstream>

void test();
void test1();

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

void findAllKey();

int main() {
//    double a = 4.5;
//    double a2 = convertBetween(a, 0.0, 4.0);
//    std::cout << a2 << std::endl;


    test();

}

void test1() {
    auto plain = randomBytes(10);
    std::cout <<"plain: " << printByteArray(plain) << std::endl;
    auto key = randomBytes(10);
    auto cypher = ChaoticCypher();
    cypher.init(ChaoticCypher::ENCRYPT_MODE, key);
    std::cout << "info: " << cypher << std::endl;
    auto encrypted = cypher.doFinal(plain);
    std::cout <<"encrypted: " << printByteArray(encrypted) << std::endl;
    cypher.init(ChaoticCypher::DECRYPT_MODE, key);
    auto decrypted = cypher.doFinal(encrypted);
    std::cout <<"decrypted: " << printByteArray(decrypted) << std::endl;
}

void findAllKey() {
    std::ofstream out("key.txt");
    auto start = std::chrono::system_clock::now();
    for (int x = 0; x < 256; ++x) {
        for (int m = 0; m < 256; ++m) {
            for (int iter = 0; iter < 256 * 32; ++iter) {
                for (int seed = 0; seed < 256; ++seed) {
                    auto x_ = x / 255.0;
                    auto m_ = m / 255.0;
                    convertBetween(m_, 0.0, 1.0, 3.7, 4.0);
                    auto lfsr = LFSR(static_cast<byte>(seed), iter * 8);
                    for (int i = 0; i < iter; ++i) {
                        x_ = m_ * x_ * (1 - x_);
                        auto x_byte_array = convertDoubleToByteArray(x_);
                        for (int j = 0; j < 8; ++j) {
                            x_byte_array[j] ^= lfsr[i * 8 + j];
                            x_ = (x_ + x_byte_array[j] / 255.0 + lfsr[i * 8 + j] / 255.0) / 3.0;
                        }
                        std::swap(x_, m_);
                        convertBetween(x_, 3.7, 4.0, 0.0, 1.0);
                        convertBetween(m_, 0.0, 1.0, 3.7, 4.0);
                    }
                    out << "x: " << x << " m: " << m << " iter: " << iter << " seed: " << seed << " x_: " << x_ << " m_: " << m_ << std::endl;
                }
            }
        }
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    out.close();
}

void test() {
    std::vector<long long> encryptTime;
    std::vector<long long> decryptTime;
    int test_case = 10;
    std::ofstream out_chaos("time_chaos.txt");
    for (int i = 1; i <= test_case; ++i) {
        std::cout << "\nTest case " << i << std::endl;
        out_chaos << "\nTest case " << i << std::endl;
        auto plaintext = randomBytes(100'000'000);
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

    std::cout << "\nAverage encryption time: " << std::accumulate(encryptTime.begin(), encryptTime.end(), 0LL) / encryptTime.size() << " milliseconds" << std::endl;
    std::cout << "Average decryption time: " << std::accumulate(decryptTime.begin(), decryptTime.end(), 0LL) / decryptTime.size() << " milliseconds" << std::endl;
    out_chaos << "\nAverage encryption time: " << std::accumulate(encryptTime.begin(), encryptTime.end(), 0LL) / encryptTime.size() << " milliseconds" << std::endl;
    out_chaos << "Average decryption time: " << std::accumulate(decryptTime.begin(), decryptTime.end(), 0LL) / decryptTime.size() << " milliseconds" << std::endl;
    out_chaos.close();
}

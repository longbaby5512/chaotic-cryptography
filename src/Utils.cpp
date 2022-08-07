//
// Created by Long Kenvy on 28/05/2022.
//

#include "Utils.h"

#include <sstream>
#include <iomanip>

std::string convertByteArrayToHexString(const bytes &digest) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (unsigned char i: digest) {
        ss << std::setw(2) << (int) i;
    }
    return ss.str();
}

bytes convertHexStringToByteArray(const std::string &hexStr) {
    auto digest = bytes(hexStr.length() / 2);
    for (size_t i = 0; i < hexStr.size(); i += 2) {
        std::string byteString = hexStr.substr(i, 2);
        digest[i / 2] = (byte) strtol(byteString.c_str(), nullptr, 16);
    }
    return digest;
}

std::string convertByteArrayToAscii(const bytes &data) {
    std::string res;
    std::for_each(data.begin(), data.begin() + static_cast<long>(data.size()), [&](byte b) {
        res += static_cast<char>(b);
    });
    return res;
}

bytes convertAsciiToByteArray(const std::string &data) {
    auto res = bytes(data.length());
    std::for_each(data.begin(), data.end(), [&](char c) {
        res[std::distance(data.begin(), std::find(data.begin(), data.end(), c))] = static_cast<byte>(c);
    });
    return res;
}

std::vector<int> convertByteToBitArray(byte data) {
    std::vector<int> res(8);
    for (int i = 0; i < 8; ++i) {
        res[i] = (data >> i) & 1;
    }
    return res;
}

byte convertBitArrayToByte(const std::vector<int> &data) {
    byte res = 0;
    for (int i = 0; i < 8; ++i) {
        res |= (data[i] << i);
    }
    return res;
}

std::vector<byte> convertDoubleToByteArray(double data){
    std::vector<byte> res(sizeof(double));
    auto *ptr = reinterpret_cast<byte *>(&data);
    for (int i = 0; i < sizeof(double); ++i) {
        res[i] = ptr[i];
    }
    return res;
}

double convertByteArrayToDouble(const std::vector<byte> & data) {
    assert(data.size() == sizeof(double));
    double res = 0;
    auto *ptr = reinterpret_cast<byte *>(&res);
    for (int i = 0; i < sizeof(double); ++i) {
        ptr[i] = data[i];
    }
    return res;
}


int sumOfByteArray(const bytes &data) {
    int res = 0;
    for (byte b: data) {
        res += b;
    }
    return res;
}

double xorDouble(double a, double b) {
    unsigned long long a_ = *reinterpret_cast<unsigned long long *>(&a);
    unsigned long long b_ = *reinterpret_cast<unsigned long long *>(&b);
    unsigned long long res = a_ ^ b_;
    return *reinterpret_cast<double *>(&res);
}

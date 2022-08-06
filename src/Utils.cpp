//
// Created by Long Kenvy on 28/05/2022.
//

#include "Utils.h"

#include <sstream>
#include <iomanip>

std::string byte2hex(const bytes& digest, size_t length) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (size_t i = 0; i < length; i++) {
        ss << std::setw(2) << (int) digest[i];
    }
    return ss.str();
}

bytes hex2byte(const std::string& hexStr) {
    auto digest = bytes(hexStr.length() / 2);
    for (size_t i = 0; i < hexStr.size(); i += 2) {
        std::string byteString = hexStr.substr(i, 2);
        digest[i / 2] = (byte) strtol(byteString.c_str(), nullptr, 16);
    }
    return digest;
}

std::string bytes2string(const bytes& data, size_t length) {
    std::string res;
    std::for_each(data.begin(), data.begin() + length, [&](byte b) {
        res += static_cast<char>(b);
    });
    return res;
}

bytes string2bytes(const std::string& data) {
    auto res = bytes(data.length());
    std::for_each(data.begin(), data.end(), [&](char c) {
        res[std::distance(data.begin(), std::find(data.begin(), data.end(), c))] = static_cast<byte>(c);
    });
    return res;
}

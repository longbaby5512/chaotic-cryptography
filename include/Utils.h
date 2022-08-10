//
// Created by Long Kenvy on 28/05/2022.
//

#ifndef CHAOTIC_UTILS_H
#define CHAOTIC_UTILS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <execution>
#include <algorithm>
#include <cassert>
#include <cmath>

typedef unsigned char byte;
typedef std::vector<byte> bytes;
typedef std::vector<double> doubles;

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    os << "[";
    for (auto i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}


std::string convertByteArrayToHexString(const bytes &);
bytes convertHexStringToByteArray(const std::string &);
std::string convertByteArrayToAscii(const bytes &);
bytes convertAsciiToByteArray(const std::string &);

std::vector<int> convertByteToBitArray(byte);
byte convertBitArrayToByte(const std::vector<int> &);

std::vector<byte> convertDoubleToByteArray(double);
double convertByteArrayToDouble(const std::vector<byte> &);

template<typename ForwardIterator, typename Compare=std::less<typename std::iterator_traits<ForwardIterator>::value_type>>
std::vector<size_t> argsort(ForwardIterator first, ForwardIterator last, Compare comp = Compare()) {
    using value_type = typename std::iterator_traits<ForwardIterator>::value_type;
    using difference_type = typename std::iterator_traits<ForwardIterator>::difference_type;
    difference_type dist = std::distance(first, last);
    std::vector<size_t> indices(dist);
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(), [&first, &comp](size_t left, size_t right) { return comp(*std::next(first, left), *std::next(first, right)); });
    return indices;
}

int sumOfByteArray(const bytes &);

template<typename T>
void convertBetween(T &value, const T &min, const T &max) {
    value = min + std::fmod(value - min, max - min);
}

template<typename T>
void convertBetween(T &value, const T &minSrc, const T &maxSrc, const T &minDes, const T &maxDes) {
    value = minDes + (value - minSrc) * (maxDes - minDes) / (maxSrc - minSrc);
}

template<typename Base, typename T>
inline bool instanceof(std::unique_ptr<T> &ptr) {
    return dynamic_cast<Base *>(ptr.get()) != nullptr;
}

double xorDouble(double a, double b);

#endif //CHAOTIC_UTILS_H

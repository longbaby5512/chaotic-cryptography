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


std::string byte2hex(const bytes &);
bytes hex2byte(const std::string &);
std::string bytes2string(const bytes &);
bytes string2bytes(const std::string &);

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

template<typename Base, typename T>
inline bool instanceof(std::unique_ptr<T> &ptr) {
    return dynamic_cast<Base *>(ptr.get()) != nullptr;
}

#endif //CHAOTIC_UTILS_H

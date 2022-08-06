//
// Created by nguye on 26/06/2022.
//

#ifndef CHAOTIC_QUICKSORT_H
#define CHAOTIC_QUICKSORT_H

#include <algorithm>
#include <cassert>
#include <functional>
#include <future>
#include <execution>

class QuickSort {
public:
    static bool multithreading;
    static size_t partition_size;

    template<typename Container, typename Compare>
    static void sort(Container &container, Compare compare) {
        sort(container.begin(), container.end(), compare);
    }

    template<typename Container>
    static void sort(Container &container) {
        sort(container.begin(), container.end());
    }

    template<class Container>
    static std::vector<size_t> argsort(const Container &array) {
        std::vector<size_t> indices(array.size());
        std::iota(indices.begin(), indices.end(), 0);
        QuickSort::sort(indices, [&array](size_t left, size_t right) { return array[left] < array[right]; });
        return indices;
    }

    template<typename ForwardIterator, typename Compare=std::less<typename std::iterator_traits<ForwardIterator>::value_type>>
    static void sort(ForwardIterator first, ForwardIterator last, Compare comp = Compare()) {
        using value_type = typename std::iterator_traits<ForwardIterator>::value_type;
        using difference_type = typename std::iterator_traits<ForwardIterator>::difference_type;
        difference_type dist = std::distance(first, last);
        assert(dist >= 0);
        if (dist < 2) {
            return;
        } else if (dist < partition_size) {
            std::sort(std::execution::par, first, last, comp);
        } else {
            auto pivot = *std::next(first, dist / 2);
            auto ucomp = [pivot, &comp](const value_type &em) { return comp(em, pivot); };
            auto not_ucomp = [pivot, &comp](const value_type &em) { return !comp(pivot, em); };

            auto middle1 = std::partition(first, last, ucomp);
            auto middle2 = std::partition(middle1, last, not_ucomp);

            auto policy = multithreading ? std::launch::async : std::launch::deferred;
            auto f1 = std::async(policy, [first, middle1, &comp] { sort(first, middle1, comp); });
            auto f2 = std::async(policy, [middle2, last, &comp] { sort(middle2, last, comp); });
            f1.wait();
            f2.wait();
        }
    }
};

bool QuickSort::multithreading = true;
size_t QuickSort::partition_size = 10000;

#endif //CHAOTIC_QUICKSORT_H

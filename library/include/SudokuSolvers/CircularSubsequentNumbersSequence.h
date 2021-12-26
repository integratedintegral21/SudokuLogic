//
// Created by wojciech on 26/12/2021.
//

#ifndef SUDOKULOGICLIBRARY_CIRCULARSUBSEQUENTNUMBERSSEQUENCE_H
#define SUDOKULOGICLIBRARY_CIRCULARSUBSEQUENTNUMBERSSEQUENCE_H


#include <iterator>

class CircularSubsequentNumbersSequence {
private:
    int first, last, start;
public:
    struct Iterator{
        using iterator_category = std::input_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = int;
        using pointer           = int*;
        using reference         = int&;

        Iterator(value_type number) { m_number = number; }

        pointer operator->() { return &m_number; }
        Iterator& operator++() {
            m_number = first + (++m_number - first) % last;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_number == b.m_number; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_number != b.m_number; };
    private:
        value_type m_number;
        value_type first, last;
    };
};


#endif //SUDOKULOGICLIBRARY_CIRCULARSUBSEQUENTNUMBERSSEQUENCE_H

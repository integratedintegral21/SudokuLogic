//
// Created by wojciech on 25/12/2021.
//

#ifndef SUDOKULOGICLIBRARY_FINITENUMBERSEQUENCE_H
#define SUDOKULOGICLIBRARY_FINITENUMBERSEQUENCE_H

#include "SudokuSolvers/Solvers.h"
#include "iterator"

class Solvers::FiniteNumberSequence {
public:
    struct Iterator{
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = int;
        using pointer           = int*;
        using reference         = int&;

        Iterator(pointer ptr) { m_ptr = ptr; }

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        Iterator& operator++() { m_ptr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
    private:
        pointer m_ptr;
    };
};


#endif //SUDOKULOGICLIBRARY_FINITENUMBERSEQUENCE_H

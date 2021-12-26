//
// Created by wojciech on 26/12/2021.
//

#ifndef SUDOKULOGICLIBRARY_CIRCULARSUBSEQUENTNUMBERSSEQUENCE_H
#define SUDOKULOGICLIBRARY_CIRCULARSUBSEQUENTNUMBERSSEQUENCE_H


#include <iterator>
#include <stdexcept>
#include "SudokuSolvers/Solvers.h"

class Solvers::CircularSubsequentNumbersSequence {
private:
    int first, last, start;
public:
    struct Iterator{
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = int;
        using pointer           = int*;
        using reference         = int&;

        Iterator(value_type first, value_type last, value_type start): first(first), last(last), m_number(start) {
            if (first > last){
                throw std::logic_error("The first number must be less or equal the last number in the sequence");
            }
            if (start < first || start > last){
                throw std::logic_error("The starting number must be between the first and the last number");
            }
        }

        pointer operator->() { return &m_number; }
        value_type operator*(){ return m_number; }
        Iterator& operator++() {
            m_number = first + (++m_number - first) % last;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        Iterator& operator--(){
            if (m_number == first){
                m_number = last;
            }
            else{
                m_number--;
            }
            return *this;
        }
        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_number == b.m_number; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_number != b.m_number; };
    private:
        value_type m_number;
        value_type first, last;
    };

    CircularSubsequentNumbersSequence(int first, int last, int start);

    [[nodiscard]] Iterator begin() const { return {first, last, first}; }
    [[nodiscard]] Iterator end() const { return {first, last, last}; }
    [[nodiscard]] Iterator startingNumber() const { return {first, last, start}; }
};


#endif //SUDOKULOGICLIBRARY_CIRCULARSUBSEQUENTNUMBERSSEQUENCE_H

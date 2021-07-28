//
// Created by wojciech on 28/07/2021.
//

#ifndef CINEMA_CELL_H
#define CINEMA_CELL_H


class Cell {
private:
    // a number0 inside a cell object (-1 if empty)
    int number = -1;
    // possible numbers inside
    bool possibleNumbers[9];

    // initializes all possibleNumbers with false
    void initStates();
    // checks if number is in range <1, 9>
    bool isNumberValid(int number) const;
public:
    Cell();
    explicit Cell(int number);

    int getNumber() const;
    bool isEmpty() const;
    bool isNumberPossible(int number) const;

    void setNumber(int number);
    void setNumberPossible(int number);
    void setNumberNotPossible(int number);

    virtual ~Cell();
};


#endif //CINEMA_CELL_H

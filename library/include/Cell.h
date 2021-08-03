//
// Created by wojciech on 28/07/2021.
//

#ifndef CINEMA_CELL_H
#define CINEMA_CELL_H

/**
 * @brief Represents single sudoku cell
 */
class Cell {
private:
    // a number0 inside a cell object (-1 if empty)
    int number = -1;
    // possible numbers inside
    bool allowedNumbers[9];

    // initializes all allowedNumbers with false
    void initStates();
    // checks if number is in range <1, 9>
    bool isNumberValid(int number) const;
public:
    /**
     * @brief Initializes an empty cell. No numbers allowed by default
     */
    Cell();
    /**
     * @brief Initializes a cell object with given number inside. Only this number allowed by default. Throws invalid_argument
     * @param number Number inside the sudoku cell
     */
    explicit Cell(int number);

    /**
     * @brief returns the number inside.
     * @return the number inside; -1 if empty
     */
    int getNumber() const;
    /**
     * @return true if a cell is empty
     */
    bool isEmpty() const;
    /**
     * @brief Checks if the given number can be put inside the cell. Throws invalid_argument
     * @param number
     * @return true if the given number can be put inside the cell
     */
    bool isNumberAllowed(int number) const;

    /**
     * @brief Puts the given number inside the cell
     * @param number
     */
    void setNumber(int number);
    void unset();
    /**
     * @brief Adds the given number to allowed numbers
     * @param number
     */
    void setNumberAllowed(int number);
    /**
     * @brief Removes the given number form allowed numbers
     * @param number
     */
    void setNumberNotAllowed(int number);

    virtual ~Cell();
};


#endif //CINEMA_CELL_H

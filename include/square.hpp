#ifndef DEF_SQUARE
#define DEF_SQUARE
#include <iostream>

/**
 * @defgroup Square Square
 * @{
*/

/**
 * @brief Store a case of the board
 */
class Square{
private:

    int line;
    int row;

public:
    /**
    * @brief Constructor, translate a string to coordinates (e.g. a1 = (0,0))
    * @param cmd string in format (letter-figure) 
    */
    Square(std::string cmd);
    /**
    * @brief Constructor
    */
    Square(int line, int row)
    : line(line), row(row)
    {}
    /**
    * @brief return the line
    */
    int get_line();
    /**
    * @brief return the row
    */
    int get_row();
};

/**
* @brief test the equality between two squares
*/
bool operator==(Square a, Square b);

/**@}*/

#endif
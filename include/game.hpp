#ifndef DEF_GAME
#define DEF_GAME

#include "../include/board.hpp"
#include "../include/piece.hpp"
#include <iostream>

#define WIN 1
#define EQUALITY 2


/**
 * @defgroup Game Game
 * @{
*/

/**
 * @brief The game itself
 */
class Game{
private:
   /**
    * @brief Board of the game
    */  
    Board board;
    /**
    * @brief Store the color of the player 
    */
    Color turn;

public:
    /**
    * @brief Constructor, initialise starter player at white
    */
    Game()
    : board(), turn(white)
    {}
    /**
    * @brief play rounds
    * @param cmd string with the origin and destination of the move
    */
    void move(std::string cmd);
    /**
    * @brief Display the board then the canonical position and finally the result
    * @param result Result of the game (1-0,0-1,1/2-1/2), default value at ""
    */
    void print(std::string result="");

private:
    /**
    * @brief check if the input is correct (e.g. [a-h][1-8][a-h][1-8])
    */
    bool check_input(std::string const &);
    /**
    * @brief check if the input is correct (e.g. O-O)
    */
    bool check_input_smallcastling(std::string const &);
    /**
    * @brief check if the input is correct (e.g. O-O-O)
    */
    bool check_input_bigcastling(std::string const &);
    /**
    * @brief swap the color of actual player
    */
    void swapturn();
};

/**@}*/

#endif
#ifndef DEF_BOARD
#define DEF_BOARD

#include <iostream>
#include <vector>
#include "../include/square.hpp"
#include "../include/piece.hpp"

class Piece;
enum Color : unsigned int;

/**
 * @defgroup Board Board
 * @{
*/
/**
 * @brief Represent the board of the game
 */
class Board{

private:
    /**
    * @brief Number of rows in the board = 8
     */
    size_t nbrow;
    /**
    * @brief The board itself
     */
    Piece ***board;
    /**
    * @brief White pieces
     */
    std::vector<Piece*> wpieces;
    /**
    * @brief Black pieces
     */
    std::vector<Piece*> bpieces;
    /**
    * @brief Result of the game (0;WIN;EQUALITY)
     */
    int iswin;
    /**
    * @brief Number of rounds played
     */
    int nbmove;
    int nn;

public:
    /**
    * @brief Constructor
     */
    Board();
    /**
    * @brief Copy constructor
     */
    Board(Board&);
    int get_iswin();
    int get_nbmove();
    /**
    * @brief Display the board
     */
    void print() const;
    /**
    * @brief Return the canonical position
     */
    std::string canonical_position() const;
    /**
    * @brief Return true if there is no piece at s, false otherwise 
     */
    bool iscaseempty(Square s);
    /**
    * @brief Return a pointer on the piece at s
     */
    Piece* getpiece(Square s);
    /**
    * @brief Try to move the piece 
     */
    bool move(Square, Square, Color);
    /**
    * @brief Realise a small castling, if possible
    * @param color Color of the player who wants to realise small castling
     */
    bool smallcatsling(Color color);
    /**
    * @brief Realise a big castling, if possible
    * @param color Color of the player who wants to realise big castling
     */
    bool bigcatsling(Color color);
    ~Board();

private:
    /**
    * @brief Return the pgn name of piece
     */
    std::string pgn_piece_name(std::string const, bool, bool) const;
    /**
    * @brief Swap the color given in argument 
     */
    Color swapcolor(Color);
    /**
    * @brief   Give the index of elem in arr
    * @return -1 if elem isn't in arr, index of elem in arr otherwise
     */
    int getindex(std::vector<Square> arr, Square elem);
    /**
    * @brief   Give the index of piece with good name in in arr
    * @return -1 if the piece with name isn't in arr, index of piece with the good name in arr otherwise
     */
    int getindex(std::vector<Piece*> arr, std::string name);
    /**
    * @brief Move the piece on board and update position for concerned piece
     */
    void movepiece(Square orig, Square dest);
    /**
    * @brief Remove the piece on board
     */
    void removepiece(Square);
    /**
    * @brief Update wpieces and bpieces
     */
    void updatepiecearr();
    /**
    * @brief Check if the move leads to take, then remove piece on board
     */
    void handletake(Square,Square,Color);
    /**
    * @brief Promote piece on dest
    * @param c If equal ' ', then the ask the user, else force the promoting 
    * @param dest Case of the piece to promote
    * @return Choice of promoting
     */
    char promote(Square dest, char c);
    /**
    * @brief Check is move leads to promoting 
     */
    char handlepromote(Square, char = ' ');
    /**
    * @brief Check if the pieces of color color, can reach dest legally
    * @param dest Optionnal, if given verify if pieces can reach it, verify if they can reach the king
    * @param color Color of pieces
    * @return All the position of pieces who can reach dest
     */
    std::vector<Square> check(Color color,Square dest = Square(8,8));
    /**
    * @brief  Return true if the king of color c can move legally, false otherwise
     */
    bool cankingmove(Color c);
    /**
    * @brief Return true if one of the pieces of color c can move legally, false otherwise
     */
    bool stalemate(Color c);

};
/**@}*/
#endif
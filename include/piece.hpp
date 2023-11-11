#ifndef DEF_PIECE
#define DEF_PIECE
#include "../include/square.hpp"
#include "../include/board.hpp"
#include <vector>


#define WPAWN "\u2659"
#define WROOK "\u2656"
#define WBISHOP "\u2657"
#define WKNIGHT "\u2658"
#define WQUEEN "\u2655"
#define WKING "\u2654"

#define BPAWN "\u265F"
#define BROOK "\u265C"
#define BBISHOP "\u265D"
#define BKNIGHT "\u265E"
#define BQUEEN "\u265B"
#define BKING "\u265A"
/**
 * @enum Color Represents the color of players
 */
enum Color : unsigned int{white, black};

class Board;

/**
 * @defgroup Piece Piece
 * @{
*/
/**
 * @brief Abstract class, represent a piece
 */
class Piece{
protected:
    /**
    * @brief Name of the piece, among #define
    */
    std::string name;
    /**
    * @brief Position of piece on the board
    */
    Square position;
    /**
    * @brief Color of the piece
    */
    Color color;
    /**
    * @brief Number of times the piece has moved
    */
    int nbmove;

public:
    /**
    * @brief Constructor
    */
    Piece(std::string name, Square position, Color color, int nbmove = 0)
    : name(name), position(position), color(color), nbmove(nbmove)
    {}
    /**
    * @brief Copy constructor
    */
    Piece(Piece& p)
    : name(p.name), position(p.position), color(p.color), nbmove(p.nbmove)
    {}
    std::string get_name();
    Color get_color();
    Square get_position();
    int get_nbmove();
    /**
    * @brief Change the position in piece to dest
    * @param dest new value of position in piece
    * @param lmove new value of nbmove in piece
    */
    void move(Square dest, int lmove);
    /**
    * @brief return a vector of all the legal position of piece
    * @param board board on which piece is 
    */
    virtual std::vector<Square> getlegalcase(Board& board)=0;
    /**
    * @brief return a vector with all position between the actual position, including position but not dest (position must be valid)
    * @param dest destination
    */
    virtual std::vector<Square> getintermediatecase(Square dest);
    virtual ~Piece(){}
};
/**@}*/
/**
 * @defgroup Pawn Pawn
 * @{
*/
/**
 * @brief Represent a Pawn
 */
class Pawn : public Piece{
    
private:
    /**
    * @brief store the position of the piece taken in passing, illegal position if there is no piece tken in passing
    */
    Square passingpiece;
public:
    /**
    * @brief Constructor
    */
    Pawn(std::string name, Square position, Color color)
    :Piece(name, position, color), passingpiece(8,8)
    {}
    /**
    * @brief Copy constructor
    */
    Pawn(Pawn& p)
    : Piece(p), passingpiece(p.passingpiece)
    {}
    Square get_passingpiece();
    std::vector<Square> getlegalcase(Board& board);
    
};
/**@}*/
/**
 * @defgroup Rook Rook
 * @{
*/
/**
 * @brief Represent a Rook
 */
class Rook : public Piece{
public:
    /**
    * @brief Constructor
    */
    Rook(std::string name, Square position, Color color)
    :Piece(name, position, color)
    {}
    /**
    * @brief Copy constructor
    */
    Rook(Rook& p)
    : Piece(p)
    {}
    std::vector<Square> getlegalcase(Board& board);
    std::vector<Square> getintermediatecase(Square dest);
};
/**@}*/
/**
 * @defgroup Knight Knight
 * @{
*/
/**
 * @brief Represent a Knight
 */
class Knight : public Piece{
public:
    /**
    * @brief Constructor
    */
    Knight(std::string name, Square position, Color color)
    :Piece(name, position, color)
    {}
    /**
    * @brief Copy constructor
    */
    Knight(Knight& p)
    : Piece(p)
    {}
    std::vector<Square> getlegalcase(Board& board);
};
/**@}*/
/**
 * @defgroup Bishop Bishop
 * @{
*/
/**
 * @brief Represent a Bishop
 */
class Bishop : public Piece{
public:
    /**
    * @brief Constructor
    */
    Bishop(std::string name, Square position, Color color)
    :Piece(name, position, color)
    {}
    /**
    * @brief Copy constructor
    */
    Bishop(Bishop& p)
    : Piece(p)
    {}
    std::vector<Square> getlegalcase(Board& board);
    std::vector<Square> getintermediatecase(Square dest);
};
/**@}*/
/**
 * @defgroup Queen Queen
 * @{
*/
/**
 * @brief Represent a Queen
 */
class Queen : public Piece{
public:
    /**
    * @brief Constructor
    */
    Queen(std::string name, Square position, Color color)
    :Piece(name, position, color)
    {}
    /**
    * @brief Copy constructor
    */
    Queen(Queen& p)
    : Piece(p)
    {}
    std::vector<Square> getlegalcase(Board& board);
    std::vector<Square> getintermediatecase(Square dest);
};
/**@}*/
/**
 * @defgroup King King
 * @{
*/
/**
 * @brief Represent a King
 */
class King : public Piece{
public:
    /**
    * @brief Constructor
    */
    King(std::string name, Square position, Color color)
    :Piece(name, position, color)
    {}
    /**
    * @brief Copy constructor
    */
    King(King& p)
    : Piece(p)
    {}
    std::vector<Square> getlegalcase(Board& board);
};
/**@}*/
#endif
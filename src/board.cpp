#include "../include/board.hpp"
#include "../include/square.hpp"
#include "../include/game.hpp"
#include <iostream>
using namespace std;


Board::Board()
:nbrow(8), iswin(0), nbmove(0)
{
    // allocate board
    board = new Piece**[nbrow];
    for(size_t i(0);i<nbrow;i++)
    {
        board[i] = new Piece*[nbrow];
        for(size_t j(0);j<nbrow;j++)
        {
            board[i][j] = nullptr;
        }
    }

    board[0][0] = new Rook  (WROOK,  Square(0,0),white);
    board[0][1] = new Knight(WKNIGHT,Square(0,1),white);
    board[0][2] = new Bishop(WBISHOP,Square(0,2),white);
    board[0][3] = new Queen (WQUEEN, Square(0,3),white);
    board[0][4] = new King  (WKING,  Square(0,4),white);
    board[0][5] = new Bishop(WBISHOP,Square(0,5),white);
    board[0][6] = new Knight(WKNIGHT,Square(0,6),white);
    board[0][7] = new Rook  (WROOK,  Square(0,7),white);

    board[7][0] = new Rook  (BROOK,  Square(7,0),black);
    board[7][1] = new Knight(BKNIGHT,Square(7,1),black);
    board[7][2]= new Bishop (BBISHOP,Square(7,2),black);
    board[7][3] = new Queen (BQUEEN, Square(7,3),black);
    board[7][4] = new King  (BKING,  Square(7,4),black);
    board[7][5] = new Bishop(BBISHOP,Square(7,5),black);
    board[7][6] = new Knight(BKNIGHT,Square(7,6),black);
    board[7][7] = new Rook  (BROOK,  Square(7,7),black);

    for(size_t i(0);i<nbrow;i++)
    {
        board[1][i] = new Pawn(WPAWN, Square(1,i),white);
        board[6][i] = new Pawn(BPAWN, Square(6,i),black);
    }
    updatepiecearr();

}

Board::Board(Board &echec)
:nbrow(echec.nbrow),iswin(echec.iswin),nbmove(echec.nbmove)
{
    board = new Piece**[nbrow];
    for(size_t i(0);i<nbrow;i++)
    {
        board[i] = new Piece*[nbrow];
        for(size_t j(0);j<nbrow;j++)
        {
            board[i][j] = nullptr;
        }
    }

    for(size_t i(0);i<nbrow;i++)
    {
        for(size_t j(0);j<nbrow;j++)
        {
            if(echec.board[i][j] == nullptr)
            {
                board[i][j] = nullptr;
                continue;;
            }
            // copy piece
            if(echec.board[i][j]->get_color() == white)
            {
                if(echec.board[i][j]->get_name() == WPAWN)
                    board[i][j] = new Pawn(*((Pawn*)echec.board[i][j]));
                else if(echec.board[i][j]->get_name() == WROOK)
                    board[i][j] = new Rook(*((Rook*)echec.board[i][j]));
                else if(echec.board[i][j]->get_name() == WKNIGHT)
                    board[i][j] = new Knight(*((Knight*)echec.board[i][j]));
                else if(echec.board[i][j]->get_name() == WBISHOP)
                    board[i][j] = new Bishop(*((Bishop*)echec.board[i][j]));
                else if(echec.board[i][j]->get_name() == WQUEEN)
                    board[i][j] = new Queen(*((Queen*)echec.board[i][j]));
                else if(echec.board[i][j]->get_name() == WKING)
                    board[i][j] = new King(*((King*)echec.board[i][j]));
                wpieces.push_back(board[i][j]);
            }
            else
            {
                if(echec.board[i][j]->get_name() == BPAWN)
                    board[i][j] = new Pawn(*((Pawn*)echec.board[i][j]));
                else if(echec.board[i][j]->get_name() == BROOK)
                    board[i][j] = new Rook(*((Rook*)echec.board[i][j]));
                else if(echec.board[i][j]->get_name() == BKNIGHT)
                    board[i][j] = new Knight(*((Knight*)echec.board[i][j]));
                else if(echec.board[i][j]->get_name() == BBISHOP)
                    board[i][j] = new Bishop(*((Bishop*)echec.board[i][j]));
                else if(echec.board[i][j]->get_name() == BQUEEN)
                    board[i][j] = new Queen(*((Queen*)echec.board[i][j]));
                else if(echec.board[i][j]->get_name() == BKING)
                    board[i][j] = new King(*((King*)echec.board[i][j]));
                bpieces.push_back(board[i][j]);
            }

        }
    }
}

int Board::get_iswin()
{
    return iswin;
}

int Board::get_nbmove()
{
    return nbmove;
}

void Board::print() const
{
    string space5 = string(5,' ');
    cout << endl;
    cout << "     a     b     c     d     e     f     g     h    "<< endl;
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    for (int i((int)nbrow-1);i >= 0;i--) 
    {
        cout << i+1 << " "; // numérotation ligne dans affichage
        for (size_t j(0);j<nbrow;j++)
        {
            cout << "|" ;
            if (board[i][j] != nullptr) { 
                cout << "\u0020\u0020";  //U+0020 est un esapce utf-8 taille police
                cout << board[i][j]->get_name();
                cout << "\u0020\u0020";
            }
            else
                cout << space5;  // 2 ascii spaces
        }
        cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
        cout << endl;
    }
}

string Board::canonical_position() const
{
    string output;
    for (size_t row(0); row<8; row++)
    {
        for (size_t col(0);col<8;col++)
        { 
            if(board[row][col] != nullptr)
            {      
                output += pgn_piece_name(board[row][col]->get_name(),true,true);
            }
            output += ",";
        }
    }
    return output;
}

bool Board::iscaseempty(Square s)
{
    if(board[s.get_line()][s.get_row()] == nullptr)
        return true;
    return false;
}

Piece* Board::getpiece(Square s)
{
    return board[s.get_line()][s.get_row()]; 
}

bool Board::move(Square orig, Square dest, Color turn)
{       
    // if the square at orig is empty
    if(iscaseempty(orig))
    {
        cout << "No piece to move" << endl;
        return false;
    }
    // wrong color
    if(getpiece(orig)->get_color() != turn)
    {
        cout << "Wrong color" << endl;
        return false;
    }
    // if destination square is the same color
    if(!iscaseempty(dest))
    {
        if(getpiece(dest)->get_color() == turn)
        {
            cout << "Illegal move" << endl;
            return false;
        }
    }
    
    
    vector<Square> lcase = getpiece(orig)->getlegalcase(*this);

    // if mouvement is illegal
    if(getindex(lcase,dest) == -1)
    {
        return false;
    }


    // we realise all the operations on a virtual board to cancel easily
    Board ecpy(*this);
    
    ecpy.handletake(orig,dest,turn);
    ecpy.movepiece(orig,dest);
    char pro = ecpy.handlepromote(dest, ' ');

    // if an ally mouvement leads to lose, we cancel it
    if(ecpy.check(swapcolor(turn)).size()>0)
    {
        cout << "Mouvement leads to check" << endl;
        return false;
    }


    //if there is a check
    if(ecpy.check(turn).size()>0)
    {
        // we verify checkmate
        if(!ecpy.cankingmove(swapcolor(turn)))
        {
            iswin = WIN;
        }
        else
            cout << "Echec" << endl;
    }

    // once we are here we upadte the real board
    handletake(orig,dest,turn);
    movepiece(orig,dest);
    handlepromote(dest,pro);
    
    nbmove++;

    if(stalemate(swapcolor(turn)))
    {
        if(iswin != WIN)
            iswin = EQUALITY;
    }
    
    return true;
}

bool Board::smallcatsling(Color color)
{
    int offset(0);
    if(color == black)
        offset = 7;

    Square orig(Square(offset,4));
    Square dest(Square(offset,6));
    if(iscaseempty(orig))
        return false;

    vector<Square> lcase = getpiece(orig)->getlegalcase(*this);

    // if mouvement is illegal
    if(getindex(lcase,dest) == -1)
        return false;
    
    Board ecpy(*this);
    ecpy.movepiece(orig,dest);
    ecpy.movepiece(Square(offset,7),Square(offset,5));

    if(ecpy.check(swapcolor(color)).size()>0)
    {
        cout << "Mouvement lead to check" << endl;  
        return false;
    }
    movepiece(orig,dest);
    movepiece(Square(offset,7),Square(offset,5));
    return true;
}

bool Board::bigcatsling(Color color)
{
    int offset(0);
    if(color == black)
        offset = 7;

    Square orig(Square(offset,4));
    Square dest(Square(offset,2));
    if(iscaseempty(orig))
        return false;

    vector<Square> lcase = getpiece(orig)->getlegalcase(*this);

    // if mouvement is illegal
    if(getindex(lcase,dest) == -1)
        return false;
    
    Board ecpy(*this);
    ecpy.movepiece(orig,dest);
    ecpy.movepiece(Square(offset,0),Square(offset,3));

    if(ecpy.check(swapcolor(color)).size()>0)
    {
        cout << "Mouvement lead to check" << endl;  
        return false;
    }
    movepiece(orig,dest);
    movepiece(Square(offset,0),Square(offset,3));
    return true;
}

Board::~Board()
{
    for(size_t i(0);i<nbrow;i++)
    {
        for(size_t j(0);j<nbrow;j++)
        {
            if(!iscaseempty(Square(i,j)))
                delete(getpiece(Square(i,j)));
        }
        delete[] board[i];
    }
    
    delete[] board;
}

string Board::pgn_piece_name(string const name, bool view_pawn, bool view_color) const
{

    string psymb;
    if     (name==WROOK)   psymb="R";  // Rook W
    else if(name==WKNIGHT) psymb="N";  // Knight W
    else if(name==WBISHOP) psymb="B";  // Bishop W
    else if(name==WQUEEN)  psymb="Q";  // Queen W
    else if(name==WKING)   psymb="K";  // King W
    else if(name.rfind(WPAWN,0)==0 && view_pawn) psymb= "P"; // Pawn W
    if (psymb.size()>0) { // one of the white piece has been found
        if(view_color)
            return "w"+psymb;
        else
            return psymb;
    } 
    if     (name==BROOK) psymb= "R";  // Rook B
    else if(name==BKNIGHT) psymb= "N";  // Knight B
    else if(name==BBISHOP) psymb= "B";  // Bishop B
    else if(name==BQUEEN) psymb= "Q";  // Queen B
    else if(name==BKING) psymb= "K";  // King B
    else if(name.rfind(BPAWN,0)==0 && view_pawn) psymb= "P"; // Pawn B
    if(psymb.size()>0) 
    { // one of the black piece has been found
        if (view_color)
            return "b"+psymb;
        else
            return psymb;
    } 
    else return "";
}

Color Board::swapcolor(Color c)
{
    if(c == white)
        return black;
    return white;
}

int Board::getindex(vector<Square> arr, Square elem)
{
    for(size_t i(0);i<arr.size();i++)
    {
        if(arr[i] == elem)
            return i;
    }
    return -1;
}

int Board::getindex(vector<Piece*> arr, string name)
{
    for(size_t i(0);i<arr.size();i++)
    {
        if(arr[i]->get_name() == name)
            return i;
    }
    return -1;
}

void Board::movepiece(Square orig, Square dest)
{
    Piece *piece = getpiece(orig);
    //update position in Piece
    piece->move(dest,nbmove);
    //update position on Board
    board[dest.get_line()][dest.get_row()] = piece;
    board[orig.get_line()][orig.get_row()] = nullptr;
}

void Board::removepiece(Square dest)
{
    delete(getpiece(dest));
    board[dest.get_line()][dest.get_row()] = nullptr;
}

void Board::updatepiecearr()
{
    wpieces.clear();
    bpieces.clear();
    for(size_t i(0);i<nbrow;i++)
    {
        for(size_t j(0);j<nbrow;j++)
        {
            if(!iscaseempty(Square(i,j)))
            {
                if(getpiece(Square(i,j))->get_color() == white)
                    wpieces.push_back(board[i][j]);
                else
                    bpieces.push_back(board[i][j]);
            }
        }
    }
}

void Board::handletake(Square orig, Square dest, Color turn)
{
    int offset(-1);
    if(turn == black)
        offset = 1;

    // classic take
    if(!iscaseempty(dest))
    {
        if(getpiece(dest)->get_color() != turn)
        {
            removepiece(dest);
            updatepiecearr();
        }
    }
    // passing take
    else if(getpiece(orig)->get_name() == WPAWN || getpiece(orig)->get_name() == BPAWN)
    {
        if(((Pawn*)getpiece(orig))->get_passingpiece() == Square(dest.get_line()+offset,dest.get_row()))
        {
            removepiece(Square(dest.get_line()+offset,dest.get_row()));
            updatepiecearr();
        }
    } 
}

char Board::promote(Square orig, char c)
{
    Color pcolor;
    string name[4], pro;
    pro[0] = c;
    
    if(getpiece(orig)->get_color() == white)
    {
        pcolor = white;
        name[0] = WQUEEN;name[1] = WROOK;name[2] = WBISHOP;name[3] = WKNIGHT;
    }
    else
    {
        pcolor = black;
        name[0] = BQUEEN;name[1] = BROOK;name[2] = BBISHOP;name[3] = BKNIGHT;
    }
    delete(getpiece(orig));
    
    // ask user
    if(pro[0] == ' ')
    {
        while(pro != "Q" && pro != "R" && pro != "B" && pro != "N")
        {
            cout << "Promote in {Q : Queen, R : Rook, B : Bishop, K: Knight} ? : ";
            cin >> pro;
        }
    }

    switch(pro[0])
    {
        case 'Q':
            board[orig.get_line()][orig.get_row()] = new Queen(name[0],orig,pcolor);
        break;
        case 'R':
            board[orig.get_line()][orig.get_row()] = new Rook(name[1],orig,pcolor);
        break;
        case 'B':
            board[orig.get_line()][orig.get_row()] = new Bishop(name[2],orig,pcolor);
        break;
        case 'N':
            board[orig.get_line()][orig.get_row()] = new Knight(name[3],orig,pcolor);
        break;
    }
    updatepiecearr();
    return pro[0];
}

char Board::handlepromote(Square dest, char c)
{
    //handle promotion
    if(getpiece(dest)->get_name() == BPAWN || getpiece(dest)->get_name() == WPAWN)
        if(getpiece(dest)->get_position().get_line() == 0 || getpiece(dest)->get_position().get_line() == 7)
            return promote(dest, c);
    return ' ';
}

vector<Square> Board::check(Color color, Square dest)
{
    vector<Square> ccase;
    vector<Piece*> karr = bpieces;
    vector<Piece*> parr = wpieces;

    if(color == black)
    {
        parr = bpieces;
        karr = wpieces;
    }
    
    if(dest == Square(8,8))
    {
        // find king in karr
        for(size_t i(0);i<karr.size();i++)
        {       
            if(karr[i]->get_name() == WKING || karr[i]->get_name() == BKING)
            {
                dest = karr[i]->get_position();
                break;
            }
        }
    }

    // for all opposite pieces
    for(size_t i(0);i<parr.size();i++)
    {
        // if they can reach dest
        if(getindex(parr[i]->getlegalcase(*this),dest) != -1)
        {
            ccase.push_back(parr[i]->get_position());
        }
    }
    
    return ccase;
}

bool Board::cankingmove(Color c)
{
    //testser si toutes les positions du roi mettent en echec et si aucune piece alliés ne peut prensre l'assaillant
    vector<Square> checksquare;
    
    vector<Piece*> karr = wpieces;
    if(c == black)
        karr = bpieces;
    
    // find index of the king
    int indexk(0);
    for(size_t i(0);i<karr.size();i++)
    {
        if(karr[i]->get_name() == WKING || karr[i]->get_name() == BKING)
        {
            indexk = i;
            break;
        }
    }
    // all the legal position of the king
    vector<Square> kpos = karr[indexk]->getlegalcase(*this);

    // position of pieces who check the king
    checksquare = check(swapcolor(c));
    
    
    if(checksquare.size() == 1)
    {
        // verify if a piece can take the attacker
        for(size_t i(0);i<karr.size();i++)
        {
            // except the king
            if(karr[i]->get_name() != WKING && karr[i]->get_name() != BKING)
            {
                vector<Square> intcase = getpiece(checksquare[0])->getintermediatecase(karr[indexk]->get_position());
                // verify if the piece can intervene between king and attcker
                for(auto scase : intcase)
                {
                    if(getindex(karr[i]->getlegalcase(*this),scase) != -1)
                        return true;
                }
            }
        }
    }
    
    // if the king can move without be cheched
    for(auto ccase : kpos)
    {
        // if the king move with a take
        if(!iscaseempty(ccase))
        {
            Piece* temp = getpiece(ccase);
            
            // delete the piece and verify if it is checked
            board[ccase.get_line()][ccase.get_row()] = nullptr;
            if(check(swapcolor(c), ccase).size() == 0)
            {
                board[ccase.get_line()][ccase.get_row()] = temp;
                return true;
            }
            board[ccase.get_line()][ccase.get_row()] = temp;
        }
        else
        {
            // verify if it is checked
            if(check(swapcolor(c), ccase).size() == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool Board::stalemate(Color c)
{
    vector<Piece*> karr = wpieces;
    if(c == black)
        karr = bpieces;
    
    // for all the pieces
    for(size_t i(0);i<karr.size();i++)
    {
        vector<Square> lcase = karr[i]->getlegalcase(*this);
        // for each case reachable by the piece
        for(auto ccase : lcase)
        {
            Piece* temp = nullptr; 
            
            if(!iscaseempty(ccase))
                temp = getpiece(ccase);
            
            Square postemp = karr[i]->get_position();
            
            // move the piece
            karr[i]->move(ccase,karr[i]->get_nbmove());
            board[ccase.get_line()][ccase.get_row()] = karr[i];
            board[postemp.get_line()][postemp.get_row()] = nullptr;
            updatepiecearr();
            
            // if the piece can move, restore the initial board and quit
            if(check(swapcolor(c)).size() == 0)
            {
                board[ccase.get_line()][ccase.get_row()] = temp;
                board[postemp.get_line()][postemp.get_row()] = karr[i];
                karr[i]->move(postemp,karr[i]->get_nbmove());
                updatepiecearr();
                return false;
            }
            // restore the board
            board[ccase.get_line()][ccase.get_row()] = temp;
            board[postemp.get_line()][postemp.get_row()] = karr[i];
            karr[i]->move(postemp,karr[i]->get_nbmove());
            updatepiecearr();
        }
    }
    // if any piece can move -> stalemate
    return true;
}

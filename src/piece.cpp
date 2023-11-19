#include "../include/piece.hpp"
#include <iostream>

using namespace std;

string Piece::get_name()
{
    return name;
}

Color Piece::get_color()
{
    return color;
}

Square Piece::get_position()
{
    return position;
}

int Piece::get_nbmove()
{
    return nbmove;
}

void Piece::move(Square dest, int lmove)
{
    position = dest;
    nbmove=lmove;
}

vector<Square> Piece::getintermediatecase(Square dest)
{
    (void)dest;
    vector<Square> lcase;
    lcase.push_back(position);
    return lcase;
}

Square Pawn::get_passingpiece()
{
    return passingpiece;
}

vector<Square> Pawn::getlegalcase(Board& board)
{
    vector<Square> lcase;
    passingpiece = Square(8,8);
    
    int factor = 1;
    if(color == black)
        factor=-1;

    // +2
    if(nbmove == 0)
    {
        if(board.iscaseempty(Square(position.get_line()+2*factor,position.get_row())) && board.iscaseempty(Square(position.get_line()+factor,position.get_row())))
            lcase.push_back(Square(position.get_line()+2*factor,position.get_row()));
    }
    // +1
    if(board.iscaseempty(Square(position.get_line()+factor,position.get_row())))
        lcase.push_back(Square(position.get_line()+factor,position.get_row()));

    // right diagonal and passing take
    if(position.get_row()+1 < 8)
    {
        // diagonal right
        if(!board.iscaseempty(Square(position.get_line()+factor,position.get_row()+1)))
            if(board.getpiece(Square(position.get_line()+factor,position.get_row()+1))->get_color() != color)
                lcase.push_back(Square(position.get_line()+factor,position.get_row()+1));

        // passing take right
        // if destination square is empty and taken square isn't empty 
        if(board.iscaseempty(Square(position.get_line()+factor,position.get_row()+1)) && !board.iscaseempty(Square(position.get_line(),position.get_row()+1)))
            // if the taken piece is a pawn
            if(board.getpiece(Square(position.get_line(),position.get_row()+1))->get_name() == WPAWN || board.getpiece(Square(position.get_line(),position.get_row()+1))->get_name() == BPAWN)
                // if it has a different color and move just before
                if(board.getpiece(Square(position.get_line(),position.get_row()+1))->get_color() != color && board.getpiece(Square(position.get_line(),position.get_row()+1))->get_nbmove() + 1 == board.get_nbmove())
                {
                    lcase.push_back(Square(position.get_line()+factor,position.get_row()+1));
                    passingpiece = Square(position.get_line(),position.get_row()+1);
                }
    }
    // left diagonal and passing take
    if(position.get_row()-1 >= 0)
    {
        if(!board.iscaseempty(Square(position.get_line()+factor,position.get_row()-1)))
            if(board.getpiece(Square(position.get_line()+factor,position.get_row()-1))->get_color() != color)
                lcase.push_back(Square(position.get_line()+factor,position.get_row()-1));

        if(board.iscaseempty(Square(position.get_line()+factor,position.get_row()-1)) && !board.iscaseempty(Square(position.get_line(),position.get_row()-1)))
            if(board.getpiece(Square(position.get_line(),position.get_row()-1))->get_name() == WPAWN || board.getpiece(Square(position.get_line(),position.get_row()-1))->get_name() == BPAWN)
                if(board.getpiece(Square(position.get_line(),position.get_row()-1))->get_color() != color && board.getpiece(Square(position.get_line(),position.get_row()-1))->get_nbmove() + 1 == board.get_nbmove())
                {
                    lcase.push_back(Square(position.get_line()+factor,position.get_row()-1));
                    passingpiece = Square(position.get_line(),position.get_row()-1);
                }
    }

    return lcase;
}

vector<Square> Rook::getlegalcase(Board& board)
{
    vector<Square> lcase;
    // left horizontal
    for(int i(position.get_row()-1);i>=0;i--)
    {
        if(!board.iscaseempty(Square(position.get_line(),i)))
        {   
            // if the piece has a different color at its position and quit
            if(board.getpiece(Square(position.get_line(),i))->get_color() != color)    
                lcase.push_back(Square(position.get_line(),i));
            break;
        }
        lcase.push_back(Square(position.get_line(),i));
    }
    // right horizontal
    for(int i(position.get_row()+1);i<8;i++)
    {
        if(!board.iscaseempty(Square(position.get_line(),i)))
        {
            if(board.getpiece(Square(position.get_line(),i))->get_color() != color)    
                lcase.push_back(Square(position.get_line(),i));
            break;
        }
        lcase.push_back(Square(position.get_line(),i));
    }
    // bottom vertical
    for(int i(position.get_line()-1);i>=0;i--)
    {
        if(!board.iscaseempty(Square(i,position.get_row())))
        {
            if(board.getpiece(Square(i,position.get_row()))->get_color() != color)    
                lcase.push_back(Square(i,position.get_row()));
            break;
        }
        lcase.push_back(Square(i,position.get_row()));
    }
    // up vertical
    for(int i(position.get_line()+1);i<8;i++)
    {
        if(!board.iscaseempty(Square(i,position.get_row())))
        {
            if(board.getpiece(Square(i,position.get_row()))->get_color() != color)    
                lcase.push_back(Square(i,position.get_row()));
            break;
        }
        lcase.push_back(Square(i,position.get_row()));
    }

    return lcase;
}

vector<Square> Rook::getintermediatecase(Square dest)
{
    vector<Square> lcase;
    if(dest.get_line() == position.get_line())
    {
        for(int i(min(position.get_row(),dest.get_row())+1); i < max(position.get_row(),dest.get_row());i++)
        {
            lcase.push_back(Square(position.get_line(),i));
        }
        lcase.push_back(position);
    }
    else if(dest.get_row() == position.get_row())
    {
        for(int i(min(position.get_line(),dest.get_line())+1); i < max(position.get_line(),dest.get_line());i++)
        {
            lcase.push_back(Square(i,position.get_row()));
        }
        lcase.push_back(position);
    }

    return lcase;
}

vector<Square> Knight::getlegalcase(Board& board)
{
    vector<Square> lcase;
    int pos[][2] = {{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}};
    for(auto i : pos)
    {
        i[0]+=position.get_line();
        i[1]+=position.get_row();
        if(i[0] >= 0 && i[0] < 8 && i[1] >= 0 && i[1] < 8)
        {
            if(!board.iscaseempty(Square(i[0],i[1])))
            {
                if(board.getpiece(Square(i[0],i[1]))->get_color() != color)
                    lcase.push_back(Square(i[0],i[1]));
            }
            else
                lcase.push_back(Square(i[0],i[1]));
        }
    }
    return lcase;
}

vector<Square> Bishop::getlegalcase(Board& board)
{
    vector<Square> lcase;
    // up right
    for(int i(1); i<8;i++)
    {
        // if the position is outside the board then quit
        if(position.get_line()+i >= 8 || position.get_row()+i >= 8)
            break;

        // if there is a piece
        if(!board.iscaseempty(Square(position.get_line()+i,position.get_row()+i)))
        {   
            // if the piece has the opposite color and the position and quit
            if(board.getpiece(Square(position.get_line()+i,position.get_row()+i))->get_color() != color)    
                lcase.push_back(Square(position.get_line()+i,position.get_row()+i));
            break;
        }
        lcase.push_back(Square(position.get_line()+i,position.get_row()+i));
    }
    // up left
    for(int i(1); i<8;i++)
    {
        if(position.get_line()+i >= 8 || position.get_row()-i < 0)
            break;

        if(!board.iscaseempty(Square(position.get_line()+i,position.get_row()-i)))
        {   
            if(board.getpiece(Square(position.get_line()+i,position.get_row()-i))->get_color() != color)    
                lcase.push_back(Square(position.get_line()+i,position.get_row()-i));
            break;
        }
        lcase.push_back(Square(position.get_line()+i,position.get_row()-i));
    }
    // bottom left
    for(int i(1); i<8;i++)
    {
        if(position.get_line()-i < 0 || position.get_row()-i < 0)
            break;

        if(!board.iscaseempty(Square(position.get_line()-i,position.get_row()-i)))
        {   
            if(board.getpiece(Square(position.get_line()-i,position.get_row()-i))->get_color() != color)    
                lcase.push_back(Square(position.get_line()-i,position.get_row()-i));
            break;
        }
        lcase.push_back(Square(position.get_line()-i,position.get_row()-i));
    }
    // bottom right
    for(int i(1); i<8;i++)
    {
        if(position.get_line()-i < 0 || position.get_row()+i >= 8)
            break;

        if(!board.iscaseempty(Square(position.get_line()-i,position.get_row()+i)))
        {   
            if(board.getpiece(Square(position.get_line()-i,position.get_row()+i))->get_color() != color)    
                lcase.push_back(Square(position.get_line()-i,position.get_row()+i));
            break;
        }
        lcase.push_back(Square(position.get_line()-i,position.get_row()+i));
    }
    return lcase;
}

vector<Square> Bishop::getintermediatecase(Square dest)
{
    vector<Square> lcase;

    // bottom left
    if(dest.get_line() < position.get_line() && dest.get_row() < position.get_row())
    {
        for(int i(dest.get_line()+1); i < position.get_line();i++)
        {
            lcase.push_back(Square(i,i-dest.get_line()+dest.get_row()));
        }
        lcase.push_back(position);
    }
    // bottom right
    else if(dest.get_line() < position.get_line() && dest.get_row() > position.get_row())
    {
        for(int i(dest.get_line()+1); i < position.get_line();i++)
        {
            lcase.push_back(Square(i,dest.get_row() - i + dest.get_line()));
        }
        lcase.push_back(position);
    }
    // up left
    else if(dest.get_line() > position.get_line() && dest.get_row() < position.get_row())
    {
        for(int i(dest.get_line()-1); i > position.get_line();i--)
        {
            lcase.push_back(Square(i,dest.get_line() - i + dest.get_row()));
        }
        lcase.push_back(position);
    }
    // up right
    else if(dest.get_line() > position.get_line() && dest.get_row() > position.get_row())
    {
        for(int i(dest.get_line()-1); i > position.get_line();i--)
        {
            lcase.push_back(Square(i,dest.get_row() + i - dest.get_line()));
        }
        lcase.push_back(position);
    }
    return lcase;
}

vector<Square> Queen::getlegalcase(Board& board)
{
    // union of Rook and Bishop square
    Rook rt(BROOK,position,color);
    Bishop bt(BBISHOP,position,color);

    vector<Square> lcase(rt.getlegalcase(board));
    vector<Square> temp = bt.getlegalcase(board);

    lcase.insert(lcase.end(),temp.begin(),temp.end());
    return lcase;
}

vector<Square> Queen::getintermediatecase(Square dest)
{
    // union of Rook and Bishop square
    Rook rt(BROOK,position,color);
    Bishop bt(BBISHOP,position,color);

    vector<Square> lcase(rt.getintermediatecase(dest));
    vector<Square> temp = bt.getintermediatecase(dest);

    lcase.insert(lcase.end(),temp.begin(),temp.end());
    return lcase;
}

vector<Square> King::getlegalcase(Board& board)
{
    vector<Square> lcase;
    int pos[][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    for(auto i : pos)
    {
        i[0]+=position.get_line();
        i[1]+=position.get_row();
        if(i[0] >= 0 && i[0] < 8 && i[1] >= 0 && i[1] < 8)
        {
            if(!board.iscaseempty(Square(i[0],i[1])))
            {
                if(board.getpiece(Square(i[0],i[1]))->get_color() != color)
                    lcase.push_back(Square(i[0],i[1]));
            }
            else
                lcase.push_back(Square(i[0],i[1]));
        }
    }

    int offset(0);
    if(color == black)
        offset = 7;
    
    // small castling 
    if(!board.iscaseempty(Square(offset,4)) && !board.iscaseempty(Square(offset,7)))
    {
        if(((King*)board.getpiece(Square(offset,4)))->get_nbmove() == 0 && ((Rook*)board.getpiece(Square(offset,7)))->get_nbmove() == 0)
        {
            // if there is no piece between king and rook
            if(board.iscaseempty(Square(offset,5)) && board.iscaseempty(Square(offset,6)))
                lcase.push_back(Square(offset,6));
        }
    }
    // big castling
    if(!board.iscaseempty(Square(offset,4)) && !board.iscaseempty(Square(offset,0)))
    {
        if(((King*)board.getpiece(Square(offset,4)))->get_nbmove() == 0 && ((Rook*)board.getpiece(Square(offset,0)))->get_nbmove() == 0)
        {
            if(board.iscaseempty(Square(offset,1)) && board.iscaseempty(Square(offset,2)) && board.iscaseempty(Square(offset,3)))
                lcase.push_back(Square(offset,2));
        }
    }               
    return lcase;
}

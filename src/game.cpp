#include "../include/game.hpp"
#include <iostream>
#include <regex>

using namespace std;

void Game::move(std::string cmd)
{
    // resign
    if(cmd == "/resign")
    {
        if(turn == white)
            print("0-1");
        else
            print("1-0");
        exit(0);
    }
    
    // draw
    if(cmd == "/draw")
    {
        print("1/2-1/2");
        exit(0);
    }

    if(check_input(cmd))
    {
        Square orig(cmd.substr(0, 2));
        Square dest(cmd.substr(2, 2));

        if(!board.move(orig,dest,turn))
        {    
            return;
        }
    }
    // small castling
    else if(check_input_smallcastling(cmd)) 
    {
        if(!board.smallcatsling(turn))
        {
            cout << "Small castling impossible" << endl;  
            return;
        }
    }
    // big castling
    else if(check_input_bigcastling(cmd))
    {
        if(!board.bigcatsling(turn))
        {
            cout << "Big castling impossible" << endl;  
            return;
        }
    }
    else
    {
        cout << "Invalid command" << endl;
        return;
    }
    
    if(board.get_iswin() == WIN)
    {
        if(turn == white)
            print("1-0");
        else
            print("0-1");
        exit(0);
    }
    else if(board.get_iswin() == EQUALITY)
    {
        print("1/2-1/2");
        exit(0);
    }


    swapturn();
    print();
}

void Game::print(string result)
{
    board.print();
    cout << board.canonical_position() << " " << result << endl;
}

bool Game::check_input(string const &cmd)
{
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd,mouvmtpattern);
}

bool Game::check_input_smallcastling(string const & cmd)
{
    regex mouvmtpattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd,mouvmtpattern);
}

bool Game::check_input_bigcastling(string const & cmd)
{
    regex mouvmtpattern("(O|o|0)-(O|o|0)-(O|o|0)");
    return regex_match(cmd,mouvmtpattern);
}

void Game::swapturn()
{
    if(turn == white)
        turn = black;
    else
        turn = white;
}
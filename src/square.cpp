#include "../include/square.hpp"
#include <iostream>
#include <string>

using namespace std;


Square::Square(string cmd)
{
    row =  cmd[0] - 'a';     // a
    line = cmd[1] - '1';     // 1
}

int Square::get_line()
{
    return line;
}

int Square::get_row()
{
    return row;
}

bool operator==(Square a, Square b)
{
    if(a.get_line() == b.get_line() && a.get_row() == b.get_row())
        return true;
    return false;
}



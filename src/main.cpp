#include "../include/game.hpp"
#include <iostream>
#include <csignal>
using namespace std;

void sigint_handler(int arg)
{
    (void)arg;
    cout << endl << "Game interrupted" << endl;
    exit(0);
}


int main()
{
    
    signal(SIGINT,sigint_handler);

    Game game;
    string mouvement;
    bool stop(false);
    game.print();
    do
    {
        cout << "Coup (eg. a1a8) ? ";
        cin >> mouvement;
        if (mouvement != "/quit")
        {           
            game.move(mouvement);
        }
        else 
            stop=true;
    }while (!stop);
    game.print("?-?");
}
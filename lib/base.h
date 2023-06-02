#ifndef BASE_H_
#define BASE_H_
#include <stdio.h>      // Basic standard input output c library
#include <stdlib.h>     // NULL constant support and malloc
#include <stdbool.h>    // Support for boolean type
#include <time.h>       // For random generation

enum Pint{ gold, sword, cup, club};

typedef struct card{
    int val;
    int pint;
    struct card* sig;
}Card;

typedef Card* Deck;

typedef struct player{
    int points;
    char* name;
    Deck hand;
    Deck pillow;
}Player;

//Auxiliar function
bool consecutive(int x, int y){
    return (((x+1)==y) || (x==y) || ((x==7)&&(y==10))) ? 1 : 0;
}

#endif
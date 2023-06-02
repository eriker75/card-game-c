#ifndef CHANTS_H_
#define CHANTS_H_

#include "base.h"

int flower(Deck deck);
int trivilin(Deck deck);
int patrol(Deck deck);
int rondValue(int card_val);
int rond(Deck deck);
int watchtower(Deck deck);
int bigHouse(Deck deck);
int littleHouse(Deck deck);
int registerChant(Deck deck);
int rondValueOfPlayer(Deck deck);

int bigHouse(Deck deck){
    orderDeck(&deck);
    int card1 = deck->val;
    int card2 = deck->sig->val;
    int card3 = deck->sig->sig->val;
    return ((card2 == 1) && (card3 == 12) && (card3 == 12)) ? 24 : 0;
}

int littleHouse(Deck deck){
    orderDeck(&deck);
    int card1 = deck->val;
    int card2 = deck->sig->val;
    int card3 = deck->sig->sig->val;
    return ((card1 == 1)&&(card2 == 1)&&(card3 == 12)) ? 12 : 0;
}

int registerChant(Deck deck){
    orderDeck(&deck);
    int card1 = deck->val;
    int card2 = deck->sig->val;
    int card3 = deck->sig->sig->val;
    return ((card1 == 1) && (card2 == 11) && (card3 == 12)) ? 8 : 0;
}

int flower(Deck deck){
    orderDeck(&deck);
    int card1 = deck->pint;
    int card2 = deck->sig->pint;
    int card3 = deck->sig->sig->pint;
    return ((card1 == card2) && (card2 == card3)) ? 5 : 0;
}

int trivilin(Deck deck){
    orderDeck(&deck);
    int card1 = deck->val;
    int card2 = deck->sig->val;
    int card3 = deck->sig->sig->val;
    return ((card1 == card2) && (card2 == card3)) ? 9 : 0;
}

int patrol(Deck deck){
    orderDeck(&deck);
    int card1 = deck->val;
    int card2 = deck->sig->val;
    int card3 = deck->sig->sig->val;
    return(consecutive(card1,card2) && consecutive(card2,card3)) ?  6 : 0;
}

int watchtower(Deck deck){
    if(bigHouse(deck)) return 0;
    if(littleHouse(deck)) return 0;
    orderDeck(&deck);
    int card1 = deck->val;
    int card2 = deck->sig->val;
    int card3 = deck->sig->sig->val;
    if((card1==card2) && consecutive(card2,card3)) return 7;
    if((card2==card3) && consecutive(card1,card2)) return 7;
    return 0;
}

int rondValue(int card_val){
    if(card_val == 12){
        return 4;
    } else if (card_val == 11) {
        return 3;
    } else if (card_val == 10) {
        return 2;
    } else if ((card_val == 7) || (card_val == 6) || (card_val == 5) ||
               (card_val == 4) || (card_val == 3) || (card_val == 2) || (card_val == 1)
    ) {
        return 1;
    } else {
        return 0;
    }
}

int rond(Deck deck){
    if(bigHouse(deck)) return 0;
    if(littleHouse(deck)) return 0;
    orderDeck(&deck);
    int card1 = deck->val;
    int card2 = deck->sig->val;
    int card3 = deck->sig->sig->val;
    if((card1==card2) && !consecutive(card2,card3)) return rondValue(card1);
    if((card2==card3) && !consecutive(card1,card2)) return rondValue(card2);
    return 0;
}

int rondValueOfPlayer(Deck deck){
    orderDeck(&deck);
    int _bigHouse = bigHouse(deck);
    int _littleHouse = littleHouse(deck);
    int _trivilin = trivilin(deck);
    int _registerChant = registerChant(deck);
    int _watchtower = watchtower(deck);
    int _patrol = patrol(deck);
    int _flower = flower(deck);
    int _rond = rond(deck);
    if(_bigHouse) return _bigHouse;          //24pts
    if(_littleHouse) return _littleHouse;    //12pts
    if(_trivilin) return _trivilin;          //9 pts
    if(_registerChant) return _registerChant;//8 pts
    if(_watchtower) return _watchtower;      //7 pts
    if(_patrol) return _patrol;              //6 pts
    if(_flower) return _flower;              //5 pts
    if(_rond) return _rond;            //1,2,3,4 pts
    return 0;
}

char* rondValueOfPlayerText(Deck deck){
    orderDeck(&deck);
    int _bigHouse = bigHouse(deck);
    int _littleHouse = littleHouse(deck);
    int _trivilin = trivilin(deck);
    int _registerChant = registerChant(deck);
    int _watchtower = watchtower(deck);
    int _patrol = patrol(deck);
    int _flower = flower(deck);
    int _rond = rond(deck);
    if(_bigHouse) return "Casa Grande, 24 puntos";  
    if(_littleHouse) return "Casa chica, 12 puntos";
    if(_trivilin) return "Trivilin, 9 puntos";      
    if(_registerChant) return "Registro, 8 puntos"; 
    if(_watchtower) return "Vigia, 7 puntos"; 
    if(_patrol) return "Patrulla, 6 punts";    
    if(_flower) return "Flor, 5 punts";
    if(_rond) return "Ronda";
    return "No obtubo ningun canto";
}

#endif
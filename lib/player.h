#ifndef PLAYER_H_
#define PLAYER_H_

#include "base.h"
#include "list.h"
#include "chants.h"

Player* initPlayers(int* num_of_players);
Player* newPlayer(Player* player, char* name);
Player* createPlayers(Player* players, int num_of_players);
void printPlayers(Player* players, int num_of_players);
bool winerExists(Player* players,int num_of_players, int points_to_win);
void deletePillows(Player* players, int num_of_players);

Player* initPlayers(int* num_of_players){
    printf("Cuantos jugadores estaran jugando la partida): ");
    scanf("%d",num_of_players);
    while( (*num_of_players < 2) || (*num_of_players > 4)){
        if( *num_of_players>4 ) {
            printf("\nEl numero de jugadores no puede ser mayor a 4\n");
            printf("ingrese un numero entre 2 y 4: ");
            scanf("%d",num_of_players);
        }
        if( *num_of_players<=1 ) {
            printf("\nEl numero de jugadores menor o igual a 1\n");
            printf("ingrese un numero entre 2 y 4: ");
            scanf("%d",num_of_players);
        }
        printf("\n");
    }
    Player* players = (Player* )malloc(sizeof(Player) * (*num_of_players));
    return players;
}

Player* createPlayers(Player* players, int num_of_players){
    for (int i = 0; i < num_of_players; i++){
        printf("Cual es el nombre del jugador numero %d: ",i+1);
        players[i].name = (char* )malloc(sizeof(char));
        scanf("%s",players[i].name);
        players[i].points = 0;
        players[i].hand = NULL;
        players[i].pillow = NULL;
    }
    printf("\n");
}

void printPlayers(Player* players, int num_of_players){
    for (int i = 0; i < num_of_players; i++)
        printf("Jugador %d de nombre %s tiene %d puntos y %d cartas en su pilon\n",
                i+1,players[i].name,players[i].points,deckLength(players[i].pillow));
    printf("\n");
}

bool winerExists(Player* players,int num_of_players, int points_to_win){
    for (int i = 0; i < num_of_players; i++)
        if(players[i].points >= points_to_win) return true;
    return false;
}

bool cardsInHandOfAnyPlayer(Player* players,int num_of_players){
    for (int i = 0; i < num_of_players; i++)
        if(players[i].hand) return true;
    return false;
}

void setPointsToTheBestChant(Player* players, int num_of_players){
    int max = 0;
    int _rondValueOfPlayer;
    for (int i = 0; i < num_of_players; i++){
        _rondValueOfPlayer = rondValueOfPlayer(players[i].hand);
        if( _rondValueOfPlayer  > max)
            max = _rondValueOfPlayer;
    }
    for (int i = 0; i < num_of_players; i++){
        _rondValueOfPlayer = rondValueOfPlayer(players[i].hand);
        if (max == rondValueOfPlayer(players[i].hand))
            players[i].points += _rondValueOfPlayer;
    }
}

void deletePillows(Player* players, int num_of_players){
    for (int i = 0; i < num_of_players; i++)
        deleteDeck(&(players[i].pillow));
}

void addPointsBasedInPillows(Player* players, int num_of_players){
    int points_to_add;
    for (int i = 0; i < num_of_players; i++){
        points_to_add = deckLength(players[i].pillow) - 40/num_of_players;
        if(points_to_add > 0){
            players[i].points += points_to_add;
        }
    }
}

void printWiner(Player* players, int num_of_players){
    int winer = 0;
    int i = 1;
    for ( i = 1; i < num_of_players; i++)
        if(players[i].points >= players[i-1].points)
            winer = i;
    printf("\n\nEl jugador numero %d de nombre %s es el ganador del juego de caida!!!\n",
            winer+1,players[winer].name);
    printf("Gracias por jugar :D\n");
}

void printChants(Player* players,int num_of_players){
    for (int i = 0; i < num_of_players; i++){
        printf("El jugador %d de nombre %s obtubo como mano %s\n",
        i+1,players[i].name,rondValueOfPlayerText(players[i].hand));
    }
    printf("\n");
}

#endif

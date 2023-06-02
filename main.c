#include "lib/base.h"   // Include TDA type definitions
#include "lib/list.h"   // Basic list operations library
#include "lib/chants.h" // Chant definitions
#include "lib/player.h" // Some struct player array utility function

void insertCardInTable(Deck* table, Player* player,int pint, int val);
void setHands(Deck* deck, Player* players, int num_of_players);
void putTable(Deck* deck, Deck* table, Player* player);
bool validOption(int option, Deck deck);
Card* selectCardFromHand(Player* player);

void insertCardInTable(Deck* table, Player* player,int pint, int val){
    if(!cardExistsInDeck(table,val)){
        insertCardInOrder(table,pint,val);
        return;
    }
    Deck* pillow = &(player->pillow);
    unshiftCard(pillow,pint,val);
    Deck* aux = removeAndReturnConsecutiveCardsFromDeck(table,val);
    concatenateDecks(pillow,*aux);
}

void setHands(Deck* deck, Player* players, int num_of_players){
    Card* c;
    int i,j;
    for (i = 0; i < num_of_players; i++){
        for (j = 0; j < 3; j++){
            c = dequeueAndReturnCard(deck);
            unshiftCard(&(players[i].hand),c->pint,c->val);
        }
        orderDeck(&(players[i].hand));
    }
}

void putTable(Deck* deck, Deck* table, Player* player){
    Card* c;
    do{
        c = popAndReturnCard(deck);
        if(!cardExistsInDeck(table,c->val)) {
            insertCardInOrder(table,c->pint,c->val);
        } else {
            unshiftCard(deck,c->pint,c->val);
        }
    }while(deckLength(*table) != 4);
    orderDeck(table);
}

bool validOption(int option, Deck deck){
    if((option!=1) && (option!=2) && (option != 3)) return false;
    if((deckLength(deck) == 3) && ((option == 1) || (option == 2) || (option == 3))) return true;
    if((deckLength(deck) == 2) && ((option == 1) || (option == 2))) return true;
    if(deckLength(deck) == option == 1 ) return true;
    return false;
}

Card* selectCardFromHand(Player* player){
    if(emptyDeck(player->hand)) return NULL;
    int option = 0;
    int handLength = deckLength(player->hand);
    Deck* card1 = &(player->hand);
    Deck* card2 = &(player->hand->sig);
    Deck* card3 = &(player->hand->sig->sig);
    while (!validOption(option,player->hand)){
        printf("opciones:\n");
        if(handLength == 3 ){
            printf("[1] pint: %d, val: %d\n",(*card1)->pint,(*card1)->val);
            printf("[2] pint: %d, val: %d\n",(*card2)->pint,(*card2)->val);
            printf("[3] pint: %d, val: %d\n",(*card3)->pint,(*card3)->val);
        } else if(handLength == 2){
            printf("[1] pint: %d, val: %d\n",(*card1)->pint,(*card1)->val);
            printf("[2] pint: %d, val: %d\n",(*card2)->pint,(*card2)->val);
        } else if(handLength == 1){
            printf("[1] pint: %d, val: %d\n",(*card1)->pint,(*card1)->val);
        }
        printf("Selecciona una carta de tu mano para poner en la meza (entre 1 y %d):",handLength);
        scanf("%d",&option);
        printf("\n");
    }
    Card* card;
    if(handLength == 1){
        card = dequeueAndReturnCard(card1);
        return card;
    } else if(handLength == 2){
        switch (option){
            case 1:
                card = dequeueAndReturnCard(card1);
                return card;
            case 2:
                card = popAndReturnCard(card2);
                return card;
            default:
                return NULL;
            break;
        }
    } else if(handLength == 3){
        switch (option){
            case 1:
                card = dequeueAndReturnCard(card1);
                return card;
                break;
            case 2:
                card = newCard((*card2)->pint,(*card2)->val,NULL);
                (*card1)->sig = *card3;
                free(card2);
                return card;
            case 3:
                card = popAndReturnCard(card3);
                return card;
            default:
                return NULL;
            break;
        }
    }
    return NULL;
}

bool fallen(Card prev_card, Card* card, Player* player, int j){
    if (j <= 0) return false;
    if(prev_card.val != card->val) return false;
    if (prev_card.val == 10) {
        player->points +=2;
        printf("%s, Has realizado una caida de sota al jugador anterior, tienes 2 puntos mas\n\n",
            player->name
        );
        return true;
    } else if(prev_card.val == 11){
        player->points +=3;
        printf("%s, Has realizado una caida de caballo jugador anterior, tienes 3 puntos mas\n\n",
            player->name
        );
        return true;
    } else if(prev_card.val == 12){
        player->points +=4;
        printf("%s, Has realizado una caida de rey al jugador anterior, tienes 4 puntos mas\n\n",
            player->name
        );
        return true;
    } else {
        player->points +=1;
        printf("%s, Has realizado una caida comun al jugador anterior, tienes 1 puntos mas\n\n",
            player->name
        );
        return true;
    }
    return false;
}

int main(){
    //Alocating memory and making the initialization of the program data
    printf("Bienvenido al juego de cartas de computacion ii :D\n");
    int num_of_players = 0;
    int points_to_win = 0;
    int _time = time(NULL);
    Deck* deck = newDeck(); //Simple Linked List of Cards
    Deck* table = newDeck();//Simple Linked List of Cards
    Player* players = initPlayers(&num_of_players);//Array of struct player


    //initializing the values
    while (points_to_win <= 0) {
        printf("Cuantos puntos seran necesarios para ganarar el juego?: ");
        scanf("%d",&points_to_win);
        printf("\n");
        if(points_to_win <= 0) {
            printf("No puede escoger un numero de puntos negativo o cero para ganar la partida\n");
        }
    }
    createPlayers(players,num_of_players);
    shuffleDeck(deck,&_time);
    putTable(deck,table,&players[0]);
    printf("\nPoniedo la meza mazo...\n");
    printf("\nHa iniciado un nuevo juego\n");

    //Game start
    while (!winerExists(players,num_of_players,points_to_win)){
        if(!enoughCardsToDeal(deck,num_of_players)) {
            printf("\nBarajeando mazo...\n");
            shuffleDeck(deck,&_time);
            addPointsBasedInPillows(players,num_of_players);
            deletePillows(players, num_of_players);
            printPlayers(players,num_of_players);
            if(winerExists(players,num_of_players,points_to_win)) break;
        }
        printf("\n\nHa iniciado una nueva ronda\n\n");
        setHands(deck,players,num_of_players);
        printChants(players,num_of_players);
        setPointsToTheBestChant(players,num_of_players);
        printPlayers(players,num_of_players);
        if(winerExists(players,num_of_players,points_to_win)) break;
        Card* card = initCard();
        Card prev_card;
        for(int i = 0, j=0; cardsInHandOfAnyPlayer(players,num_of_players); i=(i+1)%num_of_players,j++){
            printf("*********************************************************************\n");
            if(!emptyDeck(*table)){
                printf("Las cartas de la meza son:\n");
                printDeck(*table);
                printf("\n");
            }
            printf("\nTurno del jugador numero %d de nombre %s\n",i+1,players[i].name);
            card = selectCardFromHand(&players[i]);
            if(fallen(prev_card,card,&players[i],j))
                if(winerExists(players,num_of_players,points_to_win)) break;
            prev_card = *card;
            insertCardInTable(table,&players[i],card->pint,card->val);
            printPlayers(players,num_of_players);
            printf("\n");
            if(emptyDeck(*table)){
                printf("meza limpia, Has ganado 4 puntos\n");
                players[i].points += 4;
                printPlayers(players,num_of_players);
                if(winerExists(players,num_of_players,points_to_win)) break;
            }
        }
        printf("*********************************************************************\n");
    }

    printWiner(players,num_of_players);
    return 0;
}

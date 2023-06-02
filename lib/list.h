#ifndef LIST_H_
#define LIST_H_

#include "base.h"

/**
 * @note This header file contains all basic single linked list operations
 */
// Reserve and allocate memory functions
Card* initCard();
Deck* initDeck();
// Fill data in respective TDA
Card* newCard(int pint, int val,Card* card_sig);
Deck* newDeck();
// DATA VERIFICATION
bool emptyDeck(Deck deck);
// List Basic CRUD operations (Create Read Update Delete)
    // CREATE
    Deck* unshiftCard(Deck* deck, int pint, int val);
    Deck* pushCard(Deck* deck, int pint, int val);
    Deck* insertCardInOrder(Deck* deck, int pint, int val);
    // DELETE
    void dequeueCard(Deck* deck);
    Card* dequeueAndReturnCard(Deck* deck);
    void popCard(Deck *deck);
    Card* popAndReturnCard(Deck *deck);
    void deleteDeck(Deck* deck);
    // RANDOM AND ORDERED SORTING
    void swap(Deck* d1, Deck* d2);
    Deck* orderDeck(Deck* deck);
    Deck* shuffleDeck(Deck* deck, int* unixtime);
// DATA INFO
int deckLength(Deck deck);
// PRINT DATA
void printCard(Card card);
void printDeck(Deck deck);
//SPETIAL
Deck* removeAndReturnConsecutiveCardsFromDeck(Deck* head, int val);

Card* initCard(){
    Card* card = (Card* )malloc(sizeof(Card));
    return  card;
}

Deck* initDeck(){
    Deck* deck = (Deck* )malloc(sizeof(Deck));
    return deck;
}

Card* newCard(int pint, int val,Card* card_sig){
    Card* card = initCard();
    card->val = val;
    card->pint = pint;
    card->sig = card_sig;
    return card;
}

Deck* newDeck(){
    Deck* deck = initDeck();
    *deck = NULL;
    return deck;
}

bool emptyDeck(Deck deck){
    return (!deck) ? true : false;
}

Deck* unshiftCard(Deck* deck, int pint, int val){
    Deck new_deck = newCard(pint,val,*deck);
    *deck = new_deck;
    return deck;
}

void dequeueCard(Deck* deck){
    if(emptyDeck(*deck)) return;
    Deck aux_deck = *deck;
    *deck = (*deck)->sig;
    free(aux_deck);
}

Card* dequeueAndReturnCard(Deck* deck){
    if(emptyDeck(*deck)) return NULL;
    Deck aux_deck = *deck;
    Card* aux_card = newCard(aux_deck->pint,aux_deck->val,NULL);
    *deck = (*deck)->sig;
    free(aux_deck);
    return aux_card;
}

Deck* pushCard(Deck* deck, int pint, int val){
    if(emptyDeck(*deck)){
        *deck = newCard(pint,val,NULL);
        return deck;
    }
    Deck aux_deck = *deck;
    while(aux_deck->sig) aux_deck=aux_deck->sig;
    aux_deck->sig = newCard(pint,val,NULL);
    return deck;
}

void popCard(Deck *deck){
	if(emptyDeck(*deck)) return;
    Deck aux_deck = *deck;
    if(!aux_deck->sig){
        free(aux_deck);
        *deck = NULL;
        return;
    }
    while(aux_deck->sig->sig) aux_deck=aux_deck->sig;
    free(aux_deck->sig);
    aux_deck->sig = NULL;
}

Card* popAndReturnCard(Deck *deck){
	if(emptyDeck(*deck)) return NULL;
    Deck aux_deck = *deck;
    if(!aux_deck->sig){
        Card* aux_card = newCard(aux_deck->pint,aux_deck->val,NULL);
        free(aux_deck);
        *deck = NULL;
        return aux_card;
    }
    while(aux_deck->sig->sig) aux_deck=aux_deck->sig;
    Card* aux_card = newCard(aux_deck->sig->pint,aux_deck->sig->val,NULL);
    free(aux_deck->sig);
    aux_deck->sig = NULL;
    return aux_card;
}

void deleteDeck(Deck* deck){
    Deck aux_deck;
    while(*deck) {
        aux_deck = *deck;
        *deck = (*deck)->sig;
        free(aux_deck);
    }
}

void swap(Deck* d1, Deck* d2){
    int tmp = (*d1)->val;
    (*d1)->val = (*d2)->val;
    (*d2)->val = tmp;
}

Deck* orderDeck(Deck* deck){
    for (Deck aux_i=*deck; aux_i->sig; aux_i = aux_i->sig)
        for (Deck aux_j=*deck; aux_j->sig; aux_j = aux_j->sig)
            if(aux_j->val > aux_j->sig->val) swap(&aux_j,&(aux_j->sig));
    return deck;
}

Deck* shuffleDeck(Deck* deck, int* unixtime){
    deleteDeck(deck);
    int card_deck[40][2] = {
        {1,gold},{2,gold},{3,gold},{4,gold},{5,gold},{6,gold},{7,gold},{10,gold},{11,gold},{12,gold},
        {1,sword},{2,sword},{3,sword},{4,sword},{5,sword},{6,sword},{7,sword},{10,sword},{11,sword},{12,sword},
        {1,club},{2,club},{3,club},{4,club},{5,club},{6,club},{7,club},{10,club},{11,club},{12,club},
        {1,cup},{2,cup},{3,cup},{4,cup},{5,cup},{6,cup},{7,cup},{10,cup},{11,cup},{12,cup},
    };
    srand(*unixtime);
    for (int i = 0, limit = 40, random = 0; limit > 0; i++, limit--){
        random = rand() % limit;
        unshiftCard(deck,card_deck[random][1],card_deck[random][0]);
        for (int j = random + 1; j < limit; random++, j++){
            card_deck[random][0] = card_deck[j][0];
            card_deck[random][1] = card_deck[j][1];
        }
    }
    (*unixtime)++;
    return deck;
}

int deckLength(Deck deck){
    int i;
    for(i = 0; deck; deck = deck->sig) i++;
    return i;
}

void printDeck(Deck deck){
    while(deck){
        if(deck->pint == 0){
            printf("Carta con pinta %s y valor %d\n","oro",deck->val);
        } else if(deck->pint == 1){
            printf("Carta con pinta %s y valor %d\n","espada",deck->val);
        } else if(deck->pint == 2){
            printf("Carta con pinta %s y valor %d\n","copas",deck->val);
        } else if(deck->pint == 3){
            printf("Carta con pinta %s y valor %d\n","basto",deck->val);
        }
        deck = deck->sig;
    }
}
Deck* removeAndReturnConsecutiveCardsFromDeck(Deck* head, int val){
    Deck* deck = newDeck();
    if(emptyDeck(*head)) deck;
    orderDeck(head);
    Deck tmp = NULL;
    if(((*head)->val == val)){
        while(*head && (*head)->sig && consecutive((*head)->val,(*head)->sig->val)){
            tmp = *head;
            *head= (*head)->sig;
            pushCard(deck,tmp->val,tmp->val);
            free(tmp);
        }
        tmp = *head;
        *head= (*head)->sig;
        pushCard(deck,tmp->val,tmp->val);
        free(tmp);
        return deck;
    } else {
        Deck aux = *head;
        Deck prev = aux;
        while(aux && aux->val !=val){
            prev = aux;
            aux = aux->sig;
        }
        if(!aux) return deck;
        while(aux && aux->sig && consecutive(aux->val,aux->sig->val)){
            tmp = aux;
            aux= aux->sig;
            pushCard(deck,tmp->val,tmp->val);
            free(tmp);
        }
        tmp = aux;
        aux= aux->sig;
        prev->sig = aux;
        pushCard(deck,tmp->val,tmp->val);
        free(tmp);
        return deck;
    }
}

bool cardExistsInDeck(Deck* table, int val){
    for(Deck aux = *table; aux; aux = aux->sig)
        if(aux->val == val) return true;
    return false;
}

void insertCardBeforeCard(Deck* deck, int valref, int pint, int val){
    if (emptyDeck(*deck))
        *deck = newCard(pint,val,*deck);
    for(Deck aux = *deck ; aux ; aux = aux->sig)
        if(aux->val==valref)
            aux->sig = newCard(pint,val,aux->sig);
}

Deck* insertCardInOrder(Deck* deck, int pint, int val){
    if (emptyDeck(*deck)){
        *deck = newCard(pint,val,*deck);
        return deck;
    }
    if((*deck)->val > val){
        *deck = newCard(pint,val,*deck);
        return deck;
    }
    Deck aux = *deck;
    while(aux->sig && aux->sig->val <= val) aux = aux->sig;
    aux->sig = newCard(pint,val,aux->sig);
    return deck;
}

Deck* concatenateDecks(Deck* deck1, Deck deck2){
    if (emptyDeck(*deck1)){
        *deck1 = deck2;
        return deck1;
    }
    if (emptyDeck(deck2)) return deck1;
    Deck aux = *deck1;
    while(aux->sig) aux = aux->sig;
    aux->sig = deck2;
    return deck1;
}

bool enoughCardsToDeal(Deck* deck, int num_of_players){
    return (deckLength(*deck) / (num_of_players*3) >= 1) ? true : false;
}

#endif
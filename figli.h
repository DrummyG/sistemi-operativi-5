//
// Created by Davide Balestrino on 04/12/24.
//

#ifndef SO_6_FIGLI_H
#define SO_6_FIGLI_H
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

#define UDELAY 100000

typedef enum {GUARDIA, LADRO, AVVOCATO} tipo;

struct personaggio{
    int x;
    int y;
    tipo t;
};

void guardia(int giocatore[2]);
void ladroFun(int ladro[2]);
void avvocatoFun(int avvocato[2]);
int movRandom();
void scrittura(int pipe[2], struct personaggio p);
void switchDir(int dir, struct personaggio *p);

#endif //SO_6_FIGLI_H

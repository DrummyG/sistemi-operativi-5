//
// Created by Davide Balestrino on 04/12/24.
//

#include <stdlib.h>
#include "figli.h"

void switchDir(int dir, struct personaggio *p){
    int dirx = 2, diry = 1;
    switch (dir) {
        case 0: diry = 1; dirx = 0; break; // Muovi giù
        case 1: diry = -1; dirx = 0; break; // Muovi su
        case 2: dirx = -2; diry = 0; break; // Muovi sinistra
        case 3: dirx = 2; diry = 0; break; // Muovi destra
    }

    p->x += dirx;
    p->y += diry;

    if (p->x < 0) p->x = 0;
    if (p->x >= COLS) p->x = COLS - 2;
    if (p->y < 0) p->y = 0;
    if (p->y >= LINES) p->y = LINES - 1;
}

void guardia(int giocatore[2]) {
    struct personaggio g;
    g.x = 0; g.y = 0; g.t = GUARDIA;
    int dirx = 0, diry = 0;          // Direzioni iniziali
    int c;                           // Input da tastiera

    while (true) {
        // Leggi l'input da tastiera
        c = getch();
        switch (c) {
            case KEY_DOWN: diry = 1; dirx = 0; break; // Muovi giù
            case KEY_UP: diry = -1; dirx = 0; break; // Muovi su
            case KEY_LEFT: dirx = -2; diry = 0; break; // Muovi sinistra
            case KEY_RIGHT: dirx = 2; diry = 0; break; // Muovi destra
        }

        // Aggiorna le coordinate
        g.x += dirx;
        g.y += diry;

        // Controlla i bordi
        if (g.x < 0) g.x = 0;
        if (g.x >= COLS) g.x = COLS - 2;
        if (g.y < 0) g.y = 0;
        if (g.y >= LINES) g.y = LINES - 1;

        // Scrivi le coordinate nella pipe
        write(giocatore[1], &g, sizeof(struct personaggio));

        usleep(UDELAY); // Ritardo per il movimento fluido
    }

    // Non chiudiamo il processo figlio né usciamo dal ciclo
}


int movRandom() { // Movimento random
    return rand() % 4;
}



void ladroFun(int ladro[2]) {
    struct personaggio l; // Ladro
    l.x = COLS - 2; l.y = LINES - 1; l.t = LADRO; // Posizione iniziale
    usleep(UDELAY);
    int dir;
    srand(200);
    while(true) {
        dir = movRandom(); // Movimento random

        switchDir(dir, &l); // Cambia direzione
        write(ladro[1], &l, sizeof(struct personaggio));
        usleep(UDELAY);
    }
}

void avvocatoFun(int avvocato[2]) {
    struct personaggio a; // Avvocato
    a.x = COLS - 2; a.y = 0; a.t = AVVOCATO; // Posizione iniziale
    int dir;
    srand(500);

    while(true) {
        dir = movRandom(); // Movimento random

        switchDir(dir, &a); // Cambia direzione
        write(avvocato[1], &a, sizeof(struct personaggio));
        usleep(UDELAY);
    }
}


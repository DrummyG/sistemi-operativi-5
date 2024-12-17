//
// Created by Davide Balestrino on 09/12/24.
//

#include <stdlib.h>
#include "padre.h"

void padreFun(int p[2]) {
    struct personaggio g, l, a, pl; // Guardia, Ladro, Avvocato, Personaggio letto
    g.t = GUARDIA; l.t = LADRO; a.t = AVVOCATO;
    l.x = COLS - 2; l.y = LINES - 1;
    a.x = COLS - 2; a.y = 0;
    g.x = 0; g.y = 0;

    while (true) {
        read(p[0], &pl, sizeof(struct personaggio)); // Legge dalla pipe

        if(pl.t == GUARDIA) { // Controlla il tipo del personaggio
            g = pl;
        }else if(pl.t == LADRO) {
            l = pl;
        }else if(pl.t == AVVOCATO) {
            a = pl;
        }else{
            break;
        }

        // Renderizza lo schermo
        if(g.x == l.x && g.y == l.y) { // Se la guardia cattura il ladro
            mvprintw(LINES / 2, COLS / 2 - 10, "Ladro catturato");
            refresh();
            usleep(MESSAGE);
            break;
        }else if(a.x == l.x && a.y == l.y) { // Se l'avvocato libera il ladro
            mvprintw(LINES / 2, COLS / 2 - 10, "Ladro liberato");
            refresh();
            usleep(MESSAGE);
            break;
        }else { // Altrimenti, aggiorna le posizioni
            clear();
            mvaddch(g.y, g.x, 'G'); // Guardia
            mvaddch(l.y, l.x, 'L'); // Ladro
            mvaddch(a.y, a.x, 'A'); // Avvocato
            refresh();
        }
    }

    close(p[0]);

    endwin();
}
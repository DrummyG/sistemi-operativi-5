#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "padre.h"



int main() {
    int p[2];
    pid_t pid, pid2, pid3; // Crea la pipe, fornendo i file descriptors in "pipe_fds"
    if(pipe(p) == -1) {
    // Scrive su stderr, ma include la descrizione dell'ultimo errore che si è presentato
    perror("Pipe call");
    exit(1);
    }

    initscr();
    noecho();
    curs_set(0);
    cbreak();
    nodelay(stdscr, true);
    keypad(stdscr, true);

    pid=fork();
    if(pid < 0) {
        perror("fork call"); _exit(2);
    }else if (pid == 0) { // Processo figlio
        close(p[0]); // Chiusura lettura, il figlio scrive
        guardia(p);
    }

    pid2=fork();
    if(pid2 < 0) {
        perror("fork call"); _exit(3);
    }else if (pid2 == 0) { // Processo figlio
        close(p[0]); // Chiusura lettura, il figlio scrive
        ladroFun(p);
    }

    pid3=fork();
    if(pid3 < 0) {
        perror("fork call"); _exit(4);
    }else if (pid3 == 0) { // Processo figlio
        close(p[0]); // Chiusura lettura, il figlio scrive
        avvocatoFun(p);
    }else { // Processo padre
        close(p[1]);
    }

    padreFun(p);
    kill(pid, SIGKILL); // Uccide i processi figli
    kill(pid2, SIGKILL);
    kill(pid3, SIGKILL);
    return 0;
}

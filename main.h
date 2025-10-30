#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL 101
#define MAX_HISTORICO 10
#define MAX_FILA 10

typedef char URL[MAX_URL]; //url de navegação

typedef struct{ //fila de downloads
    URL url;
    int Tfalta; //quantos comandos falta para terminar
} Download;

typedef struct { //download em andamento
    URL url;
    int Tfalta;
    int on;
} DownloadON;

#endif


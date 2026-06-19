#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

static inline void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static inline void aguardar_enter() {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n');
}

#endif

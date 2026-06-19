#ifndef CONSULTA_H
#define CONSULTA_H

#define MAX_REGISTROS 100

typedef struct {
    int id;
    char nome_cliente[50];
    char nome_pet[50];
    char especie[30];
    char raca[30];
    char data[11];
    char hora[6];
    char veterinario[50];
    char motivo[200];
} Consulta;

void consulta_submenu();
void consulta_cadastrar();
void consulta_listar();
void consulta_editar();
void consulta_excluir();

#endif

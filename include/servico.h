#ifndef SERVICO_H
#define SERVICO_H

#define MAX_REGISTROS 100

typedef struct {
    int id;
    char nome_cliente[50];
    char nome_pet[50];
    char especie[30];
    char raca[30];
    int tipo_servico;
    float valor;
} Pedido;

void servico_submenu();
void servico_cadastrar_pedido();
void servico_listar_pedidos();
void servico_editar_pedido();
void servico_excluir_pedido();

#endif

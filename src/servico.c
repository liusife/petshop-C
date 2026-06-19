#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "servico.h"

#define ARQUIVO_PEDIDOS "data/pedidos.txt"

static int proximo_id(const char *arquivo) {
    FILE *arq = fopen(arquivo, "r");
    if (!arq) return 1;
    int max_id = 0, id;
    char linha[256];
    while (fgets(linha, sizeof(linha), arq)) {
        if (sscanf(linha, "%d", &id) == 1 && id > max_id)
            max_id = id;
    }
    fclose(arq);
    return max_id + 1;
}

static float calcular_valor(int opcao_servico) {
    switch (opcao_servico) {
        case 1: return 40.00;
        case 2: return 50.00;
        case 3: return 80.00;
        default: return 0.00;
    }
}

static void obter_nome_servico(int opcao, char *destino) {
    if (opcao == 1) strcpy(destino, "Banho");
    else if (opcao == 2) strcpy(destino, "Tosa");
    else if (opcao == 3) strcpy(destino, "Banho + Tosa");
    else strcpy(destino, "Desconhecido");
}

static int ler_pedidos(Pedido *pedidos) {
    FILE *arq = fopen(ARQUIVO_PEDIDOS, "r");
    if (!arq) return 0;
    int count = 0;
    char linha[400];
    while (count < MAX_REGISTROS && fgets(linha, sizeof(linha), arq)) {
        if (sscanf(linha, "%d;%49[^;];%49[^;];%29[^;];%29[^;];%d;%f",
                   &pedidos[count].id,
                   pedidos[count].nome_cliente,
                   pedidos[count].nome_pet,
                   pedidos[count].especie,
                   pedidos[count].raca,
                   &pedidos[count].tipo_servico,
                   &pedidos[count].valor) == 7) {
            count++;
        }
    }
    fclose(arq);
    return count;
}

static void escrever_pedidos(Pedido *pedidos, int count) {
    FILE *arq = fopen(ARQUIVO_PEDIDOS, "w");
    if (!arq) return;
    for (int i = 0; i < count; i++)
        fprintf(arq, "%d;%s;%s;%s;%s;%d;%.2f\n",
                pedidos[i].id, pedidos[i].nome_cliente, pedidos[i].nome_pet,
                pedidos[i].especie, pedidos[i].raca,
                pedidos[i].tipo_servico, pedidos[i].valor);
    fclose(arq);
}

void servico_cadastrar_pedido() {
    limpar_tela();

    FILE *arq = fopen(ARQUIVO_PEDIDOS, "a");
    if (!arq) {
        printf("Erro ao abrir arquivo!\n");
        aguardar_enter();
        return;
    }

    Pedido p;
    p.id = proximo_id(ARQUIVO_PEDIDOS);

    printf("\n--- CADASTRAR PEDIDO ---\n");
    printf("Nome do Cliente: ");
    fgets(p.nome_cliente, 50, stdin);
    p.nome_cliente[strcspn(p.nome_cliente, "\n")] = '\0';

    printf("Nome do Pet: ");
    fgets(p.nome_pet, 50, stdin);
    p.nome_pet[strcspn(p.nome_pet, "\n")] = '\0';

    printf("Especie: ");
    fgets(p.especie, 30, stdin);
    p.especie[strcspn(p.especie, "\n")] = '\0';

    printf("Raca: ");
    fgets(p.raca, 30, stdin);
    p.raca[strcspn(p.raca, "\n")] = '\0';

    do {
        printf("Tipo de Servico:\n");
        printf("1 - Banho (R$ 40,00)\n");
        printf("2 - Tosa (R$ 50,00)\n");
        printf("3 - Banho + Tosa (R$ 80,00)\n");
        printf("Opcao: ");
        if (scanf("%d", &p.tipo_servico) != 1) p.tipo_servico = 0;
        getchar();
    } while (p.tipo_servico < 1 || p.tipo_servico > 3);

    p.valor = calcular_valor(p.tipo_servico);

    fprintf(arq, "%d;%s;%s;%s;%s;%d;%.2f\n", p.id, p.nome_cliente, p.nome_pet,
            p.especie, p.raca, p.tipo_servico, p.valor);
    fclose(arq);

    printf("Pedido #%d cadastrado com sucesso!\n", p.id);
    aguardar_enter();
}

void servico_listar_pedidos() {
    limpar_tela();
    Pedido pedidos[MAX_REGISTROS];
    int count = ler_pedidos(pedidos);

    if (count == 0) {
        printf("\nNenhum pedido cadastrado.\n");
        aguardar_enter();
        return;
    }

    printf("\n=== PEDIDOS ===\n");
    for (int i = 0; i < count; i++) {
        char nome_servico[30];
        obter_nome_servico(pedidos[i].tipo_servico, nome_servico);
        printf("#%d\n", pedidos[i].id);
        printf("  Cliente: %s\n", pedidos[i].nome_cliente);
        printf("  Pet:     %s\n", pedidos[i].nome_pet);
        printf("  Especie: %s\n", pedidos[i].especie);
        printf("  Raca:    %s\n", pedidos[i].raca);
        printf("  Servico: %s\n", nome_servico);
        printf("  Valor:   R$ %.2f\n", pedidos[i].valor);
        printf("-----------------------------\n");
    }
    aguardar_enter();
}

void servico_editar_pedido() {
    limpar_tela();
    Pedido pedidos[MAX_REGISTROS];
    int count = ler_pedidos(pedidos);
    if (count == 0) {
        printf("Nenhum pedido cadastrado.\n");
        aguardar_enter();
        return;
    }

    servico_listar_pedidos();

    int id;
    printf("ID do pedido a editar: ");
    if (scanf("%d", &id) != 1) { getchar(); aguardar_enter(); return; }
    getchar();

    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (pedidos[i].id == id) { idx = i; break; }
    }
    if (idx == -1) {
        printf("ID nao encontrado.\n");
        aguardar_enter();
        return;
    }
    Pedido *p = &pedidos[idx];
    int opcao;
    do {
        char nome_servico[30];
        obter_nome_servico(p->tipo_servico, nome_servico);
        printf("\n--- EDITAR PEDIDO #%d ---\n", p->id);
        printf("1. Cliente: %s\n", p->nome_cliente);
        printf("2. Pet:     %s\n", p->nome_pet);
        printf("3. Especie: %s\n", p->especie);
        printf("4. Raca:    %s\n", p->raca);
        printf("5. Servico: %s\n", nome_servico);
        printf("6. Concluir\n");
        printf("Escolha um campo: ");
        if (scanf("%d", &opcao) != 1) { opcao = 6; getchar(); }
        getchar();

        switch (opcao) {
            case 1:
                printf("Novo nome do cliente: ");
                fgets(p->nome_cliente, 50, stdin);
                p->nome_cliente[strcspn(p->nome_cliente, "\n")] = '\0';
                break;
            case 2:
                printf("Novo nome do pet: ");
                fgets(p->nome_pet, 50, stdin);
                p->nome_pet[strcspn(p->nome_pet, "\n")] = '\0';
                break;
            case 3:
                printf("Nova especie: ");
                fgets(p->especie, 30, stdin);
                p->especie[strcspn(p->especie, "\n")] = '\0';
                break;
            case 4:
                printf("Nova raca: ");
                fgets(p->raca, 30, stdin);
                p->raca[strcspn(p->raca, "\n")] = '\0';
                break;
            case 5:
                do {
                    printf("Novo servico (1-Banho, 2-Tosa, 3-Banho+Tosa): ");
                    if (scanf("%d", &p->tipo_servico) != 1) p->tipo_servico = 0;
                    getchar();
                } while (p->tipo_servico < 1 || p->tipo_servico > 3);
                p->valor = calcular_valor(p->tipo_servico);
                break;
        }
    } while (opcao != 6);

    escrever_pedidos(pedidos, count);
    printf("Pedido #%d atualizado!\n", p->id);
    aguardar_enter();
}

void servico_excluir_pedido() {
    limpar_tela();
    Pedido pedidos[MAX_REGISTROS];
    int count = ler_pedidos(pedidos);
    if (count == 0) {
        printf("Nenhum pedido cadastrado.\n");
        aguardar_enter();
        return;
    }

    servico_listar_pedidos();

    int id;
    printf("ID do pedido a excluir: ");
    if (scanf("%d", &id) != 1) { getchar(); aguardar_enter(); return; }
    getchar();

    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (pedidos[i].id == id) { idx = i; break; }
    }
    if (idx == -1) {
        printf("ID nao encontrado.\n");
        aguardar_enter();
        return;
    }

    char conf;
    printf("Excluir pedido #%d? (s/N): ", id);
    conf = getchar();
    getchar();
    if (conf != 's' && conf != 'S') {
        printf("Exclusao cancelada.\n");
        aguardar_enter();
        return;
    }

    for (int i = idx; i < count - 1; i++)
        pedidos[i] = pedidos[i + 1];

    escrever_pedidos(pedidos, count - 1);
    printf("Pedido #%d excluido!\n", id);
    aguardar_enter();
}

void servico_submenu() {
    int opcao;
    do {
        limpar_tela();
        printf("\n--- PEDIDOS (Banho/Tosa) ---\n");
        printf("1. Cadastrar\n");
        printf("2. Listar\n");
        printf("3. Editar\n");
        printf("4. Excluir\n");
        printf("5. Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { opcao = 5; getchar(); }
        getchar();
        switch (opcao) {
            case 1: servico_cadastrar_pedido(); break;
            case 2: servico_listar_pedidos(); break;
            case 3: servico_editar_pedido(); break;
            case 4: servico_excluir_pedido(); break;
        }
    } while (opcao != 5);
}

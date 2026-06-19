#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "consulta.h"

#define ARQUIVO_CONSULTAS "data/consultas.txt"

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

static int ler_consultas(Consulta *consultas) {
    FILE *arq = fopen(ARQUIVO_CONSULTAS, "r");
    if (!arq) return 0;
    int count = 0;
    char linha[500];
    while (count < MAX_REGISTROS && fgets(linha, sizeof(linha), arq)) {
        if (sscanf(linha, "%d;%49[^;];%49[^;];%29[^;];%29[^;];%10[^;];%5[^;];%49[^;];%199[^\n]",
                   &consultas[count].id,
                   consultas[count].nome_cliente,
                   consultas[count].nome_pet,
                   consultas[count].especie,
                   consultas[count].raca,
                   consultas[count].data,
                   consultas[count].hora,
                   consultas[count].veterinario,
                   consultas[count].motivo) == 9) {
            count++;
        }
    }
    fclose(arq);
    return count;
}

static void escrever_consultas(Consulta *consultas, int count) {
    FILE *arq = fopen(ARQUIVO_CONSULTAS, "w");
    if (!arq) return;
    for (int i = 0; i < count; i++)
        fprintf(arq, "%d;%s;%s;%s;%s;%s;%s;%s;%s\n",
                consultas[i].id, consultas[i].nome_cliente,
                consultas[i].nome_pet, consultas[i].especie,
                consultas[i].raca, consultas[i].data,
                consultas[i].hora, consultas[i].veterinario,
                consultas[i].motivo);
    fclose(arq);
}

static void ler_campo(const char *rotulo, char *destino, int max_len) {
    char temp[256];
    printf("%s", rotulo);
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    strncpy(destino, temp, max_len - 1);
    destino[max_len - 1] = '\0';
}

void consulta_cadastrar() {
    limpar_tela();

    FILE *arq = fopen(ARQUIVO_CONSULTAS, "a");
    if (!arq) {
        printf("Erro ao abrir arquivo!\n");
        aguardar_enter();
        return;
    }

    Consulta c;
    c.id = proximo_id(ARQUIVO_CONSULTAS);

    printf("\n--- CADASTRAR CONSULTA ---\n");
    ler_campo("Nome do Cliente: ", c.nome_cliente, 50);
    ler_campo("Nome do Pet: ", c.nome_pet, 50);
    ler_campo("Especie: ", c.especie, 30);
    ler_campo("Raca: ", c.raca, 30);
    ler_campo("Data (DD/MM/AAAA): ", c.data, 11);
    ler_campo("Hora (HH:MM): ", c.hora, 6);
    ler_campo("Veterinario: ", c.veterinario, 50);
    ler_campo("Motivo da consulta: ", c.motivo, 200);

    fprintf(arq, "%d;%s;%s;%s;%s;%s;%s;%s;%s\n", c.id, c.nome_cliente,
            c.nome_pet, c.especie, c.raca, c.data, c.hora, c.veterinario, c.motivo);
    fclose(arq);

    printf("Consulta #%d cadastrada com sucesso!\n", c.id);
    aguardar_enter();
}

void consulta_listar() {
    limpar_tela();
    Consulta consultas[MAX_REGISTROS];
    int count = ler_consultas(consultas);

    if (count == 0) {
        printf("\nNenhuma consulta cadastrada.\n");
        aguardar_enter();
        return;
    }

    printf("\n=== CONSULTAS ===\n");
    for (int i = 0; i < count; i++) {
        printf("#%d\n", consultas[i].id);
        printf("  Cliente:     %s\n", consultas[i].nome_cliente);
        printf("  Pet:         %s\n", consultas[i].nome_pet);
        printf("  Especie:     %s\n", consultas[i].especie);
        printf("  Raca:        %s\n", consultas[i].raca);
        printf("  Data:        %s\n", consultas[i].data);
        printf("  Hora:        %s\n", consultas[i].hora);
        printf("  Veterinario: %s\n", consultas[i].veterinario);
        printf("  Motivo:      %s\n", consultas[i].motivo);
        printf("-----------------------------\n");
    }
    aguardar_enter();
}

void consulta_editar() {
    limpar_tela();
    Consulta consultas[MAX_REGISTROS];
    int count = ler_consultas(consultas);
    if (count == 0) {
        printf("Nenhuma consulta cadastrada.\n");
        aguardar_enter();
        return;
    }

    consulta_listar();

    int id;
    printf("ID da consulta a editar: ");
    if (scanf("%d", &id) != 1) { getchar(); aguardar_enter(); return; }
    getchar();

    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (consultas[i].id == id) { idx = i; break; }
    }
    if (idx == -1) {
        printf("ID nao encontrado.\n");
        aguardar_enter();
        return;
    }

    Consulta *c = &consultas[idx];
    int opcao;
    do {
        printf("\n--- EDITAR CONSULTA #%d ---\n", c->id);
        printf("1. Cliente:     %s\n", c->nome_cliente);
        printf("2. Pet:         %s\n", c->nome_pet);
        printf("3. Especie:     %s\n", c->especie);
        printf("4. Raca:        %s\n", c->raca);
        printf("5. Data:        %s\n", c->data);
        printf("6. Hora:        %s\n", c->hora);
        printf("7. Veterinario: %s\n", c->veterinario);
        printf("8. Motivo:      %s\n", c->motivo);
        printf("9. Concluir\n");
        printf("Escolha um campo: ");
        if (scanf("%d", &opcao) != 1) { opcao = 9; getchar(); }
        getchar();

        switch (opcao) {
            case 1: ler_campo("Novo nome do cliente: ", c->nome_cliente, 50); break;
            case 2: ler_campo("Novo nome do pet: ", c->nome_pet, 50); break;
            case 3: ler_campo("Nova especie: ", c->especie, 30); break;
            case 4: ler_campo("Nova raca: ", c->raca, 30); break;
            case 5: ler_campo("Nova data (DD/MM/AAAA): ", c->data, 11); break;
            case 6: ler_campo("Nova hora (HH:MM): ", c->hora, 6); break;
            case 7: ler_campo("Novo veterinario: ", c->veterinario, 50); break;
            case 8: ler_campo("Novo motivo: ", c->motivo, 200); break;
        }
    } while (opcao != 9);

    escrever_consultas(consultas, count);
    printf("Consulta #%d atualizada!\n", c->id);
    aguardar_enter();
}

void consulta_excluir() {
    limpar_tela();
    Consulta consultas[MAX_REGISTROS];
    int count = ler_consultas(consultas);
    if (count == 0) {
        printf("Nenhuma consulta cadastrada.\n");
        aguardar_enter();
        return;
    }

    consulta_listar();

    int id;
    printf("ID da consulta a excluir: ");
    if (scanf("%d", &id) != 1) { getchar(); aguardar_enter(); return; }
    getchar();

    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (consultas[i].id == id) { idx = i; break; }
    }
    if (idx == -1) {
        printf("ID nao encontrado.\n");
        aguardar_enter();
        return;
    }

    char conf;
    printf("Excluir consulta #%d? (s/N): ", id);
    conf = getchar();
    getchar();
    if (conf != 's' && conf != 'S') {
        printf("Exclusao cancelada.\n");
        aguardar_enter();
        return;
    }

    for (int i = idx; i < count - 1; i++)
        consultas[i] = consultas[i + 1];

    escrever_consultas(consultas, count - 1);
    printf("Consulta #%d excluida!\n", id);
    aguardar_enter();
}

void consulta_submenu() {
    int opcao;
    do {
        limpar_tela();
        printf("\n--- CONSULTAS VETERINARIAS ---\n");
        printf("1. Cadastrar\n");
        printf("2. Listar\n");
        printf("3. Editar\n");
        printf("4. Excluir\n");
        printf("5. Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { opcao = 5; getchar(); }
        getchar();
        switch (opcao) {
            case 1: consulta_cadastrar(); break;
            case 2: consulta_listar(); break;
            case 3: consulta_editar(); break;
            case 4: consulta_excluir(); break;
        }
    } while (opcao != 5);
}

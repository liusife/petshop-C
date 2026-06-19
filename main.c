#include <stdio.h>
#include "util.h"
#include "servico.h"
#include "consulta.h"

int main() {
    int opcao;
    do {
        limpar_tela();
        printf("=== PET SHOP ===\n");
        printf("1. Servicos (Banho/Tosa)\n");
        printf("2. Consultas Veterinarias\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { opcao = 3; getchar(); }
        getchar();
        switch (opcao) {
            case 1: servico_submenu(); break;
            case 2: consulta_submenu(); break;
        }
    } while (opcao != 3);
    return 0;
}

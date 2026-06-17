#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "dados_petshop.txt"

// Estrutura para armazenar os dados do pedido
typedef struct {
    char nome_cliente[50];
    char nome_pet[50];
    int tipo_servico; // 1 - Banho, 2 - Tosa, 3 - Banho + Tosa
    float valor;
} Pedido;

// Protótipos das funções
void menu();
void cadastrar_pedido();
void ler_pedidos();
float calcular_valor(int opcao_servico);
void obter_nome_servico(int opcao, char *destino);

int main() {
    menu();
    return 0;
}

// Menu principal do sistema
void menu() {
    int opcao;
    do {
        printf("\n=== PET SHOP - MENU PRINCIPAL ===\n");
        printf("1. Cadastrar Pedido\n");
        printf("2. Visualizar Pedidos (Ler Arquivo)\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            exit(1);
        }
        getchar(); // Limpa o buffer do teclado

        switch(opcao) {
            case 1:
                cadastrar_pedido();
                break;
            case 2:
                ler_pedidos();
                break;
            case 3:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 3);
}

// Função para calcular o valor com base no serviço escolhido
float calcular_valor(int opcao_servico) {
    switch(opcao_servico) {
        case 1: return 40.00;  // Valor do Banho
        case 2: return 50.00;  // Valor da Tosa
        case 3: return 80.00;  // Valor de Banho + Tosa
        default: return 0.00;
    }
}

// Retorna o texto amigável do serviço
void obter_nome_servico(int opcao, char *destino) {
    if (opcao == 1) strcpy(destino, "Banho");
    else if (opcao == 2) strcpy(destino, "Tosa");
    else if (opcao == 3) strcpy(destino, "Banho + Tosa");
    else strcpy(destino, "Desconhecido");
}

// Cadastra um novo pedido e salva diretamente no arquivo TXT
void cadastrar_pedido() {
    FILE *arq = fopen(ARQUIVO, "a"); // Abre no modo "append" (adiciona ao final)
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para gravacao!\n");
        return;
    }

    Pedido p;

    printf("\n--- CADASTRAR NOVO PEDIDO ---\n");
    printf("Nome do Cliente: ");
    fgets(p.nome_cliente, 50, stdin);
    p.nome_cliente[strcspn(p.nome_cliente, "\n")] = '\0'; // Remove o \n do final

    printf("Nome do Pet: ");
    fgets(p.nome_pet, 50, stdin);
    p.nome_pet[strcspn(p.nome_pet, "\n")] = '\0';

    do {
        printf("Escolha o Servico:\n");
        printf("1 - Banho (R$ 40.00)\n");
        printf("2 - Tosa (R$ 50.00)\n");
        printf("3 - Banho + Tosa (R$ 80.00)\n");
        printf("Opcao: ");
        if (scanf("%d", &p.tipo_servico) != 1) { p.tipo_servico = 0; }
        getchar(); // Limpa buffer
    } while (p.tipo_servico < 1 || p.tipo_servico > 3);

    p.valor = calcular_valor(p.tipo_servico);

    // Grava os dados estruturados no arquivo de texto separados por ponto e vírgula
    fprintf(arq, "%s;%s;%d;%.2f\n", p.nome_cliente, p.nome_pet, p.tipo_servico, p.valor);
    fclose(arq);

    printf("\nPedido gravado com sucesso no arquivo!\n");
}

// Lê e exibe todos os dados armazenados no arquivo TXT
void ler_pedidos() {
    FILE *arq = fopen(ARQUIVO, "r"); // Abre no modo leitura
    if (arq == NULL) {
        printf("\nNenhum pedido registrado ou arquivo nao encontrado.\n");
        return;
    }

    char linha[200];
    char nome_servico[30];
    int contador = 1;

    printf("\n=== PEDIDOS REGISTRADOS NO ARQUIVO ===\n");
    
    // Lê linha por linha do arquivo usando o delimitador ';'
    while (fgets(linha, sizeof(linha), arq)) {
        char nome_cli[50], nome_p[50];
        int servico_opt;
        float v_servico;

        // Faz o parsing das informações separadas por ';'
        sscanf(linha, "%[^;];%[^;];%d;%f", nome_cli, nome_p, &servico_opt, &v_servico);
        obter_nome_servico(servico_opt, nome_servico);

        printf("Pedido #%d\n", contador++);
        printf("  Cliente: %s\n", nome_cli);
        printf("  Pet:     %s\n", nome_p);
        printf("  Servico: %s\n", nome_servico);
        printf("  Valor:   R$ %.2f\n", v_servico);
        printf("-------------------------------------\n");
    }

    fclose(arq);
}

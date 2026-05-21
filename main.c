#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct {
    char tipo[12];
    float valor;
    float saldoDepois;
} Operacao;
 
void exibirMenu(float saldo);
void consultarSaldo(float saldo);
float depositar(float saldo, Operacao historico[], int *total);
float sacar(float saldo, Operacao historico[], int *total);
void extrato(float saldo, Operacao historico[], int total);
void salvarOperacao(Operacao historico[], int *total, char tipo[], float valor, float saldoDepois);
void pausar();
void limparTela();
 
int main() {
    float saldo = 1000.0;
    int opcao = -1;
    Operacao historico[3];
    int totalOp = 0;
 
    limparTela();
    printf("\n");
    printf("  ==============================\n");
    printf("   BEM-VINDO AO CAIXA ELETRONICO\n");
    printf("  ==============================\n");
    printf("  Saldo inicial: R$ %.2f\n\n", saldo);
    pausar();
 
    do {
        limparTela();
        exibirMenu(saldo);
        scanf("%d", &opcao);
        while(getchar() != '\n');
        limparTela();
 
        switch(opcao) {
            case 1:
                consultarSaldo(saldo);
                break;
            case 2:
                saldo = depositar(saldo, historico, &totalOp);
                break;
            case 3:
                saldo = sacar(saldo, historico, &totalOp);
                break;
            case 4:
                extrato(saldo, historico, totalOp);
                break;
            case 0:
                printf("\nObrigado por usar o caixa. Ate logo!\n\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n\n");
                pausar();
        }
 
    } while(opcao != 0);
 
    return 0;
}
 
void exibirMenu(float saldo) {
    printf("\n");
    printf("  ==============================\n");
    printf("       CAIXA ELETRONICO ATM\n");
    printf("  ==============================\n");
    printf("  Saldo: R$ %.2f\n", saldo);
    printf("  ------------------------------\n");
    printf("  1 - Consultar Saldo\n");
    printf("  2 - Depositar\n");
    printf("  3 - Sacar\n");
    printf("  4 - Extrato\n");
    printf("  0 - Sair\n");
    printf("  ==============================\n");
    printf("  Opcao: ");
}
 
void consultarSaldo(float saldo) {
    printf("\n  --- SALDO ATUAL ---\n");
    printf("  R$ %.2f\n", saldo);
    printf("  -------------------\n\n");
    pausar();
}
 
float depositar(float saldo, Operacao historico[], int *total) {
    float valor;
 
    printf("\n  --- DEPOSITO ---\n");
    printf("  Saldo atual: R$ %.2f\n", saldo);
    printf("  Valor a depositar: R$ ");
    scanf("%f", &valor);
    while(getchar() != '\n');
 
    if(valor <= 0) {
        printf("\n  Valor invalido!\n\n");
    } else {
        saldo += valor;
        salvarOperacao(historico, total, "DEPOSITO", valor, saldo);
        printf("\n  Deposito de R$ %.2f realizado!\n", valor);
        printf("  Novo saldo: R$ %.2f\n\n", saldo);
    }
 
    pausar();
    return saldo;
}
 
float sacar(float saldo, Operacao historico[], int *total) {
    float valor;
 
    printf("\n  --- SAQUE ---\n");
    printf("  Saldo disponivel: R$ %.2f\n", saldo);
    printf("  Limite por operacao: R$ 500.00\n");
    printf("  Valor a sacar: R$ ");
    scanf("%f", &valor);
    while(getchar() != '\n');
 
    if(valor <= 0) {
        printf("\n  Valor invalido!\n\n");
    } else if(valor > 500.0) {
        printf("\n  Limite de saque excedido! Maximo R$ 500.00\n\n");
    } else if(valor > saldo) {
        printf("\n  Saldo insuficiente! Voce tem R$ %.2f\n\n", saldo);
    } else {
        saldo -= valor;
        salvarOperacao(historico, total, "SAQUE", valor, saldo);
        printf("\n  Saque de R$ %.2f realizado!\n", valor);
        printf("  Saldo restante: R$ %.2f\n\n", saldo);
    }
 
    pausar();
    return saldo;
}
 
void extrato(float saldo, Operacao historico[], int total) {
    printf("\n  --- EXTRATO ---\n\n");
 
    if(total == 0) {
        printf("  Nenhuma movimentacao ainda.\n\n");
    } else {
        int i;
        for(i = 0; i < total; i++) {
            printf("  %d) %s  R$ %.2f  -> saldo: R$ %.2f\n",
                i+1, historico[i].tipo, historico[i].valor, historico[i].saldoDepois);
        }
        printf("\n");
    }
 
    printf("  Saldo atual: R$ %.2f\n", saldo);
    printf("  ---------------\n\n");
    pausar();
}
 
void salvarOperacao(Operacao historico[], int *total, char tipo[], float valor, float saldoDepois) {
    if(*total < 3) {
        strcpy(historico[*total].tipo, tipo);
        historico[*total].valor = valor;
        historico[*total].saldoDepois = saldoDepois;
        (*total)++;
    } else {
        int i;
        for(i = 0; i < 2; i++) {
            historico[i] = historico[i+1];
        }
        strcpy(historico[2].tipo, tipo);
        historico[2].valor = valor;
        historico[2].saldoDepois = saldoDepois;
    }
}
 
void pausar() {
    printf("  Pressione Enter para continuar...");
    getchar();
}
 
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

    
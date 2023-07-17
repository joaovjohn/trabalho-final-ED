#include <stdio.h>
#include <stdlib.h>
#include "agenda.h"

int main() {
    int opcao;

    while (1) {
        printf("1 - Incluir\n");
        printf("2 - Consultar\n");
        printf("3 - Alterar\n");
        printf("4 - Excluir\n");
        printf("5 - Listar\n");
        printf("6 - Sair\n");
        printf("Digite uma opção: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1:
                incluir();
                break;
            case 2:
                consultar();
                break;
            case 3:
                alterar();
                break;
            case 4:
                excluir();
                break;
            case 5:
                listar();
                break;
            case 6:
                liberarAgenda();
                printf("Programa encerrado.\n");
                return 0;
            default:
                printf("Opção inválida.\n");
                break;
        }

        printf("\n");
    }
}
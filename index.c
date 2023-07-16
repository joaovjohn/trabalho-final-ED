#include <stdio.h>
#include <stdlib.h>
#include "agenda.h"

int main() {
    int opcao;

    while (1) {
        printf("1 - Incluir evento\n");
/*        printf("2 - Consultar por data\n");
        printf("3 - Consultar por data e hora\n");
        printf("4 - Alterar evento\n");
        printf("5 - Excluir evento\n");
        printf("6 - Listar eventos\n");
        printf("7 - Sair\n");*/
        printf("Digite uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirEvento();
                break;
/*            case 2:
                consultarPorData();
                break;
            case 3:
                consultarPorDataHora();
                break;
            case 4:
                alterarEvento();
                break;
            case 5:
                excluirEvento();
                break;
            case 6:
                listarEventos();
                break;
            case 7:
                liberarAgenda();
                printf("Programa encerrado.\n");
                return 0;
            default:
                printf("Opção inválida.\n");
                break;
                */
        }

        printf("\n");
    }
}
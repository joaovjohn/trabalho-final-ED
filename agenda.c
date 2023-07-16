#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

Evento *agenda = NULL;

int isNumero(char c) {
    return c >= '0' && c <= '9';
}

void incluirEvento() {
    static int proxCodigo = 1;

    Evento *novoEvento = (Evento *)malloc(sizeof(Evento));
    if (novoEvento == NULL) {
        printf("Erro: não foi possível alocar memória para o novo evento.\n");
        return;
    }

    novoEvento->codigo = proxCodigo++;

    char dataStr[11];
    printf("Digite a data do evento (formato: dd/mm/aaaa): ");
    scanf("%10s", dataStr);

    if (strlen(dataStr) != 10 || dataStr[2] != '/' || dataStr[5] != '/') {
        printf("Erro: formato de data inválido.\n");
        free(novoEvento);
        return;
    }

    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && !isNumero(dataStr[i])) {
            printf("Erro: formato de data inválido.\n");
            free(novoEvento);
            return;
        }
    }

    sscanf(dataStr, "%d/%d/%d", &novoEvento->dataEvento.dia, &novoEvento->dataEvento.mes, &novoEvento->dataEvento.ano);

    printf("Digite a hora do evento (formato: hh:mm): ");
    scanf("%d:%d", &novoEvento->dataEvento.hora, &novoEvento->dataEvento.minuto);

    printf("Digite a duração do evento em horas: ");
    scanf("%f", &novoEvento->duracao);

    printf("Digite a descrição do evento: ");
    getchar(); 
    fgets(novoEvento->descricao, sizeof(novoEvento->descricao), stdin);
    novoEvento->descricao[strcspn(novoEvento->descricao, "\n")] = '\0'; 

    novoEvento->proximo = NULL;
    novoEvento->anterior = NULL;

    Evento *eventoAtual = agenda;
    while (eventoAtual != NULL) {
        if (compareDataHora(eventoAtual->dataEvento, novoEvento->dataEvento) == 0) {
            printf("Erro: já existe um evento agendado para a mesma data e hora.\n");
            free(novoEvento);
            return;
        }
        eventoAtual = eventoAtual->proximo;
    }

    if (agenda == NULL) {
        agenda = novoEvento;
    } else {
        Evento *eventoAtual = agenda;
        while (eventoAtual->proximo != NULL) {
            eventoAtual = eventoAtual->proximo;
        }
        eventoAtual->proximo = novoEvento;
        novoEvento->anterior = eventoAtual;
    }

    printf("Evento agendado com sucesso.\n");
}
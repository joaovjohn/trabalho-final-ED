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

    Evento *novoEvento = (Evento*)malloc(sizeof(Evento));
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

void consultarPorData() {
    ordenarAgendaPorDataHora();
    int dia, mes, ano;
    printf("Digite a data para consulta (formato: dd/mm/aaaa): ");
    scanf("%d/%d/%d", &dia, &mes, &ano);

    Evento *eventoAtual = agenda;
    int eventosEncontrados = 0;

    while (eventoAtual != NULL) {
        if (eventoAtual->dataEvento.dia == dia &&
            eventoAtual->dataEvento.mes == mes &&
            eventoAtual->dataEvento.ano == ano) {
            printf("Código: %d\n", eventoAtual->codigo);
            printf("Data: %02d/%02d/%04d\n", eventoAtual->dataEvento.dia, eventoAtual->dataEvento.mes, eventoAtual->dataEvento.ano);
            printf("Hora: %02d:%02d\n", eventoAtual->dataEvento.hora, eventoAtual->dataEvento.minuto);
            printf("Duração: %.1f\n", eventoAtual->duracao);
            printf("Descrição: %s\n", eventoAtual->descricao);
            printf("\n");
            eventosEncontrados++;
        }
        eventoAtual = eventoAtual->proximo;
    }

    if (eventosEncontrados == 0) {
        printf("Nenhum evento encontrado para a data especificada.\n");
    }
}

void consultarPorDataHora() {
    ordenarAgendaPorDataHora();
    int dia, mes, ano, hora, minuto;
    printf("Digite a data para consulta (formato: dd/mm/aaaa): ");
    scanf("%d/%d/%d", &dia, &mes, &ano);

    printf("Digite a hora para consulta (formato: hh:mm): ");
    scanf("%d:%d", &hora, &minuto);

    Evento *eventoAtual = agenda;
    int eventoEncontrado = 0;

    while (eventoAtual != NULL) {
        if (eventoAtual->dataEvento.dia == dia &&
            eventoAtual->dataEvento.mes == mes &&
            eventoAtual->dataEvento.ano == ano &&
            eventoAtual->dataEvento.hora == hora &&
            eventoAtual->dataEvento.minuto == minuto) {
            printf("Código: %d\n", eventoAtual->codigo);
            printf("Data: %02d/%02d/%04d\n", eventoAtual->dataEvento.dia, eventoAtual->dataEvento.mes, eventoAtual->dataEvento.ano);
            printf("Hora: %02d:%02d\n", eventoAtual->dataEvento.hora, eventoAtual->dataEvento.minuto);
            printf("Duração: %.1f\n", eventoAtual->duracao);
            printf("Descrição: %s\n", eventoAtual->descricao);
            printf("\n");
            eventoEncontrado = 1;
            break;
        }
        eventoAtual = eventoAtual->proximo;
    }

    if (!eventoEncontrado) {
        printf("Nenhum evento encontrado para a data e hora especificadas.\n");
    }
}

void alterarEvento() {
    int dia, mes, ano, hora, minuto;
    printf("Digite a data do evento a ser alterado (formato: dd/mm/aaaa): ");
    scanf("%d/%d/%d", &dia, &mes, &ano);

    printf("Digite a hora do evento a ser alterado (formato: hh:mm): ");
    scanf("%d:%d", &hora, &minuto);

    Evento *eventoAtual = agenda;
    int eventoEncontrado = 0;

    while (eventoAtual != NULL) {
        if (eventoAtual->dataEvento.dia == dia &&
            eventoAtual->dataEvento.mes == mes &&
            eventoAtual->dataEvento.ano == ano &&
            eventoAtual->dataEvento.hora == hora &&
            eventoAtual->dataEvento.minuto == minuto) {
            printf("Digite a nova descrição do evento: ");
            getchar();
            fgets(eventoAtual->descricao, sizeof(eventoAtual->descricao), stdin);
            eventoAtual->descricao[strcspn(eventoAtual->descricao, "\n")] = '\0';

            printf("Digite a nova duração do evento em horas: ");
            scanf("%f", &eventoAtual->duracao);

            printf("Evento alterado com sucesso.\n");
            eventoEncontrado = 1;
            break;
        }
        eventoAtual = eventoAtual->proximo;
    }

    if (!eventoEncontrado) {
        printf("Compromisso não encontrado.\n");
    }
}

void excluirEvento() {
    int dia, mes, ano, hora, minuto;
    printf("Digite a data do evento a ser excluído (formato: dd/mm/aaaa): ");
    scanf("%d/%d/%d", &dia, &mes, &ano);

    printf("Digite a hora do evento a ser excluído (formato: hh:mm): ");
    scanf("%d:%d", &hora, &minuto);

    Evento *eventoAtual = agenda;
    Evento *eventoAnterior = NULL;
    int eventoEncontrado = 0;

    while (eventoAtual != NULL) {
        if (eventoAtual->dataEvento.dia == dia &&
            eventoAtual->dataEvento.mes == mes &&
            eventoAtual->dataEvento.ano == ano &&
            eventoAtual->dataEvento.hora == hora &&
            eventoAtual->dataEvento.minuto == minuto) {
            if (eventoAnterior == NULL) {
                agenda = eventoAtual->proximo;
                if (agenda != NULL) {
                    agenda->anterior = NULL;
                }
            } else {
                eventoAnterior->proximo = eventoAtual->proximo;
                if (eventoAtual->proximo != NULL) {
                    eventoAtual->proximo->anterior = eventoAnterior;
                }
            }

            free(eventoAtual);
            printf("Evento excluído com sucesso.\n");
            eventoEncontrado = 1;
            break;
        }
        eventoAnterior = eventoAtual;
        eventoAtual = eventoAtual->proximo;
    }

    if (!eventoEncontrado) {
        printf("Compromisso não encontrado.\n");
    }
}

void listarEventos() {
    ordenarAgendaPorDataHora();

    if (agenda == NULL) {
        printf("Agenda vazia.\n");
        return;
    }

    Evento *eventoAtual = agenda;

    while (eventoAtual != NULL) {
        printf("Código: %d\n", eventoAtual->codigo);
        printf("Data: %02d/%02d/%04d\n", eventoAtual->dataEvento.dia, eventoAtual->dataEvento.mes, eventoAtual->dataEvento.ano);
        printf("Hora: %02d:%02d\n", eventoAtual->dataEvento.hora, eventoAtual->dataEvento.minuto);
        printf("Duração: %.1f\n", eventoAtual->duracao);
        printf("Descrição: %s\n", eventoAtual->descricao);
        printf("\n");
        eventoAtual = eventoAtual->proximo;
    }
}

void liberarAgenda() {
    Evento *eventoAtual = agenda;
    Evento *eventoProximo;

    while (eventoAtual != NULL) {
        eventoProximo = eventoAtual->proximo;
        free(eventoAtual);
        eventoAtual = eventoProximo;
    }

    agenda = NULL;
}

void ordenarAgendaPorDataHora() {
    if (agenda == NULL || agenda->proximo == NULL) {
        return;
    }

    int trocou;
    Evento *eventoAtual;
    Evento *eventoAnterior = NULL;
    Evento *eventoTemp = NULL;

    do {
        trocou = 0;
        eventoAtual = agenda;

        while (eventoAtual->proximo != NULL) {
            if (compareDataHora(eventoAtual->dataEvento, eventoAtual->proximo->dataEvento) > 0) {
                eventoTemp = eventoAtual->proximo;
                eventoAtual->proximo = eventoTemp->proximo;
                eventoTemp->anterior = eventoAtual->anterior;

                if (eventoAtual->anterior != NULL) {
                    eventoAtual->anterior->proximo = eventoTemp;
                } else {
                    agenda = eventoTemp;
                }

                eventoAtual->anterior = eventoTemp;
                eventoTemp->proximo = eventoAtual;

                if (eventoAtual->proximo != NULL) {
                    eventoAtual->proximo->anterior = eventoAtual;
                }

                eventoAtual = eventoTemp;
                trocou = 1;
            }

            eventoAnterior = eventoAtual;
            eventoAtual = eventoAtual->proximo;
        }
    } while (trocou);
}

int compareDataHora(Data dataHora1, Data dataHora2) {
    if (dataHora1.ano != dataHora2.ano) {
        return dataHora1.ano - dataHora2.ano;
    } else if (dataHora1.mes != dataHora2.mes) {
        return dataHora1.mes - dataHora2.mes;
    } else if (dataHora1.dia != dataHora2.dia) {
        return dataHora1.dia - dataHora2.dia;
    } else if (dataHora1.hora != dataHora2.hora) {
        return dataHora1.hora - dataHora2.hora;
    } else {
        return dataHora1.minuto - dataHora2.minuto;
    }
}

void trocarEventos(Evento *eventoAnterior, Evento *evento1, Evento *evento2) {
    Evento *eventoTemp = evento2->proximo;

    if (eventoAnterior != NULL) {
        eventoAnterior->proximo = evento2;
    } else {
        agenda = evento2;
    }

    evento2->proximo = evento1;
    evento1->proximo = eventoTemp;

    if (eventoTemp != NULL) {
        eventoTemp->anterior = evento1;
    }

    evento1->anterior = evento2;
    if (evento2->proximo != NULL) {
        evento2->proximo->anterior = evento2;
    }
    evento2->anterior = eventoAnterior;
}
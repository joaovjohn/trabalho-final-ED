typedef struct {
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
} DataHora;

typedef struct _evento {
    int codigo;
    DataHora dataEvento;
    float duracao;
    char descricao[100];
    struct _evento* anterior;
    struct _evento* proximo;
} Evento;

void incluirEvento();
void consultarPorData();
void consultarPorDataHora();

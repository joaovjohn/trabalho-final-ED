typedef struct {
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
} Data;

typedef struct _evento {
    int codigo;
    Data dataEvento;
    float duracao;
    char descricao[100];
    struct _evento *anterior;
    struct _evento *proximo;
} Evento;

void incluirEvento();
void consultarPorData();
void consultarPorDataHora();
void alterarEvento();
void excluirEvento();
void listarEventos();
void liberarAgenda();
void ordenarAgendaPorDataHora();
int compareDataHora(Data dataHora1, Data dataHora2);
void trocarEventos(Evento *eventoAnterior, Evento *evento1, Evento *evento2);
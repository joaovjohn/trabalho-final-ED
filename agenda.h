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
    struct _evento* anterior;
    struct _evento* proximo;
} Evento;

void incluir();
void consultar();
void alterar();
void excluir();
void listar();
void liberarAgenda();
void ordenarAgendaPorDataHora();
int compareDataHora(Data, Data);
void trocarEventos(Evento*, Evento*, Evento*);
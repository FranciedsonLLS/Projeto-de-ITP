#define MAX_NOME_COMPLETO 120

typedef struct assento Assento;
typedef struct teatro Teatro;

struct assento {
    int reservado;
    int fileira;
    int numero;
    char nomeCompleto[MAX_NOME_COMPLETO];
};

struct teatro {
    Assento **assentos;
    int numFileiras;
    int numAssentosPorFileira;
};

Assento **inicializarMatriz(int numFileiras, int numAssentosPorFileira);
Teatro criarTeatro(int numFileiras, int numAssentosPorFileira);
void exibirTeatro(Teatro teatro);
void liberarMatriz(Assento **matriz, int linhas);

int reservarAssento(Teatro t, int linha, int coluna, char *nome);
int reservarAssentosConsecutivos(Teatro t, int linha, int coluna, int n, char *nome);
Assento *reservarAssentoPeloSistema(Teatro t, char *nome);
Assento **reservarAssentosConsecutivosPeloSistema(Teatro t, int n, char *nome);
int cancelarReserva(Teatro t, int linha, int coluna);
int cancelarReservas(Teatro t, char *nome);
int cancelarTodasAsReservas(Teatro t);

int verificarDisponibilidade(Teatro t, int linha, int coluna);
void consultarAssentosConsecutivos(Teatro t, int n);
void exibirInformacoes(Teatro t);

int salvarEstado(Teatro t, char *nomeArquivo);
Teatro carregarEstado(char *nomeArquivo);

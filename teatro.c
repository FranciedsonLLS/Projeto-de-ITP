#include "teatro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOME_COMPLETO 120

struct Assento **inicializarMatriz(int numFileiras, int numAssentosPorFileira) {
    if (numFileiras > 26 || numAssentosPorFileira > 99) {
        return NULL;
    }

    struct Assento **matriz = (struct Assento **)malloc(numFileiras * sizeof(struct Assento *));
    for (int i = 0; i < numFileiras; ++i) {
        matriz[i] = (struct Assento *)malloc(numAssentosPorFileira * sizeof(struct Assento));
        for (int j = 0; j < numAssentosPorFileira; ++j) {
            matriz[i][j].reservado = 0;
            matriz[i][j].fileira = i;
            matriz[i][j].numero = j;
            memset(matriz[i][j].nomeCompleto, 0, MAX_NOME_COMPLETO);
        }
    }

    return matriz;
}

struct Teatro criarTeatro(int numFileiras, int numAssentosPorFileira) {
    struct Teatro teatro;
    teatro.numFileiras = numFileiras;
    teatro.numAssentosPorFileira = numAssentosPorFileira;
    teatro.assentos = inicializarMatriz(numFileiras, numAssentosPorFileira);
    return teatro;
}

void exibirTeatro(struct Teatro teatro) {
    printf("Mapa do Teatro:\n");
    for (int i = 0; i < teatro.numFileiras; ++i) {
        for (int j = 0; j < teatro.numAssentosPorFileira; ++j) {
            printf("[%c]", teatro.assentos[i][j].reservado ? 'X' : 'O');
        }
        printf("\n");
    }
    printf("\n");
}

void liberarMatriz(struct Assento **matriz, int linhas) {
    for (int i = 0; i < linhas; ++i) {
        free(matriz[i]);
    }
    free(matriz);
}

int reservarAssento(struct Teatro t, int linha, int coluna, char *nome) {
    if (linha < 0 || linha >= t.numFileiras || coluna < 0 || coluna >= t.numAssentosPorFileira) {
        return 0;
    }

    if (!t.assentos[linha][coluna].reservado) {
        t.assentos[linha][coluna].reservado = 1;
        t.assentos[linha][coluna].fileira = linha;
        t.assentos[linha][coluna].numero = coluna;
        strncpy(t.assentos[linha][coluna].nomeCompleto, nome, MAX_NOME_COMPLETO);
        return 1;
    } else {
        return 0;
    }
}

int reservarAssentosConsecutivos(struct Teatro t, int linha, int coluna, int n, char *nome) {
    if (linha < 0 || linha >= t.numFileiras || coluna < 0 || coluna >= t.numAssentosPorFileira) {
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        if (coluna + i >= t.numAssentosPorFileira || t.assentos[linha][coluna + i].reservado) {
            return 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        t.assentos[linha][coluna + i].reservado = 1;
        t.assentos[linha][coluna + i].fileira = linha;
        t.assentos[linha][coluna + i].numero = coluna + i;
        strncpy(t.assentos[linha][coluna + i].nomeCompleto, nome, MAX_NOME_COMPLETO);
    }

    return 1;
}

struct Assento *reservarAssentoPeloSistema(struct Teatro t, char *nome) {
    for (int i = 0; i < t.numFileiras; ++i) {
        for (int j = 0; j < t.numAssentosPorFileira; ++j) {
            if (!t.assentos[i][j].reservado) {
                t.assentos[i][j].reservado = 1;
                t.assentos[i][j].fileira = i;
                t.assentos[i][j].numero = j;
                strncpy(t.assentos[i][j].nomeCompleto, nome, MAX_NOME_COMPLETO);
                return &t.assentos[i][j];
            }
        }
    }

    return NULL;
}

struct Assento **reservarAssentosConsecutivosPeloSistema(struct Teatro t, int n, char *nome) {
    struct Assento **assentosReservados = (struct Assento **)malloc(n * sizeof(struct Assento *));

    for (int i = 0; i < t.numFileiras; ++i) {
        for (int j = 0; j <= t.numAssentosPorFileira - n; ++j) {
            int consecutivosDisponiveis = 1;

            for (int k = 0; k < n; ++k) {
                if (t.assentos[i][j + k].reservado) {
                    consecutivosDisponiveis = 0;
                    break;
                }
            }

            if (consecutivosDisponiveis) {
                for (int k = 0; k < n; ++k) {
                    t.assentos[i][j + k].reservado = 1;
                    t.assentos[i][j + k].fileira = i;
                    t.assentos[i][j + k].numero = j + k;
                    strncpy(t.assentos[i][j + k].nomeCompleto, nome, MAX_NOME_COMPLETO);
                    assentosReservados[k] = &t.assentos[i][j + k];
                }

                return assentosReservados;
            }
        }
    }

    free(assentosReservados);
    return NULL;
}

int cancelarReserva(struct Teatro t, int linha, int coluna) {
    if (linha < 0 || linha >= t.numFileiras || coluna < 0 || coluna >= t.numAssentosPorFileira) {
        return 0;
    }

    if (t.assentos[linha][coluna].reservado) {
        t.assentos[linha][coluna].reservado = 0;
        memset(t.assentos[linha][coluna].nomeCompleto, 0, MAX_NOME_COMPLETO);
        return 1;
    } else {
        return 0;
    }
}

int cancelarReservas(struct Teatro t, char *nome) {
    int totalCancelado = 0;

    for (int i = 0; i < t.numFileiras; ++i) {
        for (int j = 0; j < t.numAssentosPorFileira; ++j) {
            if (strcmp(t.assentos[i][j].nomeCompleto, nome) == 0) {
                t.assentos[i][j].reservado = 0;
                memset(t.assentos[i][j].nomeCompleto, 0, MAX_NOME_COMPLETO);
                ++totalCancelado;
            }
        }
    }

    return totalCancelado;
}

int cancelarTodasAsReservas(struct Teatro t) {
    int totalCancelado = 0;

    for (int i = 0; i < t.numFileiras; ++i) {
        for (int j = 0; j < t.numAssentosPorFileira; ++j) {
            if (t.assentos[i][j].reservado) {
                t.assentos[i][j].reservado = 0;
                memset(t.assentos[i][j].nomeCompleto, 0, MAX_NOME_COMPLETO);
                ++totalCancelado;
            }
        }
    }

    return totalCancelado;
}

int verificarDisponibilidade(struct Teatro t, int linha, int coluna) {
    if (linha < 0 || linha >= t.numFileiras || coluna < 0 || coluna >= t.numAssentosPorFileira) {
        return 0;
    }

    return !t.assentos[linha][coluna].reservado;
}

void consultarAssentosConsecutivos(struct Teatro t, int n) {
    printf("Intervalos de assentos com pelo menos %d assentos disponíveis:\n", n);

    for (int i = 0; i < t.numFileiras; ++i) {
        int consecutivosDisponiveis = 0;
        int inicioIntervalo = -1;

        for (int j = 0; j < t.numAssentosPorFileira; ++j) {
            if (!t.assentos[i][j].reservado) {
                if (consecutivosDisponiveis == 0) {
                    inicioIntervalo = j;
                }
                ++consecutivosDisponiveis;
            } else {
                if (consecutivosDisponiveis >= n) {
                    printf("Fileira %c, Assentos de %d a %d\n", 'A' + i, inicioIntervalo, inicioIntervalo + consecutivosDisponiveis - 1);
                }
                consecutivosDisponiveis = 0;
                inicioIntervalo = -1;
            }
        }

        if (consecutivosDisponiveis >= n) {
            printf("Fileira %c, Assentos de %d a %d\n", 'A' + i, inicioIntervalo, inicioIntervalo + consecutivosDisponiveis - 1);
        }
    }

    printf("\n");
}

void exibirInformacoes(struct Teatro t) {
    int reservas = 0;
    int espacosLivres = 0;
    int maiorSequenciaLivre = 0;
    int sequenciaAtual = 0;

    for (int i = 0; i < t.numFileiras; ++i) {
        for (int j = 0; j < t.numAssentosPorFileira; ++j) {
            if (t.assentos[i][j].reservado) {
                ++reservas;
                sequenciaAtual = 0;
            } else {
                ++espacosLivres;
                ++sequenciaAtual;
                if (sequenciaAtual > maiorSequenciaLivre) {
                    maiorSequenciaLivre = sequenciaAtual;
                }
            }
        }
    }

    printf("Informações sobre as reservas:\n");
    printf("Número total de reservas: %d\n", reservas);
    printf("Número total de espaços livres: %d\n", espacosLivres);
    printf("Maior sequência livre de assentos: %d\n", maiorSequenciaLivre);
    printf("\n");
}

int salvarEstado(struct Teatro t, char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 0;
    }

    fprintf(arquivo, "%d %d\n", t.numFileiras, t.numAssentosPorFileira);

    for (int i = 0; i < t.numFileiras; ++i) {
        for (int j = 0; j < t.numAssentosPorFileira; ++j) {
            fprintf(arquivo, "%d %d %d %s\n", t.assentos[i][j].reservado, t.assentos[i][j].fileira, t.assentos[i][j].numero, t.assentos[i][j].nomeCompleto);
        }
    }

    fclose(arquivo);
    return 1;
}

struct Teatro carregarEstado(char *nomeArquivo) {
    struct Teatro teatro;
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        teatro.numFileiras = 0;
        teatro.numAssentosPorFileira = 0;
        return teatro;
    }

    fscanf(arquivo, "%d %d\n", &teatro.numFileiras, &teatro.numAssentosPorFileira);
    teatro.assentos = inicializarMatriz(teatro.numFileiras, teatro.numAssentosPorFileira);

    for (int i = 0; i < teatro.numFileiras; ++i) {
        for (int j = 0; j < teatro.numAssentosPorFileira; ++j) {
            fscanf(arquivo, "%d %d %d %s\n", &teatro.assentos[i][j].reservado, &teatro.assentos[i][j].fileira, &teatro.assentos[i][j].numero, teatro.assentos[i][j].nomeCompleto);
        }
    }

    fclose(arquivo);
    return teatro;
}
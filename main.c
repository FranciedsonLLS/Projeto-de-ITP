#include "teatro.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Teatro teatro;
    int opcao, linha, coluna, n;
    char nome[MAX_NOME_COMPLETO], nomeArquivo[100];

    printf("Informe o número de fileiras e assentos por fileira: ");
    scanf("%d %d", &teatro.numFileiras, &teatro.numAssentosPorFileira);

    teatro.assentos = inicializarMatriz(teatro.numFileiras, teatro.numAssentosPorFileira);

    do {
        printf("\nOpções:\n");
        printf("0 - Sair do programa\n");
        printf("1 - Salvar estado\n");
        printf("2 - Carregar estado\n");
        printf("3 - Visualizar\n");
        printf("4 - Reservar assento específico\n");
        printf("5 - Reservar assentos consecutivos específicos\n");
        printf("6 - Reservar assento pelo sistema\n");
        printf("7 - Reservar assentos consecutivos pelo sistema\n");
        printf("8 - Cancelar reserva de um assento\n");
        printf("9 - Cancelar reservas de uma pessoa\n");
        printf("10 - Cancelar todas as reservas\n");
        printf("11 - Verificar disponibilidade\n");
        printf("12 - Consultar assentos consecutivos\n");
        printf("13 - Exibir informações\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("Programa encerrado.\n");
                break;

            case 1:
                printf("Informe o nome do arquivo para salvar o estado: ");
                scanf("%s", nomeArquivo);
                if (salvarEstado(teatro, nomeArquivo)) {
                    printf("Estado salvo com sucesso.\n");
                } else {
                    printf("Erro ao salvar o estado.\n");
                }
                break;

            case 2:
                printf("Informe o nome do arquivo para carregar o estado: ");
                scanf("%s", nomeArquivo);
                teatro = carregarEstado(nomeArquivo);
                if (teatro.numFileiras > 0 && teatro.numAssentosPorFileira > 0) {
                    printf("Estado carregado com sucesso.\n");
                } else {
                    printf("Erro ao carregar o estado.\n");
                }
                break;

            case 3:
                exibirTeatro(teatro);
                break;

            case 4:
                printf("Informe a linha, coluna e nome para reservar o assento: ");
                scanf("%d %d %s", &linha, &coluna, nome);
                if (reservarAssento(teatro, linha, coluna, nome)) {
                    printf("Assento reservado com sucesso.\n");
                } else {
                    printf("Erro ao reservar o assento.\n");
                }
                break;

            case 5:
                printf("Informe a linha, coluna, número de assentos consecutivos e nome para reservar: ");
                scanf("%d %d %d %s", &linha, &coluna, &n, nome);
                if (reservarAssentosConsecutivos(teatro, linha, coluna, n, nome)) {
                    printf("%d assentos consecutivos reservados com sucesso.\n", n);
                } else {
                    printf("Erro ao reservar assentos consecutivos.\n");
                }
                break;

            case 6:
                printf("Informe o nome para reservar um assento pelo sistema: ");
                scanf("%s", nome);
                Assento *assento = reservarAssentoPeloSistema(teatro, nome);
                if (assento != NULL) {
                    printf("Assento reservado com sucesso: [%c][%d]\n", 'A' + assento->fileira, assento->numero);
                } else {
                    printf("Erro ao reservar assento pelo sistema.\n");
                }
                break;

            case 7:
                printf("Informe o número de assentos consecutivos e o nome para reservar pelo sistema: ");
                scanf("%d %s", &n, nome);
                Assento **assentosReservados = reservarAssentosConsecutivosPeloSistema(teatro, n, nome);
                if (assentosReservados != NULL) {
                    printf("%d assentos consecutivos reservados pelo sistema com sucesso.\n", n);
                    for (int i = 0; i < n; ++i) {
                        printf("[%c][%d] ", 'A' + assentosReservados[i]->fileira, assentosReservados[i]->numero);
                    }
                    printf("\n");
                    free(assentosReservados);
                } else {
                    printf("Erro ao reservar assentos consecutivos pelo sistema.\n");
                }
                break;

            case 8:
                printf("Informe a linha e coluna para cancelar a reserva do assento: ");
                scanf("%d %d", &linha, &coluna);
                if (cancelarReserva(teatro, linha, coluna)) {
                    printf("Reserva cancelada com sucesso.\n");
                } else {
                    printf("Erro ao cancelar a reserva.\n");
                }
                break;

            case 9:
                printf("Informe o nome para cancelar as reservas da pessoa: ");
                scanf("%s", nome);
                int reservasCanceladas = cancelarReservas(teatro, nome);
                printf("%d reservas canceladas.\n", reservasCanceladas);
                break;

            case 10:
                printf("Cancelando todas as reservas...\n");
                int totalCancelado = cancelarTodasAsReservas(teatro);
                printf("%d reservas canceladas.\n", totalCancelado);
                break;

            case 11:
                printf("Informe a linha e coluna para verificar disponibilidade: ");
                scanf("%d %d", &linha, &coluna);
                if (verificarDisponibilidade(teatro, linha, coluna)) {
                    printf("O assento está disponível.\n");
                } else {
                    printf("O assento está reservado.\n");
                }
                break;

            case 12:
                printf("Informe o número mínimo de assentos para consultar assentos consecutivos: ");
                scanf("%d", &n);
                consultarAssentosConsecutivos(teatro, n);
                break;

            case 13:
                exibirInformacoes(teatro);
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    liberarMatriz(teatro.assentos, teatro.numFileiras);

    return 0;
}

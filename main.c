#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Musica {
    char artista[100];
    char nome[100];
    struct Musica *ant;
    struct Musica *prox;
} Musica;



void Menu() {
    printf("\nMenu:\n");
    printf("1. Exibir playlist pela ordem de cadastro\n");
    printf("2. Exibir playlist ordenada pelo nome das músicas\n");
    printf("3. Inserir nova música\n");
    printf("4. Remover uma música\n");
    printf("5. Buscar por uma música\n");
    printf("6. Avançar para próxima música\n");
    printf("7. Retornar à música anterior\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    Musica* playlist = NULL;
    Musica* atual = NULL;

    carregarArquivo(&playlist, "musicas.txt");
    atual = playlist;

    int opcao;
    do {
        Menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirPlaylist(playlist);
                break;
            case 2:
                exibirPlaylistOrdenada(playlist);
                break;
            case 3:
                inserirNovaMusica(&playlist);
                break;
            case 4:
                removerMusica(&playlist);
                break;
            case 5:
                buscarMusica(playlist);
                break;
            case 6:
                avancarMusica(&atual);
                break;
            case 7:
                retornarMusica(&atual);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);


    return 0;
}

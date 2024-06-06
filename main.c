#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Musica {
    char artista[100];
    char nome[100];
    struct Musica *prev;
    struct Musica *next;
} Musica;

Musica* criarNo(char* artista, char* nome) {
    Musica* novoNo = (Musica*)malloc(sizeof(Musica));
    strcpy(novoNo->artista, artista);
    strcpy(novoNo->nome, nome);
    novoNo->prev = novoNo->next = novoNo;
    return novoNo;
}

void inserirNo(Musica** head, char* artista, char* nome) {
    Musica* novoNo = criarNo(artista, nome);
    if (*head == NULL) {
        *head = novoNo;
    } else {
        Musica* tail = (*head)->prev;
        tail->next = novoNo;
        novoNo->prev = tail;
        novoNo->next = *head;
        (*head)->prev = novoNo;
    }
}

void salvarArquivo(Musica* head, const char* musicas) {
    FILE* file = fopen("musicas.txt", "w");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    if (!head) return;
    Musica* atual = head;
    do {
        fprintf(file, "%s;%s\n", atual->artista, atual->nome);
        atual = atual->next;
    } while (atual != head);
    fclose(file);
}

void carregarArquivo(Musica** head, const char* musicas) {
    FILE* file = fopen("musicas.txt", "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        char* artista = strtok(linha, ";");
        char* nome = strtok(NULL, "\n");
        if (artista && nome) {
            inserirNo(head, artista, nome);
        }
    }
    fclose(file);
}

void exibirPlaylist(Musica* head) {
    if (!head) return;
    Musica* atual = head;
    do {
        printf("Artista: %s, Música: %s\n", atual->artista, atual->nome);
        atual = atual->next;
    } while (atual != head);
}

void exibirPlaylistOrdenada(Musica* head) {
    if (!head) return;
    int count = 0;
    Musica* atual = head;
    do {
        count++;
        atual = atual->next;
    } while (atual != head);

    Musica** array = (Musica**)malloc(count * sizeof(Musica*));
    atual = head;
    for (int i = 0; i < count; i++) {
        array[i] = atual;
        atual = atual->next;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(array[i]->nome, array[j]->nome) > 0) {
                Musica* temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
    for (int i = 0; i < count; i++) {
        printf("Artista: %s, Música: %s\n", array[i]->artista, array[i]->nome);
    }

    free(array);
}

void inserirNovaMusica(Musica** head) {
    char artista[100];
    char nome[100];
    printf("Digite o nome do artista: ");
    scanf("%s", artista);
    printf("Digite o nome da música: ");
    scanf("%s", nome);
    inserirNo(head, artista, nome);
    salvarArquivo(*head, "musicas.txt");
}

void removerMusica(Musica** head) {
    char nome[100];
    printf("Digite o nome da música a ser removida: ");
    scanf("%s", nome);
    if (!head || !(*head)) return;
    Musica* atual = *head;
    do {
        if (strcmp(atual->nome, nome) == 0) {
            if (atual->next == atual) {
                free(atual);
                *head = NULL;
            } else {
                atual->prev->next = atual->next;
                atual->next->prev = atual->prev;
                if (*head == atual) *head = atual->next;
                free(atual);
            }
            printf("Música removida.\n");
            salvarArquivo(*head, "musicas.txt");
            return;
        }
        atual = atual->next;
    } while (atual != *head);
    printf("Música não encontrada.\n");
}

void buscarMusica(Musica* head) {
    char nome[100];
    printf("Digite o nome da música: ");
    scanf("%s", nome);
    if (!head) return;
    Musica* atual = head;
    do {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Artista: %s, Música: %s\n", atual->artista, atual->nome);
            return;
        }
        atual = atual->next;
    } while (atual != head);
    printf("Musica não encontrada.\n");
}

void avancarMusica(Musica** atual) {
    if (*atual) {
        *atual = (*atual)->next;
        printf("=======================================");
        printf("\nTocando agora: Artista: %s\n Música: %s\n", (*atual)->artista, (*atual)->nome);
        printf("=======================================");
    }
}

void retornarMusica(Musica** atual) {
    if (*atual) {
        *atual = (*atual)->prev;
        printf("=======================================");
        printf("\nTocando agora: Artista: %s\n Música: %s\n", (*atual)->artista, (*atual)->nome);
        printf("=======================================");
    }
}

void exibirMenu() {
    printf("\nMenu:\n");
    printf("\nEscolha uma opção: \n");
    printf("1. Exibir playlist pela ordem de cadastro\n");
    printf("2. Exibir playlist ordenada pelo nome das musicas\n");
    printf("3. Inserir nova musica\n");
    printf("4. Remover uma musica\n");
    printf("5. Buscar por uma musica\n");
    printf("6. Avançar para proxima musica\n");
    printf("7. Retornar a musica anterior\n");
    printf("0. Sair\n");
}

int main() {
    Musica* playlist = NULL;
    Musica* atual = NULL;

    carregarArquivo(&playlist, "musicas.txt");
    atual = playlist;

    int opcao;
    do {
        exibirMenu();
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

    if (playlist) {
        Musica* start = playlist;
        Musica* atual = playlist;
        do {
            Musica* proximo = atual->next;
            free(atual);
            atual = proximo;
        } while (atual != start);
    }

    return 0;
}

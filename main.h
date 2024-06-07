#ifndef MUSICA_H
#define MUSICA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Musica {
    char cantor[100];
    char nome[100];
    struct Musica *prev;
    struct Musica *next;
} Musica;

Musica* criarNo(char* artista, char* nome);
void inserirNo(Musica** head, char* artista, char* nome);
void salvarArquivo(Musica* head, const char* musicas);
void carregarArquivo(Musica** head, const char* musicas);
void exibirPlaylist(Musica* head);
void exibirPlaylistOrdenada(Musica* head);
void inserirNovaMusica(Musica** head);
void removerMusica(Musica** head);
void buscarMusica(Musica* head);
void avancarMusica(Musica** atual);
void retornarMusica(Musica** atual);
void exibirMenu();

#endif 

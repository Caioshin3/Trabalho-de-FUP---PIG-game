#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

#define MAX_PLAYERS 100

typedef struct
{
    char nome[50];
    int Dado_Player;
    int Dado_Player_2;
    int Resultado_Player;
    int Resultado_Def_Player;
} Player;

typedef struct
{
    int Dado_PC;
    int Dado_PC_2;
    int Resultado_PC;
    int Resultado_Def_PC;
} PC;

typedef struct
{
    char nome[50];
    int jogadas;
    int vitorias;
    double taxa_vitoria_por_jogada;
} Lista_Jogadores;

void Menu();
void Menu_Login(int, Player *, int *, int *);
void Cadastro(Player *, int *, int *, int);
void Login(int, Player *, int *, int *);
void Lancar_Dado(Player *, PC *, int *, int *);
void Lancar_Dado_PC(PC *, Player *);
void Segurar_Dado(Player *);
void Lancar_Dois_Dados(Player *, PC *, int *, int *);
void Lancar_Dois_Dado_PC(PC *, Player *);
int compararRanking(const void *, const void *);
void CalcularTaxaVitoriaPorJogada(Lista_Jogadores *);
void Mostrar_Ranking();
void Atualizar_Ranking(Player *, int *, int *);
void Zerar_Dados(Player *, PC *);
void Dificuldade(int *);

#endif
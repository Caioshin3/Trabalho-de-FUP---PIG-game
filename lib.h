#ifndef LIB_H
#define LIB_H

// Inclusão das bibliotecas nativas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

// Definição de constante para o número máximo de jogadores
#define MAX_PLAYERS 100

// Definição de estruturas

// Estrutura para armazenar informações do jogador
typedef struct
{
    char nome[50];
    int Dado_Player;
    int Dado_Player_2;
    int Resultado_Player;
    int Resultado_Def_Player;
} Player;

// Estrutura para armazenar informações do computador
typedef struct
{
    int Dado_PC;
    int Dado_PC_2;
    int Resultado_PC;
    int Resultado_Def_PC;
} PC;

// Estrutura para armazenar informações da lista de jogadores
typedef struct
{
    char nome[50];
    int jogadas;
    int vitorias;
    double taxa_vitoria_por_jogada;
} Lista_Jogadores;

// Protótipos de funções

// Exibe o menu principal
void Menu();

// Exibe o menu de login
void Menu_Login(int, Player *, int *, int *);

// Realiza o cadastro de jogadores
void Cadastro(Player *, int *, int *, int);

// Realiza o login de jogadores
void Login(int, Player *, int *, int *);

// Realiza o lançamento do dado pelo jogador
void Lancar_Dado(Player *, PC *, int *, int *);

// Realiza o lançamento do dado pelo computador
void Lancar_Dado_PC(PC *, Player *);

// Atualiza os resultados após o jogador decidir segurar o dado
void Segurar_Dado(Player *);

// Realiza o lançamento de dois dados pelo jogador
void Lancar_Dois_Dados(Player *, PC *, int *, int *);

// Realiza o lançamento de dois dados pelo computador
void Lancar_Dois_Dado_PC(PC *, Player *);

// Função de comparação utilizada para ordenar o ranking
int compararRanking(const void *, const void *);

// Calcula a taxa de vitória por jogada para um jogador
void CalcularTaxaVitoriaPorJogada(Lista_Jogadores *);

// Exibe o ranking dos jogadores
void Mostrar_Ranking();

// Atualiza as informações no arquivo de ranking
void Atualizar_Ranking(Player *, int *, int *);

// Zera os dados dos jogadores e do computador
void Zerar_Dados(Player *, PC *);

// Define a dificuldade do jogo
void Dificuldade(int *);

#endif

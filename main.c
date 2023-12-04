// lib.h

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

void Menu_Login(int, Player *, int *, int *, int *);
void Cadastro(Player *, int *, int *, int *);
void Login(Player *, int *, int *, int *);
void Lancar_Dado(Player *, PC *, int *, int, int *);
void Lancar_Dado_PC(PC *, Player *);
void Segurar_Dado(Player *);
void Lancar_Dois_Dados(Player *, PC *, int *, int *);
void Lancar_Dois_Dado_PC(PC *, Player *);
void Criar_Ranking(Player *, int *, int *, int *);
void Atualizar_Ranking(Player *, int *, int *);
int Jogador_Existente_Ranking(Player *player, int *victory, int *num_jogadores);
void Mostrar_Ranking();
void Zerar_Dados(Player *, PC *);
void Dificuldade(int *);

// main.c

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao, dificuldade = 1, continuar_jogo = 1, vitoria = 0, Dev = 0, cont_jogadas = 0, num_jogadores = 0;
    Player player;
    PC computador;

    player.Resultado_Player = 0;
    player.Resultado_Def_Player = 0;
    computador.Resultado_PC = 0;
    computador.Resultado_Def_PC = 0;

    srand(time(NULL));

    Menu_Login(opcao, &player, &num_jogadores, &vitoria, &cont_jogadas);

    while (continuar_jogo)
    {
        int Soma_Resultado_Def = player.Resultado_Player + player.Resultado_Def_Player;

        if (player.Dado_Player != 1)
        {
            printf("Rodada: Player %d - PC %d\n", Soma_Resultado_Def, computador.Resultado_Def_PC);
            printf("Quantidade de jogadas: %d\n", cont_jogadas);
            printf("Vitorias: %d\n", vitoria);
        }
        else
        {
            printf("Rodada: Player %d - PC %d\n", player.Resultado_Def_Player, computador.Resultado_Def_PC);
            printf("Vitórias: %d\n", vitoria);
        }

        if (computador.Resultado_Def_PC < 100 && player.Resultado_Def_Player < 100)
        {
            printf("1. Lançar o dado\n2. Segurar\n3. Alterar Dificuldade\n4. Mostrar Ranking\n5. Icarus Mode\n6. Encerrar o jogo\n");
            scanf("%d", &opcao);
            getchar();
            system("cls");
        }

        switch (opcao)
        {
        case 1:
            if (dificuldade == 1)
            {
                Lancar_Dado(&player, &computador, &vitoria, Dev, &cont_jogadas);
            }
            if (dificuldade == 2)
            {
                Lancar_Dois_Dados(&player, &computador, &cont_jogadas, &vitoria);
            }
            break;
        case 2:
            Segurar_Dado(&player);
            if (dificuldade == 1)
            {
                Lancar_Dado_PC(&computador, &player);
            }
            if (dificuldade == 2)
            {
                Lancar_Dois_Dado_PC(&computador, &player);
            }
            break;
        case 3:
            Dificuldade(&dificuldade);
            break;
        case 4:
            Mostrar_Ranking();
            break;
        case 5:
            printf("Red Bull te dá asas!\n");
            Dev = 1;
            break;
        case 6:
            printf("Encerrando o jogo...\n");
            continuar_jogo = 0;
            break;

        default:
            printf("Operação inválida!\n");
            break;
        }
    }

    return 0;
}

// modulo.c

void Menu_Login(int opcao, Player *players, int *num_jogadores, int *victory, int *cont_jogadas)
{
    printf("1. Registrar novo jogador\n2. Login\n");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        Cadastro(players, num_jogadores, victory, cont_jogadas);
        break;
    case 2:
        Login(players, num_jogadores, victory, cont_jogadas);
        break;

    default:
        printf("Opção inválida!\n");
        break;
    }
}

void Cadastro(Player *players, int *num_jogadores, int *victory, int *cont_jogadas)
{
    int cont = 0;
    char linha[100];
    
    FILE *arquivo_ranking = fopen("./arquivo_ranking.txt", "a+");
    
     while (fgets(linha, sizeof(linha), arquivo_ranking)!=NULL){
        cont++;    
     }
     
     if(cont<=MAX_PLAYERS){
        printf("Informe o nome do jogador: ");
        scanf("%s", players->nome);
        system("cls");
        printf("Novo jogador cadastrado!\n");
        
        fprintf(arquivo_ranking, "%s,", players->nome);
        fprintf(arquivo_ranking, "%d,", *cont_jogadas);
        fprintf(arquivo_ranking, "%d,\n", *victory);
        
        fclose(arquivo_ranking);
    }
    else{
     printf("Numero maximo de Jogadores atingido\n\n");
     fclose(arquivo_ranking);
     exit(0);
    }
}

void Login(Player *players, int *num_jogadores, int *victory, int *cont_jogadas)
{
    FILE *arquivo_ranking = fopen("arquivo_ranking.txt", "r");

    char nome[50];
    char linha[100];
    int jogador_existente = 0;
    int verificar = 0;

        printf("Informe o nome do jogador: ");
        scanf("%s", players->nome);
        system("cls");
        while (fgets(linha, sizeof(linha), arquivo_ranking)!=NULL)
        {
           sscanf(linha, "%[^,],%d,%d",nome,&*cont_jogadas,&*victory);
            if (strcmp(nome, players->nome) == 0)
            {
                verificar = 1;
                fclose(arquivo_ranking);
            }
        }
    if(verificar == 0)
    {
        printf("Usuario não encontrado!\n");
        fclose(arquivo_ranking);
        
    }
}

void Lancar_Dado(Player *player, PC *computador, int *victory, int dev, int *jogadas)
{
    if (dev == 1)
    {
        player->Dado_Player = 2 + rand() % (6 - 2 + 1);
    }
    else
    {
        player->Dado_Player = 1 + (rand() % 6);
    }

    if (player->Dado_Player == 1)
    {
        printf("Você tirou 1! Perdeu os pontos da rodada.\n");
        player->Resultado_Player = 0;
        Lancar_Dado_PC(computador, player);
    }
    else
    {
        player->Resultado_Player += player->Dado_Player;

        if (player->Dado_Player > 6)
        {
            printf("Você tirou 1! Perdeu os pontos da rodada.\n");
            player->Resultado_Player = 0;
            return;
        }

        printf("Você tirou %d\n", player->Dado_Player);
        (*jogadas)++;
        Atualizar_Ranking(player, jogadas, victory);

        if (player->Resultado_Player > 0)
        {
            player->Resultado_Def_Player += player->Resultado_Player;
        }

        if (player->Resultado_Def_Player >= 100)
        {
            system("cls");
            printf("%s ganhou!\n", player->nome);
            Zerar_Dados(player, computador);
            (*victory)++;
        }
        else
        {
            player->Resultado_Def_Player = player->Resultado_Def_Player - player->Resultado_Player;
        }
    }
}

void Segurar_Dado(Player *player)
{
    player->Resultado_Def_Player += player->Resultado_Player;
    player->Resultado_Player = 0;
}

void Lancar_Dado_PC(PC *computador, Player *player)
{
    printf("Vez do Computador\n");

    while (computador->Resultado_PC < 100)
    {
        computador->Dado_PC = 1 + (rand() % 20);

        if (computador->Dado_PC > 6)
        {
            computador->Dado_PC = 2 + rand() % (6 - 2 + 1);
        }

        if (computador->Dado_PC == 1)
        {
            printf("Computador tirou 1! Perdeu os pontos da rodada.\n");
            computador->Resultado_PC = 0;
            break;
        }
        else
        {
            computador->Resultado_PC += computador->Dado_PC;

            printf("Computador tirou %d\n", computador->Dado_PC);

            if (computador->Resultado_Def_PC >= 100)
            {
                system("cls");
                printf("Computador ganhou!\n");
                Zerar_Dados(player, computador);
                break;
            }

            if (computador->Resultado_PC >= 20)
            {
                printf("O computador decidiu parar\n");
                computador->Resultado_Def_PC += computador->Resultado_PC;
                computador->Resultado_PC = 0;
                break;
            }
        }
    }
}

void Lancar_Dois_Dados(Player *player, PC *computador, int *cont_jogadas, int *victory)
{

    player->Dado_Player = 1 + (rand() % 6);
    player->Dado_Player_2 = 1 + (rand() % 6);

    if (player->Dado_Player == 1 || player->Dado_Player_2 == 1)
    {
        printf("Você tirou 1! Perdeu os pontos da rodada.\n");
        player->Resultado_Player = 0;
        Lancar_Dois_Dado_PC(computador, player);
    }
    else
    {
        player->Resultado_Player += player->Dado_Player;
        player->Resultado_Player += player->Dado_Player_2;

        printf("Você tirou %d e %d\n", player->Dado_Player, player->Dado_Player_2);
        (*cont_jogadas)++;
        Atualizar_Ranking(player, cont_jogadas, victory);

        if (player->Resultado_Player > 0)
        {
            player->Resultado_Def_Player += player->Resultado_Player;
        }

        if (player->Resultado_Def_Player >= 100)
        {
            system("cls");
            printf("Player ganhou!\n");
            (*victory)++;
            Zerar_Dados(player, computador);
        }
        else
        {
            player->Resultado_Def_Player = player->Resultado_Def_Player - player->Resultado_Player;
        }
    }
}

void Lancar_Dois_Dado_PC(PC *computador, Player *player)
{
    printf("Vez do Computador\n");

    while (computador->Resultado_PC < 100)
    {
        computador->Dado_PC = 1 + (rand() % 20);
        computador->Dado_PC_2 = 1 + (rand() % 20);

        if (computador->Dado_PC > 6 || computador->Dado_PC_2 > 6)
        {
            computador->Dado_PC = 2 + rand() % (6 - 2 + 1);
            computador->Dado_PC_2 = 2 + rand() % (6 - 2 + 1);
        }

        if (computador->Dado_PC == 1 || computador->Dado_PC_2 == 1)
        {
            printf("Computador tirou 1! Perdeu os pontos da rodada.\n");
            computador->Resultado_PC = 0;
            break;
        }
        else
        {
            computador->Resultado_PC += computador->Dado_PC;
            computador->Resultado_PC += computador->Dado_PC_2;

            printf("Computador tirou %d e %d\n", computador->Dado_PC, computador->Dado_PC_2);

            if (computador->Resultado_Def_PC >= 100)
            {
                system("cls");
                printf("Computador ganhou!\n");
                Zerar_Dados(player, computador);
                break;
            }

            if (computador->Resultado_PC >= 20)
            {
                printf("O computador decidiu parar\n");
                computador->Resultado_Def_PC += computador->Resultado_PC;
                computador->Resultado_PC = 0;
                break;
            }
        }
    }
}

void Criar_Ranking(Player *players, int *victory, int *cont_jogadas, int *num_jogadores)
{
    FILE *arquivo_ranking = fopen("./arquivo_ranking.txt", "a");

    if (arquivo_ranking != NULL)
    {
        fprintf(arquivo_ranking, "%s,", players->nome);
        fprintf(arquivo_ranking, "%d,", *cont_jogadas);
        fprintf(arquivo_ranking, "%d\n", *victory);
    }
    else
    {
        printf("ERRO AO CRIAR O ARQUIVO!");
    }

    fclose(arquivo_ranking);
}

void Atualizar_Ranking(Player *player, int *cont_jogadas, int *victory)
{
    FILE *arquivo_ranking_temp = fopen("./arquivo_ranking_temp.txt", "w+");
    FILE *arquivo_ranking = fopen("./arquivo_ranking.txt", "r");
    
    char nome[50];
    int jogadas, vitorias;
    char linha[100];
    
    while(fgets(linha, sizeof(linha), arquivo_ranking) != NULL)
    {
       sscanf(linha, "%[^,],%d,%d", nome, &jogadas, &vitorias);
      
      if(strcmp(nome, player->nome) == 0)
      {
        fprintf(arquivo_ranking_temp, "%s,%d,%d\n", player->nome, *cont_jogadas, *victory);
      }
      else
      {
        fprintf(arquivo_ranking_temp, "%s,%d,%d\n", nome, jogadas, vitorias);
      }
    }
    
    fclose(arquivo_ranking_temp);
    fclose(arquivo_ranking);
    
    remove("./arquivo_ranking.txt");
    rename("./arquivo_ranking_temp.txt", "./arquivo_ranking.txt");
}

// erro na lógica da função

int Jogador_Existente_Ranking(Player *player, int *victory, int *num_jogadores)
{
    FILE *arquivo_ranking = fopen("./arquivo_ranking.txt", "r");

    char nome[50];
    int jogador_existente = 0;

    if (arquivo_ranking != NULL)
    {
        while (fscanf(arquivo_ranking, "%[^,]\n", nome) != EOF)
        {
            if (strcmp(player->nome, nome) == 0)
            {
                jogador_existente = 1;
                break;
            }
        }
    }
    else
    {
        printf("ERRO AO VERIFICAR EXISTÊNCIA DO JOGADOR!\n");
    }

    fclose(arquivo_ranking);
    return jogador_existente;
}

void Mostrar_Ranking()
{
    FILE *arquivo_ranking = fopen("./arquivo_ranking.txt", "r");

    if (arquivo_ranking != NULL)
    {
        char conteudo[100];

        while (fgets(conteudo, 100, arquivo_ranking) != NULL)
        {
            printf("%s", conteudo);
        }

        getchar();
        system("cls");
    }
    else
    {
        printf("ERRO AO VISUALIZAR O ARQUIVO!\n");
    }

    fclose(arquivo_ranking);
}

void Zerar_Dados(Player *player, PC *computador)
{
    computador->Resultado_Def_PC = 0;
    player->Resultado_Def_Player = 0;
    player->Resultado_Player = 0;
    computador->Resultado_PC = 0;
    player->Dado_Player = 0;
    computador->Dado_PC = 0;
}

void Dificuldade(int *dificuldade)
{

    printf("1. Fácil\n2. Difícil\n");
    scanf("%d", &*dificuldade);
    system("cls");

    switch (*dificuldade)
    {
    case 1:
        printf("Modo Fácil\n");
        break;
    case 2:
        printf("Modo Difícil\n");
        break;

    default:
        printf("Opção inválida");
        break;
    }
}
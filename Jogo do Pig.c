#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    int Dado_Player;
    int Dado_Player_2;
    int Dado_PC;
    int Dado_PC_2;
} Dado;

typedef struct
{
    char nome[50];
    int Resultado_Player;
    int Resultado_PC;
} Resultado;

typedef struct
{
    int Resultado_Def_Player;
    int Resultado_Def_PC;
} Definitivo;

void Login(Resultado *, int *);
void Lancar_Dado(Dado *, Resultado *, Definitivo *, int *, int);
void Lancar_Dado_PC(Dado *, Resultado *, Definitivo *);
void Segurar_Dado(Dado *, Resultado *, Definitivo *);
void Lancar_Dois_Dados(Dado *, Resultado *, Definitivo *);
void Lancar_Dois_Dado_PC(Dado *, Resultado *, Definitivo *);
void Criar_Ranking(Resultado *, int *, int *);
int Jogador_Existente_Ranking(Resultado *, int *, int *);
void Mostrar_Ranking(Resultado *, int *);
void Zerar_Dados(Dado *, Resultado *, Definitivo *);
void Dificuldade(int *);

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao, dificuldade = 1, continuar_jogo = 1, vitoria = 0, Dev = 0, cont_user = 0;
    Dado dado;
    Resultado resultado = {0, 0};
    Definitivo resultado_definitivo = {0, 0};

    srand(time(NULL));

    while (continuar_jogo)
    {
        Login(&resultado, &cont_user);
        Criar_Ranking(&resultado, &vitoria, &cont_user);

        int Soma_Resultado_Def = resultado.Resultado_Player + resultado_definitivo.Resultado_Def_Player;

        if (dado.Dado_Player != 1)
        {
            printf("Rodada: %s %d - PC %d\n", resultado.nome, Soma_Resultado_Def, resultado_definitivo.Resultado_Def_PC);
            printf("Usuários cadastrados: %d\n", cont_user);
            printf("Vitorias: %d\n", vitoria);
        }
        else
        {
            printf("Rodada: %s %d - PC %d\n", resultado.nome, resultado_definitivo.Resultado_Def_Player, resultado_definitivo.Resultado_Def_PC);
            printf("Vitórias: %d\n", vitoria);
        }

        if (resultado_definitivo.Resultado_Def_PC < 100 && resultado_definitivo.Resultado_Def_Player < 100)
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
                Lancar_Dado(&dado, &resultado, &resultado_definitivo, &vitoria, Dev);
            }
            if (dificuldade == 2)
            {
                Lancar_Dois_Dados(&dado, &resultado, &resultado_definitivo);
            }
            break;
        case 2:
            Segurar_Dado(&dado, &resultado, &resultado_definitivo);
            if (dificuldade == 1)
            {
                Lancar_Dado_PC(&dado, &resultado, &resultado_definitivo);
            }
            if (dificuldade == 2)
            {
                Lancar_Dois_Dado_PC(&dado, &resultado, &resultado_definitivo);
            }
            break;
        case 3:
            Dificuldade(&dificuldade);
            break;
        case 4:
            Mostrar_Ranking(&resultado, &vitoria);
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

void Login(Resultado *nome, int *cont)
{
    if (strcmp(nome->nome, "") == 0)
    {
        printf("Informe o nome do jogador: ");
        scanf("%s", &nome->nome);
        system("cls");
        (*cont)++;
    }
}

void Lancar_Dado(Dado *dado, Resultado *resultado, Definitivo *resultado_definitivo, int *victory, int dev)
{
    if (dev == 1)
    {
        dado->Dado_Player = 2 + rand() % (6 - 2 + 1);
    }
    else
    {
        dado->Dado_Player = 1 + (rand() % 6);
    }

    if (dado->Dado_Player == 1)
    {
        printf("Você tirou 1! Perdeu os pontos da rodada.\n");
        resultado->Resultado_Player = 0;
        Lancar_Dado_PC(dado, resultado, resultado_definitivo);
    }
    else
    {
        resultado->Resultado_Player += dado->Dado_Player;

        if (dado->Dado_Player > 6)
        {
            printf("Você tirou 1! Perdeu os pontos da rodada.\n");
            resultado->Resultado_Player = 0;
            return;
        }

        printf("Você tirou %d\n", dado->Dado_Player);

        if (resultado->Resultado_Player > 0)
        {
            resultado_definitivo->Resultado_Def_Player += resultado->Resultado_Player;
        }

        if (resultado_definitivo->Resultado_Def_Player >= 100)
        {
            system("cls");
            printf("%s ganhou!\n", resultado->nome);
            Zerar_Dados(dado, resultado, resultado_definitivo);
            (*victory)++;
        }
        else
        {
            resultado_definitivo->Resultado_Def_Player = resultado_definitivo->Resultado_Def_Player - resultado->Resultado_Player;
        }
    }
}

void Segurar_Dado(Dado *dado, Resultado *resultado, Definitivo *resultado_definitivo)
{
    resultado_definitivo->Resultado_Def_Player += resultado->Resultado_Player;
    resultado->Resultado_Player = 0;
}

void Lancar_Dado_PC(Dado *dado, Resultado *resultado, Definitivo *resultado_definitivo)
{
    printf("Vez do Computador\n");

    while (resultado->Resultado_PC < 100)
    {
        dado->Dado_PC = 1 + (rand() % 20);

        if (dado->Dado_PC > 6)
        {
            dado->Dado_PC = 2 + rand() % (6 - 2 + 1);
        }

        if (dado->Dado_PC == 1)
        {
            printf("Computador tirou 1! Perdeu os pontos da rodada.\n");
            resultado->Resultado_PC = 0;
            break;
        }
        else
        {
            resultado->Resultado_PC += dado->Dado_PC;

            printf("Computador tirou %d\n", dado->Dado_PC);

            if (resultado_definitivo->Resultado_Def_PC >= 100)
            {
                system("cls");
                printf("Computador ganhou!\n");
                Zerar_Dados(dado, resultado, resultado_definitivo);
                break;
            }

            if (resultado->Resultado_PC >= 20)
            {
                printf("O computador decidiu parar\n");
                resultado_definitivo->Resultado_Def_PC += resultado->Resultado_PC;
                resultado->Resultado_PC = 0;
                break;
            }
        }
    }
}

void Lancar_Dois_Dados(Dado *dado, Resultado *resultado, Definitivo *resultado_definitivo)
{

    dado->Dado_Player = 1 + (rand() % 6);
    dado->Dado_Player_2 = 1 + (rand() % 6);

    if (dado->Dado_Player == 1 || dado->Dado_Player_2 == 1)
    {
        printf("Você tirou 1! Perdeu os pontos da rodada.\n");
        resultado->Resultado_Player = 0;
        Lancar_Dois_Dado_PC(dado, resultado, resultado_definitivo);
    }
    else
    {
        resultado->Resultado_Player += dado->Dado_Player;
        resultado->Resultado_Player += dado->Dado_Player_2;

        printf("Você tirou %d e %d\n", dado->Dado_Player, dado->Dado_Player_2);

        if (resultado->Resultado_Player > 0)
        {
            resultado_definitivo->Resultado_Def_Player += resultado->Resultado_Player;
        }

        if (resultado_definitivo->Resultado_Def_Player >= 100)
        {
            system("cls");
            printf("Player ganhou!\n");
            Zerar_Dados(dado, resultado, resultado_definitivo);
        }
        else
        {
            resultado_definitivo->Resultado_Def_Player = resultado_definitivo->Resultado_Def_Player - resultado->Resultado_Player;
        }
    }
}

void Lancar_Dois_Dado_PC(Dado *dado, Resultado *resultado, Definitivo *resultado_definitivo)
{
    printf("Vez do Computador\n");

    while (resultado->Resultado_PC < 100)
    {
        dado->Dado_PC = 1 + (rand() % 20);
        dado->Dado_PC_2 = 1 + (rand() % 20);

        if (dado->Dado_PC > 6 || dado->Dado_PC_2 > 6)
        {
            dado->Dado_PC = 2 + rand() % (6 - 2 + 1);
            dado->Dado_PC_2 = 2 + rand() % (6 - 2 + 1);
        }

        if (dado->Dado_PC == 1 || dado->Dado_PC_2 == 1)
        {
            printf("Computador tirou 1! Perdeu os pontos da rodada.\n");
            resultado->Resultado_PC = 0;
            break;
        }
        else
        {
            resultado->Resultado_PC += dado->Dado_PC;
            resultado->Resultado_PC += dado->Dado_PC_2;

            printf("Computador tirou %d e %d\n", dado->Dado_PC, dado->Dado_PC_2);

            if (resultado_definitivo->Resultado_Def_PC >= 100)
            {
                system("cls");
                printf("Computador ganhou!\n");
                Zerar_Dados(dado, resultado, resultado_definitivo);
                break;
            }

            if (resultado->Resultado_PC >= 20)
            {
                printf("O computador decidiu parar\n");
                resultado_definitivo->Resultado_Def_PC += resultado->Resultado_PC;
                resultado->Resultado_PC = 0;
                break;
            }
        }
    }
}

void Criar_Ranking(Resultado *resultado, int *victory, int *cont_user)
{
    FILE *arquivo_ranking = fopen("./arquivo_ranking.txt", "w");

    if (arquivo_ranking != NULL)
    {
        fprintf(arquivo_ranking, "Player: %s\n", resultado->nome);
        fprintf(arquivo_ranking, "Vitórias: %d\n\n", *victory);
    }
    else
    {
        printf("ERRO AO CRIAR O ARQUIVO!");
    }

    fclose(arquivo_ranking);
}

// falta criar a lógica da função

int Jogador_Existente_Ranking(Resultado *resultado, int *victory, int *cont_user)
{
    FILE *arquivo_ranking = fopen("./arquivo_ranking.txt", "r");

    
    
    fclose(arquivo_ranking);
}

void Mostrar_Ranking(Resultado *resultado, int *victory)
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

void Zerar_Dados(Dado *dado, Resultado *resultado, Definitivo *resultado_definitivo)
{
    resultado_definitivo->Resultado_Def_PC = 0;
    resultado_definitivo->Resultado_Def_Player = 0;
    resultado->Resultado_Player = 0;
    resultado->Resultado_PC = 0;
    dado->Dado_Player = 0;
    dado->Dado_PC = 0;
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
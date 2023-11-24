#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct
{
    int Dado_Player;
    int Dado_PC;
} Dado;

typedef struct
{
    int Resultado_Player;
    int Resultado_PC;
} Resultado;

typedef struct
{
    int Resultado_Def_Player;
    int Resultado_Def_PC;
} Definitivo;

void Lancar_Dado(Dado *, Resultado *, Definitivo *);
void Lancar_Dado_PC(Dado *, Resultado *, Definitivo *);
void Segurar_Dado(Resultado *, Definitivo *);

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao, continuar_jogo = 1;
    Dado dado;
    Resultado resultado = {0, 0};
    Definitivo resultado_definitivo = {0, 0};
    int definir_resultado = (dado.Dado_Player == 1) ? resultado_definitivo.Resultado_Def_Player : resultado.Resultado_Player; //não tá funcionando

    srand(time(NULL));

    while (continuar_jogo)
    {
        printf("Rodada: Player %d - PC %d\n", resultado.Resultado_Player, resultado_definitivo.Resultado_Def_PC);
        printf("1. Lançar o dado\n2. Segurar\n3. Encerrar o jogo\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            Lancar_Dado(&dado, &resultado, &resultado_definitivo);
            break;
        case 2:
            Segurar_Dado(&resultado, &resultado_definitivo);
            Lancar_Dado_PC(&dado, &resultado, &resultado_definitivo);
            break;
        case 3:
            printf("Encerrando o jogo...\n");
            continuar_jogo = 0;
            break;

        default:
            printf("Opção inválida!\n");
            break;
        }
    }

    return 0;
}

void Lancar_Dado(Dado *dado, Resultado *resultado, Definitivo *resultado_definitivo)
{
    dado->Dado_Player = 1 + (rand() % 12);

    if (dado->Dado_Player == 1)
    {
        printf("Você tirou 1! Perdeu os pontos da rodada.\n");
        resultado->Resultado_Player = 0;
    }
    else
    {
        if (dado->Dado_Player > 6)
        {
            printf("Você tirou 1! Perdeu os pontos da rodada.\n");
            resultado->Resultado_Player = 0;
            return;
        }

        resultado->Resultado_Player += dado->Dado_Player;

        printf("Você tirou %d\n", dado->Dado_Player);

        if (resultado->Resultado_Player == 100)
        {
            printf("Player ganhou!\n");
        }
    }
}

void Segurar_Dado(Resultado *resultado, Definitivo *resultado_definitivo)
{
    resultado_definitivo->Resultado_Def_Player = resultado->Resultado_Player;
    resultado->Resultado_Player = 0;
}

void Lancar_Dado_PC(Dado *dado, Resultado *resultado, Definitivo *resultado_definitivo)
{
    printf("Vez do Computador\n");

    dado->Dado_PC = 1 + (rand() % 6);

    while (1)
    {
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

            if (resultado_definitivo->Resultado_Def_PC == 100)
            {
                printf("Computador ganhou!\n");
                break;
            }
            else if (resultado->Resultado_PC >= 20)
            {
                printf("O computador decidiu parar\n");
                resultado_definitivo->Resultado_Def_PC += resultado->Resultado_PC;
                resultado->Resultado_PC = 0;
                break;
            }
        }
    }
}
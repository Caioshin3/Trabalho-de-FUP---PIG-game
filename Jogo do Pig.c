#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct{
int Dado_Player;
int Dado_PC;
}Dado;

typedef struct{
int Resultado_Player;
int Resultado_PC;
}Resultado;

typedef struct{
int Resultado_Def_Player;
int Resultado_Def_PC;
}Definitivo;

void Lancar_Dado(Dado *, Resultado *, Definitivo *, int *, int);
void Lancar_Dado_PC(Dado *, Resultado *, Definitivo *);
void Segurar_Dado(Dado * ,Resultado *, Definitivo *);
void Lancar_Dois_Dados(Dado *, Resultado *, Definitivo *, int *);

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao, continuar_jogo = 1, vitoria = 0, Dev = 0;
    Dado dado;
    Resultado resultado = {0, 0};
    Definitivo resultado_definitivo = {0, 0};
    

    srand(time(NULL));

    while (continuar_jogo)
    {
        int Soma_Resultado_Def = resultado.Resultado_Player+resultado_definitivo.Resultado_Def_Player;
        
        if(dado.Dado_Player != 1)
        {
            printf("Rodada: Player %d - PC %d\n", Soma_Resultado_Def, resultado_definitivo.Resultado_Def_PC);
            printf("Vitorias: %d\n",vitoria);
        }
        else
        {
            printf("Rodada: Player %d - PC %d\n", resultado_definitivo.Resultado_Def_Player, resultado_definitivo.Resultado_Def_PC);
            printf("Vitorias: %d\n",vitoria);
        }
        
        if(resultado_definitivo.Resultado_Def_PC < 100 && resultado_definitivo.Resultado_Def_Player < 100){
        printf("1. Lançar o dado\n2. Segurar\n3. Encerrar o jogo\n4. Icarus Mode\n");
        scanf("%d", &opcao);
        getchar();
        system("cls");
        }
        switch (opcao)
        {
        case 1:
            Lancar_Dado(&dado, &resultado, &resultado_definitivo,&vitoria,&Dev);
            break;
        case 2:
            Segurar_Dado(&dado, &resultado, &resultado_definitivo);
            Lancar_Dado_PC(&dado, &resultado, &resultado_definitivo);
            break;
        case 3:
            printf("Encerrando o jogo...\n");
            continuar_jogo = 0;
            break;
        case 4:
          printf("Red Bull te dá asas!\n");
          Dev = 1;
          break;       

        default:
            printf("Opção inválida!\n");
            break;
        }
    }

    return 0;
}

void Lancar_Dado(Dado *dado, Resultado *resultado, Definitivo *resultado_definitivo, int * victory, int dev)
{
    if(dev == 1){
    dado->Dado_Player = 2 + rand()%(6-2+1);
    }
    else{
    dado->Dado_Player = 1 + (rand()%6);
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

        if(resultado->Resultado_Player > 0){
        resultado_definitivo->Resultado_Def_Player += resultado->Resultado_Player;    
        }
        
                
        if (resultado_definitivo->Resultado_Def_Player >= 100)
        {
            system("cls");
            printf("Player ganhou!\n");
            resultado_definitivo->Resultado_Def_PC = 0;
            resultado_definitivo->Resultado_Def_Player = 0;
            resultado->Resultado_Player = 0;
            resultado->Resultado_PC = 0;
            dado->Dado_Player = 0;
            dado->Dado_PC = 0;
           (*victory)++;
        }else{
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
        
        if(dado->Dado_PC > 6){
        dado->Dado_PC = 2 + rand() % (6-2+1);   
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
                resultado_definitivo->Resultado_Def_PC = 0;
                resultado_definitivo->Resultado_Def_Player = 0;
                resultado->Resultado_Player = 0;
                resultado->Resultado_PC = 0;
                dado->Dado_Player = 0;
                dado->Dado_PC = 0;
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



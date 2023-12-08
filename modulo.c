#include "lib.h"

void Menu()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao, dificuldade = 1, continuar_jogo = 1, vitoria = 0, cont_jogadas = 0;
    Player player;
    PC computador;

    player.Resultado_Player = 0;
    player.Resultado_Def_Player = 0;
    computador.Resultado_PC = 0;
    computador.Resultado_Def_PC = 0;

    srand(time(NULL));

    Menu_Login(opcao, &player, &vitoria, &cont_jogadas);

    while (continuar_jogo)
    {
        int Soma_Resultado_Def = player.Resultado_Player + player.Resultado_Def_Player;

        if (player.Dado_Player != 1)
        {
            printf("Rodada: %s %d - PC %d\n", player.nome, Soma_Resultado_Def, computador.Resultado_Def_PC);
            printf("Quantidade de jogadas: %d\n", cont_jogadas);
            printf("Vitorias: %d\n", vitoria);
        }
        else
        {
            printf("Rodada: %s %d - PC %d\n", player.nome, player.Resultado_Def_Player, computador.Resultado_Def_PC);
            printf("Vitórias: %d\n", vitoria);
        }

        if (computador.Resultado_Def_PC < 100 && player.Resultado_Def_Player < 100)
        {
            printf("1. Lançar o dado\n2. Segurar\n3. Alterar Dificuldade\n4. Mostrar Ranking\n5. Encerrar o jogo\n");
            scanf("%d", &opcao);
            getchar();
            system("cls");
        }

        switch (opcao)
        {
        case 1:
            if (dificuldade == 1)
            {
                Lancar_Dado(&player, &computador, &vitoria, &cont_jogadas);
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
            Mostrar_Ranking(&player, &vitoria, &cont_jogadas);
            break;
        case 5:
            printf("Encerrando o jogo...\n");
            continuar_jogo = 0;
            break;

        default:
            printf("Operação inválida!\n");
            break;
        }
    }
}

void Menu_Login(int opcao, Player *players, int *victory, int *cont_jogadas)
{
    printf("1. Registrar novo jogador\n2. Login\n");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        Cadastro(players, victory, cont_jogadas, opcao);
        break;
    case 2:
        Login(opcao, players, victory, cont_jogadas);
        break;

    default:
        printf("Opção inválida!\n");
        break;
    }
}

void Cadastro(Player *players, int *victory, int *cont_jogadas, int opcao)
{
    int cont = 0;
    char linha[100];
    char nome[50];
    int verificar = 0;

    FILE *arquivo_ranking = fopen("./arquivo_ranking.txt", "a+");

    while (fgets(linha, sizeof(linha), arquivo_ranking) != NULL)
    {
        cont++;
    }

    if (cont <= MAX_PLAYERS)
    {
        printf("Informe o nome do jogador: ");
        scanf("%s", players->nome);

        rewind(arquivo_ranking);

        while (fgets(linha, sizeof(linha), arquivo_ranking) != NULL)
        {
            sscanf(linha, "%[^,],%d,%d", nome, &*cont_jogadas, &*victory);
            if (strcmp(nome, players->nome) == 0)
            {
                verificar = 1;
                break;
            }
        }

        if (verificar == 1)
        {
            printf("Jogador já registrado!\n");
            Menu_Login(opcao, players, victory, cont_jogadas);
        }
        else
        {
            system("cls");
            printf("Novo jogador cadastrado!\n");
            fprintf(arquivo_ranking, "%s,", players->nome);
            fprintf(arquivo_ranking, "%d,", *cont_jogadas);
            fprintf(arquivo_ranking, "%d\n", *victory);
        }

        fclose(arquivo_ranking);
    }
    else
    {
        printf("Número máximo de jogadores atingido!\n\n");
        fclose(arquivo_ranking);
        exit(0);
    }
}

void Login(int opcao, Player *players, int *victory, int *cont_jogadas)
{
    FILE *arquivo_ranking = fopen("arquivo_ranking.txt", "r");

    char nome[50];
    char linha[100];
    int verificar = 0;

    printf("Informe o nome do jogador: ");
    scanf("%s", players->nome);
    system("cls");
    while (fgets(linha, sizeof(linha), arquivo_ranking) != NULL)
    {
        sscanf(linha, "%[^,],%d,%d", nome, &*cont_jogadas, &*victory);
        if (strcmp(nome, players->nome) == 0)
        {
            verificar = 1;
            fclose(arquivo_ranking);
        }
    }
    if (verificar == 0)
    {
        printf("Usuario não encontrado!\n");
        Menu_Login(opcao, players, victory, cont_jogadas);
        fclose(arquivo_ranking);
    }
}

void Lancar_Dado(Player *player, PC *computador, int *victory, int *jogadas)
{
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
            Atualizar_Ranking(player, jogadas, victory);
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
            Atualizar_Ranking(player, cont_jogadas, victory);
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

void Atualizar_Ranking(Player *player, int *cont_jogadas, int *victory)
{
    FILE *arquivo_ranking_temp = fopen("./arquivo_ranking_temp.txt", "w+");
    FILE *arquivo_ranking = fopen("./arquivo_ranking.txt", "r");

    char nome[50];
    int jogadas, vitorias;
    char linha[100];

    while (fgets(linha, sizeof(linha), arquivo_ranking) != NULL)
    {
        sscanf(linha, "%[^,],%d,%d", nome, &jogadas, &vitorias);

        if (strcmp(nome, player->nome) == 0)
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

int compararRanking(const void *a, const void *b)
{
    const Lista_Jogadores *jogadorA = (const Lista_Jogadores *)a;
    const Lista_Jogadores *jogadorB = (const Lista_Jogadores *)b;

    // Ordena por maior taxa de vitória por jogada
    if (jogadorA->taxa_vitoria_por_jogada > jogadorB->taxa_vitoria_por_jogada)
    {
        return -1;
    }
    else if (jogadorA->taxa_vitoria_por_jogada < jogadorB->taxa_vitoria_por_jogada)
    {
        return 1;
    }

    // Se as taxas de vitórias por jogada são iguais, ordena por maior vitoria
    if (jogadorA->vitorias > jogadorB->vitorias)
    {
        return -1;
    }
    else if (jogadorA->vitorias < jogadorB->vitorias)
    {
        return 1;
    }

    // Se as maiores vitorias são iguais, ordena por menor jogada
    if (jogadorA->jogadas < jogadorB->jogadas)
    {
        return -1;
    }
    else if (jogadorA->jogadas > jogadorB->jogadas)
    {
        return 1;
    }

    return 0;
}

void CalcularTaxaVitoriaPorJogada(Lista_Jogadores *jogador)
{
    // Adicione o cálculo da taxa de vitória por jogada aqui
    jogador->taxa_vitoria_por_jogada = (jogador->jogadas != 0) ? (double)jogador->vitorias / jogador->jogadas : 0;
}

void Mostrar_Ranking()
{
    FILE *arquivo_ranking = fopen("./arquivo_ranking.txt", "r");

    if (arquivo_ranking != NULL)
    {
        Lista_Jogadores lista[100];
        char linha[100];
        int cont = 0;

        while (fgets(linha, sizeof(linha), arquivo_ranking) != NULL)
        {
            sscanf(linha, "%[^,],%d,%d", lista[cont].nome, &lista[cont].jogadas, &lista[cont].vitorias);
            CalcularTaxaVitoriaPorJogada(&lista[cont]); // Calcula a taxa de vitória por jogada
            cont++;
        }

        // Ordenar o ranking usando qsort
        qsort(lista, cont, sizeof(Lista_Jogadores), compararRanking);

        // Mostrar resultados hierárquicos
        for (int i = 0; i < cont; i++)
        {
            printf("Nome do jogador: %s\n", lista[i].nome);
            printf("Quantidade de jogadas: %d\n", lista[i].jogadas);
            printf("Quantidade de vitórias: %d\n\n", lista[i].vitorias);
        }

        getchar();
        system("cls");

        fclose(arquivo_ranking);
    }
    else
    {
        fprintf(stderr, "Erro ao abrir o arquivo de ranking\n");
    }
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
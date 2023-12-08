// Inclui o arquivo de cabeçalho "lib.h", que contém definições e declarações de funções utilizadas no código principal.
#include "lib.h"

// Função principal que representa o menu do jogo.
void Menu()
{
    // Define a língua que o código será executado para Português.
    setlocale(LC_ALL, "Portuguese");

    // Declaração de variáveis inteiras para opções, dificuldade, status do jogo, vitórias e contagem de jogadas.
    int opcao, dificuldade = 1, continuar_jogo = 1, vitoria = 0, cont_jogadas = 0;

    // Criação de instâncias das structs Player e PC (representando o jogador e o computador).
    Player player;
    PC computador;

    // Inicialização de resultados para zero.
    player.Resultado_Player = 0;
    player.Resultado_Def_Player = 0;
    computador.Resultado_PC = 0;
    computador.Resultado_Def_PC = 0;

    // Inicialização do gerador de números aleatórios usando o tempo atual.
    srand(time(NULL));

    // Chama a função Menu_Login passando algumas variáveis por referência.
    Menu_Login(opcao, &player, &vitoria, &cont_jogadas);

    // Loop principal do jogo.
    while (continuar_jogo)
    {
        // Calcula a soma dos resultados do jogador.
        int Soma_Resultado_Def = player.Resultado_Player + player.Resultado_Def_Player;

        // Mostra informações da rodada.
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

        // Verifica se o jogo ainda está em andamento e mostra opções ao jogador.
        if (computador.Resultado_Def_PC < 100 && player.Resultado_Def_Player < 100)
        {
            printf("1. Lançar o dado\n2. Segurar\n3. Alterar Dificuldade\n4. Mostrar Ranking\n5. Encerrar o jogo\n");
            scanf("%d", &opcao);
            getchar();
            system("cls");
        }

        // Estrutura switch para lidar com diferentes opções.
        switch (opcao)
        {
        case 1:
            // Caso 1: Chama a função Lancar_Dado ou Lancar_Dois_Dados com base na dificuldade.
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
            // Caso 2: Chama a função Segurar_Dado e, dependendo da dificuldade, chama Lancar_Dado_PC ou Lancar_Dois_Dado_PC.
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
            // Caso 3: Chama a função Dificuldade para alterar a dificuldade.
            Dificuldade(&dificuldade);
            break;

        case 4:
            // Caso 4: Chama a função Mostrar_Ranking para exibir o ranking.
            Mostrar_Ranking(&player, &vitoria, &cont_jogadas);
            break;

        case 5:
            // Caso 5: Encerra o jogo.
            printf("Encerrando o jogo...\n");
            continuar_jogo = 0;
            break;

        default:
            // Caso padrão: Mensagem de operação inválida.
            printf("Operação inválida!\n");
            break;
        }
    }
}


// Inclui o arquivo de cabeçalho "lib.h", que contém definições e declarações de funções utilizadas no código principal.
#include "lib.h"

// Função principal que representa o menu do jogo.
void Menu()
{
    // Define a língua que o código será executado para Português.
    setlocale(LC_ALL, "Portuguese");

    // Declaração de variáveis inteiras para opções, dificuldade, status do jogo, vitórias e contagem de jogadas.
    int opcao, dificuldade = 1, continuar_jogo = 1, vitoria = 0, cont_jogadas = 0;

    // Criação de instâncias das structs Player e PC (representando o jogador e o computador).
    Player player;
    PC computador;

    // Inicialização de resultados para zero.
    player.Resultado_Player = 0;
    player.Resultado_Def_Player = 0;
    computador.Resultado_PC = 0;
    computador.Resultado_Def_PC = 0;

    // Inicialização do gerador de números aleatórios usando o tempo atual.
    srand(time(NULL));

    // Chama a função Menu_Login passando algumas variáveis por referência.
    Menu_Login(opcao, &player, &vitoria, &cont_jogadas);

    // Loop principal do jogo.
    while (continuar_jogo)
    {
        // Calcula a soma dos resultados do jogador.
        int Soma_Resultado_Def = player.Resultado_Player + player.Resultado_Def_Player;

        // Mostra informações da rodada.
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

        // Verifica se o jogo ainda está em andamento e mostra opções ao jogador.
        if (computador.Resultado_Def_PC < 100 && player.Resultado_Def_Player < 100)
        {
            printf("1. Lançar o dado\n2. Segurar\n3. Alterar Dificuldade\n4. Mostrar Ranking\n5. Encerrar o jogo\n");
            scanf("%d", &opcao);
            getchar();
            system("cls");
        }

        // Estrutura switch para lidar com diferentes opções.
        switch (opcao)
        {
        case 1:
            // Caso 1: Chama a função Lancar_Dado ou Lancar_Dois_Dados com base na dificuldade.
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
            // Caso 2: Chama a função Segurar_Dado e, dependendo da dificuldade, chama Lancar_Dado_PC ou Lancar_Dois_Dado_PC.
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
            // Caso 3: Chama a função Dificuldade para alterar a dificuldade.
            Dificuldade(&dificuldade);
            break;

        case 4:
            // Caso 4: Chama a função Mostrar_Ranking para exibir o ranking.
            Mostrar_Ranking(&player, &vitoria, &cont_jogadas);
            break;

        case 5:
            // Caso 5: Encerra o jogo.
            printf("Encerrando o jogo...\n");
            continuar_jogo = 0;
            break;

        default:
            // Caso padrão: Mensagem de operação inválida.
            printf("Operação inválida!\n");
            break;
        }
    }
}


// Inclui o arquivo de cabeçalho "lib.h", que contém definições e declarações de funções utilizadas no código principal.
#include "lib.h"

// Função principal que representa o menu do jogo.
void Menu()
{
    // Define a língua que o código será executado para Português.
    setlocale(LC_ALL, "Portuguese");

    // Declaração de variáveis inteiras para opções, dificuldade, status do jogo, vitórias e contagem de jogadas.
    int opcao, dificuldade = 1, continuar_jogo = 1, vitoria = 0, cont_jogadas = 0;

    // Criação de instâncias das structs Player e PC (representando o jogador e o computador).
    Player player;
    PC computador;

    // Inicialização de resultados para zero.
    player.Resultado_Player = 0;
    player.Resultado_Def_Player = 0;
    computador.Resultado_PC = 0;
    computador.Resultado_Def_PC = 0;

    // Inicialização do gerador de números aleatórios usando o tempo atual.
    srand(time(NULL));

    // Chama a função Menu_Login passando algumas variáveis por referência.
    Menu_Login(opcao, &player, &vitoria, &cont_jogadas);

    // Loop principal do jogo.
    while (continuar_jogo)
    {
        // Calcula a soma dos resultados do jogador.
        int Soma_Resultado_Def = player.Resultado_Player + player.Resultado_Def_Player;

        // Mostra informações da rodada.
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

        // Verifica se o jogo ainda está em andamento e mostra opções ao jogador.
        if (computador.Resultado_Def_PC < 100 && player.Resultado_Def_Player < 100)
        {
            printf("1. Lançar o dado\n2. Segurar\n3. Alterar Dificuldade\n4. Mostrar Ranking\n5. Encerrar o jogo\n");
            scanf("%d", &opcao);
            getchar();
            system("cls");
        }

        // Estrutura switch para lidar com diferentes opções.
        switch (opcao)
        {
        case 1:
            // Caso 1: Chama a função Lancar_Dado ou Lancar_Dois_Dados com base na dificuldade.
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
            // Caso 2: Chama a função Segurar_Dado e, dependendo da dificuldade, chama Lancar_Dado_PC ou Lancar_Dois_Dado_PC.
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
            // Caso 3: Chama a função Dificuldade para alterar a dificuldade.
            Dificuldade(&dificuldade);
            break;

        case 4:
            // Caso 4: Chama a função Mostrar_Ranking para exibir o ranking.
            Mostrar_Ranking(&player, &vitoria, &cont_jogadas);
            break;

        case 5:
            // Caso 5: Encerra o jogo.
            printf("Encerrando o jogo...\n");
            continuar_jogo = 0;
            break;

        default:
            // Caso padrão: Mensagem de operação inválida.
            printf("Operação inválida!\n");
            break;
        }
    }
}

// Inclui o arquivo de cabeçalho "lib.h", que contém definições e declarações de funções utilizadas no código principal.
#include "lib.h"

// Função principal que representa o menu do jogo.
void Menu()
{
    // Define a língua que o código será executado para Português.
    setlocale(LC_ALL, "Portuguese");

    // Declaração de variáveis inteiras para opções, dificuldade, status do jogo, vitórias e contagem de jogadas.
    int opcao, dificuldade = 1, continuar_jogo = 1, vitoria = 0, cont_jogadas = 0;

    // Criação de instâncias das structs Player e PC (representando o jogador e o computador).
    Player player;
    PC computador;

    // Inicialização de resultados para zero.
    player.Resultado_Player = 0;
    player.Resultado_Def_Player = 0;
    computador.Resultado_PC = 0;
    computador.Resultado_Def_PC = 0;

    // Inicialização do gerador de números aleatórios usando o tempo atual.
    srand(time(NULL));

    // Chama a função Menu_Login passando algumas variáveis por referência.
    Menu_Login(opcao, &player, &vitoria, &cont_jogadas);

    // Loop principal do jogo.
    while (continuar_jogo)
    {
        // Calcula a soma dos resultados do jogador.
        int Soma_Resultado_Def = player.Resultado_Player + player.Resultado_Def_Player;

        // Mostra informações da rodada.
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

        // Verifica se o jogo ainda está em andamento e mostra opções ao jogador.
        if (computador.Resultado_Def_PC < 100 && player.Resultado_Def_Player < 100)
        {
            printf("1. Lançar o dado\n2. Segurar\n3. Alterar Dificuldade\n4. Mostrar Ranking\n5. Encerrar o jogo\n");
            scanf("%d", &opcao);
            getchar();
            system("cls");
        }

        // Estrutura switch para lidar com diferentes opções.
        switch (opcao)
        {
        case 1:
            // Caso 1: Chama a função Lancar_Dado ou Lancar_Dois_Dados com base na dificuldade.
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
            // Caso 2: Chama a função Segurar_Dado e, dependendo da dificuldade, chama Lancar_Dado_PC ou Lancar_Dois_Dado_PC.
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
            // Caso 3: Chama a função Dificuldade para alterar a dificuldade.
            Dificuldade(&dificuldade);
            break;

        case 4:
            // Caso 4: Chama a função Mostrar_Ranking para exibir o ranking.
            Mostrar_Ranking(&player, &vitoria, &cont_jogadas);
            break;

        case 5:
            // Caso 5: Encerra o jogo.
            printf("Encerrando o jogo...\n");
            continuar_jogo = 0;
            break;

        default:
            // Caso padrão: Mensagem de operação inválida.
            printf("Operação inválida!\n");
            break;
        }
    }
}

// Função para lançar o dado do jogador.
void Lancar_Dado(Player *player, PC *computador, int *victory, int *jogadas)
{
    // Verifica se o jogador tirou 1.
    if (player->Dado_Player == 1)
    {
        // Se o jogador tirar 1, perde os pontos da rodada.
        printf("Você tirou 1! Perdeu os pontos da rodada.\n");
        player->Resultado_Player = 0;
        Lancar_Dado_PC(computador, player);
    }
    else
    {
        // Adiciona o valor do dado à pontuação do jogador.
        player->Resultado_Player += player->Dado_Player;

        // Verifica se o dado tirado é maior que 6.
        if (player->Dado_Player > 6)
        {
            // Se o dado for maior que 6, jogador perde os pontos da rodada.
            printf("Você tirou 1! Perdeu os pontos da rodada.\n");
            player->Resultado_Player = 0;
            return;
        }

        // Exibe o valor tirado no dado.
        printf("Você tirou %d\n", player->Dado_Player);
        
        // Incrementa o número de jogadas.
        (*jogadas)++;
        
        // Atualiza o ranking do jogador.
        Atualizar_Ranking(player, jogadas, victory);

        // Verifica se a pontuação do jogador é positiva.
        if (player->Resultado_Player > 0)
        {
            player->Resultado_Def_Player += player->Resultado_Player;
        }

        // Verifica se a pontuação do jogador atingiu 100.
        if (player->Resultado_Def_Player >= 100)
        {
            // Se a pontuação do jogador atingir 100, ele ganha.
            system("cls");
            printf("%s ganhou!\n", player->nome);
            Zerar_Dados(player, computador);
            (*victory)++;
            Atualizar_Ranking(player, jogadas, victory);
        }
        else
        {
            // Caso contrário, atualiza a pontuação acumulada do jogador.
            player->Resultado_Def_Player = player->Resultado_Def_Player - player->Resultado_Player;
        }
    }
}



// Função para o jogador decidir segurar os pontos da rodada.
void Segurar_Dado(Player *player)
{
    // Adiciona os pontos da rodada à pontuação total do jogador.
    player->Resultado_Def_Player += player->Resultado_Player;
    // Zera os pontos da rodada atual.
    player->Resultado_Player = 0;
}

// Função para simular a jogada do computador ao lançar um dado.
void Lancar_Dado_PC(PC *computador, Player *player)
{
    // Mensagem indicando que é a vez do computador jogar.
    printf("Vez do Computador\n");

    // Loop enquanto a pontuação do computador for menor que 100.
    while (computador->Resultado_PC < 100)
    {
        // Gera um número aleatório de 1 a 20 para simular o lançamento do dado pelo computador.
        computador->Dado_PC = 1 + (rand() % 20);

        // Se o resultado do dado for maior que 6, ajusta para um valor entre 2 e 6.
        if (computador->Dado_PC > 6)
        {
            computador->Dado_PC = 2 + rand() % (6 - 2 + 1);
        }

        // Verifica se o computador tirou 1.
        if (computador->Dado_PC == 1)
        {
            // Mensagem indicando que o computador tirou 1 e perdeu os pontos da rodada.
            printf("Computador tirou 1! Perdeu os pontos da rodada.\n");
            // Zera a pontuação do computador na rodada.
            computador->Resultado_PC = 0;
            // Sai do loop.
            break;
        }
        else
        {
            // Adiciona o resultado do dado à pontuação do computador na rodada.
            computador->Resultado_PC += computador->Dado_PC;

            // Mensagem indicando o resultado do dado do computador.
            printf("Computador tirou %d\n", computador->Dado_PC);

            // Verifica se a pontuação total do computador atingiu ou ultrapassou 100.
            if (computador->Resultado_Def_PC >= 100)
            {
                // Mensagem indicando que o computador ganhou.
                system("cls");
                printf("Computador ganhou!\n");
                // Zera as pontuações para iniciar um novo jogo.
                Zerar_Dados(player, computador);
                // Sai do loop.
                break;
            }

            // Verifica se a pontuação do computador na rodada atingiu 20.
            if (computador->Resultado_PC >= 20)
            {
                // Mensagem indicando que o computador decidiu parar.
                printf("O computador decidiu parar\n");
                // Adiciona a pontuação da rodada à pontuação total do computador.
                computador->Resultado_Def_PC += computador->Resultado_PC;
                // Zera a pontuação do computador na rodada.
                computador->Resultado_PC = 0;
                // Sai do loop.
                break;
            }
        }
    }
}



// Função para simular o lançamento de dois dados pelo jogador.
void Lancar_Dois_Dados(Player *player, PC *computador, int *cont_jogadas, int *victory)
{
    // Gera valores aleatórios para os dois dados do jogador.
    player->Dado_Player = 1 + (rand() % 6);
    player->Dado_Player_2 = 1 + (rand() % 6);

    // Verifica se algum dos dados tirou 1.
    if (player->Dado_Player == 1 || player->Dado_Player_2 == 1)
    {
        // Mensagem indicando que o jogador tirou 1 e perdeu os pontos da rodada.
        printf("Você tirou 1! Perdeu os pontos da rodada.\n");
        // Zera a pontuação do jogador na rodada.
        player->Resultado_Player = 0;
        // Simula a jogada do computador após o jogador tirar 1.
        Lancar_Dois_Dado_PC(computador, player);
    }
    else
    {
        // Adiciona o resultado dos dois dados à pontuação do jogador na rodada.
        player->Resultado_Player += player->Dado_Player;
        player->Resultado_Player += player->Dado_Player_2;

        // Mensagem indicando os resultados dos dois dados do jogador.
        printf("Você tirou %d e %d\n", player->Dado_Player, player->Dado_Player_2);
        
        // Incrementa o contador de jogadas.
        (*cont_jogadas)++;
        // Atualiza o ranking com base nos resultados da jogada.
        Atualizar_Ranking(player, cont_jogadas, victory);

        // Verifica se a pontuação do jogador na rodada é positiva.
        if (player->Resultado_Player > 0)
        {
            // Adiciona a pontuação da rodada à pontuação total do jogador.
            player->Resultado_Def_Player += player->Resultado_Player;
        }

        // Verifica se a pontuação total do jogador atingiu ou ultrapassou 100.
        if (player->Resultado_Def_Player >= 100)
        {
            // Mensagem indicando que o jogador ganhou.
            system("cls");
            printf("Player ganhou!\n");
            // Incrementa a contagem de vitórias.
            (*victory)++;
            // Zera as pontuações para iniciar um novo jogo.
            Zerar_Dados(player, computador);
            // Atualiza o ranking com base nos resultados da partida.
            Atualizar_Ranking(player, cont_jogadas, victory);
        }
        else
        {
            // Ajusta a pontuação do jogador na rodada.
            player->Resultado_Def_Player = player->Resultado_Def_Player - player->Resultado_Player;
        }
    }
}



// Função para simular o lançamento de dois dados pelo computador.
void Lancar_Dois_Dado_PC(PC *computador, Player *player)
{
    // Mensagem indicando que é a vez do computador.
    printf("Vez do Computador\n");

    // Loop enquanto a pontuação do computador na rodada for menor que 100.
    while (computador->Resultado_PC < 100)
    {
        // Gera valores aleatórios para os dois dados do computador.
        computador->Dado_PC = 1 + (rand() % 20);
        computador->Dado_PC_2 = 1 + (rand() % 20);

        // Verifica se algum dos dados tirou 1.
        if (computador->Dado_PC == 1 || computador->Dado_PC_2 == 1)
        {
            // Mensagem indicando que o computador tirou 1 e perdeu os pontos da rodada.
            printf("Computador tirou 1! Perdeu os pontos da rodada.\n");
            // Zera a pontuação do computador na rodada.
            computador->Resultado_PC = 0;
            // Sai do loop.
            break;
        }
        else
        {
            // Adiciona o resultado dos dois dados à pontuação do computador na rodada.
            computador->Resultado_PC += computador->Dado_PC;
            computador->Resultado_PC += computador->Dado_PC_2;

            // Mensagem indicando os resultados dos dois dados do computador.
            printf("Computador tirou %d e %d\n", computador->Dado_PC, computador->Dado_PC_2);

            // Verifica se a pontuação total do computador atingiu ou ultrapassou 100.
            if (computador->Resultado_Def_PC >= 100)
            {
                // Mensagem indicando que o computador ganhou.
                system("cls");
                printf("Computador ganhou!\n");
                // Zera as pontuações para iniciar um novo jogo.
                Zerar_Dados(player, computador);
                // Sai do loop.
                break;
            }

            // Verifica se a pontuação do computador na rodada é maior ou igual a 20.
            if (computador->Resultado_PC >= 20)
            {
                // Mensagem indicando que o computador decidiu parar.
                printf("O computador decidiu parar\n");
                // Adiciona a pontuação da rodada à pontuação total do computador.
                computador->Resultado_Def_PC += computador->Resultado_PC;
                // Zera a pontuação do computador na rodada.
                computador->Resultado_PC = 0;
                // Sai do loop.
                break;
            }
        }
    }
}



// Função para atualizar o arquivo de ranking com novos resultados do jogador.
void Atualizar_Ranking(Player *player, int *cont_jogadas, int *victory)
{
    // Abre o arquivo de ranking original para leitura.
    FILE *arquivo_ranking_temp = fopen("./arquivo_ranking_temp.txt", "w+");
    FILE *arquivo_ranking = fopen("./arquivo_ranking.txt", "r");

    // Variáveis para armazenar dados do arquivo de ranking.
    char nome[50];
    int jogadas, vitorias;
    char linha[100];

    // Percorre cada linha do arquivo de ranking original.
    while (fgets(linha, sizeof(linha), arquivo_ranking) != NULL)
    {
        // Lê os dados de cada linha.
        sscanf(linha, "%[^,],%d,%d", nome, &jogadas, &vitorias);

        // Verifica se o nome na linha atual é o mesmo do jogador atual.
        if (strcmp(nome, player->nome) == 0)
        {
            // Se for, escreve os novos dados do jogador no arquivo temporário.
            fprintf(arquivo_ranking_temp, "%s,%d,%d\n", player->nome, *cont_jogadas, *victory);
        }
        else
        {
            // Se não for, mantém os dados originais no arquivo temporário.
            fprintf(arquivo_ranking_temp, "%s,%d,%d\n", nome, jogadas, vitorias);
        }
    }

    // Fecha os arquivos.
    fclose(arquivo_ranking_temp);
    fclose(arquivo_ranking);

    // Remove o arquivo de ranking original.
    remove("./arquivo_ranking.txt");
    // Renomeia o arquivo temporário para o nome original.
    rename("./arquivo_ranking_temp.txt", "./arquivo_ranking.txt");
}



// Função de comparação para qsort, ordena a lista de jogadores com base em critérios específicos.
int compararRanking(const void *a, const void *b)
{
    // Converte os ponteiros genéricos para ponteiros do tipo Lista_Jogadores.
    const Lista_Jogadores *jogadorA = (const Lista_Jogadores *)a;
    const Lista_Jogadores *jogadorB = (const Lista_Jogadores *)b;

    // Ordena por maior taxa de vitória por jogada.
    if (jogadorA->taxa_vitoria_por_jogada > jogadorB->taxa_vitoria_por_jogada)
    {
        return -1;
    }
    else if (jogadorA->taxa_vitoria_por_jogada < jogadorB->taxa_vitoria_por_jogada)
    {
        return 1;
    }

    // Se as taxas de vitórias por jogada são iguais, ordena por maior vitória.
    if (jogadorA->vitorias > jogadorB->vitorias)
    {
        return -1;
    }
    else if (jogadorA->vitorias < jogadorB->vitorias)
    {
        return 1;
    }

    // Se as maiores vitórias são iguais, ordena por menor número de jogadas.
    if (jogadorA->jogadas < jogadorB->jogadas)
    {
        return -1;
    }
    else if (jogadorA->jogadas > jogadorB->jogadas)
    {
        return 1;
    }

    // Se todas as condições anteriores forem iguais, considera os jogadores como equivalentes.
    return 0;
}



// Função para calcular a taxa de vitória por jogada de um jogador.
void CalcularTaxaVitoriaPorJogada(Lista_Jogadores *jogador)
{
    // Adicione o cálculo da taxa de vitória por jogada aqui.

    // Verifica se o jogador possui pelo menos uma jogada para evitar divisão por zero.
    // Calcula a taxa de vitória por jogada usando a fórmula: (vitórias / jogadas) se jogadas != 0, senão, define como 0.
    jogador->taxa_vitoria_por_jogada = (jogador->jogadas != 0) ? (double)jogador->vitorias / jogador->jogadas : 0;
}



// Função para mostrar o ranking dos jogadores.
void Mostrar_Ranking()
{
    // Abre o arquivo de ranking para leitura.
    FILE *arquivo_ranking = fopen("./arquivo_ranking.txt", "r");

    // Verifica se o arquivo foi aberto corretamente.
    if (arquivo_ranking != NULL)
    {
        Lista_Jogadores lista[100];  // Array para armazenar informações dos jogadores.
        char linha[100];              // String para armazenar cada linha do arquivo.
        int cont = 0;                 // Contador de jogadores.

        // Lê cada linha do arquivo, extrai informações e calcula a taxa de vitória por jogada.
        while (fgets(linha, sizeof(linha), arquivo_ranking) != NULL)
        {
            sscanf(linha, "%[^,],%d,%d", lista[cont].nome, &lista[cont].jogadas, &lista[cont].vitorias);
            CalcularTaxaVitoriaPorJogada(&lista[cont]); // Calcula a taxa de vitória por jogada
            cont++;
        }

        // Ordena o ranking usando qsort com base nas funções definidas em compararRanking.
        qsort(lista, cont, sizeof(Lista_Jogadores), compararRanking);

        // Mostra os resultados hierárquicos no console.
        for (int i = 0; i < cont; i++)
        {
            printf("Nome do jogador: %s\n", lista[i].nome);
            printf("Quantidade de jogadas: %d\n", lista[i].jogadas);
            printf("Quantidade de vitórias: %d\n\n", lista[i].vitorias);
        }

        getchar();     // Aguarda uma entrada do usuário antes de continuar.
        system("cls");  // Limpa a tela do console.

        fclose(arquivo_ranking);  // Fecha o arquivo de ranking.
    }
    else
    {
        fprintf(stderr, "Erro ao abrir o arquivo de ranking\n");  // Exibe uma mensagem de erro se o arquivo não puder ser aberto.
    }
}



// Função para resetar os dados do jogo (pontuações, resultados e valores dos dados).
void Zerar_Dados(Player *player, PC *computador)
{
    computador->Resultado_Def_PC = 0;     // Zera a pontuação do computador.
    player->Resultado_Def_Player = 0;     // Zera a pontuação do jogador.
    player->Resultado_Player = 0;         // Zera o resultado da jogada do jogador.
    computador->Resultado_PC = 0;         // Zera o resultado da jogada do computador.
    player->Dado_Player = 0;              // Zera o valor do dado do jogador.
    computador->Dado_PC = 0;              // Zera o valor do dado do computador.
}



// Função para escolher a dificuldade do jogo.
void Dificuldade(int *dificuldade)
{
    // Exibe as opções de dificuldade.
    printf("1. Fácil\n2. Difícil\n");
    
    // Solicita ao jogador que escolha a dificuldade.
    scanf("%d", &*dificuldade);
    
    // Limpa a tela do console para melhor visualização.
    system("cls");

    // Estrutura de seleção para exibir a mensagem correspondente à dificuldade escolhida.
    switch (*dificuldade)
    {
    case 1:
        printf("Modo Fácil\n");     // Mensagem para o modo fácil.
        break;
    case 2:
        printf("Modo Difícil\n");   // Mensagem para o modo difícil.
        break;

    default:
        printf("Opção inválida");   // Mensagem para opção inválida.
        break;
    }
}

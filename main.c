#include "Labirinto.h"
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

void main()
{
    FILE *fp;
    char nomeArquivo[30], **labirinto;
    int Nlinhas,Ncolunas,sair,opcao,cachorro[2],carregado,qtdMovimentos,rMAX,MAX;

    #if(ANALISE == 1)
        printf("MODO ANALISE ATIVADO!\n");
        printf("Pressione enter para continuar ...");
        getchar();
    #endif

    while(1){
        system("clear");
        printf("=======================================================\n");
        printf("|                    Voce deseja :                    |\n");
        printf("|-----------------------------------------------------|\n");
        printf("|                                                     |\n");
        printf("| 1 - Inserir um novo labirinto                       |\n");
        printf("|                                                     |\n");
        printf("| 2 - Resolver o labirinto e mostrar resultados       |\n");
        printf("|                                                     |\n");
        printf("| Pressione 0 para encerrar o programa ...            |\n");
        printf("|                                                     |\n");
        printf("=======================================================\n");
        printf("-> Opcao: ");
        scanf("%d",&opcao);
        switch(opcao){
            case 0:
                system("clear");
                printf("PROGRAMA ENCERRADO !!\n");
                exit(EXIT_SUCCESS);
            case 1:
                system("clear");
                printf("-> Digite o nome do arquivo do labirinto: ");
                scanf("%s",nomeArquivo);
                fp = fopen(nomeArquivo,"r");
                if(fp == NULL){
                    printf("Nome do arquivo incorreto !!\n");
                    printf("Pressione enter para continuar ...");
                    getchar();
                    getchar();
                    break;
                }
                fscanf(fp,"%d%d",&Nlinhas,&Ncolunas);//lendo linha e coluna primeiro
                labirinto = CriaLabirinto(fp,Nlinhas,Ncolunas);
                if(labirinto == NULL){
                    printf("Nao foi possivel carregar o labirinto ...\n");
                    printf("Pressione enter para continuar ...");
                    getchar();
                    getchar();
                    break;
                }
                carregado = TRUE;
                printf("Labirinto inserido com suscesso !!\n");
                printf("Pressione enter para continuar ...");
                getchar();
                getchar();
                break;
            case 2:
                system("clear");
                if(carregado == TRUE){//se existir um labirinto carregado
                    sair = EXIT_FAILURE;
                    qtdMovimentos = 0;
                    rMAX = 0;
                    MAX = 0;
                    printf("CAMINHO PERCORRIDO:\n");
                    ProcuraCachorro(cachorro,labirinto,Nlinhas,Ncolunas);
                    MovimentaCachorro(labirinto,cachorro,cachorro[0],cachorro[1],Nlinhas,Ncolunas,&sair,&qtdMovimentos,&rMAX,&MAX);
                    printf("\nLabirinto Solucionado :\n");
                    ImprimeLabirinto(labirinto,cachorro,Nlinhas,Ncolunas);

                    if(sair == EXIT_SUCCESS)
                        printf("\nO cachorro movimentou %d vezes e chegou na coluna %d da primeira linha.\n",qtdMovimentos,cachorro[1]);
                    else if(sair == EXIT_FAILURE)
                        printf("\nO cachorro movimentou %d vezes e percebeu que nao existe saida\n.",qtdMovimentos);

                    #if(ANALISE == 1)
                        printf("O total de chamadas recursivas foi %d.\n", qtdMovimentos);
                        printf("O nivel mais alto de recursividade foi %d.\n", rMAX);
                    #endif

                    printf("Pressione enter para continuar ...");
                    getchar();
                    getchar();
                    carregado = FALSE;
                    free(labirinto);
                    break;
                }else{
                    printf("Voce nao carregou nenhum labirinto !!\n");
                    printf("Pressione enter para continuar ...");
                    getchar();
                    getchar();
                    break;
                }
            default:
                system("clear");
                printf("Opcao invalida !!\n");
                printf("Pressione enter para continuar ...");
                getchar();
                getchar();
                break;
        }
    }
}

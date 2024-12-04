#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Ing.h"
#include "Pizzas.h"


I* PrimeiroCadastro(int* IngTotais){

    //Definir dados
    I* tmp = CadastroIngredientes(IngTotais);

    if(tmp){

       printf("\nCadastro feito com sucesso!");
       return tmp;
    } else{

        return NULL;
    }
}

void exibirMenu(){

    printf("\n\nGESTAO DE PIZZAS - SEJA BEM VINDO - v0.0\n\n");


    //Menu de metodos
    printf("Opcao 0 - Encerrar programa\n");
    printf("Opcao 1 - Primeiro cadastro de ingredientes\n");
    printf("Opcao 2 - Primeiro cadastro de pizzas\n");
    printf("Opcao 3 - Visualizar ingredientes da loja\n");
    printf("Opcao 4 - Visualizar Pizzas da loja\n");
    printf("Opcao 5 - Adicionar ingrediente ao Banco de dados\n");
    printf("Opcao 6 - Adicionar pizza ao Banco de dados\n");
    printf("Opcao 7 - Remover ingrediente do Banco de dados\n");
    printf("Opcao 8 - Remover pizza do Banco de dados\n");
    printf("Opcao 9 - Editar ingrediente do Banco de dados\n");
    printf("Opcao 10 - Editar pizza do Banco de dados\n");
    printf("Opcao 11 - Realizar Venda\n");



}




int main(){

    //Definicao de dados
    int opcao = 1, IngTotais, PizzasTotais, idRI = 0, idRP = 0, idscan = 0, edit;  //Variaveis para controlar indices
    float venda = 0.0;
    I* ing = NULL; P* Pizzas = NULL;
    FILE* perdidosP;
    FILE* perdidosI;


    //Ler para saber se existem ingredientes disponiveis
    ing = LerBancoDeDadosIngredientes("ING.TXT", &IngTotais);

    //Ler para saber se existem pizzas disponiveis
    Pizzas = LerBancoDeDadosPizzas("PIZZAS.TXT", &PizzasTotais);

    exibirMenu();

    //Implementacao
    while(opcao != 0){

        printf("\n\nDigite a opcao: ");
        scanf("%d", &opcao);
        getchar();


        switch(opcao){

        case 0:

            printf("\nEncerrando o programa!");
            break;

        case 1:

            if(ing){

                printf("\nPrimeiro cadastro de ingredientes ja feito. Favor escolher outro metodo!");
            } else {

                printf("\n\n====== PRIMEIRO CADASTRO DE INGREDIENTES ======\n\n");

                printf("\nDefina a quantia de ingredientes a cadastrar: ");
                scanf("%d", &IngTotais);
                getchar();

                if(NumeroValidoMaxIng(IngTotais)){

                    ing = PrimeiroCadastro(&IngTotais);
                    BancoDeDadosGravarIng("ING.TXT", ing, IngTotais);
                } else {

                    printf("\nERROR: Cadastro invalido. Revise o numero de ingredientes!");
                    break;
                }
            }
            break;

        case 2:

            if(ing && Pizzas){

                printf("\nPrimeiro cadastro de Pizzas ja feito. Favor escolher outro metodo!");
            } else if(ing && !Pizzas){

                printf("\n\n====== PRIMEIRO CADASTRO DE PIZZAS ======\n\n");
                printf("\nDefinir a quantia de Pizzas a cadastrar: ");
                scanf("%d", &PizzasTotais);
                getchar();

                if(NumeroValidoMaxPizzas(PizzasTotais)){

                    Pizzas = PrimeiroCadastroPizzas(&PizzasTotais, &IngTotais, ing);
                    BancoDeDadosGravarPiz("PIZZAS.TXT", Pizzas, PizzasTotais);
                    printf("\n\nPizzas cadastradas com sucesso\n\n");
                } else {

                    printf("\nERROR: Cadastro invalido. Revise o numero de Pizzas!");
                }
            } else {

                printf("\nPrimeiro cadastro de ingredientes nao foi feito ainda!");
            }

            break;

        case 3:

            if(ing){

                printf("\n\n\n====== VISUALIZAR INGREDIENTES ======\n");
                if(NumeroValidoMaxIng(IngTotais)){

                    ImprimirIngredientes(ing, IngTotais);
                } else {

                    printf("\nNumero de ingredientes invalido!");
                }
            } else {

                printf("\nPrimeiro cadastro nao foi feito. Favor realiza-lo!");
            }
            break;

        case 4:

            if(Pizzas){

                printf("\n\n\n====== VISUALIZAR CARDAPIO ======\n");
                if(NumeroValidoMaxPizzas(PizzasTotais)){

                    ImprimirPizzas(Pizzas, PizzasTotais);
                    printf("\n\n\n");
                } else {

                    printf("\nNumero de pizzas invalido!");
                }
            } else {

                printf("\nPrimeiro cadastro nao foi feito. Favor realiza-lo!");
            }
            break;

        case 5:

            if(ing){

                printf("\n\n\n====== ADICIONAR INGREDIENTE AO BANCO ======\n");
                if(NumeroValidoMaxIng(IngTotais)){

                    ing = AdicionarIngrediente(ing, &IngTotais);
                    if(ing){

                       BancoDeDadosGravarIng("ING.TXT", ing, IngTotais);
                    } else {

                        //Mensagem de erro na funcao
                    }

                } else {

                    printf("\nNao e possivel adicionar ingredientes ao banco de dados. Valor maximo atingido!");
                }
            } else {

                printf("\nPrimeiro cadastro nao foi feito. Para adicionar ingredientes e ter melhor gerenciamento, escolha a opcao 1!");
            }
            break;

        case 6:

            printf("\n\n====== ADICIONAR PIZZA AO BANCO ======\n\n");
            if(!ing){

                printf("\nNao e possivel adicionar pizzas, pois nao existem ingredientes. Favor cadastrar ingredientes!");
                break;
            }

            if(PizzasTotais == 20){

                printf("\nNao e possivel adicionar pizzas. Banco de dados cheio!");
                break;
            }

            Pizzas = AdicionarPizza(Pizzas, &PizzasTotais, ing, &IngTotais);
            if(!Pizzas){

                //Mensagem de erro na funcao
            } else {

                BancoDeDadosGravarPiz("PIZZAS.TXT", Pizzas, PizzasTotais);
            }

            break;

        case 7:

            if(ing){

                printf("\n\n====== REMOVER INGREDIENTE DO BANCO ======\n\n");
                if(Pizzas){

                    printf("\nDefina pelo Id o ingrediente que deseja remover: ");
                    scanf("%d", &idscan);
                    getchar();

                    if(!ExistenciaId(idscan, ing, IngTotais) || idscan <= 0){

                        printf("\nNao foi possivel remover ingrediente. Id nao encontrado!");
                    } else {

                        BancoDeDadosGravarPiz("SALVAR.TXT", Pizzas, PizzasTotais);
                        Pizzas = ingRemovidos(Pizzas, &PizzasTotais, idscan);
                        if(Pizzas && IngTotais > 1){

                            ing = RemoverIngrediente(ing, &IngTotais, idscan);
                            BancoDeDadosGravarIng("ING.TXT", ing, IngTotais);
                            BancoDeDadosGravarPiz("PIZZAS.TXT", Pizzas, PizzasTotais);
                            printf("\nIngredientes removidos com sucesso!");
                        } else if(Pizzas && IngTotais == 1){

                            ing = NULL;
                            Pizzas = NULL;

                            perdidosP = fopen("PIZZAS.TXT", "wt");
                            fprintf(perdidosP, "%d", -1);

                            perdidosI = fopen("ING.TXT", "wt");
                            fprintf(perdidosI, "%d", -1);

                            fclose(perdidosP);
                            fclose(perdidosI);
                            printf("\nErro programado: Necessario fechar programa! Necessidade do metodo 7 -> Ajustar ingredientes e pizzas");
                        } else if(!Pizzas){

                            ing = NULL;
                            perdidosI = fopen("ING.TXT", "wt");
                            fprintf(perdidosI, "%d", -1);
                            fclose(perdidosI);

                            perdidosP = fopen("PIZZAS.TXT", "wt");
                            fprintf(perdidosP, "%d", -1);
                        }
                    }

                } else {

                    printf("\nDefina pelo Id o ingrediente que deseja remover: ");
                    scanf("%d", &idscan);
                    getchar();

                    if(!ExistenciaId(idscan, ing, IngTotais) || idscan <= 0){

                        printf("\nNao foi possivel remover ingrediente. Id nao encontrado!");
                    } else {

                        ing = RemoverIngrediente(ing, &IngTotais, idscan);
                        BancoDeDadosGravarIng("ING.TXT", ing, IngTotais);
                    }

                }

            } else {

                printf("\nNao foi possivel remover ingredientes. Nao ha itens disponiveis no banco de dados!");
            }

            break;

        case 8:

            if(!Pizzas){

                printf("\nPrimeiro cadastro de pizzas nao foi feito. Nao e possivel remover pizzas!");
            } else{

                printf("\n\n====== REMOVER PIZZA DO BANCO ======\n\n");
                if(NumeroValidoMaxPizzas(PizzasTotais)){

                    Pizzas = RemoverPizza(Pizzas, &PizzasTotais);
                    if(!Pizzas){

                        perdidosP = fopen("PIZZAS.TXT", "wt");
                        if(!perdidosP){

                            printf("\nNao foi possivel atualizar banco de dados. Sem permissao!");
                        } else {

                            fprintf(perdidosP, "%d", -1);
                            fclose(perdidosP);
                        }

                    } else {

                       BancoDeDadosGravarPiz("PIZZAS.TXT", Pizzas, PizzasTotais);
                    }


                } else {

                    printf("\nERROR: Numero de pizzas invalido ou alem da capacidade do Banco. Tente novamente!");
                }
            }

            break;

        case 9:

            if(ing){

                printf("\n\n====== EDITAR INGREDIENTE DO BANCO ======\n\n");
                printf("DETALHE: EDITAR PRECO OU NOME MUDA O INGREDIENTE NAS PIZZAS!");

                ImprimirIngredientes(ing, IngTotais);
                printf("\nCom base no Id, informe qual ingrediente ira ser editado: ");
                scanf("%d", &idscan);
                getchar();

                if(ExistenciaId(idscan, ing, IngTotais)){

                    printf("\nInforme o que deseja editar (1 - Nome / 2 - preco): ");
                    scanf("%d", &edit);
                    getchar();

                    ing = EditarIngrediente(ing, IngTotais, idscan, edit);
                    Pizzas = AtualizarIngredientes(Pizzas, ing, PizzasTotais, IngTotais);
                    BancoDeDadosGravarIng("ING.TXT", ing, IngTotais);
                    BancoDeDadosGravarPiz("PIZZAS.TXT", Pizzas, PizzasTotais);

                } else {

                    printf("\nNao foi possivel editar ingrediente. Id nao encontrado!");

                }
            } else {

                printf("\nPrimeiro cadastro nao foi feito. Para editar ingredientes e ter melhor gerenciamento, escolha a opcao 1!");
            }
            break;

        case 10:
            if(Pizzas){

                printf("\n\n====== EDITAR PIZZA DO BANCO ======\n\n");
                ImprimirPizzas(Pizzas, PizzasTotais);
                printf("\nCom base no Id, informe qual pizza sera editada: ");
                scanf("%d", &idscan);
                getchar();

                if(ExistenciaIdP(idscan, Pizzas, PizzasTotais)){

                    printf("\nInforme o que deseja editar (1 - Nome / 2 - Tamanho / 3 - Preco / 4 - Ingrediente / 5 - Numero de Pizzas): ");
                    scanf("%d", &edit);
                    getchar();

                    Pizzas = EditarPizza(Pizzas, PizzasTotais, ing, IngTotais, edit, idscan);
                    BancoDeDadosGravarPiz("PIZZAS.TXT", Pizzas, PizzasTotais);
                    printf("\nProcesso de edicao de pizzas realizado com sucesso!");
                } else{

                    printf("\nNao foi possivel editar pizza. Id nao encontrado");
                }

            } else {

                printf("\nPrimeiro cadastro nao foi feito. Para editar pizzas e ter melhor gerenciamento, escolha a opcao 2!");
            }
            break;

        case 11:
            if(Pizzas){

                printf("\n\n====== REALIZAR VENDA ======\n\n");
                ImprimirPizzas(Pizzas, PizzasTotais);

                printf("\nDefina pelo id a pizza que sera vendida: ");
                scanf("%d", &idscan);
                getchar();

                if(ExistenciaIdP(idscan, Pizzas, PizzasTotais)){

                    printf("\nInforme se deseja adicionar ingrediente extra (1 - SIM / 2 - NAO): ");
                    scanf("%d", &edit);
                    getchar();

                    venda = RealizarVenda(Pizzas, PizzasTotais, ing, IngTotais, edit, idscan);

                    if(venda == -1.0){

                        printf("\nNao foi possivel realizar a venda. Ingrediente adicional nao encontrado!");
                    }

                    printf("\nVenda realizada com sucesso - %.2f!", venda);

                } else {

                    printf("\nNao foi possivel realizar a venda. Pizza nao encontrada!");
                }

            } else {

                printf("\nPrimeiro cadastro nao foi feito. Para editar ingredientes e ter melhor gerenciamento, escolha a opcao 2!");
            }

            break;

        default:

            exibirMenu();
            printf("\nOpcao invalida. Favor escolher uma opcao do menu!");
            break;
        }
    }

    printf("\n\nAperte ENTER para encerrar o programa");
    getchar();

    if(Pizzas){

        FreePizzas(Pizzas, PizzasTotais);
    }

    if(ing){

        FreeIngredientes(ing);
    }

    return 0;
}


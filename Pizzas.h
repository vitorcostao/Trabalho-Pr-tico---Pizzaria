#ifndef PIZZAS_H
#define PIZZAS_H

//Inclusoes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include "Ing.h"


/**

1) Trata-se de um CRUD de Pizzas disponiveis em uma loja para gestao de dados.

-> O programa principal devera fazer um primeiro cadastro caso nao haja dados nos arquivos de banco de dados.
-> Se tiver dados nos arquivos, o programa nao realizara nenhum outro metodo disponivel a nao ser o primeiro cadastro
-> Os dados das Pizzas serao guardados em Arquivo.txt

*/



///----------------------------------------------ESTRUTURAS
typedef struct Pizzas {

        int id;
        char nome[50];
        char tamanho;
        int quantiaPizzas;
        int quantiaIngre;
        I* ingredientes;
        float preco;
} P;
///----------------------------------------------FIM ESTRUTURAS










///----------------------------------------------FUNCOES EXTRAS

bool OkAlocP(P* Pizzas);                                                                     //Funcao para verificar alocacao das pizzas
bool NumeroValidoMaxPizzas(int num);                                                         //Funcao para verificar validade do numero maximo de pizzas
bool NumeroValidoMaxIngPorPizza(int num);                                                    //Funcao para verificar validade do numero maximo de ingredientes por pizzas
bool ExistenciaIdP(int uid, P* PizzasTotais, int PizzasLoja);                                //Funcao para verificar existencia de uma pizza pelo id
void imprimirId(P* Pizzas, int PizzasLoja);                                                  //Procedimento para imprimir pizzas
int DefinirIdP(P* PizzasTotais, int PizzasLoja);                                             //Funcao que retorna um id valido para pizzas
int ReturnPositionPId(P* Pizzas, int PizzasLoja, int id);                                    //Funcao que retorna posicao da Pizza pelo id

///----------------------------------------------FIM FUNCOES EXTRAS








///----------------------------------------------GESTAO DE MEMORIA

P* AlocarTotalPizzas(int PizzasLoja);                                                        //Funcao que reserva espaco na memoria para as pizzas
void FreePizzas(P* Pizzas, int PizzasLoja);                                                  //Procedimento que libera memoria alocada para as pizzas
P CopiarDados(P Pizzas, int IngPorPizza);                                                    //Funcao que retorna uma copia dos dados de uma pizza

///----------------------------------------------FIM GESTAO DE MEMORIA








///----------------------------------------------FUNCOES DE CADASTRO

P* PrimeiroCadastroPizzas(int* PizzasLoja, int* ingTotais, I* ing);                          //Funcao que retorna pizzas cadastradas

///----------------------------------------------FIM FUNCOES DE CADASTRO








///----------------------------------------------OPERACOES COM ARQUIVOS

int LerQuantiaPBancoDeDados(char* filename);                                                 //Funcao que le a quantia de pizzas do Banco de dados
int LerQuantiaIPBancoDeDados(FILE* arq, P* Pizzas);                                          //Funcao que le a quantia de ingredientes por pizzas do Banco de dados
void BancoDeDadosGravarPiz(char* filename, P* PizzasTotais, int PizzasLoja);                 //Procedimento que grava pizzas no Banco de dados
P* LerBancoDeDadosPizzas(char* filename, int* PizzasLoja);                                   //Funcao que le pizzas do Banco de dados

///----------------------------------------------FIM OPERACOES COM ARQUIVOS








///----------------------------------------------OPERACOES COM DADOS

P* ingRemovidos(P* Pizzas, int* PizzasLoja, int uid);                                        //Funcao que remove na pizza o ingrediente removido do Banco de dados
P* AdicionarPizza(P* Pizzas, int* PizzasTotais, I* ingTotais, int* IngredientesLoja);        //Funcao que adiciona pizza no Banco de dados
P* RemoverPizza(P* Pizzas, int* PizzasLoja);                                                 //Funcao que remove pizza do banco de dados
P* AtualizarIngredientes(P* Pizzas, I* ingTotais, int PizzasLoja, int IngredientesLoja);     //Funcao que atualiza ingrediente da pizza que foi editado do banco
P* EditarPizza(P* Pizzas, int PizzasLoja, I* ing, int IngredientesLoja, int edit, int uid);  //Funcao que edita pizzas



//Operacao com dados!
float RealizarVenda(P* Pizzas, int PizzasLoja, I* ing, int IngredientesLoja, int edit, int idscan); //Realizar venda de Pizza

///----------------------------------------------FIM OPERACOES COM DADOS

#endif // PIZZAS_H



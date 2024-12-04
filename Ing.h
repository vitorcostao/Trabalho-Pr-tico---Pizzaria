#ifndef ING_H
#define ING_H

//Inclusoes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>


/**

1) Trata-se de um CRUD de Ingredientes disponiveis em uma loja para gestao de dados.

-> O programa principal devera fazer um primeiro cadastro caso nao haja dados nos arquivos de banco de dados.
-> Se tiver dados nos arquivos, o programa nao realizara nenhum metodo disponivel, e sera obrigado a fazer o primeiro cadastro
-> Os dados de Ingredientes serao guardados em Arquivo.txt

*/


///----------------------------------------------ESTRUTURAS
typedef struct Ingredientes{

        int id;
        char nome[50];
        float preco;
} I;
///----------------------------------------------FIM ESTRUTURAS










///----------------------------------------------FUNCOES EXTRAS

bool OkAlocI(I* Ingredientes);                                                  //Funcao para verificar alocacao de ingredientes
bool NumeroValidoMaxIng(int num);                                               //Funcao para verificar se o ingredientes escolhido e valido
void ImprimirIngredientes(I* ing, int IngTotais);                               //Procedimento para imprimir os ingredientes
bool ExistenciaId(int uid, I* ingTotais, int IngredientesLoja);                 //Funcao para verificar se existe um ingrediente no banco o id escolhido
int DefinirId(I* ingTotais, int IngredientesLoja);                              //Funcao para definir um id ao cadastrar (Contem verificacoes de entrada)
bool IdJaInserido(int uid, I* ingredientesPizza, int numIngredientes);          //Funcao para verificar se id dos ingredientes das pizzas sao unicos
I IngredienteReturnId(int uid, I* ingTotais, int IngredientesLoja);             //Funcao que retorna ingrediente do Banco de dados pelo id
int PosicaoPeloId(I* ingTotais, int IngredientesLoja, int uid);                 //Funcao que retorna a posicao do ingrediente do Banco de dados pelo id

///----------------------------------------------FIM FUNCOES EXTRAS








///----------------------------------------------GESTAO DE MEMORIA

I* AlocarTotalIng(int IngredientesLoja);                                        //Funcao que reserva espaco na memoria para os ingredientes
void FreeIngredientes(I* IngredientesLoja);                                     //Procedimento que libera memoria alocada para os ingredientes
I inicializar();                                                                //Funcao que inicializa dados dos ingredientes

///----------------------------------------------FIM GESTAO DE MEMORIA








///----------------------------------------------FUNCOES DE CADASTRO

I* CadastroIngredientes(int* IngredientesLoja);                                  //Funcao que retorna ingredientes cadastrados

///----------------------------------------------FIM FUNCOES DE CADASTRO








///----------------------------------------------OPERACOES COM ARQUIVOS

int LerQuantiaIBancoDeDados(char* filename);                                    //Funcao que le a quantia de ingredientes do Banco de dados
void BancoDeDadosGravarIng(char* filename, I* ingTotais, int IngredientesLoja);  //Procedimento que grava ingredientes no Banco de dados
I* LerBancoDeDadosIngredientes(char* filename, int* IngredientesLoja);          //Funcao que le ingredientes do Banco de dados
I BuscarIngredienteNoBanco(int idScan, int* IngredientesLoja);                   //Funcao que retorna ingrediente do Banco de dados pelo id

///----------------------------------------------FIM OPERACOES COM ARQUIVOS








///----------------------------------------------OPERACOES COM DADOS

I* AdicionarIngrediente(I* ingTotais, int* IngredientesLoja);                   //Funcao que adiciona ingrediente no Banco de dados
I* RemoverIngrediente(I* ingTotais, int* IngredientesLoja, int uid);            //Funcao que remove ingrediente do Banco de dados
I* IngredientesNovaPizza(int quantiaI, I* ingTotais, int ingredienteLoja);      //Funcao que adiciona ingrediente na Pizza
I* EditarIngrediente(I* ingTotais, int IngredientesLoja, int uid, int edit);    //Funcao que edita ingredientes

///----------------------------------------------FIM OPERACOES COM DADOS

#endif // ING_H


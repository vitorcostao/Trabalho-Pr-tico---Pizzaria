//Inclusoes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "../Ingredientes/Ing.h"
#include "Pizzas.h"

/**

1) Trata-se de um CRUD de Pizzas disponiveis em uma loja para gestao de dados.

-> O programa principal devera fazer um primeiro cadastro caso nao haja dados nos arquivos de banco de dados.
-> Se tiver dados nos arquivos, o programa nao realizara nenhum outro metodo disponivel a nao ser o primeiro cadastro
-> Os dados das Pizzas serao guardados em Arquivo.txt

*/

//----------------------------------------------------------Funcoes extras
//1) Testar alocacao de memoria
bool OkAlocP(P* Pizzas){

    if(!Pizzas){

        return false;
    }

    return true;
}

//2) Imprimir Pizzas
void ImprimirPizzas(P* Pizzas, int PizzasLoja){

    for(int i = 0; i < PizzasLoja; i++){

        printf("\n===== Pizza %d =====\n\n", Pizzas[i].id);
        printf("Nome: %s\n", Pizzas[i].nome);
        printf("Tamanho: %c\n", Pizzas[i].tamanho);
        printf("Preco: %.2f\n", Pizzas[i].preco);
        printf("Quantia de Pizzas: %d", Pizzas[i].quantiaPizzas);
        printf("\nIngredientes (%d):\n", Pizzas[i].quantiaIngre);

        for(int j = 0; j < Pizzas[i].quantiaIngre; j++){

                printf("%d: %s - %.2f\n",
                Pizzas[i].ingredientes[j].id,
                Pizzas[i].ingredientes[j].nome,
                Pizzas[i].ingredientes[j].preco);
        }
    }
}

//3) Calcular preco das pizzas
float CalcularPrecoPizza(P Pizza){

    float soma = 0.0;

    for(int i = 0; i < Pizza.quantiaIngre; i++){

        soma = soma + Pizza.ingredientes[i].preco;
    }

    if(Pizza.tamanho == 'G'){

        soma = soma * 1.5;
    } else if(Pizza.tamanho == 'M'){

        soma = soma * 1.2;
    } else{

        soma = soma * 1.1;
    }

    return soma;
}

//4) Validar numero maximo de pizzas
bool NumeroValidoMaxPizzas(int num){

    if(num <= 0 || num > 20){

        return false;
    }

    return true;
}

//5) Validar numero maximo de ingredientes por Pizza
bool NumeroValidoMaxIngPorPizza(int num){

    if(num <= 0 || num > 15){

        return false;
    }

    return true;
}

//6) Verificar se Id ja existe
bool ExistenciaIdP(int uid, P* PizzasTotais, int PizzasLoja){

    for(int i = 0; i < PizzasLoja; i++){

        if(PizzasTotais[i].id == uid){

            return true;
        }
    }
    return false;
}

//7) Mostrar Id das pizzas
void imprimirId(P* Pizzas, int PizzasLoja){

    for(int i = 0; i < PizzasLoja; i++){

        printf("\nID das pizzas: %d", Pizzas[i].id);
    }
}

//8) Definir Id para Pizzas
int DefinirIdP(P* PizzasTotais, int PizzasLoja){

    //Definir dados
    int uid = 0;

    imprimirId(PizzasTotais, PizzasLoja);

    printf("\nCom base nos numeros. Digite um Id que seja diferente de um existente para a nova Pizza: ");
    scanf("%d", &uid);
    getchar();

    if(ExistenciaIdP(uid, PizzasTotais, PizzasLoja) || uid <= 0){

        printf("\nId inserido invalido. Voltando ao menu!");
        return -1;
    }

    return uid;
}

//10) Retornar posicao da pizza pelo id
int ReturnPositionPId(P* Pizzas, int PizzasLoja, int id){

    for(int i = 0; i < PizzasLoja; i++){

        if(Pizzas[i].id == id){

            return i;
        }
    }

    return -1;
}

//----------------------------------------------------------Fim funcoes extras






//------------------------------------------------Gestao de memoria
//1) Alocar memoria para Pizzas
P* AlocarTotalPizzas(int PizzasLoja){


    if(NumeroValidoMaxPizzas(PizzasLoja)){

        P* PizzasTotais = (P*)malloc(PizzasLoja * sizeof(P));

        if(OkAlocP(PizzasTotais)){

            //Inicializar
            for(int i = 0; i < PizzasLoja; i++){

                PizzasTotais[i].id = -1;
                strcpy(PizzasTotais[i].nome, "inicializar");
                PizzasTotais[i].tamanho = '1';
                PizzasTotais[i].quantiaIngre = -1;
                PizzasTotais[i].quantiaPizzas = -1;
                PizzasTotais[i].ingredientes = NULL;
                PizzasTotais[i].preco = 0.0;
            }

            return PizzasTotais;
        } else {

            return NULL;
        }
    }

    return NULL;
}

//2) Liberar memoria alocada para as pizzas
void FreePizzas(P* Pizzas, int PizzasTotais){


    if(Pizzas){
        if(NumeroValidoMaxPizzas(PizzasTotais)){
          for(int i = 0; i < PizzasTotais; i++){
              if(Pizzas[i].ingredientes){

                 free(Pizzas[i].ingredientes);
              } else {

                 printf("\nIngredientes ja liberados ou pizza mais ingredientes!");
              }
          }

          free(Pizzas);
       } else {

       }
    } else {

        printf("\n\nOs dados ja foram liberados ou nao foram alocados corretamente!\n\n");
    }
}


//10) Copiar dados
P CopiarDados(P Pizzas, int IngPorPizza){

    P cpy;

    cpy.id = Pizzas.id;
    cpy.preco = Pizzas.preco;
    cpy.quantiaPizzas = Pizzas.quantiaPizzas;
    cpy.quantiaIngre = Pizzas.quantiaIngre;
    cpy.tamanho = Pizzas.tamanho;
    strcpy(cpy.nome, Pizzas.nome);
    cpy.ingredientes = AlocarTotalIng(Pizzas.quantiaIngre);

    for(int j = 0; j < Pizzas.quantiaIngre; j++){

        cpy.ingredientes[j].id = Pizzas.ingredientes[j].id;
        strcpy(cpy.ingredientes[j].nome, Pizzas.ingredientes[j].nome);
        cpy.ingredientes[j].preco = Pizzas.ingredientes[j].preco;
    }

    return cpy;
}


//------------------------------------------------Fim Gestao de memoria






//------------------------------------------------------------------------------Funcoes e metodos de Cadastros
// Funções e métodos de cadastro
P* PrimeiroCadastroPizzas(int* PizzasLoja, int* ingTotais, I* ing){

    //Definir dados
    int IdScan = 0, IngDaPizza = 0, k = 0;
    *ingTotais = LerQuantiaIBancoDeDados("ING.TXT");
    I IngreEscolhido = inicializar();

    if(!NumeroValidoMaxPizzas(*PizzasLoja) || !NumeroValidoMaxIng(*ingTotais)){

        printf("\nERROR: Numero de pizzas ou ingredientes do banco invalido(s)!\n");
        return NULL;
    }

    P* PizzasTotais = AlocarTotalPizzas(*PizzasLoja);

    if(!OkAlocP(PizzasTotais)){

        printf("\nERROR: Não foi possível cadastrar, alocação mal sucedida!");
        return NULL;
    }

    for(int i = 0; i < *PizzasLoja; i++){

        //Id
        PizzasTotais[i].id = i + 1;

        //Nome
        printf("\nNome: ");
        fgets(PizzasTotais[i].nome, 50, stdin);
        PizzasTotais[i].nome[strcspn(PizzasTotais[i].nome, "\n")] = '\0';

        //Tamanho
        printf("\nTamanho: ");
        scanf(" %c", &PizzasTotais[i].tamanho);

        while(PizzasTotais[i].tamanho != 'P' && PizzasTotais[i].tamanho != 'M' &&
              PizzasTotais[i].tamanho != 'G'){

            printf("\nTamanho invalido. Favor inserir um tamanho correto (P - M - G -> Maiusculo): ");
            scanf(" %c", &PizzasTotais[i].tamanho);
            getchar();
        }

        //Quantia de Pizzas disponiveis
        printf("\nDefina a quantia de pizzas disponiveis: ");
        scanf("%d", &PizzasTotais[i].quantiaPizzas);
        getchar();


        while(PizzasTotais[i].quantiaPizzas <= 0 || PizzasTotais[i].quantiaPizzas > 50){

            printf("\nValor para quantia de pizzas invalido. Favor insira um valor ate %d: ", 50);
            scanf("%d", &PizzasTotais[i].quantiaPizzas);
            getchar();
        }


        //Quantia de ingredientes
        printf("\nDefina a quantia de ingredientes desta pizza: ");
        scanf("%d", &IngDaPizza);
        getchar();

        if(!NumeroValidoMaxIngPorPizza(IngDaPizza) || IngDaPizza > *ingTotais){

            while(IngDaPizza <= 0 || IngDaPizza > *ingTotais){

                printf("\nValor para ingrediente da Pizza invalido. Favor insira um valor ate %d: ", *ingTotais);
                scanf("%d", &IngDaPizza);
                getchar();
            }

        }

            PizzasTotais[i].quantiaIngre = IngDaPizza;

            //Ingredientes
            PizzasTotais[i].ingredientes = AlocarTotalIng(IngDaPizza);

            if(!OkAlocI(PizzasTotais[i].ingredientes)){

                printf("\nERROR: Nao foi possivel alocar memoria para ingredientes");
                FreePizzas(PizzasTotais, i);
                return NULL;
            }


            //Definindo
            printf("\nDefina, pelo id, os ingredientes presentes na pizza:");
            printf("\n");
            ImprimirIngredientes(ing, *ingTotais);


            for(int j = 0; j < IngDaPizza; j++){

                bool idValido = false;
                while(!idValido){

                    printf("\nId do ingrediente %d: ", j + 1);
                    scanf("%d", &IdScan);
                    getchar();


                    if(ExistenciaId(IdScan, ing, *ingTotais) && !IdJaInserido(IdScan, PizzasTotais[i].ingredientes, j)){

                        PizzasTotais[i].ingredientes[j] = IngredienteReturnId(IdScan, ing, *ingTotais);
                        idValido = true;
                    } else {

                        if (!ExistenciaId(IdScan, ing, *ingTotais)) {

                            printf("\nID invalido. O ingrediente nao existe. Tente novamente.\n");
                        } else {

                            printf("\nID ja inserido para esta pizza. Tente novamente.\n");
                        }
                    }
                }
            }


            //Preco
            PizzasTotais[i].preco = CalcularPrecoPizza(PizzasTotais[i]);
        }


    return PizzasTotais;
}




//------------------------------------------------------------------------------Fim funcoes e metodos de Cadastros








//------------------------------------------------------------------------------Gravar e ler arquivos
//1) Ler quantia de pizzas que existem no banco de dados
int LerQuantiaPBancoDeDados(char* filename){

    //Definir dados
    FILE* arq = fopen(filename, "rt");
    int PizzasLoja;

    if(!arq){

        printf("\nNao foi possivel ler os dados, cadastro nao foi feito ou sem permissao para abrir arquivo!");
        return -1;
    }

    //Ler valor
    fscanf(arq, "%d", &PizzasLoja);
    if(!NumeroValidoMaxPizzas(PizzasLoja)){

        printf("\nNao foi possivel ler os dados, cadastro nao foi feito ou valor lido invalido!");
        fclose(arq);
        return -1;
    } else{

        fclose(arq);
        return PizzasLoja;
    }
}

int LerQuantiaIPBancoDeDados(FILE* arq, P* Pizzas){

    int q;
    fscanf(arq, "%d", &q);

    if(!NumeroValidoMaxIngPorPizza(q)){

        printf("\nNao foi possivel ler os dados, cadastro nao foi feito ou valor lido invalido!");
        fclose(arq);
        return -1;
    } else{

        fclose(arq);
        return q;
    }
}

//3) Gravar valores das pizzas em um arquivo .txt
void BancoDeDadosGravarPiz(char* filename, P* PizzasTotais, int PizzasLoja){

    //Definir dados
    FILE* arq = fopen(filename, "wt");

    if(!arq){

        printf("\nERROR: Nao foi possivel gravar em arquivo, documento nao foi aberto!");
        return;
    }

    if(!NumeroValidoMaxPizzas(PizzasLoja)){

        printf("\nERROR: Nao foi possivel gravar arquivo, numero de dados invalidos!");
        fclose(arq);
        return;
    }


    //Quantia de dados
    fprintf(arq, "%d\n", PizzasLoja);

    for(int i = 0; i < PizzasLoja; i++){

        fprintf(arq, "%d\n", PizzasTotais[i].quantiaIngre);
        fprintf(arq, "%d\n", PizzasTotais[i].quantiaPizzas);
        fprintf(arq, "%d\n", PizzasTotais[i].id);
        fprintf(arq, "%s\n", PizzasTotais[i].nome);
        fprintf(arq, "%c\n", PizzasTotais[i].tamanho);

        //Ingredientes
        for(int j = 0; j < PizzasTotais[i].quantiaIngre; j++){

            fprintf(arq, "%d: %s | %.2f\n", PizzasTotais[i].ingredientes[j].id, PizzasTotais[i].ingredientes[j].nome, PizzasTotais[i].ingredientes[j].preco);
        }

        //Preco
        fprintf(arq, "%.2f\n", PizzasTotais[i].preco);


    }

    fclose(arq);
}

//4) Ler Pizzas do Banco de dados
P* LerBancoDeDadosPizzas(char* filename, int* PizzasLoja){

    //Definir dados
    FILE* arq = fopen(filename, "rt");
    if(!arq){

        printf("\nNao foi possivel ler os dados. Sem permissao para abrir arquivo ou ele nao existe!");
        return NULL;
    }

    // Lê a quantidade de pizzas
    fscanf(arq, " %d", PizzasLoja);
    if(!NumeroValidoMaxPizzas(*PizzasLoja)){

        printf("\nNao foi possivel ler os dados. Cadastro de pizzas nao foi feito ou valor lido invalido!");
        fclose(arq);
        return NULL;
    }

    // Aloca memória para as pizzas
    P* PizzasTotais = AlocarTotalPizzas(*PizzasLoja);
    if(!OkAlocP(PizzasTotais)){

        printf("\nERROR: Falha na alocacao de memoria para as pizzas!\n");
        fclose(arq);
        return NULL;
    }

    // Ler dados das pizzas
    for(int i = 0; i < *PizzasLoja; i++){

        fscanf(arq, "%d", &PizzasTotais[i].quantiaIngre);
        fscanf(arq, "%d", &PizzasTotais[i].quantiaPizzas);
        if(PizzasTotais[i].quantiaPizzas <= 0 || PizzasTotais[i].quantiaPizzas > 50){

            printf("\nERROR: Nao foi possivel ler o dados! Quantia de numeros de uma das pizzas invalido!");
            FreePizzas(PizzasTotais, *PizzasLoja);
            return NULL;
        }

        fscanf(arq, "%d", &PizzasTotais[i].id);

        if(fscanf(arq, " %49s", PizzasTotais[i].nome) != 1){

            FreePizzas(PizzasTotais, i);
            fclose(arq);
            return NULL;
        }


        fscanf(arq, " %c", &PizzasTotais[i].tamanho);


        if(PizzasTotais[i].quantiaIngre == 0){

            PizzasTotais[i].ingredientes = NULL;

        } else {

            PizzasTotais[i].ingredientes = AlocarTotalIng(PizzasTotais[i].quantiaIngre);
            if(!OkAlocI(PizzasTotais[i].ingredientes)){

                printf("\nERROR: Falha na alocacao de memoria para ingredientes!\n");
                FreePizzas(PizzasTotais, i);
                fclose(arq);
                return NULL;
            }


            for(int j = 0; j < PizzasTotais[i].quantiaIngre; j++){

                fscanf(arq, " %d: ", &PizzasTotais[i].ingredientes[j].id);
                fscanf(arq, " %49s", PizzasTotais[i].ingredientes[j].nome);
                fscanf(arq, " | %f", &PizzasTotais[i].ingredientes[j].preco);
            }
        }

        fscanf(arq, " %f", &PizzasTotais[i].preco);
    }

    fclose(arq);
    return PizzasTotais;
}

//------------------------------------------------------------------------------Fim gravar e ler arquivos







//------------------------------------------------------------------------------Adicionar e remover dados
//1) Remover ingrediente removido da Pizza
P* ingRemovidos(P* Pizzas, int* PizzasLoja, int uid){

    int num = 0, k = 0;

    //Contar numero de pizzas com ingredientes igual a 1
    for(int i = 0; i < *PizzasLoja; i++){
        if(Pizzas[i].quantiaIngre == 1){

           num++;
        }
    }

    P* NovaPizza = AlocarTotalPizzas(*PizzasLoja - num);
    if(!NovaPizza){

        printf("\nNao ha mais pizzas no banco de dados ou alocacao falha!");
        return NULL;
    }


    for(int i = 0; i < *PizzasLoja; i++){

        if(Pizzas[i].quantiaIngre != 1){

            I* IngAjust = AlocarTotalIng(Pizzas[i].quantiaIngre);
            if(!IngAjust){

                printf("\nERROR: Nao foi possivel alocar memoria para os ingredientes.");
                FreePizzas(NovaPizza, *PizzasLoja);
                return NULL;
            }

            int idx = 0;
            for (int j = 0; j < Pizzas[i].quantiaIngre; j++){

                if (Pizzas[i].ingredientes[j].id != uid){

                    IngAjust[idx].id = Pizzas[i].ingredientes[j].id;
                    strcpy(IngAjust[idx].nome, Pizzas[i].ingredientes[j].nome);
                    IngAjust[idx].preco = Pizzas[i].ingredientes[j].preco;
                    idx++;
                }
            }


            NovaPizza[k].id = Pizzas[i].id;
            strcpy(NovaPizza[k].nome, Pizzas[i].nome);
            NovaPizza[k].preco = Pizzas[i].preco;
            NovaPizza[k].quantiaIngre = idx;
            NovaPizza[k].quantiaPizzas = Pizzas[i].quantiaPizzas;
            NovaPizza[k].ingredientes = IngAjust;
            NovaPizza[k].tamanho = Pizzas[i].tamanho;
            NovaPizza[k].preco = CalcularPrecoPizza(NovaPizza[k]);
            k++;
        }
    }

    FreePizzas(Pizzas, *PizzasLoja);
    (*PizzasLoja) = k;
    return NovaPizza;
}

//2) Adicionar Pizza ao Banco de dados
P* AdicionarPizza(P* Pizzas, int* PizzasTotais, I* ingTotais, int* IngredientesLoja){

    //Definir dados
    P* NovaPizza = AlocarTotalPizzas(*PizzasTotais + 1);
    int i = 0;

    if(!NovaPizza){

        printf("\nERROR: Nao foi possivel adicionar nova Pizza. Falha na alocacao!");
        return Pizzas;
    }

    //Copiar dados
    for(i = 0; i < *PizzasTotais; i++){

        NovaPizza[i].id = Pizzas[i].id;
        strcpy(NovaPizza[i].nome, Pizzas[i].nome);
        NovaPizza[i].tamanho = Pizzas[i].tamanho;
        NovaPizza[i].quantiaIngre = Pizzas[i].quantiaIngre;
        NovaPizza[i].quantiaPizzas = Pizzas[i].quantiaPizzas;

        if(Pizzas[i].quantiaPizzas <= 0 || Pizzas[i].quantiaPizzas > 50){

            printf("\nERROR: Quantia do numero de uma das pizzas invalida!");
            FreePizzas(Pizzas, *PizzasTotais);
            return Pizzas;
        }

        if(!NovaPizza[i].quantiaIngre){

            printf("\nERROR: Quantia de ingredientes na pizza invalido ou inexistente!");
            FreePizzas(NovaPizza, i);
            return Pizzas;
        }
        NovaPizza[i].ingredientes = AlocarTotalIng(NovaPizza[i].quantiaIngre);


        for(int j = 0; j < NovaPizza[i].quantiaIngre; j++){

            NovaPizza[i].ingredientes[j].id = Pizzas[i].ingredientes[j].id;
            strcpy(NovaPizza[i].ingredientes[j].nome, Pizzas[i].ingredientes[j].nome);
            NovaPizza[i].ingredientes[j].preco = Pizzas[i].ingredientes[j].preco;
        }

        NovaPizza[i].preco = Pizzas[i].preco;

    }

    ImprimirPizzas(Pizzas, *PizzasTotais);
    NovaPizza[i].id = DefinirIdP(Pizzas, *PizzasTotais);

    if(NovaPizza[i].id == -1){

        FreePizzas(NovaPizza, i);
        return Pizzas;
    }

    printf("\nNome: ");
    fgets(NovaPizza[i].nome, 50, stdin);
    NovaPizza[i].nome[strcspn(NovaPizza[i].nome, "\n")] = '\0';

    printf("\nTamanho: ");
    scanf(" %c", &NovaPizza[i].tamanho);
    getchar();

    printf("\nQuantia pizzas: ");
    scanf("%d", &NovaPizza[i].quantiaPizzas);
    getchar();

    if(NovaPizza[i].quantiaPizzas <= 0 || NovaPizza[i].quantiaPizzas > 50){

        printf("\nNao foi possivel adicionar Pizzas. Quantia de pizzas definida invalida!");
        FreePizzas(NovaPizza, i);
        return Pizzas;

    }

    printf("\nQuantia ingredientes: ");
    scanf("%d", &NovaPizza[i].quantiaIngre);
    getchar();

    if(NovaPizza[i].quantiaIngre <= 0 || NovaPizza[i].quantiaIngre > *IngredientesLoja){

        printf("\nNao foi possivel adicionar Pizzas. Quantia de ingredientes definida invalida!");
        FreePizzas(NovaPizza, i);
        return NULL;
    }

    NovaPizza[i].ingredientes = IngredientesNovaPizza(NovaPizza[i].quantiaIngre, ingTotais, *IngredientesLoja);
    if(!NovaPizza[i].ingredientes){

        printf("\nERROR: Nao foi possivel adicionar pizza. Falha na alocacao de ingredientes");
        FreePizzas(NovaPizza, i);
        return Pizzas;
    }

    NovaPizza[i].preco = CalcularPrecoPizza(NovaPizza[i]);

    printf("\nPizza adicionada com sucesso!");
    (*PizzasTotais)++;
    FreePizzas(Pizzas, *PizzasTotais - 1);
    return NovaPizza;
}

//3) Remover Pizza do banco de dados
P* RemoverPizza(P* Pizzas, int* PizzasLoja){

    if(*PizzasLoja - 1 == 0){

        printf("\nPizza removida com sucesso. Nao existem mais pizzas no banco!");
        return NULL;
    }

    //Definir dados
    P* rem = AlocarTotalPizzas(*PizzasLoja - 1);
    int idScan, j = 0, i = 0;

    if(!rem){

        printf("\nNao foi possivel remover pizzas. Falha na alocacao!");
        return Pizzas;
    }

    ImprimirPizzas(Pizzas, *PizzasLoja);
    printf("\nDefina a pizza que sera removida pelo Id: ");
    scanf("%d", &idScan);
    getchar();

    if(!ExistenciaIdP(idScan, Pizzas, *PizzasLoja) || idScan <= 0){

        printf("\nNao foi possivel remover a pizza. Id nao encontrado!");
        return Pizzas;
    }


    //Copiar dados
    for(i = 0; i < *PizzasLoja; i++){

        if(idScan != Pizzas[i].id){

            rem[j].id = Pizzas[i].id;
            strcpy(rem[j].nome, Pizzas[i].nome);
            rem[j].tamanho = Pizzas[i].tamanho;
            rem[j].quantiaIngre = Pizzas[i].quantiaIngre;
            rem[j].quantiaPizzas = Pizzas[i].quantiaPizzas;
            rem[j].ingredientes = AlocarTotalIng(rem[j].quantiaIngre);
            if(!rem[j].ingredientes){

                printf("\nERROR: Quantia de ingredientes na pizza invalido ou inexistente!");
                FreePizzas(rem, i);
                return Pizzas;
            }

            for(int k = 0; k < rem[j].quantiaIngre; k++){

                rem[j].ingredientes[k].id = Pizzas[i].ingredientes[k].id;
                strcpy(rem[j].ingredientes[k].nome, Pizzas[i].ingredientes[k].nome);
                rem[j].ingredientes[k].preco = Pizzas[i].ingredientes[k].preco;
            }

            rem[j].preco = Pizzas[i].preco;
            j++;
        }

    }



    FreePizzas(Pizzas, *PizzasLoja);
    (*PizzasLoja)--;
    return rem;
}

//4) Atualizar ingredientes nas pizzas devido a edicao de ingredientes do banco
P* AtualizarIngredientes(P* Pizzas, I* ingTotais, int PizzasLoja, int IngredientesLoja){

    for(int i = 0; i < PizzasLoja; i++){
        for(int j = 0; j < IngredientesLoja; j++){


            if(Pizzas[i].ingredientes[j].id == ingTotais[j].id){

                strcpy(Pizzas[i].ingredientes[j].nome, ingTotais[j].nome);
                Pizzas[i].ingredientes[j].preco = ingTotais[j].preco;
                Pizzas[i].preco = CalcularPrecoPizza(Pizzas[i]);
            }
        }
    }

    return Pizzas;
}

//5) Editar pizza do banco
P* EditarPizza(P* Pizzas, int PizzasLoja, I* ing, int IngredientesLoja, int edit, int uid){

    if(!ExistenciaIdP(uid, Pizzas, PizzasLoja)){

            printf("\nNao foi possivel editar pizza. Id nao encontrado!");
            return Pizzas;
    }

    if(edit == 1){

        char nome[50];
        printf("\nInforme o novo nome da Pizza: ");
        fgets(nome, 50, stdin);
        nome[strcspn(nome, "\n")] = '\0';

        for(int i = 0; i < PizzasLoja; i++){

            if(uid == Pizzas[i].id){

                strcpy(Pizzas[i].nome, nome);
            }
        }

        return Pizzas;

    } else if(edit == 2){

        char Ntam;
        printf("\nInforme o novo tamanho da Pizza (P - M - G -> Maiusculo): ");
        scanf(" %c", &Ntam);
        getchar();

        while(Ntam != 'P' && Ntam != 'M' && Ntam != 'G'){

            printf("\nTamanho invalido. Insira um que seja valido (P - M - G -> Maiusculo): ");
            scanf(" %c", &Ntam);
            getchar();
        }

        for(int i = 0; i < PizzasLoja; i++){

            if(uid == Pizzas[i].id){

                Pizzas[i].tamanho = Ntam;
                Pizzas[i].preco = CalcularPrecoPizza(Pizzas[i]);
            }
        }

        return Pizzas;

    } else if(edit == 3){

        float preco;
        printf("\nInforme o novo preco da Pizza: ");
        scanf("%f", &preco);
        getchar();

        if(preco <= 0){

            printf("\nNao foi possivel editar Pizza. Preco invalido!");
            return Pizzas;
        }

        for(int i = 0; i < PizzasLoja; i++){

            if(uid == Pizzas[i].id){

                Pizzas[i].preco = preco;
            }
        }

        return Pizzas;

    } else if(edit == 4){

        printf("\nPara editar ingredientes escolher a opcao 9!");
        return Pizzas;


    } else if(edit == 5){

        int novonum;
        printf("\nInforme o novo numero de pizzas deste sabor: ");
        scanf("%d", &novonum);
        getchar();

        if(novonum <= 0 || novonum > 50){

            printf("\nProcesso de edicao encerrado. Novo numero inserido invalido!");
            return Pizzas;
        }

        for(int i = 0; i < PizzasLoja; i++){

            if(uid == Pizzas[i].id){

                Pizzas[i].quantiaPizzas = novonum;
            }
        }
        return Pizzas;

    } else {

        printf("\nNao foi possivel editar pizza. Opcao invalida!");
        return Pizzas;
    }
}
//------------------------------------------------------------------------------Fim adicionar e remover dados


//Venda
float RealizarVenda(P* Pizzas, int PizzasLoja, I* ing, int IngredientesLoja, int edit, int idscan){

    int uid, pI, pP;
    if(edit == 1){

        printf("\nInforme pelo id qual ingrediente voce deseja adicionar: ");
        scanf("%d", &uid);
        getchar();

        if(!ExistenciaId(uid, ing, IngredientesLoja)){

            return -1.0;
        }

        pI = PosicaoPeloId(ing, IngredientesLoja, uid);
        pP = ReturnPositionPId(Pizzas, PizzasLoja, idscan);

        float venda = Pizzas[pP].preco + (ing[pI].preco * 0.7);
        Pizzas[pP].quantiaIngre--;

        return venda;
    } else if(edit == 2){

        pP = ReturnPositionPId(Pizzas, PizzasLoja, idscan);
        Pizzas[pP].quantiaIngre--;
        float venda = Pizzas[pP].preco;
    }
}


//Inclusoes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include "Ing.h"





///----------------------------------------------------------Funcoes extras

bool OkAlocI(I* Ingredientes){

    if(!Ingredientes){

        return false;
    }

    return true;
}


bool NumeroValidoMaxIng(int num){

    if(num <= 0 || num > 40){

        return false;
    }

    return true;
}


void ImprimirIngredientes(I* ing, int IngTotais){

    printf("\n===== Ingredientes  =====\n\n");

    for(int i = 0; i < IngTotais; i++){

        printf("Id: %d - Nome: %s - Preco: %.2f\n", ing[i].id, ing[i].nome, ing[i].preco);
    }

    printf("\n=========================\n\n");
}


bool ExistenciaId(int uid, I* ingTotais, int IngredientesLoja){

    for(int i = 0; i < IngredientesLoja; i++){

        if(ingTotais[i].id == uid){

            return true;
        }
    }
    return false;
}


int DefinirId(I* ingTotais, int IngredientesLoja){

    //Definir dados
    int uid = 0;

    ImprimirIngredientes(ingTotais, IngredientesLoja - 1);

    printf("\nCom base nos numeros. Digite um Id que seja diferente de um existente para o novo ingrediente: ");
    scanf("%d", &uid);
    getchar();

    //Retornar -1 para manipulacao do erro
    if(ExistenciaId(uid, ingTotais, IngredientesLoja) || uid <= 0){

        printf("\nId inserido invalido. Voltando ao menu!");
        return -1;
    }

    return uid;
}


bool IdJaInserido(int uid, I* ingredientesPizza, int numIngredientes){

    for(int i = 0; i < numIngredientes; i++){

        if(ingredientesPizza[i].id == uid){

            return true;
        }
    }
    return false;
}


I IngredienteReturnId(int uid, I* ingTotais, int IngredientesLoja){

    I lixo;

    lixo.id = -1;
    strcpy(lixo.nome, "falha");
    lixo.preco = -1;

    for(int i = 0; i < IngredientesLoja; i++){


        if(ingTotais[i].id == uid){

            return ingTotais[i];
        }
    }

    //Retornar lixo para manipulacao do erro
    return lixo;
}


int PosicaoPeloId(I* ingTotais, int IngredientesLoja, int uid){

    for(int i = 0; i < IngredientesLoja; i++){
        if(uid == ingTotais[i].id){

            return i;
        }
    }

    return -1;
}

///----------------------------------------------------------Fim Funcoes extras





///----------------------------------------------------------Gestao de memoria

I* AlocarTotalIng(int IngredientesLoja){


    //Verifica tamaho
    if(NumeroValidoMaxIng(IngredientesLoja)){
        I* ingTotais = (I*)malloc(IngredientesLoja * sizeof(I));

        //Testa alocacao
        if(OkAlocI(ingTotais)){

            for(int i = 0; i < IngredientesLoja; i++){

                //Inicializar
                ingTotais[i].id   = -1;
                strcpy(ingTotais[i].nome, "inicializar");
                ingTotais[i].preco = 0.0;
            }

            return ingTotais;
        } else {

            //Retorna NULL para manipulacao do erro
            return NULL;
        }
    }

    //Retorna NULL para manipulacao do erro
    return NULL;
}


void FreeIngredientes(I* IngredientesLoja){

    if(IngredientesLoja){

       free(IngredientesLoja);
    } else {

    }
}

I inicializar(){

    //Definir dados
    I ing;

    //Inicializar
    ing.id   = -1;
    strcpy(ing.nome, "inicializar");
    ing.preco = 0.0;

    return ing;
}

///----------------------------------------------------------Fim gestao de memoria






///----------------------------------------------------------Funcoes de cadastro

I* CadastroIngredientes(int* IngredientesLoja){

    //Verifica validade numero
    if(!NumeroValidoMaxIng(*IngredientesLoja)){

        printf("\nERROR: Número de ingredientes inválido!\n");
        return NULL;
    }

    //Alocacao com teste
    I* IngTotais = AlocarTotalIng(*IngredientesLoja);
    if(!OkAlocI(IngTotais)){

        printf("\nERROR: Nao foi possivel cadastrar, alocacao mal sucedida!");

        //Retorna NULL para manipulacao do erro
        return NULL;
    }

    //Cadastro
    for(int i = 0; i < *IngredientesLoja; i++){

        IngTotais[i].id = i + 1;

        printf("\nNome: ");
        fgets(IngTotais[i].nome, 50, stdin);
        IngTotais[i].nome[strcspn(IngTotais[i].nome, "\n")] = '\0';

        printf("Preco: ");
        scanf("%f", &IngTotais[i].preco);
        getchar(); // Limpar buffer
    }

    return IngTotais;
}

///----------------------------------------------------------Funcoes de cadastro







///----------------------------------------------------------Operacoes com arquivos

int LerQuantiaIBancoDeDados(char* filename){

    //Definir dados
    FILE* arq = fopen(filename, "rt");
    int IngredientesLoja;

    //Testa abertura do arquivo
    if(!arq){

       printf("\nNao foi possivel ler os dados, sem permissao para abrir arquivo!");

       //Retorna -1 para manipulacao do erro
       return -1;
    }

    //Ler valor
    fscanf(arq, "%d", &IngredientesLoja);
    if(!NumeroValidoMaxIng(IngredientesLoja)){

        printf("\nNao foi possivel ler os dados, cadastro nao foi feito ou valor lido invalido!");
        fclose(arq);

        //Retorna -1 para manipulacao do erro
        return -1;
    } else{


        fclose(arq);
        return IngredientesLoja;
    }
}


void BancoDeDadosGravarIng(char* filename, I* ingTotais, int IngredientesLoja){

    //Definir dados
    FILE* arq = fopen(filename, "wt");

    //Testa abertura do arquivo
    if(!arq){

        printf("\nERROR: Nao foi possivel gravar em arquivo, documento nao foi aberto!");
        return;
    }

    //Testa validade do numero
    if(!NumeroValidoMaxIng(IngredientesLoja)){

        printf("\nERROR: Nao foi possivel gravar arquivo, numero de dados invalidos!");
        fclose(arq);
        return;
    }

    //Quantia de dados
    fprintf(arq, "%d\n", IngredientesLoja);

    //Ingredientes
    for(int i = 0; i < IngredientesLoja; i++){

        fprintf(arq, "%d\n", ingTotais[i].id);
        fprintf(arq, "%s\n", ingTotais[i].nome);
        fprintf(arq, "%.2f\n", ingTotais[i].preco);

    }

    fclose(arq);
}


I* LerBancoDeDadosIngredientes(char* filename, int* IngredientesLoja){

    //Definir dado
    FILE* arq = fopen(filename, "rt");
    I* ingTotais;

    //Testa abertura do arquivo
    if(!arq){

       printf("\nNao foi possivel ler os dados. Sem permissao para abrir arquivo ou ele nao existe!");
       return NULL;
    }

    //Ler valores existente e verificar
    fscanf(arq, "%d", IngredientesLoja);
    if(!NumeroValidoMaxIng(*IngredientesLoja)){

        printf("\nNao foi possivel ler os dados. Cadastro de ingredientes nao foi feito ou valor lido invalido!");
        fclose(arq);
        return NULL;
    }

    //Reservar espaco
    ingTotais = AlocarTotalIng(*IngredientesLoja);
    if(!ingTotais){

        printf("\nNao foi possivel ler os dados. Falha na alocacao!");
        fclose(arq);
        return NULL;
    }

    //Copiar dados
    for(int i = 0; i < *IngredientesLoja; i++){

        // Ler ID
        if(fscanf(arq, "%d", &ingTotais[i].id) != 1){

            FreeIngredientes(ingTotais);
            fclose(arq);
            return NULL;
        }

        // Ler Nome
        if(fscanf(arq, " %49s", ingTotais[i].nome) != 1){

            FreeIngredientes(ingTotais);
            fclose(arq);
            return NULL;
        }

        // Ler Preço
        if(fscanf(arq, "%f", &ingTotais[i].preco) != 1){

            FreeIngredientes(ingTotais);
            fclose(arq);
            return NULL;
        }

    }

    fclose(arq);
    return ingTotais;
}


I BuscarIngredienteNoBanco(int idScan, int* IngredientesLoja){

    //Inicializar dado de falha
    I falha;

    falha.id = -1;
    strcpy(falha.nome, "inicializar");
    falha.preco = 0.0;

    //Definir dados
    *IngredientesLoja = LerQuantiaIBancoDeDados("ING.TXT");
    I* ingTotais = LerBancoDeDadosIngredientes("ING.TXT", IngredientesLoja);

    //Testar existencia de dados
    if(!ingTotais || !NumeroValidoMaxIng(*IngredientesLoja)){

        printf("\nNao foi possivel encontrar o ingrediente. Nao ha dados ou arquivo nao foi aberto");
        return falha;
    }

    //Procurar pelo Id
    for(int i = 0; i < *IngredientesLoja; i++){

        if(idScan == ingTotais[i].id){

            I resultado = ingTotais[i];
            FreeIngredientes(ingTotais);
            return resultado;
        }
    }

    printf("\nNao foi possivel encontrar o ingrediente. Ele nao existe. Favor digitar outro");
    FreeIngredientes(ingTotais);

    //Retorna falha para manipulacao do erro
    return falha;
}


///----------------------------------------------------------Fim Operacoes com arquivos







///----------------------------------------------------------OPERACOES COM DADOS

I* AdicionarIngrediente(I* ingTotais, int* IngredientesLoja){

    //Testar validade do numero
    if(!NumeroValidoMaxIng(*IngredientesLoja)){

        printf("\nERROR: Nao foi possivel adicionar ingrediente. Banco de dados cheio, ou numero de ingredientes incorreto!");
        return ingTotais;
    } else {

        // Alocar memória para o novo banco de dados
        I* add = AlocarTotalIng(*IngredientesLoja + 1);
        if(!add){

            printf("\nERROR: Nao foi possivel adicionar ingrediente. Erro de alocacao.");

            //Retorna banco antigo em caso de erro
            return ingTotais;
        }

        // Copiar dados existentes
        for(int i = 0; i < *IngredientesLoja; i++){

            add[i].id = ingTotais[i].id;
            strcpy(add[i].nome, ingTotais[i].nome);
            add[i].preco = ingTotais[i].preco;
        }


        //Id
        add[*IngredientesLoja].id = DefinirId(ingTotais, *IngredientesLoja + 1);

        if(add[*IngredientesLoja].id == -1){

            //Retorna banco antigo em caso de erro
            return ingTotais;
        }

        //Nome
        printf("\nDigite o nome do novo ingrediente: ");
        fgets(add[*IngredientesLoja].nome, 50, stdin);
        add[*IngredientesLoja].nome[strcspn(add[*IngredientesLoja].nome, "\n")] = '\0';

        //Preco
        printf("\nDigite o preco do novo ingrediente: ");
        scanf("%f", &add[*IngredientesLoja].preco);
        getchar();

        printf("\nIngrediente adicionado com sucesso!");
        (*IngredientesLoja)++;
        FreeIngredientes(ingTotais);
        return add;
    }
}


I* RemoverIngrediente(I* ingTotais, int* IngredientesLoja, int uid){


    //Definir dados
    int j = 0;

    //Testa validade do numero
    if(*IngredientesLoja - 1 <= 0){

        //Retorna NULL para manipulacao do erro
        return NULL;
    }

    //Aloca memoria e tesa
    I* rem = AlocarTotalIng(*IngredientesLoja - 1);
    if(!rem){

        printf("\nERROR: Nao foi possivel Remover ingrediente. Erro de alocacao.");

        //Retorna banco antigo em caso de erro
        return ingTotais;
    }

    for(int i = 0; i < *IngredientesLoja; i++){

        if(ingTotais[i].id != uid){

            rem[j].id = ingTotais[i].id;
            strcpy(rem[j].nome, ingTotais[i].nome);
            rem[j].preco = ingTotais[i].preco;
            j++;
        }
    }

    (*IngredientesLoja)--;
    FreeIngredientes(ingTotais);
    return rem;

}


I* IngredientesNovaPizza(int quantiaI, I* ingTotais, int ingredienteLoja){

    //Definir dados
    I* ingAdd = AlocarTotalIng(quantiaI);
    int uid, j = 0;

    //Testa alocacao
    if(!ingAdd){

        //Retorna NULL para manipulacao do erro
        return NULL;
    }

    //Imprime ingredientes para opcao
    ImprimirIngredientes(ingTotais, ingredienteLoja);
    for(int i = 0; i < quantiaI; i++){

        if(i == 0){

            printf("\nDefina pelo id os ingredientes que a pizza tera: ");
            scanf("%d", &uid);
            getchar();

            //Trava looping para insercao correta de dados
            while(!ExistenciaId(uid, ingTotais, ingredienteLoja)){

                printf("\nId invalido. Favor inserir um Id existente: ");
                scanf("%d", &uid);
                getchar();
            }

        } else {

            printf("\nDefina pelo id os ingredientes que a pizza tera: ");
            scanf("%d", &uid);
            getchar();

            //Trava looping para insercao correta de dados verificando se ha id existente
            while(!ExistenciaId(uid, ingTotais, ingredienteLoja) || IdJaInserido(uid, ingAdd, j)){

                printf("\nId invalido. Favor inserir um Id existente ou nao digitado: ");
                scanf("%d", &uid);
                getchar();
            }
        }

        ingAdd[i] = IngredienteReturnId(uid, ingTotais, ingredienteLoja);
        j++;

    }

    return ingAdd;
}


I* EditarIngrediente(I* ingTotais, int IngredientesLoja, int uid, int edit){

        //Definir dados
        int p;

        //Retorna o posicao pelo id
        for(int i = 0; i < IngredientesLoja; i++){

            if(uid == ingTotais[i].id){

                p = PosicaoPeloId(ingTotais, IngredientesLoja, uid);
            }
        }

        //Serie de opcao para edicao
        if(edit == 1){

           char nome[50];

           printf("\nInforme o novo nome do ingrediente: ");
           fgets(nome, 50, stdin);
           nome[strcspn(nome, "\n")] = '\0';
           strcpy(ingTotais[p].nome, nome);

           return ingTotais;

        } else if(edit == 2){

            int preco;

            printf("\nInforme o valor do novo preco: ");
            scanf("%d", &preco);
            getchar();

            if(preco <= 0){

                printf("\nERROR: Preco digitado invalido!");
                return ingTotais;
            }

            ingTotais[p].preco = preco;
            return ingTotais;

        } else {

            printf("\nNao foi possivel editar ingrediente. Componente do ingrediente nao encontrado. Tente novamente!");

            //Retorna banco antigo em caso de erro
            return ingTotais;
        }
}

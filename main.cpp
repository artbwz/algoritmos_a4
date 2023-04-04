#include<iostream>
#include<stdio.h>
#include<math.h>
#include<cstdio>
#include<fstream>
#include<locale.h>
#include<string>
#include<stdlib.h>

using namespace std;

//criar um sistema de cadastro de usuarios de plano de saude, com as seguintes informacoes:
//id, nome completo, idade, sexo, altura, peso, plano de saude, valor da mensalidade, data de   vencimento da mensalidade
//as informações devem ser armazenadas em um arquivo csv
//o programa deve permitir a busca de um usuario pelo id, nome completo ou plano de saude
//o programa deve permitir a alteração de qualquer informação do usuario
//o programa deve permitir a exclusão de um usuario
//o programa deve permitir a inclusão de um novo usuario
//o programa deve permitir a listagem e ordenação de todos os usuarios cadastrados, por nome, idade, sexo, altura, peso, plano de saude, valor da mensalidade, data de vencimento da mensalidade


//Repositorio interno.
const int REGS = 100;//Numero de registros.

//Colocar o caminho do arquivo.
#define nomeArquivo "C:\\Users\\artur\\Desktop\\cadastro.csv"

struct user{
    int id;
    char nome[REGS];
    int idade;
    char sexo;
    float altura;
    float peso;
    char plano[REGS];
    float valor;
    char data[REGS];
};

user dados[REGS];

int posicao = -1;

void create_user(){
    ++posicao;
    printf("Digite o nome do usuario: ");
    scanf("%s", &dados[posicao].nome);
    printf("Digite a idade do usuario: ");
    scanf("%d", &dados[posicao].idade);
}

void gravar_dados(){
    FILE* fp = NULL;
    fopen_s(&fp,nomeArquivo, "w");
    fprintf(fp,"%d\n", dados->id);
    for(int i = 0; i < REGS; i++){
        fprintf(fp,"%s\n", dados[i].nome);
        fprintf(fp,"%d\n", dados[i].idade);
    }
    fclose(fp);
}

int main(){
    create_user();
    gravar_dados();
}
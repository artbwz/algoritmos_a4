#include<iostream>
#include<stdio.h>
#include<math.h>
#include<cstdio>
#include<fstream>
#include<locale.h>
#include<string>
#include<stdlib.h>

using namespace std;

//criar um sistema de cadastro de funcionarios de uma empresa:
//os dados armazenados serão: id, nome, idade, genero, salario, departamento
//as informações devem ser armazenadas em um arquivo csv
//o programa deve permitir a busca de um usuario
//o programa deve permitir a alteração de qualquer informação do usuario
//o programa deve permitir a exclusão de um usuario
//o programa deve permitir a inclusão de um novo usuario


//Repositorio interno.
//const int REGS = 255;//Numero de registros.

//Colocar o caminho do arquivo.
const char* dir_arq = "C:\\Users\\artur\\Desktop\\";
char nome_arq[255];
const int REGS = 100; //Número de registros.

struct funcionario{
    char nome[40];
    int idade;
    char genero[10];
    float salario;
    char departamento[10];
};

funcionario dados[REGS];


int posicao = -1;

void tratar_linha(char buffer[]) {
    posicao++;
    char* token;
    char* next_token = NULL;
    token = strtok_s(NULL, ";", &next_token);
    strcpy_s(dados[posicao].nome,token);

    token = strtok_s(NULL, ";", &next_token);
    dados[posicao].idade = atoi(token);

    token = strtok_s(NULL, ";", &next_token);
    strcpy_s(dados[posicao].genero,token);

    token = strtok_s(NULL, ";", &next_token);
    dados[posicao].salario = atof(token);

    token = strtok_s(NULL, ";", &next_token);
    strcpy_s(dados[posicao].departamento,token);
}


void ler_arq() {
    cout << "Nome do arquivo: ";
    cin >> nome_arq;
    char arq_entrada[255];
    strcpy_s(arq_entrada, dir_arq);
    strcat_s(arq_entrada, nome_arq);
    strcat_s(arq_entrada, ".csv");
    ifstream fin(arq_entrada);
    char linha[255];
    while (!fin.eof()) {
        if (fin >> linha) {
            tratar_linha(linha);
        }
    }
    fin.close();
}

void salvar_arq() {
    cout << "Nome do arquivo: ";
    cin >> nome_arq;
    char arq_saida[255];
    strcpy_s(arq_saida, dir_arq);
    strcat_s(arq_saida, nome_arq);
    strcat_s(arq_saida, ".csv");
    ofstream fout(arq_saida);
    for (int i = 0; i <= posicao; i++) {
        fout << dados[i].nome << ";" << dados[i].idade <<";"<<dados[i].genero<<";"
            <<dados[i].salario<<";"<<dados[i].departamento << endl;
    }
    fout.flush();
    fout.close();
}


void criar_funcionario(){
    ++posicao;
    cout<< "Nome: ";
    cin>> dados[posicao].nome;
    cout <<"Idade: ";
    cin>> dados[posicao].idade;
    cout <<"Genero: (M/F)";
    cin>> dados[posicao].genero;
    cout <<"Salario: ";
    cin>> dados[posicao].salario;
    cout <<"Departamento: ";
    cin>> dados[posicao].departamento;
}

void imprimir() {
    printf("%2s %-40s %-3s %3s %10s %10s\n\n", " #", "Nome", "Idade", "Genero", "Salario", "Departamento");
    for (int i = 0; i <= posicao; i++) {
        printf("%2d %-40s %-3d %3s %10.2f %10s\n", i, dados[i].nome, 
                               dados[i].idade, dados[i].genero, dados[i].salario, dados[i].departamento);
    }
    printf("\n");
}

void trocar(int pos1, int pos2) {
    funcionario aux = dados[pos1];
    dados[pos1] = dados[pos2];
    dados[pos2] = aux;
}

void quick_sort_nome(int inicio, int fim) {
    if (inicio >= fim)
        return;
    char* pivot = dados[(inicio + fim) / 2].nome;
    int i = inicio;
    int j = fim;
    while (i <= j) {
        while (strcmp(dados[i].nome, pivot) < 0)
            i++;
        while (strcmp(dados[j].nome, pivot) > 0)
            j--;
        if (i <= j) {
            trocar(i, j);
            i++;
            j--;
        }
    }
    quick_sort_nome(inicio, j);
    quick_sort_nome(i, fim);
}

void quick_sort_idade(int inicio, int fim) {
    if (inicio >= fim)
        return;
    int pivot = dados[(inicio + fim) / 2].idade;
    int i = inicio;
    int j = fim;
    while (i <= j) {
        while (dados[i].idade < pivot)
            i++;
        while (dados[j].idade > pivot)
            j--;
        if (i <= j) {
            trocar(i, j);
            i++;
            j--;
        }
    }
    quick_sort_idade(inicio, j);
    quick_sort_idade(i, fim);
}


int pesquisa_binaria(char* nome) {
    int inicio = 0;
    int fim = posicao;
    int meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (strcmp(dados[meio].nome, nome) == 0)
            return meio;
        else if (strcmp(dados[meio].nome, nome) < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

int pesquisar_bin(int valor, int val[], int tam) {
    int pos = -1;
    int i = 0;
    int j = tam - 1;
    while (i <= j) {
        int meio = (i + j) / 2;
        if (val[meio] == valor) {
            pos = meio;
            break;
        }
        else if (val[meio] > valor) {
            j = meio - 1;
        }
        else {
            i = meio + 1;
        }
    }
    return pos;
}

int main(){

    int opcao;
    do {
        cout << "1 - Criar funcionario" << endl;
        cout << "2 - Ler arquivo" << endl;
        cout << "3 - Salvar arquivo" << endl;
        cout << "4 - Imprimir" << endl;
        cout << "5 - Ordenar por nome" << endl;
        cout << "6 - Ordenar por idade" << endl;
        cout << "7 - Pesquisar por nome" << endl;
        cout << "8 - Pesquisar por idade" << endl;
        cout << "0 - Sair" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        switch (opcao) {
        case 1:
            criar_funcionario();
            break;
        case 2:
            ler_arq();
            break;
        case 3:
            salvar_arq();
            break;
        case 4:
            imprimir();
            break;
        case 5:
            quick_sort_nome(0, posicao);
            break;
        case 6:
            quick_sort_idade(0, posicao);
            break;
        case 7:
            char nome[40];
            cout << "Nome: ";
            cin >> nome;
            int pos = pesquisa_binaria(nome);
            if (pos == -1)
                cout << "Nome nao encontrado" << endl;
            else
                cout << "Nome encontrado na posicao " << pos << endl;
            break;
        }
    } while (opcao != 0);
    return 0;

}
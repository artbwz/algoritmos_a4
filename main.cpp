#include<iostream>
#include<stdio.h>
#include<math.h>
#include<cstdio>
#include<fstream>
#include<locale.h>
#include<string>
#include<stdlib.h>

using namespace std;

//Todas as livrarias usadas neste codigo:
//iostream, math, fstream, locale, string, stdlib

/*criar um sistema de cadastro de funcionarios de uma empresa:
os dados armazenados serão: id, nome, idade, genero, salario, departamento
as informações devem ser armazenadas em um arquivo csv
o programa deve permitir a busca de um usuario
o programa deve permitir a alteração de qualquer informação do usuario
o programa deve permitir a exclusão de um usuario
o programa deve permitir a inclusão de um novo usuario*/



//Colocar o caminho do arquivo.
const char* dir_arq = "C:\\Users\\artur\\Desktop\\c++\\algoritmos_a4\\";
char nome_arq[255];

const int REGS = 255; //Número de registros.

//Struct para criar o objeto funcionario
struct funcionario {
    int id;
    char nome[40];
    int idade;
    char genero[10];
    float salario;
    char departamento[12];
};

funcionario dados[REGS];


int posicao = -1;

//tratamento das informações para exportação do arquivo.
void tratar_linha(char buffer[]) {
    posicao++;
    char* token;
    char* next_token = NULL;
    token = strtok_s(buffer, ";", &next_token);
    dados[posicao].id = atoi(token);
    token = strtok_s(NULL, ";", &next_token);
    strcpy_s(dados[posicao].nome, token);
    token = strtok_s(NULL, ";", &next_token);
    dados[posicao].idade = atoi(token);
    token = strtok_s(NULL, ";", &next_token);
    strcpy_s(dados[posicao].genero, token);
    token = strtok_s(NULL, ";", &next_token);
    dados[posicao].salario = atof(token);
    token = strtok_s(NULL, ";", &next_token);
    strcpy_s(dados[posicao].departamento, token);
}

//importação do arquivo
void ler_arq() {
    cout << "Nome do arquivo: ";
    cin >> nome_arq;
    char arq_entrada[255];
    strcpy_s(arq_entrada, dir_arq);
    strcat_s(arq_entrada, nome_arq);
    strcat_s(arq_entrada,".csv");
    ifstream fin(arq_entrada);
    char linha[255];
    if (!fin.is_open()) {
        cout << "Erro ao abrir o arquivo" << endl;
        return;
    }
    while (!fin.eof()) {
        if (fin >> linha) {
            tratar_linha(linha);
        }
    }
    fin.close();
}


//exportar as informações para um arquivo externo.
void salvar_arq() {
    cout << "Nome do arquivo: ";
    cin >> nome_arq;
    char arq_saida[255];
    strcpy_s(arq_saida, dir_arq);
    strcat_s(arq_saida, nome_arq);
    strcat_s(arq_saida, ".csv");
    ofstream fout(arq_saida);
    for (int i = 0; i <= posicao; i++) {
        fout <<dados[i].id << ";" << dados[i].nome << ";" << dados[i].idade << ";" << dados[i].genero << ";"
            << dados[i].salario << ";" << dados[i].departamento << endl;
    }
    fout.flush();
    fout.close();
}

//criar flag ordenado, e sempre que for inserir, excluir, alterar um funcionario ordenar o vetor.


//Função para inserir dados de um novo funcionario.
void criar_funcionario() {
    ++posicao;
    cout << "ID: ";
    cin >> dados[posicao].id;
    cout << "Nome: ";
    cin >> dados[posicao].nome;
    cout << "Idade: ";
    cin >> dados[posicao].idade;
    cout << "Genero: (M/F)";
    cin >> dados[posicao].genero;
    cout << "Salario: ";
    cin >> dados[posicao].salario;
    cout << "Departamento: ";
    cin >> dados[posicao].departamento;


}

void imprimir() {
    printf("%2s %-30s %-3s %8s %10s %15s\n\n", "ID", "Nome", "Idade", "Genero", "Salario", "Departamento");
    for (int i = 0; i <= posicao; i++) {
        printf("%2d %-30s %-3d %8s %11.2f %9s\n", dados[i].id, dados[i].nome,
            dados[i].idade, dados[i].genero, dados[i].salario, dados[i].departamento);
    }
    printf("\n");
}

void trocar(int pos1, int pos2) {
    funcionario aux = dados[pos1];
    dados[pos1] = dados[pos2];
    dados[pos2] = aux;
}

//alterar dado de um funcionario
void alterar_funcionario() {
    int id;
    imprimir();
    cout << "ID do funcionario: ";
    cin >> id;
    for (int i = 0; i <= posicao; i++) {
        if (dados[i].id == id) {
            cout << "Nome: " << dados[i].nome << endl;
            cin >> dados[i].nome;
            cout << "Idade: " << dados[i].idade << endl;
            cin >> dados[i].idade;
            cout << "Genero: (M/F)" << dados[i].genero << endl;
            cin >> dados[i].genero;
            cout << "Salario: " << dados[i].salario << endl;
            cin >> dados[i].salario;
            cout << "Departamento: " << dados[i].departamento << endl;
            cin >> dados[i].departamento;
            return;
        }
    }
    cout << "Funcionario nao encontrado" << endl;
}

//excluir funcionario
void excluir_funcionario() {
    int id;
    imprimir();
    cout << "ID do funcionario: ";
    cin >> id;
    for (int i = 0; i <= posicao; i++) {
        if (dados[i].id == id) {
            for (int j = i; j < posicao; j++) {
                dados[j] = dados[j + 1];
            }
            posicao--;
            return;
        }
    }
    cout << "Funcionario nao encontrado" << endl;
}

//quicksort para ordenar os nomes
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
};

//ordenadacao por idade bubblesort
void bubble_sort_idade() {
    for (int i = 0; i < posicao; i++) {
        for (int j = 0; j < posicao - i; j++) {
            if (dados[j].idade > dados[j + 1].idade) {
                trocar(j, j + 1);
            }
        }
    }
};

//bubblesort para ordenar por salario
void bubble_sort_salario() {
    for (int i = 0; i < posicao; i++) {
        for (int j = 0; j < posicao - i; j++) {
            if (dados[j].salario > dados[j + 1].salario) {
                trocar(j, j + 1);
            }
        }
    }
};

//busca sequencial para ordenar por departamento
void busca_sequencial_departamento() {
    for (int i = 0; i < posicao; i++) {
        for (int j = i + 1; j <= posicao; j++) {
            if (strcmp(dados[i].departamento, dados[j].departamento) > 0) {
                trocar(i, j);
            }
        }
    }
};

//buscar nome de um funcionario e imprimir seus dados usando busca binaria
void buscar_nome() {
    char nome[30];
    cout << "Nome: ";
    cin >> nome;
    int inicio = 0;
    int fim = posicao;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (strcmp(dados[meio].nome, nome) == 0) {
            printf("%2s %-30s %-3s %8s %10s %15s\n\n", "ID", "Nome", "Idade", "Genero", "Salario", "Departamento");
            printf("%2d %-30s %-3d %8s %11.2f %9s\n", dados[meio].id, dados[meio].nome,
                dados[meio].idade, dados[meio].genero, dados[meio].salario, dados[meio].departamento);
            printf("\n");
            return;
        }
        else if (strcmp(dados[meio].nome, nome) < 0) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }
    cout << "Funcionario nao encontrado" << endl;
};


int main() {
    int opcao;
    setlocale(LC_ALL, "Portuguese_Brazil");
    do {
        system("cls");
        cout << "1 - Ler arquivo" << endl;
        cout << "2 - Salvar arquivo" << endl;
        cout << "3 - Criar funcionario" << endl;
        cout << "4 - Imprimir" << endl;
        cout << "5 - Alterar funcionario" << endl;
        cout << "6 - Excluir funcionario" << endl;
        cout << "7 - Ordenar por nome" << endl;
        cout << "8 - Ordenar por idade" << endl;
        cout << "9 - Ordenar por salario" << endl;
        cout << "10 - Ordenar por departamento" << endl;
        cout << "11 - Buscar por nome" << endl;
        cout << "0 - Sair" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        if (opcao < 0 || opcao>11) {
            cout << "Opcao invalida" << endl;
            system("PAUSE");
        }
        else {
            system("PAUSE");
            switch (opcao) {
            case 1:
                system("cls");
                ler_arq();
                system("PAUSE");
                break;

            case 2:
                system("cls");
                salvar_arq();
                system("PAUSE");
                break;

            case 3:
                system("cls");
                criar_funcionario();
                system("PAUSE");
                break;

            case 4:
                system("cls");
                imprimir();
                system("PAUSE");
                break;

            case 5:
                system("cls");
                alterar_funcionario();
                system("PAUSE");
                break;

            case 6:
                system("cls");
                excluir_funcionario();
                system("PAUSE");
                break;
            
            case 7:
                system("cls");
                quick_sort_nome(0, posicao);
                cout << "Ordenado por nome." << endl;
                imprimir();
                system("PAUSE");
                break;
            
            case 8:
                system("cls");
                bubble_sort_idade();
                cout << "Ordenado por idade." << endl;
                imprimir();
                system("PAUSE");
                break;
               
            case 9:
                system("cls");
                bubble_sort_salario();
                cout << "Ordenado por salario." << endl;
                imprimir();
                system("PAUSE");
                break;

            case 10:
                system("cls");
                busca_sequencial_departamento();
                cout << "Ordenado por departamento." << endl;
                imprimir();
                system("PAUSE");
                break;

            case 11:
                system("cls");
                buscar_nome();
                system("PAUSE");
                break;

            }
        }
    } while (opcao != 0);
    return 0;

}
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

string palavra_secreta;
map<char, bool> chutou;
vector<char> chutes_errados;

bool letra_existe (char chute) {
    /*for (int = 0; i < palavra_secreta.size(); i++){
        if(chute == palavra_secreta[i]){
            return true;
        } }*/
    for (char letra : palavra_secreta) {
        if (chute == letra) {
            return true;
        }
    }
    return false;
}

bool nao_acertou () {
    for (char letra : palavra_secreta) {
        if (!chutou[letra]) {
            return true;
        }
    }
    return false;
}

bool nao_enforcou () {
    return chutes_errados.size() < 5;

}

void imprime_cabecalho () {
    cout << "*********************" << endl;
    cout << "*** Jogo da Forca ***" << endl;
    cout << "*********************" << endl;
    cout << endl;
}

void imprime_erros () {

     cout << "Chutes errados: ";
        for (char letra : chutes_errados) { //imprimir chutes errados
            cout <<letra<< " ";
        }
        cout <<endl;

}

void imprime_palavra() {
     for(char letra : palavra_secreta) { //imprimir a palavra
        if(chutou[letra]) {
            cout << letra<<" ";
        } else {
            cout <<"_ ";
        }
    }
    cout << endl;
}

void chuta () {
    cout << "Chute uma letra: "<< endl;
    char chute_letras;
    cin >> chute_letras;

    chutou[chute_letras] = true;
    
    if (letra_existe(chute_letras)) {
        cout <<"Seu acertou! Seu chute está na palavra."<< endl;
    } else{
        cout <<"Seu errou! Seu chute não está na palavra."<< endl;
        chutes_errados.push_back(chute_letras);
    }
     cout << endl;

}

vector<string> le_arquivo() {
    ifstream arquivo;
   
    arquivo.open("palavras.txt");

    if (arquivo.is_open()) {
    int quantidade_palavras;
    arquivo >> quantidade_palavras;

    //cout <<"O arquivo possui " <<quantidade_palavras<<" palavras."<<endl;

    vector<string> palavra_do_arquivo;
    
    for (int i = 0; i <quantidade_palavras; i++) {
        string palavra_lida;
        arquivo >> palavra_lida;
       // cout << "Na linha "<< i << " : "<< palavra_lida<<endl;
        palavra_do_arquivo.push_back(palavra_lida);
    }
    arquivo.close();
    return palavra_do_arquivo;
    
    } else {
        cout <<"Não foi possível acessar banco de palavras :("<<endl;
        exit(0);
    }
}

void sorteia_palavra() {
    vector<string> palavras = le_arquivo();

    srand(time(NULL));
    int indice_sorteado = rand()% palavras.size();

    palavra_secreta = palavras[indice_sorteado];

}

void salva_arquivo(vector<string> nova_lista) {
    ofstream arquivo;//output escrita de valores em um arquivo 
   
    arquivo.open("palavras.txt");

    if (arquivo.is_open()) {
        arquivo<<nova_lista.size() << endl;

        for(string palavra: nova_lista) {
            arquivo << palavra<<endl;
        }
        arquivo.close();
    }
    else{
        cout <<"Não foi possível acessar banco de palavras :("<<endl;
        exit(0);

    }
}

void adiciona_palavra(){
    cout << "Digite a nova palavra usando letras maiusculas."<<endl;
    string nova_palavra;
    cin >> nova_palavra;

    vector<string> lista_palavras = le_arquivo();
    lista_palavras.push_back(nova_palavra);

    salva_arquivo(lista_palavras);
}

int main () {

    imprime_cabecalho ();
    le_arquivo();
    sorteia_palavra();

    while (nao_acertou () && nao_enforcou ()) {

    imprime_erros();
    imprime_palavra();
    chuta();

    }
    cout <<"Fim de jogo!"<<endl;
    cout <<"A palavra secreta era: "<<palavra_secreta << endl;
    
    if(nao_acertou()) {
    cout <<"Você perdeu! Tente novamente!" << endl;
    } else {
        cout <<"Parabéns! Você acertou a palavra secreta!" << endl;

        cout <<"Você deseja adicionar uma nova palavr ao banco? (S/N)"<<endl;
        char resposta;
        cin >> resposta;
        if(resposta =='S'){
            adiciona_palavra();
        }else{

        }
    }
}
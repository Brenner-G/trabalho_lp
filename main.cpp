#include <iostream>
#include <vector>
#include <list>

#define TAM 20

using namespace std;

struct Heap{
    bool vazio; //true = posição vazia, false = posição ocupada
    char nome; // id da memória
};

struct AreaLivre{
    int endereco;   // Endereço inicial da área livre no heap
    int qtd;    // Quantidade de blocos livres contíguos da área
};

vector<Heap> InicializarHeap(){
    vector<Heap> heap;
    for(int i = 0;i<TAM;i++){
        struct Heap b{true};
        heap.push_back(b);
    }
    return heap;
}

vector<AreaLivre> InicializarLista(){
    struct AreaLivre a{0,TAM + 1};
    vector<AreaLivre> HeapLivre;
    HeapLivre.push_back(a);
    return HeapLivre;
}

vector<AreaLivre> AtualizarLista(vector<Heap> heap){
    int i,j;
    vector<AreaLivre> temp;
    for(i=0;i<heap.size();i++){
        if(heap[i].vazio){
            for(j=i;j<heap.size();j++){
                if(!heap[j].vazio){
                    break;
                }
            }
            struct AreaLivre temp2{i,j-i};
            temp.push_back(temp2);
            i = j;
        }
    }
    return temp;
}

void AlteraHeap(struct AreaLivre temp,vector<Heap>& heap,char nome, int tam){
    for(int j = temp.endereco;j<temp.endereco + tam;j++){
        struct Heap b{false,nome};
        heap[j] = b;
    }
}

void FirstFit(vector<Heap>& heap, vector<AreaLivre>& HeapLivre, int tam,char nome){
    bool entrou = false;
    // Percorrer a Lista de Area Livre
    for(int i =0;i<HeapLivre.size();i++){
        // Verificar se exite na Lista uma sequência de blocos que corresponde com o tamanho da nova inserção
        if(HeapLivre[i].qtd >= tam){
            entrou = true;
            // Alterar o Heap
            AlteraHeap(HeapLivre[i],heap,nome,tam);
            // Alterar a lista de Area Livre
            HeapLivre = AtualizarLista(heap);
            break;
        }
    }
    if(!entrou){
        cout << "Não foi encontrado nenhum espaço Livre no Heap" << endl;
    }
}

void BestFit(vector<Heap>& heap, vector<AreaLivre>& HeapLivre, int tam, char nome) {
    bool entrou = false;
    int dif = TAM + 1; // Inicializa com um valor maior do que qualquer diferença possível
    struct AreaLivre temp{};
    // Percorrer a Lista de Área Livre
    for(auto & i : HeapLivre){
        // Verificar se existe na Lista uma sequência de blocos que corresponde ao tamanho da nova inserção
        if (i.qtd >= tam) {
            entrou = true;
            int novaDif = i.qtd - tam;
            if (novaDif < dif){
                dif = novaDif;
                temp = i;
            }
        }
    }
    if(entrou){
        // Alterar o Heap
        AlteraHeap(temp, heap, nome, tam);
        // Alterar a lista de Área Livre
        HeapLivre = AtualizarLista(heap);
    }
    else {
        cout << "Não foi encontrado nenhum espaço livre no Heap" << endl;
    }
}


void Alocar(vector<Heap>& heap, vector<AreaLivre>& HeapLivre,bool ff){
    char nome;
    int tam;
    cout << "Digite o ID: ";
    cin >> nome;
    cout << endl;
    cout << "Digite o tamanho: ";
    cin >> tam;
    cout << endl;
    if(ff)
        FirstFit(heap,HeapLivre,tam,nome);
    else
        BestFit(heap,HeapLivre,tam,nome);
}

void Deletar(vector<Heap>& heap,vector<AreaLivre>& HeapLivre,char nome) {
    bool achou = false;
    for(int i =0;i<size(heap);i++){
        if(nome == heap[i].nome){
            achou = true;
            struct Heap temp{true};
            heap[i] = temp;
        }
    }
    if(achou)
        HeapLivre = AtualizarLista(heap);
    else
        cout << "ID nao encontrado" << endl;
}

void ChamarDeletar(vector<Heap>& heap, vector<AreaLivre>& HeapLivre){
    char nome;
    cout << "Digite o ID: ";
    cin >> nome;
    Deletar(heap,HeapLivre,nome);
}

void PrintaHeap(vector<Heap> heap){
    for(int i = 0; i < size(heap);i++){
        if(heap[i].vazio){
            cout << " ";
        }
        else{
            cout << heap[i].nome << " ";
        }
        cout << "|";
    }
    cout << endl;

}

void PrintaLista(vector<AreaLivre> HeapLivre){
    for(int i = 0; i < size(HeapLivre);i++){
        cout << HeapLivre[i].endereco << "|" << HeapLivre[i].qtd << "--> ";
    }
    cout << endl;
}

void imprimirMenu() {
    cout << "MENU" << endl;
    cout << "1 - Inserir Fist-Fit" << endl;
    cout << "2 - Inserir Best-Fit" << endl;
    cout << "3 - Deletar" << endl;
    cout << "4 - Printar o Heap" << endl;
    cout << "5 - Printar a Lista de Areas Livres" << endl;
    cout << "6 - Encerrar o programa" << endl;
    cout << "Digite a opcao desejada: ";
}

int main(){
    vector<Heap> heap = InicializarHeap(); //vetor que simula o heap com TAM de tamanho
    vector<AreaLivre> HeapLivre = InicializarLista();
    int opcao;
    do{
        imprimirMenu();
        cin >> opcao;
        cout << endl;

        switch(opcao){
            case 1:
                Alocar(heap,HeapLivre,true);
                break;
            case 2:
                Alocar(heap,HeapLivre,false);
                break;
            case 3:
                ChamarDeletar(heap,HeapLivre);
                break;
            case 4:
                PrintaHeap(heap);
                break;
            case 5:
                PrintaLista(HeapLivre);
                break;
            case 6:
                cout << "Programa encerrado." << endl;
                break;
            default:
                cout << "Opcao invalida. Digite novamente." << endl;
        }
        cout << endl;
    }while(opcao != 6);
    return 0;
}

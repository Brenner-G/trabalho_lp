#include <iostream>
#include <vector>
#include <list>

#define TAM 20

using namespace std;

struct Heap{
    bool vazio; //true = posição vazia, false = posição ocupada
    char nome; // id da memória
};
// Estrutura para representar cada nó da lista de áreas livres
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

vector<AreaLivre> InicializarList(){
    struct AreaLivre a{0,TAM + 1};
    vector<AreaLivre> HeapLivre;
    HeapLivre.push_back(a);
    return HeapLivre;
}

vector<AreaLivre> AtualizarLista(vector<Heap> heap){
    int i,j;
    vector<AreaLivre> temp;
    for(i=0;i<size(heap);i++){
        if(heap[i].vazio){
            for(j=i;j<size(heap);j++){
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

void FirstFit(vector<Heap>& heap, vector<AreaLivre>& HeapLivre, int tam,char nome){
    bool entrou = false;
    // Percorrer a Lista de Area Livre
    for(int i =0;i<HeapLivre.size();i++){
        // Verificar se exite na Lista uma sequência de blocos que corresponde com o tamanho da nova inserção
        if(HeapLivre[i].qtd >= tam){
            entrou = true;
            struct AreaLivre a = HeapLivre[i];
            // Alterar o heap
            for(int j = a.endereco;j<a.endereco + tam;j++){
                struct Heap b{false,nome};
                heap[j] = b;
            }
            // Alterar a lista de Area Livre
            HeapLivre = AtualizarLista(heap);
            break;
        }
    }
    if(!entrou){
        cout << "Não foi encontrado nenhum espaço Livre no Heap" << endl;
    }
}

void ChamarFirstFit(vector<Heap>& heap, vector<AreaLivre>& HeapLivre){
    char nome;
    int tam;
    cout << "Digite o ID: ";
    cin >> nome;
    cout << endl;
    cout << "Digite o tamanho: ";
    cin >> tam;
    cout << endl;
    FirstFit(heap,HeapLivre,tam,nome);
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
    cout << "2 - Inserir Next-Fit" << endl;
    cout << "3 - Deletar" << endl;
    cout << "4 - Printar o Heap" << endl;
    cout << "5 - Printar a Lista de Areas Livres" << endl;
    cout << "6 - Encerrar o programa" << endl;
    cout << "Digite a opcao desejada: ";
}

int main(){
    vector<Heap> heap = InicializarHeap(); //vetor que simula o heap com TAM de tamanho
    vector<AreaLivre> HeapLivre = InicializarList();
    int opcao;
    do{
        imprimirMenu();
        cin >> opcao;
        cout << endl;

        switch(opcao){
            case 1:
                ChamarFirstFit(heap,HeapLivre);
                break;
            case 2:

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

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class NodoBinario {
   public:

   int valor;
   string str;
   int FB;
   NodoBinario *Hizq, *Hder, *siguiente, *anterior;


    NodoBinario(int num, string cliente, NodoBinario *der = NULL, NodoBinario *izq = NULL, NodoBinario *sig=NULL, NodoBinario *ant=NULL):
        Hizq(izq), Hder(der), valor(num),str(cliente),siguiente(sig), anterior(ant), FB(0) {}

    void InsertaBinario(int num,string cliente);
};

typedef NodoBinario *pNodoBinario;

class Binario{
public:
    pNodoBinario raiz;

    Binario():raiz(NULL){}

    void InsertaNodo(int num, string str);
    void PreordenI();
    void InordenI();
    void PostordenI();

    bool Hh;

    void Borrar(NodoBinario *nodoB, bool);
    void BorrarBalanceado(NodoBinario *r, bool, int eliminar);
    void InsertarBalanceado(NodoBinario *r, bool, int x);
    void insertarIndices();


};

void NodoBinario::InsertaBinario(int num,string str)
{
    if(num<valor){
        if(Hizq==NULL){
            Hizq = new NodoBinario(num,str);
        }else{
            Hizq->InsertaBinario(num,str);
        }
    }else{
        if(Hder==NULL){
            Hder = new NodoBinario(num,str);
        }else{
            Hder->InsertaBinario(num,str);
        }
    }
}

void Binario::InsertaNodo(int num,string str)
{
    if(raiz==NULL){
        raiz = new NodoBinario(num,str);
    }else{
        raiz->InsertaBinario(num,str);
    }
}

void PreordenR(NodoBinario *R){

    if(R==NULL){
        return;
    }else{
        cout<<R->valor<<" - ";
        PreordenR(R->Hizq);
        PreordenR(R->Hder);
    }
}

void InordenR(NodoBinario *R){

    if(R==NULL){
        return;
    }else{
        InordenR(R->Hizq);
        cout<<R->valor<<","<<R->str<<" - ";
        InordenR(R->Hder);
    }
}

void PostordenR(NodoBinario *R){

    if(R==NULL){
        return;
    }else{
        PostordenR(R->Hizq);
        PostordenR(R->Hder);
        cout<<R->valor<<" - ";
    }
}

string getSegmento(string str, int pos){
  string segmento;
  int cont = 1;
  stringstream stream(str);
  string resultado;
  while (getline(stream, segmento, ','))
  {
    if (cont == pos){
      resultado = segmento;
    }
    cont++;
  }
  return resultado;
}


void Binario::insertarIndices(){
  std::ifstream Archivo("Indices.txt");
  string str;
  string segmento;
  int llave;

  while (std::getline(Archivo, segmento))
  {
    cout<<segmento<<endl;
    llave = stoi(getSegmento(segmento,2));
    str = getSegmento(segmento,1);
    InsertaNodo(llave,str);

  }
}
void CrearIndices(){
  //Lee Clientes y copia el contenido en Indices
  std::ofstream borrar("Indices.txt");//Para borrar datos residuo
  std::ofstream arch1("Indices.txt",fstream::app);
  string archivo = "Clientes.txt";
  string expresion;
  int cont = 0;
  std::ifstream Archivo(archivo);
	std::string str;
  while (std::getline(Archivo, str)) {
    expresion = str;
    cont++;
    expresion = to_string(cont)+","+expresion;
    arch1 << expresion << std::endl;

  }
}
/*void Binario::IngresarExpresion(string expresion){
  //separa la expresion y la mete en un nodo que después se ingresa a la cola
  string v = "";
  int a = 0;|
  bool f = false;
  if (isdigit(expresion[0])){
    while (isdigit(expresion[a])){
      v = v+expresion[a];
      a++;
    }
    expresion.erase(0,a-1);
  }
  else
    v = expresion[0];
  pnodo aux = new nodo(v);
  insertar(aux);
  for(std::string::size_type cont = 1; cont < expresion.length();cont++){
    v = "";
    if (isdigit(expresion[cont]) == false){
      v = expresion[cont];
    }
    else{
      while (isdigit(expresion[cont])){
        v = v+expresion[cont];
        cont++;
        f = true;
      }
      if (f){
        f = false;
        cont--;
      }
    }
    aux->siguiente = new nodo(v);
    aux = aux->siguiente;
  }
}*/
int main(){
  Binario Arbol;
  CrearIndices();
  Arbol.insertarIndices();
  InordenR(Arbol.raiz);
  cin.get();
  return 0;
}

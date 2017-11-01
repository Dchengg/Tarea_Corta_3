#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


class nodo {
   public:
    nodo(string v)
    {
       valor = v;
       siguiente = NULL;
       anterior = NULL;
    }

nodo(string v, nodo * signodo)
    {
       valor = v;
       siguiente = signodo;
    }

   private:
    string valor;
    nodo *siguiente;
    nodo *anterior;


   friend class lista;
};

typedef nodo *pnodo;

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

class lista {
public:
	lista() { primero = actual = NULL; }
	~lista();

  bool ListaVacia() { return primero == NULL; }
  void Mostrar();
  void CargarMemoria(int indice);
  void InsertarFinal(string v);


protected:
	pnodo primero;
	pnodo actual;
};

lista::~lista()
{
	pnodo aux;
	while (primero) {
		aux = primero;
		primero = primero->siguiente;
		delete aux;
	}
	actual = NULL;
}


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
void lista::Mostrar()
{
   pnodo aux=primero;
   while(aux->siguiente!=primero)
     {

      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->valor<<"->";
     cout<<endl;
}
void lista::InsertarFinal(string v)
{
	if (ListaVacia()){
		primero = new nodo(v);
  }
	else
	{
		pnodo aux = primero;
		while (aux->siguiente != NULL)
			aux = aux->siguiente;
		aux->siguiente = new nodo(v);
	}
}
void lista::CargarMemoria(int indice){
  int pos;
  int times;
  int cont = 0;
  string cliente;
  std::ifstream Clientes("Clientes.txt");
  times = indice/20;
  pos = indice%20;
  while(times != cont){
    for(int i = 0;i < 20;i++){
      getline(Clientes,cliente);
      InsertarFinal(cliente);
    }
    cont++;
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
int main(){
  Binario Arbol;
  lista Mem;
  CrearIndices();
  Arbol.insertarIndices();
  InordenR(Arbol.raiz);
  cout<<endl;
  Mem.CargarMemoria(35);
  Mem.Mostrar();
  cin.get();
  return 0;
}

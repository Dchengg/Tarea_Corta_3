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
    void indexar();
    void insertarCliente();
    void limpiar();
    void EliminarCliente (int cedula);
};

class lista {
public:
	lista() { primero = actual = NULL; }
	~lista();

  bool ListaVacia() { return primero == NULL; }
  void Mostrar();
  void CargarMemoria(int indice);
  void InsertarFinal(string v);
  void BorrarInicio();
  void limpiar();


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
    // cout<<segmento<<endl;
    llave = stoi(getSegmento(segmento,2));
    str = getSegmento(segmento,1);
    InsertaNodo(llave,str);

  }
}

void lista::Mostrar()
{
   pnodo aux=primero;
   while(aux->siguiente!=NULL)
     {

      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->valor<<"->";
     cout<<endl;
}

void lista::InsertarFinal(string v){
	if (ListaVacia()){
		primero = new nodo(v);
  }
	else{
		pnodo aux = primero;
		while (aux->siguiente != NULL)
			aux = aux->siguiente;
		aux->siguiente = new nodo(v);
	}
}

void lista::BorrarInicio(){
	if (ListaVacia())
		cout << "No hay elementos en la lista:" << endl;
	else {
		if (primero->siguiente == NULL) {
			primero = NULL;
		}
		else {

			pnodo aux = primero;
			primero = primero->siguiente;
			delete aux;
		}
	}
}

void lista::limpiar(){
	while (!ListaVacia())
	{
		BorrarInicio();
	}
}

void lista::CargarMemoria(int indice){
  int pos;
  int times;
  int cont = -1;
  string cliente;
  std::ifstream Clientes("Clientes.txt");
  times = indice/21;
  pos = indice%20;
  while(times != cont){
    limpiar();
    for(int i = 0;i < 20;i++){
      getline(Clientes,cliente);
      InsertarFinal(cliente);
    }
    cont++;
  }
}

void Binario::limpiar(){
  raiz = NULL;
}

void Binario::insertarCliente(){
  std::ofstream Archivo("Clientes.txt",fstream::app);
  string cliente;
  string nombre;
  string cedula;
  cout<<"Ingrese el nombre del cliente: ";
  cin>>nombre;
  cout<<endl<<"Ingrese el numero de cedula del cliente :";
  cin>>cedula;
  cout<<endl;
  cliente = cedula+','+nombre;
  Archivo<<cliente <<endl;
  indexar();
  cout<<"El cliente "<<cliente<<" ha sido agregado"<<endl;
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
    if (str.back() != '1'){
      expresion = str;
      cont++;
      expresion = to_string(cont)+","+expresion;
      arch1 << expresion << std::endl;
    }
  }
}

void Binario::indexar(){
  CrearIndices();
  limpiar();
  insertarIndices();
}

/*void Binario::Borrar(NodoBinario* D){
  NodoBinario *q;
  if (D->Hder != NULL)
    Borrar(D->Hder);
  else{
    q->valor = D->valor;
    q = D;
    D = D->Hizq;
  }
}

void Binario::BorrarBalanceado(NodoBinario *raiz, int x){
  NodoBinario *q;
  cout << "raiz:  " << raiz->valor << endl;
  if (raiz != NULL){
    if (x < raiz->valor){
      cout << "entro" << endl;
      BorrarBalanceado(raiz->Hizq, x);
    }
    else{
      if (x > raiz->valor){
        cout << "entro 2" << endl;
        BorrarBalanceado(raiz->Hder, x);
      }
      else
        q = raiz;
    }
    if (q->Hder == NULL){
      cout << "entro 3" << endl;
      raiz = q->Hizq;
    }
    else{
      if (q->Hizq == NULL){
        raiz = q->Hder;
      }
    }
  }
  else{
    Borrar(q->Hizq);
  }
}*/


void AgregarUno(string cedula){
  string str, str2;
  ifstream original ( "Clientes.txt" );
  ofstream copia ( "Clientes2.txt" );
  while (!original.eof()){
      getline(original,str);
      str2 = str;
      if (getSegmento(str,1) == cedula)
        str2 = str + ",1";
      copia << str2 << endl;
  }
  original.close();
  copia.close();
  remove("Clientes.txt");
  rename("Clientes2.txt","Clientes.txt");
  ifstream original2 ( "Clientes.txt" );
  ofstream copia2 ( "Clientes2.txt" );
  string linea;
  while ( getline( original2, linea ) ) {
    if ( ! linea.empty() ) {
        copia2 << linea << '\n';
    }
  }
  original2.close();
  copia2.close();
  remove("Clientes.txt");
  rename("Clientes2.txt","Clientes.txt");
}

void Binario::EliminarCliente (int cedula){
  //if (BorrarBalanceado(raiz,cedula)){
  string cedulaString = to_string(cedula);
  AgregarUno(cedulaString);
  //}
  //else{
    //cout << "La cédula que digito no existe" << endl;
  //}
}

int main(){
  Binario Arbol;
  lista Mem;
  int opcion;
  CrearIndices();
  Arbol.insertarIndices();
  bool seguirTrabajando = true;
  while (seguirTrabajando){
    cout << "Bievenido" << endl;
    cout << "Digite el numero de la accion que desea realizar :" << endl;
    cout << "    1. Indexar" << endl;
    cout << "    2. Agregar un cliente" << endl;
    cout << "    3. Eliminar un cliente" << endl;
    cout << "    99. Mostrar recorridos" << endl;
    cout << "    100. Salir" << endl;
    cin >> opcion;
    if(opcion == 1)
      Arbol.indexar();
    else if(opcion == 2)
      Arbol.insertarCliente();
    else if(opcion == 3){
      int clienteAEliminar;
      cout << endl << "Digite la cedula del cliente que desea eliminar: ";
      cin >> clienteAEliminar;
      Arbol.EliminarCliente(clienteAEliminar);
      Arbol.indexar();
    }
    else if(opcion == 99){
      cout << "Inorden: " << endl;
      InordenR(Arbol.raiz);
      cout << endl << endl << "Preorden: " << endl;
      PreordenR(Arbol.raiz);
      cout << endl << endl << "Postorden: " << endl;
      PostordenR(Arbol.raiz);
    }
    else if(opcion == 100)
      seguirTrabajando = false;
    else
      cout<<"Por favor digite una opcion valida"<<endl;
  }
  cin.get();
  return 0;
}

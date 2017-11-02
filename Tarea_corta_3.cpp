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

    void Borrar(NodoBinario *nodoB);
    void BorrarBalanceado(NodoBinario *r, int eliminar);
    void insertarIndices();
    void indexar();
    int insertarCliente();
    void limpiar();
    string EliminarCliente (int cedula);
    int Buscar(NodoBinario *raiz, int x);

};

class lista {
public:
	lista() { primero = actual = NULL; }
	~lista();

  bool ListaVacia() { return primero == NULL; }
  void Mostrar();
  string BuscarMemoria(int indice,string type);
  void CargarMemoriaBusqueda(int indice);
  void CargarMemoriaInsertar(int indice);
  void InsertarFinal(string v);
  void BorrarInicio();
  void limpiar();
  void BorrarMemoria(string cliente);



protected:
	pnodo primero;
	pnodo actual;
  int Inicio;
  int Final;
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

void lista::CargarMemoriaInsertar(int indice){
  Inicio = indice-19;
  if(Inicio <=0){
    Inicio = 1;
  }
  Final = indice;
  int cont = 1;
  string cliente;
  std::ifstream Indices("Indices.txt");
  limpiar();
  while(Final >= cont){
    getline(Indices,cliente);
    if(cliente == ""){
      break;
    }
    if(Inicio <= cont){
      cout<<Inicio<<" == "<<cont<<endl;
      cliente = cliente.substr(cliente.find(",")+1);
      InsertarFinal(cliente);
      }
      cont++;
    }
}

void lista::CargarMemoriaBusqueda(int indice){
  Inicio = indice;
  Final = indice+20;
  int cont = 1;
  string cliente;
  std::ifstream Indices("Indices.txt");
  limpiar();
  while(Final != cont){
    getline(Indices,cliente);
    if(cliente == ""){
      break;
    }
    if(Inicio <= cont){
      cliente = cliente.substr(cliente.find(",")+1);
      cout<<cliente<<endl;
      InsertarFinal(cliente);
      }
      cont++;
    }
}
string lista::BuscarMemoria(int indice,string type){
  string cliente;
  string v;
  int cont = Inicio;
  pnodo aux = primero;
  if(Inicio <= indice && Final >= indice){
    while(cont != indice){
      aux = aux->siguiente;
      cont++;
    }
    cliente = aux->valor;
    return cliente;

  }
  if(type == "Busqueda"){
    CargarMemoriaBusqueda(indice);
    cliente = BuscarMemoria(indice,"Busqueda");
    return cliente;
  }else{
    CargarMemoriaInsertar(indice);
    cliente = BuscarMemoria(indice,"Insertar");
    return cliente;
  }
}
void lista::BorrarMemoria(string cliente){
  Mostrar();
  pnodo aux = primero;
  while(aux != NULL){
    if(cliente == aux->valor){
      if(primero->siguiente == NULL){
        primero = NULL;
      }else if(aux == primero){
        primero = primero->siguiente;
        delete aux;
      }else{
        pnodo temp = primero;
        while(temp->siguiente != aux){
          temp = temp->siguiente;
        } 
        temp->siguiente = aux->siguiente;
        aux->siguiente = NULL;
        delete aux;
      }
    }
    aux = aux->siguiente;
  }
}
void Binario::limpiar(){
  raiz = NULL;
}


int Binario::insertarCliente(){
  std::ofstream Archivo("Clientes.txt",fstream::app);
  string cliente;
  string nombre;
  string cedula;
  int v;
  int indice;
  cout<<"Ingrese el nombre del cliente: ";
  cin>>nombre;
  cout<<endl<<"Ingrese el numero de cedula del cliente :";
  cin>>cedula;
  cout<<endl;
  v = stoi(cedula);
  indice = Buscar(raiz,v);
  if(indice == 0){
    cliente = cedula+','+nombre;
    Archivo<<endl<<cliente;
    cout<<"El cliente "<<cliente<<" ha sido agregado"<<endl;
  }else{
    cout<<"El numero "<<v<<" de cedula esta repetido"<<endl;
    v = 0;
  }
  return v;
  
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
  limpiar();
  CrearIndices();
  insertarIndices();
}

void Binario::Borrar(NodoBinario* D){
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
  if (raiz != NULL){
    if (x < raiz->valor){
      BorrarBalanceado(raiz->Hizq, x);
    }
    else{
      if (x > raiz->valor){
        BorrarBalanceado(raiz->Hder, x);
      }
      else
        q = raiz;
    }
    if (q->Hder == NULL){
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
}
int Binario::Buscar(NodoBinario *raiz, int x){
  int indice;
  if (raiz != NULL){
    if (x < raiz->valor){
      Buscar(raiz->Hizq, x);
    }
    else{
      if (x > raiz->valor){
        Buscar(raiz->Hder, x);
      }
      else{
        cout<<"Encontrado en arbol!!!"<<endl;
        indice = stoi(raiz->str);
        return indice;
      }
    }
  }
  else{
    return 0;
  }
}

string AgregarUno(string cedula){
  string str, str2, info;
  ifstream original ( "Clientes.txt" );
  ofstream copia ( "Clientes2.txt" );
  while (!original.eof()){
      getline(original,str);
      str2 = str;
      if (getSegmento(str,1) == cedula){
        info = str;
        str2 = str + ",1";
      }
      copia << str2 << endl;
  }
  original.close();
  copia.close();
  remove("Clientes.txt");
  rename("Clientes2.txt","Clientes.txt");
  ifstream original2 ( "Clientes.txt" );
  ofstream copia2 ( "Clientes2.txt" );
  bool Primeral = true;
  string linea;
  while ( getline( original2, linea ) ) {
    if ( ! linea.empty() ) {
      if(Primeral == false){
        copia2 <<endl<< linea;
      }else{
        copia2<<linea;
        Primeral = false;
      }
    }
  }
  original2.close();
  copia2.close();
  remove("Clientes.txt");
  rename("Clientes2.txt","Clientes.txt");
  return info;
}

string Binario::EliminarCliente (int cedula){
  //if (<<metodo para buscar cédulas en el arbol>>){
  string cliente;
  string cedulaString = to_string(cedula);
  cliente = AgregarUno(cedulaString);
  return cliente;
  
  //}
  //else{
    //cout << "La cédula que digito no existe" << endl;
  //}
}

void Purgar(){
  std::ofstream borrar("Clientes2.txt");//Para borrar datos residuo
  std::ofstream arch1("Clientes2.txt",fstream::app);
  string archivo = "Clientes.txt";
  string expresion;
  std::ifstream Archivo(archivo);
	std::string str;
  while (std::getline(Archivo, str)) {
    if (str.back() != '1'){
      expresion = str;
      arch1 << expresion << std::endl;
    }
  }
  borrar.close();
  arch1.close();
  Archivo.close();
  remove("Clientes.txt");
  rename("Clientes2.txt","Clientes.txt");
  ifstream original2 ( "Clientes.txt" );
  ofstream copia2 ( "Clientes2.txt" );
  bool Primeral = true;
  string linea;
  while ( getline( original2, linea ) ) {
    if ( ! linea.empty() ) {
      if(Primeral == false){
        copia2 <<endl<< linea;
      }else{
        copia2<<linea;
        Primeral = false;
      }
    }
  }
  original2.close();
  copia2.close();
  remove("Clientes.txt");
  rename("Clientes2.txt","Clientes.txt");
}

int main(){
  Binario Arbol;
  lista Mem;
  int opcion;
  CrearIndices();
  Arbol.insertarIndices();
  Mem.CargarMemoriaBusqueda(1);
  bool seguirTrabajando = true;
  while (seguirTrabajando){
    cout << "Bievenido" << endl;
    cout << "Digite el numero de la accion que desea realizar :" << endl;
    cout << "    1. Indexar" << endl;
    cout << "    2. Agregar un cliente" << endl;
    cout << "    3. Eliminar un cliente" << endl;
    cout << "    4. Purgar" << endl;
    cout << "    5. Busqueda de un cliente" <<endl;
    cout << "    6. Mostrar recorridos" << endl;
    cout << "    0. Salir" << endl;
    cin >> opcion;
    if(opcion == 1)
      Arbol.indexar();
    else if(opcion == 2){
      int cedula;
      int indice;
      cedula = Arbol.insertarCliente();
      if(cedula != 0){
        Arbol.indexar();
        indice = Arbol.Buscar(Arbol.raiz,cedula);
        cout<<indice<<endl;
        Mem.CargarMemoriaInsertar(indice);
      }
    }else if(opcion == 5){  
      int indice;
      int v;
      string prueba;
      string cliente;
      cout<<"Introduzca el numero de cedula del cliente: ";
      cin >> indice;
      cout<<endl;
      v = Arbol.Buscar(Arbol.raiz,indice);
      cout<<v<<endl;
      if(v != 0){
        cliente = Mem.BuscarMemoria(v,"Busqueda");
        cout<<"Se ha encontrado el cliente"<<endl;
        cout<<"El cliente es : "<<cliente<<endl;
      }else{
        cout<<"El cliente no esta en los archivos"<<endl;
      }
    }else if(opcion == 4){
        Purgar();
    }else if(opcion == 3){
      int clienteAEliminar;
      string cliente;
      cout << endl << "Digite la cedula del cliente que desea eliminar: ";
      cin >> clienteAEliminar;
      cliente = Arbol.EliminarCliente(clienteAEliminar);
      cout<<cliente<<endl;
      Arbol.indexar();
      PreordenR(Arbol.raiz);
      Mem.BorrarMemoria(cliente);
      Mem.Mostrar();
    }else if(opcion == 6){
      cout << "Inorden: " << endl;
      InordenR(Arbol.raiz);
      cout << endl << endl << "Preorden: " << endl;
      PreordenR(Arbol.raiz);
      cout << endl << endl << "Postorden: " << endl;
      PostordenR(Arbol.raiz);
    }
    else if(opcion == 0)
      seguirTrabajando = false;
    else
      cout<<"Por favor digite una opcion valida"<<endl;
  }
  cin.get();
  return 0;
}

#ifndef GRAFOHPP
#define GRAFOHPP

#include "nodoGrafo.hpp"
#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
#include <list>
#include <queue>
using namespace std;

/*
    GRAFO DIRIGIDO
*/
//yisus mongolo

template<typename Element>
class Grafo{
    protected:
        NodoVertice<Element> *g;
        int nVertices,mArcos;
        bool verificarExistenciaElementoEnCola(queue<Element> cola, Element info); // Metodo privado para verificar la existerncia de ese elemento en la cola, implicando que hay que desenconlar para encontrarla
        
        void copiarVertices(const Grafo<Element> &grafo,map<NodoVertice<Element>*,NodoVertice<Element>*> &espejo);
        void copiarArcos(const Grafo<Element> &grafo,map<NodoVertice<Element>*,NodoVertice<Element>*> &espejo);
        //Recorridos auxiliares
        void BFS(NodoVertice<Element>* inicial,map<NodoVertice<Element>*,bool> &visitados,list<Element> &result);
        void DFS(NodoVertice<Element>* inicial,map<NodoVertice<Element>*,bool> &visitados,list<Element> &result);
        void compConexDFS(map<NodoVertice<Element>*,bool> &visistados,list<Element> &compConexa,NodoVertice<Element>* inicial); //busca recursivamente elementos de una componente conexa
        void compConexDFS(map<NodoVertice<Element>*,bool> &visistados,NodoVertice<Element>* inicial);
        void llenarMapa(map<NodoVertice<Element>*,bool> &visitados,NodoVertice<Element>* &inicial,Element v);       //llena un mapa de no visitados y guarda la posicion del vertice inicial

    private:
        NodoVertice<Element> *getVerticeInicia(){return g;}
        
    public:
        // Este metodo puede utilizarse sin instanciar un objeto
        // Esta funcion sirve para mapear los datos de un diccionario, permitiendo asi la facilidad de controlar los recorridos del grafo
        // la funcion retorna un diccionario [int,lista(int)] , recibira el mapa de con los datos orginales [Element, list(Element)] y otro dicionario que pasaremos por referencia
        // Debido a que lo estaremos utilizando para decodificar el mapeo o los resultados que nos deje el grafo [Element,int]
        
        //Constructores
        Grafo();    // Crea un grafo vacio
        ~Grafo();   // Destruye el grafo
        Grafo(const Grafo<Element> &target);  // Constructor copia

        //Getters
        int getNVertices();     // Consultar el numero de vertices, O(1)
        int getMArcos();        // Consultar el numero de arcos, O(1)
        Element getFuente();    // Devuelve el nodo inicial del grafo, es decir el atributo NodoVertice<Element> *g, pero en este caso, su elemento contenido en el 
        virtual list<list<Element> > getArcos();    // Devuelve la lista de arcos del grafo

        //Setters

        //Recorridos
        list<Element> BFS();    // Versiones optimas de los recorridos, recorrido por ondas
        list<Element> DFS();    // Recorrido por profundidad
        list<Element> BFS(Element v);   //recorrido por ondas
        list<Element> DFS(Element v);   //recorrido en profundidad

        //Basicos
        // Nodo: estos dos metodos que tienen virtual estan pensados para reinventarse en la clase hija de grafo, Grafo no dirigido
        virtual void agregarArco(Element v, Element w, float c);// Buscar el vertice 'v' en la lista de vertices y agregar un nodo de adyacencia a ese vertice para apuntar el vertice 'w', O(n)
        virtual void agregarArco(Element v, Element w);     // Crea un arco con peso 1
        void agregarVertice(Element v);                     // Anadir una vertice al principio de la vertice apuntada por el apuntador "g" de NodoVertice O(1)
        void eliminarVertice(Element v);                    // Buscar el vertice y eliminarlo (eso implica tambien eliminar o destruir sus arcos) O(n + m)
        virtual void eliminarArco(Element v,Element w);     // Eliminar el arco es buscar el vertice inicial y luego el vertice correspondiente O(n + m)
        float getPesoArco(Element v, Element w);            // O(n + m)
        list<Element> getPredecesores(Element e);           // Conocer los predecesores (los que le envian la informacion a una vertice especifica) O(n + m)
        list<Element> getSucesores(Element e);              // O(n), simplemente devuelve la lista de los arcos del vertice
        list<Element> getVecinos(Element e);                // 
        list<Element> getVertices();                        // O(n)retorna una lista con los vertices del grafo

        //Otros
        void getReverse();      // Metodo para invertir los arcos de un grafo(Valido para grafo Dirigido)
        void vaciar();          // Vacia el grafo existente
        bool esVacio();         // Metodo logico si el grafo no tiene nodos // O(1) porque solo se verifica los atributos nVertices
        bool existeVertice(Element v);    // Buscar el elemento en la lista de vertices, la lista en casos generales se encontrara desgetNVerticesada, asi que la forma mas viables es iterar en ella, O(n)
        bool existeArco(Element v, Element w);  // Buscar el vertice de adyacencia, primero buscar la vertice para luego buscar su arco O(n + m)
        map<int,Element> getMapVertices(); //O(n)  retorna un mapa con un mapeo de los vertices
        map<Element,int> getMapVerticesInvertido(); // Retorna el mapar pero clave =Element : contenido = numero
        Grafo<int> getMapGrafo(); //retorna un el mismo grafo con valores mapeados
        int getGradoSalida(Element v);              //retorna el grado de salida (numero de arcos que apuntan a otros Vertices)
        int getGradoEntrada(Element v);             //Retorna el grado de entrada (numnero de arcos que apuntan al Vertice)
        list<list<Element>> getCompConexas();      //retorna una lista de listas de componentes conexas
        int getNumCompConexas();                   //retorna el numero de componentes conexas que posee el grafo
        static unordered_map<int, list<int> > mapearDiccionario(unordered_map<Element, list<Element> > diccionario, unordered_map<Element,int> &mapaComp);    // Metodo funcion que servira para mapear diccionarios y que tenga facil acceso a la hora de procesarlos
        bool esConexo();
        list<list<Element>> getPuentes();           // Busca todos los arcos que actuan como puerte del grafo, son aquellos que, si se eliminan, el grafo pasa a ser disconexo
        int getGradoVertice(Element v);             // Obtiene el grafo de una vertice v
    protected:
        // Este dfs esta modificado para realizar el recorrido de los puentes, utilizando el algoritmo de tarjan
        void dfsPuentes(NodoVertice<Element> *inicio, map<NodoVertice<Element>*,bool> &visitados, map<NodoVertice<Element>*,int> &desc, map<NodoVertice<Element>*,int> &low, map<NodoVertice<Element>*,NodoVertice<Element>*> &parents, list<list<Element>> &arcosRes, int &time);
        
        //Operadores
    public:
        bool operator==(const Grafo<Element> &grafo);                        //compara dos grafos y retorna verdadero en caso de ser iguales
        bool operator!=(const Grafo<Element> &grafo){return !(*this == grafo);}//compara dos grafos y retorna verdadero en caso de ser digerentes
        Grafo<Element>& operator=(const Grafo<Element> &grafo);                 //asigna (copia) un grafo a otro

};


template <typename Element>
inline void Grafo<Element>::vaciar()
{
    if(nVertices == 0  || !g) return;  // No puede vaciar un grafo vacio

    NodoVertice<Element> *iterVer = g, *del = NULL;    // Empezamos en el nodo fuente

    while(iterVer){
        del = iterVer;
        iterVer = iterVer->getProximoNodo();
        delete del; // Elimina el nodo y sus nodos adyacencia
    }

    // Se vuelve vacio sus atributos
    g = NULL;
    nVertices = mArcos = 0;
}

template <typename Element>
Element Grafo<Element>::getFuente()
{
    return g->getInfo();
}

template <typename Element>
unordered_map<int, list<int>> Grafo<Element>::mapearDiccionario(unordered_map<Element, list<Element>> diccionario, unordered_map<Element,int> &mapaComp)
{

    int i = 0;

    for(const auto &n : diccionario){
        if(mapaComp.count(n.first) == 0){
            mapaComp[n.first] = i;
            i++;
        }

        for(const auto &m : n.second){
            if(mapaComp.count(m) == 0){
                mapaComp[m] = i;
                i++;
            }
        }
    }

    // Cambiamos los valores del actual
    unordered_map<int,list<int> > nuevoDic;

    for(const auto &n: diccionario){
        for(const auto &m: n.second){
            nuevoDic[mapaComp[n.first]].push_back(mapaComp[m]);
        }
    }

    return nuevoDic;
}

template <typename Element>
inline bool Grafo<Element>::verificarExistenciaElementoEnCola(queue<Element> cola, Element info)
{
    while(!cola.empty()){
        if(cola.front() = info)
            return true;

        cola.pop();
    }
    return false;
}

// Grafo vacio  
// Inicializa con los datos nulos
template <typename Element>
Grafo<Element>::Grafo() : g(NULL), nVertices(0), mArcos(0)
{
}

template <typename Element>
inline Grafo<Element>::~Grafo()
{
    vaciar();  // Llama directamente al vaciar
    g = NULL;
    nVertices = 0;
    mArcos = 0;
}

template <typename Element>
inline Grafo<Element>::Grafo(const Grafo<Element> &target) : g(NULL),nVertices(0),mArcos(0)
{
    if (!target.g) return;
    // Copiar todos los vértices
    NodoVertice<Element>* actual = target.g;
    NodoVertice<Element>* ultimo = NULL;

    // Mapeo para relacionar los vértices originales con los nuevos
    unordered_map<NodoVertice<Element>*, NodoVertice<Element>*> mapaVertices;

    // Primera pasada: copiar vértices
    while(actual) {
        NodoVertice<Element>* nuevoVertice = new NodoVertice<Element>(actual->getInfo());
        mapaVertices[actual] = nuevoVertice;
        if (!g) {
            g = nuevoVertice;
        } else {
            ultimo->setProximoNodo(nuevoVertice);
        }
        ultimo = nuevoVertice;
        actual = actual->getProximoNodo();
        nVertices += 1;
    }

    // Segunda pasada: copiar arcos
    actual = target.g;
    while (actual) {
        NodoArco<Element>* arcoActual = actual->getListaAdyacencia();
        NodoVertice<Element>* nuevoVertice = mapaVertices[actual];
        NodoArco<Element>* ultimoArco = NULL;
        
        while (arcoActual) {
            NodoArco<Element>* nuevoArco = new NodoArco<Element>();
            nuevoArco->setCosto(arcoActual->getCosto());
            nuevoArco->setInfo(mapaVertices[arcoActual->getInfo()]);
            if (!nuevoVertice->getListaAdyacencia()) {
                nuevoVertice->setListaAdyacencia(nuevoArco);
            } else {
                ultimoArco->setProximoNodo(nuevoArco);
            }
            ultimoArco = nuevoArco;
            arcoActual = arcoActual->getProximoNodo();
            mArcos++;
        }
        actual = actual->getProximoNodo();
    }
}


// en caso de que no haya ninguna vertice en el grafo
// grafo vacio
template <typename Element>
bool Grafo<Element>::esVacio()
{
    return nVertices == 0;
}

template <typename Element>
void Grafo<Element>::agregarVertice(Element v)
{
    // Anadiremos el vertice la principio de la lista de grafos

    NodoVertice<Element> *nuevoVertice = new NodoVertice<Element>(v);   // Creamos el nodo asignando memoria
    NodoVertice<Element> *ant=g;

    while(ant && ant->getProximoNodo()){
        ant = ant->getProximoNodo();
    }

    if(ant){
        // en caso de estar en la ultima vertice de la lista
        ant->setProximoNodo(nuevoVertice);
    }else{
        // caso contrario, osea que seria un grafo vacio inicialmente
        nuevoVertice->setProximoNodo(g);
        g = nuevoVertice;
    }

    nVertices += 1; // Sumamos la cantidad
}


// Inserta un arco con su peso correspondiente a una vertice hacia otra vertice
template <typename Element>
void Grafo<Element>::agregarArco(Element v, Element w, float c)
{
    // if(!g) return;  // El grafo esta vacio, no hay vertices para enlazar

    NodoVertice<Element> *iterVertices = g;   // puntero iterador desde nodo apuntado por el grafo
    NodoArco<Element> *nuevoArco = NULL;   // puntero para crear el nuevo arco
    NodoVertice<Element> *memorizarVertice = NULL;    // Este puntero servira para guardar la direccion del vertice w

    while(iterVertices && iterVertices->getInfo() != v){
        if(iterVertices->getInfo() == w)    // En caso de encontrar el vertice w antes del vertice v, guardarlo para ahorrar tiempo
            memorizarVertice = iterVertices;
        
        iterVertices = iterVertices->getProximoNodo();
    }

    // En caso de no haber encontrado la vertice, tendra que crearlo e insertarlo como nuevo
    if(!iterVertices){
        iterVertices = new NodoVertice<Element>(v);

        // Debemos colocar esta vertice, al final de la lista de vertices
        NodoVertice<Element> *iteradorAux = g;
        while(iteradorAux && iteradorAux->getProximoNodo()){
            iteradorAux = iteradorAux->getProximoNodo();
        }

        // Pregunta si el iteradorAux no es Null
        if(iteradorAux){
            // insertar el nuevoVertice despues del iteradorAux
            iteradorAux->setProximoNodo(iterVertices);
        }else{
            // Quiere decir que es al inicio
            iterVertices->setProximoNodo(g);
            g = iterVertices;
        }

        nVertices += 1;
    }
    

    if(!memorizarVertice)    // si el iterador no se topo con w antes que v
    {
        memorizarVertice = iterVertices;    // memorizar vertice va a iterar desde la posicion actual del vertice v
        while(memorizarVertice && memorizarVertice->getInfo() != w){
            memorizarVertice = memorizarVertice->getProximoNodo();
        }

        // en caso de que w no sea encontrado en el grafo
        if(!memorizarVertice){
            // Tendra que ser creado tambien
            memorizarVertice = new NodoVertice<Element>(w);
            
            // Insertamos igualmente al final

            NodoVertice<Element> *iterAux = g;
            while(iterAux->getProximoNodo()){
                iterAux = iterAux->getProximoNodo();
            }

            iterAux->setProximoNodo(memorizarVertice);
            nVertices += 1;
        }
    }

    // Agregamos el nuevo arco
    nuevoArco =  new NodoArco<Element>(memorizarVertice,c,iterVertices->getListaAdyacencia());  // Apunta al vertice w y lo guarda en la lista enlazada de v
    iterVertices->setListaAdyacencia(nuevoArco);    // Ajustamos la lista de adyacencia de v
    mArcos += 1;    // Aumenta el numero

}


template <typename Element>
void Grafo<Element>::agregarArco(Element v, Element w)    //realiza la misma funcion que agregarArco original pero su coste por defecto es 1
{
    agregarArco(v,w,1);
}

template <typename Element>
inline void Grafo<Element>::getReverse()
{
    // Para este metodo, tendremos que invertir todas los arcos del grafo dirigido
    // es decir, v -> w va a ser w -> v

    // Para facilitar el trabajo de inversion, utilizaremos una clase conjunto
    set<pair<NodoVertice<Element>*, NodoVertice<Element>* > > arcosUnicos;   // Este objeto coleccionara los arcos ya anteriormente volteados
    
    // Iteradores
    NodoVertice<Element> *iteradorVertices  = g;    // Iterador de vertices
    NodoArco<Element> *iteradorArcos = NULL, *ant, *nuevoArco, *aux;     // Iterador de arcos, puntero para memorizar el arco anterior y otro para crear el nuevo arco

    // Begin

    // iteramos cada vertice
    while(iteradorVertices){
        iteradorArcos = iteradorVertices->getListaAdyacencia(); 
        ant = NULL;

        // iteramos cada arco
        while(iteradorArcos){
            
            // Auxiliar para tomar un par de vertices
            pair<NodoVertice<Element>*, NodoVertice<Element>* > auxiliar(iteradorVertices,iteradorArcos->getInfo());
            
            // Primero preguntamos si el arco w -> v existe

            // Cuando vayamos iterando por los arcos del los vertices, debemos tener cuidado en cambiar nuevamente las aristas ya cambiadas en pasos anteriores
            
            // En caso de no existir ese caso, se elimina el arco iterArcos y se asigna un nuevo arco otro
            if(arcosUnicos.find(auxiliar) == arcosUnicos.end()){
                
                // Creamos el nuevo arco
                nuevoArco = new NodoArco<Element>(iteradorVertices,0,iteradorArcos->getInfo()->getListaAdyacencia());
                // A su ves, debemos incorporarlo en el conjunto
                arcosUnicos.insert(make_pair(iteradorArcos->getInfo(),iteradorVertices));   // Tiene que ser el arco w->v
                iteradorArcos->getInfo()->setListaAdyacencia(nuevoArco);    // Se agrega un nuevoArco al vertice w


                // Eliminaremos el arco de v
                aux = iteradorArcos;

                if(ant){
                    // En caso de estar en medio de la lista
                    ant->setProximoNodo(iteradorArcos->getProximoNodo());
                    iteradorArcos = ant->getProximoNodo();
                }else{
                    // Caso de estar al principio
                    iteradorVertices->setListaAdyacencia(iteradorArcos->getProximoNodo());
                    iteradorArcos = iteradorVertices->getListaAdyacencia();
                }

                // Liberamos ese arco
                delete aux;
            }else{
                // En caso de que sea un arco ya incorporado en la inversion
                // seguimos iterando normalmente
                ant = iteradorArcos;
                iteradorArcos = iteradorArcos->getProximoNodo();
            }

            
        }
            // Vamos hacia otra vertice

        iteradorVertices = iteradorVertices->getProximoNodo();

    }

}

template <typename Element>
inline void Grafo<Element>::eliminarVertice(Element v)
{
    if(g == NULL) return;

    NodoVertice<Element> *iterador = g,*ant =NULL;   // Iterador a nodos
    // tambien un puntero ant para apuntar al nodo que le sigue despues del eliminado
    NodoArco<Element> *listaAdy = NULL, *antArco = NULL;    // Para eliminar los nodos de adyacencia

    // tendriamos que eliminar los arcos predecesores a v


    while(iterador){
        antArco = NULL;
        listaAdy = iterador->getListaAdyacencia();

        while(listaAdy && listaAdy->getInfo()->getInfo() != v){
            antArco = listaAdy;
            listaAdy = listaAdy->getProximoNodo();
        }
        
        if(listaAdy){
            if(antArco){
                antArco->setProximoNodo(listaAdy->getProximoNodo());
            }else{
                iterador->setListaAdyacencia(listaAdy->getProximoNodo());
            }
            delete listaAdy;
            mArcos -= 1;
        }
        iterador = iterador->getProximoNodo();
    }
    
    iterador = g;

    // Buscamos el vertice

    while(iterador && iterador->getInfo() != v){
        ant = iterador;
        iterador = iterador->getProximoNodo();
    }
    
    // En caso de haberlo encontrado
    if(iterador){
        NodoVertice<Element> *del = iterador; // Puntero de eliminacion
        if(ant){
            ant->setProximoNodo(iterador->getProximoNodo());    // cambiamos el puntero al siguiente del eliminado
        }else{
            g->setProximoNodo(iterador->getProximoNodo());
        }
        // Eliminamos la vertice(el metodo destructor de la clase NodoVertice esta programado para eliminar tanto los nodos adyacentes como el mismo)
        // con ello, se elimina los sucesores
        delete del; // liberamos memoria

        nVertices -= 1; // Reducimos la cantidad de vertices
    }
}

template <typename Element>
void Grafo<Element>::eliminarArco(Element v, Element w){

    if(!g) return;  // Caso de que el grafo este vacio

    NodoVertice<Element> *ptrVertice = g; // iterador entre vertices
    NodoArco<Element> *ptrAd = NULL, *ant = NULL; // iterador entre nodos adyacencia

    // Buscamos primero el vertice
    // El iterador llega hasta null en caso de no encontrarlo
    while(ptrVertice && ptrVertice->getInfo() != v){
        ptrVertice = ptrVertice->getProximoNodo();  // Se desplaza
    }

    if(ptrVertice)  // en caso de haberlo encontrado
    {
        ptrAd = ptrVertice->getListaAdyacencia();   // Se situa en el primer elemento de adyacencia

        while(ptrAd && ptrAd->getInfo()->getInfo() != w){ // en caso de ser el nodo ady w
            ant = ptrAd;
            ptrAd = ptrAd->getProximoNodo();    // Itera sobre la lista de nodos
        }

        if(ptrAd)   // Pregunta si fue encontrado
        {
            // en caso de que ant apunte al nodo adyacencia anterior
            // hay que tener cuidado en utilizar ant, porque si ant es null, se produce violacion segmento en la compilacion
            if(ant){
                ant->setProximoNodo(ptrAd->getProximoNodo());   // el nodo anterior apunta al siguiente del eliminado
            }else{
                // en caso contrario, implica que el nodoAdyacencia es el primero en la lista
                ptrVertice->setListaAdyacencia(ptrAd->getProximoNodo());
            }
            delete ptrAd;   // Eliminamos ese nodo adyacencia
            mArcos -= 1;    // Reducimos la cantidad
        }
    }

}

template <typename Element>
inline bool Grafo<Element>::existeVertice(Element v)
{
    bool encontrado = false;
    if(!g) return encontrado;    // Devuelve falso si el grafo es vacio

    NodoVertice<Element> *iteradorVer = this->g;

    while(iteradorVer && iteradorVer->getInfo() != v){
        iteradorVer = iteradorVer->getProximoNodo();
    }

    if(iteradorVer) 
        encontrado = true; // Pregunta si fue encontrado
    
    return encontrado;
}

template <typename Element>
inline bool Grafo<Element>::existeArco(Element v, Element w)
{
    if(!g)  return false;   // Grafo vacio

    bool res = false;   // La respuesta inicializa en falso para una buena practica

    // Puntero para iterar vertice y nodo Adyacencia
    NodoVertice<Element> *iterVer = g;
    NodoArco<Element> *iterAd = NULL;

    // Buscamos el vertice primero

    while(iterVer && iterVer->getInfo() != v)
        iterVer = iterVer->getProximoNodo();    // Iterar sobre los vertices

    if(iterVer) // Si encontro el vertice, en caso de no haberlo encontrado significa que el nodo de V no existe y ese arco a W tampoco
    {
        // Buscamos el vertice
        // Apuntamos el primer arco de la lista
        iterAd = iterVer->getListaAdyacencia();

        while(iterAd && iterAd->getInfo()->getInfo() != w)  // Buscar ese arco apuntando
            iterAd = iterAd->getProximoNodo();

        if(iterAd)  // Preguntar si fue encontrado
            res = true; // Si fue verdadero, existe V -> W

        // En caso contrario, no existe el arco dirgido de V -> W
    }

    return res;
    
}

template <typename Element>
float Grafo<Element>::getPesoArco(Element v, Element w)  // Encontrar el peso del arco existente de V -> W
{
    if(!g)  return false;   // Grafo vacio

    // Puntero para iterar vertice y nodo Adyacencia
    NodoVertice<Element> *iterVer = g;
    NodoArco<Element> *iterAd = NULL;

    // Variable que capture el peso del arco V -> W
    float weight = 0.0; // Inicializado en 0.0

    // Buscamos el vertice primero

    while(iterVer && iterVer->getInfo() != v)
        iterVer = iterVer->getProximoNodo();    // Iterar sobre los vertices

    if(iterVer) // Si encontro el vertice, en caso de no haberlo encontrado significa que el nodo de V no existe y ese arco a W tampoco
    {
        // Buscamos el vertice
        // Apuntamos el primer arco de la lista
        iterAd = iterVer->getListaAdyacencia();

        while(iterAd && iterAd->getInfo()->getInfo() != w)  // Buscar ese arco apuntando
            iterAd = iterAd->getProximoNodo();

        if(iterAd)  // Preguntar si fue encontrado
        {
            weight = iterAd->getCosto();    // Obtenemos el peso/Costo del arco
        }

        // En caso contrario, no existe el arco dirgido de V -> W
    }

    return weight;  // Retornamos el costo
}

template <typename Element>
inline int Grafo<Element>::getNVertices()
{
    return nVertices;
}

template <typename Element>
inline int Grafo<Element>::getMArcos()
{
    return mArcos;
}

template <typename Element>
list<Element> Grafo<Element>::getPredecesores(Element e)
{
    if(!g) return list<Element>();    // Devuelve una lista vacia en caso de ser un grafo vacio

    list<Element> result; // Creamos la lista de nodos que tienen direccion V -> e

    NodoVertice<Element> *iterVer = g;
    NodoArco<Element> *iterAdy = NULL;

    while(iterVer)  // Iteramos toda la lista de vertices
    {
        iterAdy = iterVer->getListaAdyacencia();    // Apuntamos al primer elemento de adyacencia
        while(iterAdy){
            if(iterAdy->getInfo()->getInfo() == e){ // en caso de que el vertice tenga un nodo adyacencia hacia el nodo e
                result.push_back(iterVer->getInfo());   // guarda el vertice que tienen arista hacia e
                // Asumiendo que solo existe dentro de ese vertice, 
                //  un arco hacia ese nodo(obviamente solo hay una flecha de a -> b), 
                // no es necesario seguir recorriendo la lista de adyacencia, paramos el ciclo(usando una variable booleana o un break)
                break;
            }else{
                // iteramos al siguiente nodo de adyacencia
                iterAdy = iterAdy->getProximoNodo();
            }
        }

        // Seguimos buscando en los demas vertices
        iterVer = iterVer->getProximoNodo();
    }

    return result;  // Retornamos la lista

}

template <typename Element>
list<Element> Grafo<Element>::getSucesores(Element e){
    // Creamos una lista vacia
    list<Element> result;

    if(!g)  return result;   // devuelve lista vacia


    // Declaramos los punteros necesarios
    NodoVertice<Element> *iterVer = g;    // Apuntando al nodo g
    NodoArco<Element> *iterAdy = NULL;

    // Buscamos e
    while(iterVer && iterVer->getInfo() != e)
        iterVer = iterVer->getProximoNodo();
    
    // Preguntar si fue encontrado
    if(iterVer){
        iterAdy = iterVer->getListaAdyacencia();    // apuntamos al primer elemento
        while(iterAdy){
            result.push_back(iterAdy->getInfo()->getInfo()); // enlistamos el/los nodo de adyacencia que contiene el vertice e
            iterAdy = iterAdy->getProximoNodo();
        }
    }

    return result; // Devolvemos la lista
}

template <typename Element>
inline list<Element> Grafo<Element>::getVecinos(Element e)
{
    list<Element> vecinos;
    bool insertadosAntes[nVertices];
    NodoVertice<Element> *iterVertice = g;
    NodoArco<Element> *iterAdy = NULL;
    bool encontrado;

    // Buscamos los 

    for(int i =0 ; i < nVertices ; i++){
        insertadosAntes[i] = false;
    }

    while(iterVertice){
        iterAdy = iterVertice->getListaAdyacencia();
        encontrado = false;

        while(iterAdy && !encontrado){
            // en caso de estar la misma vertice e, toma todos los sucesores, es decir, la lista de adyacencia completa
            if(iterVertice->getInfo() == e && !insertadosAntes[iterAdy->getInfo()->getInfo()]){
                // Inserta la vertice que esta siendo apuntada
                vecinos.push_back(iterAdy->getInfo()->getInfo());
                insertadosAntes[iterAdy->getInfo()->getInfo()] = true; 
            }else{
                // en caso de no serlo, es posible que el vertice contenga un nodo que apunte al vertice e
                if(iterAdy->getInfo()->getInfo() == e && !insertadosAntes[iterVertice->getInfo()]){
                    // Guardas el vertice que la apunta
                    vecinos.push_back(iterVertice->getInfo());
                    // En este punto no hace falta seguir iterando en la lista de adyacencia porque el nodo deseado ya fue encontrado
                    // no hay mas de un nodo que apunte a ese nodo en la misma vertice
                    insertadosAntes[iterVertice->getInfo()] = true;
                    encontrado = true;
                }
            }
            // iteramos en el siguiente nodo de adyacencia
            iterAdy = iterAdy->getProximoNodo();
        }
        // iteramos en la siguiente vertice
        iterVertice = iterVertice->getProximoNodo();

    }

    // Devolvemos la lista
    return vecinos;
}

template <typename Element>
list<Element> Grafo<Element>::getVertices(){
    NodoVertice<Element> *act=this->g;
    list<Element> vertices;
    //recorre todos los vertices del grafo
    while (act!=NULL)
    {
        vertices.push_back(act->getInfo());     //incerta el elemento de cada vertice en la lista
        act=act->getProximoNodo();
    }
    return vertices;
}

template <typename Element>
map<int,Element> Grafo<Element>::getMapVertices(){
    map<int,Element> mapa;
    NodoVertice<Element> *act=g;
    int i=0;
    //recorre todos los vertices del grafo
    while (act)
    {
        mapa[i]=act->getInfo();     //incerta el elemneto de cada vertice en el mapa en la posicion i
        act=act->getProximoNodo();
        i++;
    }
    return mapa;
}
template <typename Element>
Grafo<int> Grafo<Element>::getMapGrafo(){
    NodoVertice<Element> *act=g;
    NodoArco<Element> *adyAct;
    map<NodoVertice<Element>*,int> mapa;
    Grafo<int> grafo;
    int i=0;
    
    //crea los vertices mapeados del grafo
    while (act){
        grafo.agregarVertice(i);
        mapa[act]=i;    //crea un mapa que relaciona vertice y su posicion asignada
        act=act->getProximoNodo();
        i++;
    }

    //crea los arcos mapeados del grafo
    act=g;
    while (act)     //recorre todos los vertices
    {
        adyAct=act->getListaAdyacencia();
        while (adyAct)  //recorre todos los arcos de los vertices
        {
            grafo.agregarArco(mapa[act],mapa[adyAct->getInfo()],this->getPesoArco(act->getInfo(),adyAct->getInfo()->getInfo()));    //crea el arco mapeado
            adyAct=adyAct->getProximoNodo();
        }
        act=act->getProximoNodo();
    }
    return grafo;
}
template <typename Element>
inline list<list<Element> > Grafo<Element>::getArcos()
{
    //  Para guardar los arcos utilizare una clase llamada pair, esta clase guarda los
    // pares de vertices que son conectadas por el mismo arco, es una clase que sera de
    // utilidad para el problema de los arcos no dirigidos

    // Cuando recibas la lista de arcos y quieras acceder a los pares, se utiliza como el mapa, el first y
    // second para consultar

    list<list<Element> > arcos;

    NodoVertice<Element> *iterarVertice = g;
    NodoArco<Element> *iterarAdy = NULL;

    while(iterarVertice){
        iterarAdy = iterarVertice->getListaAdyacencia();

        while(iterarAdy){
            // Se crea un para y se guarda en la lista de arcos
            arcos.push_back(list<Element>({iterarVertice->getInfo(),iterarAdy->getInfo()->getInfo()}));
            iterarAdy = iterarAdy->getProximoNodo();
        }
        iterarVertice = iterarVertice->getProximoNodo();
    }

    return arcos;
}

template <typename Element>
inline list<Element> Grafo<Element>::BFS()
{
    queue<NodoVertice<Element>* > recorrido;    // cola de punteros
    list<Element> resultado;    // El resultado
    NodoVertice<Element> *iteradorVertices;
    NodoArco<Element> *iteradorVecinos;

    map<NodoVertice<Element>*,bool> visitados;  // El diccionario para las vertices visitadas

    // Inicializamos el diccionario
    // itera sobre la lista de los vertices primero
    iteradorVertices = g;
    while(iteradorVertices){
        visitados[iteradorVertices] = false;
        iteradorVertices = iteradorVertices->getProximoNodo();
    }

    // una vez inicializada, encolamos el primer nodo y le inidicamos que ya fue visitado
    visitados[g] = true;
    recorrido.push(g);

    while(!recorrido.empty()){
        iteradorVertices = recorrido.front();
        resultado.push_back(iteradorVertices->getInfo());
        recorrido.pop();

        // visitamos los vecinos

        iteradorVecinos = iteradorVertices->getListaAdyacencia();
        while(iteradorVecinos){
            if(!visitados[iteradorVecinos->getInfo()]){
                recorrido.push(iteradorVecinos->getInfo());
                visitados[iteradorVecinos->getInfo()] = true;
            }
            iteradorVecinos = iteradorVecinos->getProximoNodo();
        }
    }

    return resultado;
}

template <typename Element>
inline list<Element> Grafo<Element>::DFS()
{
    list<Element> resultado;
    NodoVertice<Element> *iterVer = g;

    map<NodoVertice<Element>*,bool> visitados;

    // inicializamos el mapa

    while(iterVer){
        visitados[iterVer] = false;
        iterVer = iterVer->getProximoNodo();
    }

    // Cargamos el metodo recursivo
    DFS(g,visitados,resultado);

    return resultado;
}

template <typename Element>
int Grafo<Element>::getGradoSalida(Element v){
    NodoVertice<Element>* act;
    NodoArco<Element>* arcoAct;
    int grado=0;
    //itera hasta encontrar el vercice v
    act=g;
    while (act && act->getInfo()!= v)
    {
        act=act->getProximoNodo();
    }
    //si lo encuentra, cuenta el numero de sucesores que tiene
    if (act!=NULL)
    {
        arcoAct=act->getListaAdyacencia();
        while (arcoAct)
        {
            grado++;
            arcoAct=arcoAct->getProximoNodo();
        }
    }else//en caso contrario retornara -1 porque no existe tal vertise
    {
        grado = -1;
    }
    
    return grado;
}

template <typename Element>
int Grafo<Element>::getGradoEntrada(Element v){
    NodoVertice<Element>* act;
    NodoArco<Element>* arcoAct;
    int grado=0;
    bool found=false;

    act=g;
    //verifica que exista el vertice
    while (act && act->getInfo()!= v)
    {
        act=act->getProximoNodo();
    }

    
    if (act)
    {
        act=g;          //si exite, recorre desde el primer nodo en busca de los vertices que lo apunten
        while (act)
        {
            if (act->getInfo()!=v)
            {
                found=false;
                arcoAct=act->getListaAdyacencia();
                while (arcoAct && found)
                {
                    if (arcoAct->getInfo()->getInfo() == v)     //si un vertice lo apunta, suma 1 y se sale del ciclo
                    {
                        grado++;
                        found = true;
                    }
                    arcoAct=arcoAct->getProximoNodo();
                }
            
            }
            act=act->getProximoNodo();
       }
    }else
    {//si no existe el vertice, retornara -1
        grado=-1;
    }
    
    return grado;
}

template <typename Element>
inline map<Element, int> Grafo<Element>::getMapVerticesInvertido()
{
    map<Element,int> diccionario;

    NodoVertice<Element> *iterarVertices = g;
    int i = 0;
    while(iterarVertices){
        diccionario[iterarVertices->getInfo()] = i;
        iterarVertices = iterarVertices->getProximoNodo();
        i += 1;
    }

    return diccionario;
}

template <typename Element>
list<list<Element>> Grafo<Element>::getCompConexas(){
    list<NodoVertice<Element>*> vertices;   //lista de vertices(Nodos vertice)
    list<Element> compConexa;       //almacenara la lista auxiliar con todos los elementos de la componente conexa
    list<list<Element>> result;     //variable a retornar
    map<NodoVertice<Element>*,bool> visitados;      //mapa para marcar los vertices visitados
    NodoVertice<Element>*act;       //nodo en el cual se iterara para llenar el mapa de visitados

    act=g;
    while (act) //ciclo para llenar el mapa de visitados y lista de vertices
    {
        visitados[act]=false;
        vertices.push_back(act);
        act=act->getProximoNodo();
    }
    
    while (!vertices.empty())       //ciclo para recorrer todos los vertices
    {
        if (!visitados[vertices.front()])       //condicional para recorrer una componente conexa
        {
            compConexDFS(visitados,compConexa,vertices.front());        //busca recursivamente elementos de una componente conexa
            result.push_back(compConexa);       //alamneca la componente conexa
            compConexa.clear();         //limpia la lista para prepararla para otra iteracion
        }
        vertices.pop_front();
    }
    return result;
}

template <typename Element>
void Grafo<Element>::compConexDFS(map<NodoVertice<Element>*,bool> &visistados,list<Element> &compConexa,NodoVertice<Element>* inicial){
    NodoArco<Element>* arcoAct;     //iterador de los sucesores del vertice inicial
    if (!visistados[inicial])
    {
        visistados[inicial]=true;       //marca el vertice como visitados
        compConexa.push_back(inicial->getInfo());       //guarda el vertice visitado
        arcoAct=inicial->getListaAdyacencia();
        while (arcoAct)     //ciclo que busca los sucesores nde los sucesores de forma recursiva
        {
            compConexDFS(visistados,compConexa,arcoAct->getInfo());    //busca recursivamente sucesores
            arcoAct=arcoAct->getProximoNodo();     //se mueve al siguiente sucesor
        }
        
    }
    
}


template <typename Element>
int Grafo<Element>::getNumCompConexas(){
    list<NodoVertice<Element>*> vertices;   //lista de vertices(Nodos vertice)
    list<Element> compConexa;       //almacenara la lista auxiliar con todos los elementos de la componente conexa
    int result=0;     //variable a retornar
    map<NodoVertice<Element>*,bool> visitados;      //mapa para marcar los vertices visitados
    NodoVertice<Element>*act;       //nodo en el cual se iterara para llenar el mapa de visitados

    act=g;
    while (act) //ciclo para llenar el mapa de visitados y lista de vertices
    {
        visitados[act]=false;
        vertices.push_back(act);
        act=act->getProximoNodo();
    }
    
    while (!vertices.empty())       //ciclo para recorrer todos los vertices
    {
        if (!visitados[vertices.front()])       //condicional para recorrer una componente conexa
        {
            compConexDFS(visitados,vertices.front());        //busca recursivamente elementos de una componente conexa
            result++;
        }
        vertices.pop_front();
    }
    return result;
}

template <typename Element>
inline list<list<Element>> Grafo<Element>::getPuentes()
{
    /*
        Para este algoritmos utilizaremos el algoritmo de tarjan, con la finalidad de obtener
        un orden de complejidad O(n + m)
    */

    list<list<Element> > arcosResultados;   // Lista de arcos resultante

    // En caso de ser un grafo vacio
    if(!g) return arcosResultados;

    map<NodoVertice<Element>*,bool> visitados;  // Mapa de visitados
    map<NodoVertice<Element>*,int>  desc, low;  // Estos mapas seran fundamentales, el primero des tiempo de descubrimiento y el otro el minimo alcance
    map<NodoVertice<Element>*,NodoVertice<Element>*> parents;   // Mapa de las vertices que son padre de otras vertices

    // inicializamos los mapas

    for(NodoVertice<Element> *iterador = g; iterador; iterador = iterador->getProximoNodo()){
        visitados[iterador] = false;
        desc[iterador] = -1;
        low[iterador] = -1;
        parents[iterador] = NULL;
    }
    // tiempo
    int tiempo = 0;

    // iteramos y utilizamos el dfs para este problema

    for(NodoVertice<Element> *iterador = g; iterador; iterador = iterador->getProximoNodo())
    {
        if(!visitados[iterador])
            dfsPuentes(iterador,visitados,desc,low,parents,arcosResultados,tiempo);
    }
    return arcosResultados;
}

template <typename Element>
inline int Grafo<Element>::getGradoVertice(Element v)
{
    //O(n + m)

    NodoVertice<Element> *iteradorVer = g;
    int count = -1; // SI el vertice no ha sido encontrada, devolvera -1

    while(iteradorVer && iteradorVer->getInfo() != v){
        iteradorVer = iteradorVer->getProximoNodo();
    }

    // En caso de encontrarla
    if(iteradorVer){
        count = 0;

        for(NodoArco<Element> *iteradorArco = iteradorVer->getListaAdyacencia() ; iteradorArco; iteradorArco = iteradorArco->getProximoNodo()){
            count += 1;
        }
    }
    return count;
}

template <typename Element>
void Grafo<Element>::compConexDFS(map<NodoVertice<Element>*,bool> &visistados,NodoVertice<Element>* inicial){
    NodoArco<Element>* arcoAct;
    if (!visistados[inicial])
    {
        visistados[inicial]=true;       //marca el vertice como visitados
        arcoAct=inicial->getListaAdyacencia();      //guarda el vertice visitado
        while (arcoAct)
        {
            compConexDFS(visistados,arcoAct->getInfo());        //busca recursivamente sucesores
            arcoAct=arcoAct->getProximoNodo();      //se mueve al proximo sucesor del vertice actual
        }
        
    }
    
}

template <typename Element>
inline void Grafo<Element>::dfsPuentes(NodoVertice<Element> *inicio, map<NodoVertice<Element> *, bool> &visitados, map<NodoVertice<Element> *, int> &desc, map<NodoVertice<Element> *, int> &low, map<NodoVertice<Element> *, NodoVertice<Element> *> &parents, list<list<Element> > &arcosRes, int &time)
{
    visitados[inicio] = true;
    desc[inicio] = time;
    low[inicio] = time;
    time += 1;

    // recorremo sus vecinos
    NodoArco<Element>* vecino = inicio->getListaAdyacencia();

    while(vecino){
        if(!visitados[vecino->getInfo()]){
            parents[vecino->getInfo()] = inicio;    // Le indicamos quien es su padre
            dfsPuentes(vecino->getInfo(),visitados,desc,low,parents,arcosRes,time);


            // Actualizar el valor del low del padre, o vertice actual
            low[inicio] = min(low[inicio],low[vecino->getInfo()]);

            // si low[vecino] >  dis[inicio] entonces inicio-vecino es puente
            if(low[vecino->getInfo()] >  desc[inicio]){
                // Creamos una sublista, guardamos u-v en la lista resultante
                arcosRes.push_back(list<Element>({inicio->getInfo(),vecino->getInfo()->getInfo()}));
            }


        }else if(vecino->getInfo() != parents[inicio]){
            low[inicio] = min(low[inicio],desc[vecino->getInfo()]);
        }
        vecino = vecino->getProximoNodo();
    }
}
template <typename Element>
bool Grafo<Element>::operator==(const Grafo<Element> &grafo)
{
    if (nVertices != grafo.nVertices || mArcos!=grafo.mArcos)   //Si el numero de vertices o de arcos no concuerdan, entonces son grafos distintos
        return false;
    
    NodoVertice<Element>*i,*j;       //Variables que iteran sobre los vertices
    NodoArco<Element>*arcoActI,*arcoActJ;//Variables que iteran sobre los arcos
    
    for (i = g; i ; i=i->getProximoNodo())       //Ciclo principal que itera sobre los vertices del grafo instanciado
    {
        for ( j = grafo.g; j && j->getInfo()!=i->getInfo(); j=j->getProximoNodo()){}    //ciclo que itera sobre el grafo comparado
        
        if (!j)    //si no se encontro el vertice i en el grafo comparado, entonces ambos grafos son distintos
        {
            return false;
        }

        for ( arcoActI=i->getListaAdyacencia(); arcoActI; arcoActI=arcoActI->getProximoNodo())  //Ciclo que itera sobre los arcos del grafo instanciado
        {
            for (arcoActJ=j->getListaAdyacencia(); arcoActJ && arcoActJ->getInfo()->getInfo()!=arcoActI->getInfo()->getInfo(); arcoActJ= arcoActJ->getProximoNodo()){}   //Ciclo que itera sobre los arcos del grafo comparado
            
            if (!arcoActJ)     //si no se encontro el arco i en el grafo comparado, entonces ambos grafos son distintos
            {
                return false;
            }
            
        }
        
    }
    
    return true;
}
template <typename Element>
Grafo<Element>& Grafo<Element>::operator=(const Grafo<Element> &grafo){
    if(this==&grafo) //si son iguales retornas el mismo grafo
        return *this;
    
    this->vaciar(); //vacias el grafo para asignarle el nuevo

    if(!grafo.g) {  // Si el grafo fuente está vacío
        nVertices = 0;
        mArcos = 0;
        return *this;
    }
    nVertices=grafo.nVertices;
    mArcos=grafo.mArcos;
    map<NodoVertice<Element>*,NodoVertice<Element>*> espejo;
    copiarVertices(grafo,espejo);
    copiarArcos(grafo,espejo);
    
    return *this;
}

template <typename Element>
void Grafo<Element>::copiarVertices(const Grafo<Element> &grafo,map<NodoVertice<Element>*,NodoVertice<Element>*> &espejo){
    NodoVertice<Element>*sig,*nuevo;
    NodoVertice<Element>*anterior=NULL;
    sig = grafo.g;

    while (sig)
    {
        nuevo = new NodoVertice<Element>(sig->getInfo());
        if(sig==grafo.g){
            g=nuevo;
        }else{
            anterior->setProximoNodo(nuevo);
        }
        espejo[sig]=nuevo;
        sig = sig->getProximoNodo();
        anterior=nuevo;
    }
}

template <typename Element>
void Grafo<Element>::copiarArcos(const Grafo<Element> &grafo, map<NodoVertice<Element>*, NodoVertice<Element>*> &espejo){
    NodoVertice<Element>* act = grafo.g;
    NodoVertice<Element>* newAct = g;
    
    while (act)
    {
        NodoArco<Element>* arcoSig = act->getListaAdyacencia();
        NodoArco<Element>* ultimoArco = NULL;
        
        while (arcoSig)
        {
            NodoArco<Element>* nuevo = new NodoArco<Element>();
            nuevo->setCosto(arcoSig->getCosto());
            nuevo->setInfo(espejo[arcoSig->getInfo()]);
            
            // Insertar en la lista de adyacencia del nuevo vértice
            if (!newAct->getListaAdyacencia()) {
                // Primer arco de la lista
                newAct->setListaAdyacencia(nuevo);
            } else {
                // Insertar al final
                ultimoArco->setProximoNodo(nuevo);
            }
            ultimoArco = nuevo;//actualiza para la siguiente iteracion
            arcoSig = arcoSig->getProximoNodo();
        }
        
        act = act->getProximoNodo();
        newAct = newAct->getProximoNodo();
    }
}

template <typename Element>
void Grafo<Element>::llenarMapa(map<NodoVertice<Element>*,bool> &visitados,NodoVertice<Element>* &inicial,Element v){
    NodoVertice<Element>*act;

    act=g;
    while (act)
    {
        visitados[act]=false;   //llena el mapa como no visitado
        if(act->getInfo()==v)
            inicial=act;        //guardar el nodo del vertice inicial
        act=act->getProximoNodo();
    }
    
}

template <typename Element>
list<Element> Grafo<Element>::BFS(Element v){
    NodoVertice<Element>*inicial=NULL;
    map<NodoVertice<Element>*,bool> visitados;
    list<Element> result;

    llenarMapa(visitados,inicial,v);
    if(inicial)
        BFS(inicial,visitados,result);  
    return result;
}
template <typename Element>
void Grafo<Element>::BFS(NodoVertice<Element>* inicial,map<NodoVertice<Element>*,bool> &visitados,list<Element> &result){
    NodoArco<Element> *arcoAct;
    queue<NodoVertice<Element>*> cola;

    cola.push(inicial);
    while (!cola.empty())   //recorre los sucesores de inicial
    {
        inicial=cola.front();
        cola.pop();
        
        if (!visitados[inicial])
        {
            visitados[inicial]=true;                    //marca el vertice como visitado
            result.push_back(inicial->getInfo());       //guarda el vertice no visitado
            arcoAct=inicial->getListaAdyacencia();

            while (arcoAct)                             //guarda en la cola los vertices no visitados
            {
                if (!visitados[arcoAct->getInfo()])
                {
                    cola.push(arcoAct->getInfo());
                }
                arcoAct=arcoAct->getProximoNodo();
            }
            
        }
        
    }
    
}

template <typename Element>
list<Element> Grafo<Element>::DFS(Element v){
    NodoVertice<Element>*inicial=NULL;
    map<NodoVertice<Element>*,bool> visitados;
    list<Element> result;

    llenarMapa(visitados,inicial,v);
    if(inicial)
        DFS(inicial,visitados,result);  
    return result;
}
template <typename Element>
void Grafo<Element>::DFS(NodoVertice<Element>* inicial,map<NodoVertice<Element>*,bool> &visitados,list<Element> &result){
    NodoArco<Element> *arcoAct;

    if (!visitados[inicial])
    {
        arcoAct=inicial->getListaAdyacencia();

        visitados[inicial]=true;             //marca el vertice como visitado
        result.push_back(inicial->getInfo());//guarda el vertice no visitado

        while (arcoAct)
        {
            DFS(arcoAct->getInfo(),visitados,result);//busca recursivamente los sucesores
            arcoAct=arcoAct->getProximoNodo();
        }
        
    }
    
}
#endif


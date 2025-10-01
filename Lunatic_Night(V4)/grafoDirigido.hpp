#ifndef GRAFOHPP
#define GRAFOHPP

#include "nodoGrafo.hpp"
#include <iostream>
#include <unordered_map>
#include <map>
#include <algorithm>
#include<list>
#include<queue>
using namespace std;

/*
    GRAFO DIRIGIDO
*/


template<typename Element>
class Grafo{
    protected:
        VerticeNode<Element> *g;
        int nVertices,mArcos;
        bool verificarExistenciaElementoEnCola(queue<Element> cola, Element info); // Metodo privado para verificar la existerncia de ese elemento en la cola, implicando que hay que desenconlar para encontrarla

    private:
        VerticeNode<Element> *getVerticeInicia(){return g;}
        void DFS(Grafo<int> &g, int fuente, list<int> &recorrido, bool *visitados);
        void BFS(Grafo<int> &g, vector<bool> &visitados, list<int> &recorrido, int nodoInicial);
    public:
        // Este metodo puede utilizarse sin instanciar un objeto
        // Esta funcion sirve para mapear los datos de un diccionario, permitiendo asi la facilidad de controlar los recorridos del grafo
        // la funcion retorna un diccionario [int,lista(int)] , recibira el mapa de con los datos orginales [Element, list(Element)] y otro dicionario que pasaremos por referencia
        // Debido a que lo estaremos utilizando para decodificar el mapeo o los resultados que nos deje el grafo [Element,int]
        static unordered_map<int, list<int> > mapearDiccionario(unordered_map<Element, list<Element> > diccionario, unordered_map<Element,int> &mapaComp);    // Metodo funcion que servira para mapear diccionarios y que tenga facil acceso a la hora de procesarlos
    
        Grafo();    // Crea un grafo vacio
        ~Grafo();   // Destruye el grafo
        Grafo(const Grafo<Element> &target);  // Constructor copia
        void vaciarGrafo(); // Vacia el grafo existente
        Element getFuente();  // Devuelve el nodo inicial del grafo, es decir el atributo VerticeNode<Element> *g, pero en este caso, su elemento contenido en el 
        bool esVacio();     // Metodo logico si el grafo no tiene nodos // O(1) porque solo se verifica los atributos nVertices
        void addVertice(Element v);   // Anadir una vertice al principio de la vertice apuntada por el apuntador "g" de VerticeNode O(1)
        
        // Nodo: estos dos metodos que tienen virtual estan pensados para reinventarse en la clase hija de grafo, Grafo no dirigido
        virtual void agregarArco(Element v, Element w, float c);    // Buscar el vertice 'v' en la lista de vertices y agregar un nodo de adyacencia a ese vertice para apuntar el vertice 'w', O(n)
        virtual void agregarArco(Element v, Element w);             // Crea un arco con peso 1
        void getReverse();  // Metodo para invertir los arcos de un grafo(Valido para grafo Dirigido)
        void eliminarVertice(Element v);      // Buscar el vertice y eliminarlo (eso implica tambien eliminar o destruir sus arcos) O(n + m)
        virtual void eliminarArco(Element v,Element w);     // Eliminar el arco es buscar el vertice inicial y luego el vertice correspondiente O(n + m)
        bool existeVertice(Element v);    // Buscar el elemento en la lista de vertices, la lista en casos generales se encontrara desgetNVerticesada, asi que la forma mas viables es iterar en ella, O(n)
        bool existeArco(Element v, Element w);  // Buscar el vertice de adyacencia, primero buscar la vertice para luego buscar su arco O(n + m)
        float getPesoArco(Element v, Element w);   // O(n + m)
        int getNVertices(); // Consultar el numero de vertices, O(1)
        int getMArcos();    // Consultar el numero de arcos, O(1)
        list<Element> predecesores(Element e); // Conocer los predecesores (los que le envian la informacion a una vertice especifica) O(n + m)
        list<Element> sucesores(Element e); // O(n + m), simplemente devuelve la lista de los arcos del vertice
        list<Element> getVecinos(Element e);
        list<Element> getVertices(); //O(n)retorna una lista con los vertices del grafo
        virtual list<list<Element> > getArcos();    // Devuelve la lista de arcos del grafo
        map<int,Element> getMapVertices(); //O(n)  retorna un mapa con un mapeo de los vertices
        Grafo<int> getMapGrafo(); //retorna un el mismo grafo con valores mapeados
        list<int> BFS(Grafo<int> &g);
        list<int> DFS(Grafo<int> &g);    
        
};


template <typename Element>
inline void Grafo<Element>::vaciarGrafo()
{
    if(nVertices == 0) return;  // No puede vaciar un grafo vacio

    VerticeNode<Element> *iterVer = g, *del = NULL;    // Empezamos en el nodo fuente

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
    vaciarGrafo();  // Llama directamente al vaciarGrafo
    g = NULL;
    nVertices = 0;
    mArcos = 0;
}

template <typename Element>
inline Grafo<Element>::Grafo(const Grafo<Element> &target) : g(NULL),nVertices(0),mArcos(0)
{
    // Copiar todos los vértices
    VerticeNode<Element>* actual = target.g;
    VerticeNode<Element>* ultimo = NULL;

    // Mapeo para relacionar los vértices originales con los nuevos
    unordered_map<VerticeNode<Element>*, VerticeNode<Element>*> mapaVertices;

    // Primera pasada: copiar vértices
    while(actual) {
        VerticeNode<Element>* nuevoVertice = new VerticeNode<Element>(actual->getInfo());
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
        ArcNode<Element>* arcoActual = actual->getListaAdyacencia();
        VerticeNode<Element>* nuevoVertice = mapaVertices[actual];
        ArcNode<Element>* ultimoArco = NULL;
        
        while (arcoActual) {
            ArcNode<Element>* nuevoArco = new ArcNode<Element>();
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
void Grafo<Element>::addVertice(Element v)
{
    // Anadiremos el vertice la principio de la lista de grafos

    VerticeNode<Element> *nuevoVertice = new VerticeNode<Element>(v);   // Creamos el nodo asignando memoria
    VerticeNode<Element> *ant=NULL,*sig=g;
    while (sig)
    {
        ant=sig;
        sig=sig->getProximoNodo();
    }
    

    if(!g)   // si el puntero al vertice inicial (puntero g) es vacio entoces se incerta al principio
    {
        g=nuevoVertice;
    }else
    {
        //sino, se inserta en la ultima posicion
        ant->setProximoNodo(nuevoVertice);
        nuevoVertice->setProximoNodo(NULL);
    }
    

    nVertices += 1; // Sumamos la cantidad
}


// Inserta un arco con su peso correspondiente a una vertice hacia otra vertice
template <typename Element>
void Grafo<Element>::agregarArco(Element v, Element w, float c)
{
    // if(!g) return;  // El grafo esta vacio, no hay vertices para enlazar

    VerticeNode<Element> *iterVertices = g;   // puntero iterador desde nodo apuntado por el grafo
    ArcNode<Element> *nuevoArco = NULL;   // puntero para crear el nuevo arco
    VerticeNode<Element> *memorizarVertice = NULL;    // Este puntero servira para guardar la direccion del vertice w

    while(iterVertices && iterVertices->getInfo() != v){
        if(iterVertices->getInfo() == w)    // En caso de encontrar el vertice w antes del vertice v, guardarlo para ahorrar tiempo
            memorizarVertice = iterVertices;
        
        iterVertices = iterVertices->getProximoNodo();
    }

    // En caso de no haber encontrado la vertice, tendra que crearlo e insertarlo como nuevo
    if(!iterVertices){
        iterVertices = new VerticeNode<Element>(v);
        iterVertices->setProximoNodo(g);    // Lo colocamos al principio del grafo
        g = iterVertices;
        nVertices += 1;
    }
    
    nuevoArco = new ArcNode<Element>();   // Creamos el nuevo nodo de adyacencia

    if(!memorizarVertice)    // si el iterador no se topo con w antes que v
    {
        memorizarVertice = iterVertices;    // memorizar vertice va a iterar desde la posicion actual del vertice v
        while(memorizarVertice && memorizarVertice->getInfo() != w){
            memorizarVertice = memorizarVertice->getProximoNodo();
        }

        // en caso de que w no sea encontrado en el grafo
        if(!memorizarVertice){
            // Tendra que ser creado tambien
            memorizarVertice = new VerticeNode<Element>(w);
            VerticeNode<Element> *act=g;
            while (act->getProximoNodo())
            {
                act=act->getProximoNodo();
            }
            act->setProximoNodo(memorizarVertice);
            memorizarVertice->setProximoNodo(NULL);
            // igual se insertara al principio
            /*memorizarVertice->setProximoNodo(g);
            g = memorizarVertice;*/
            nVertices += 1;
        }
    }

    // Cargamos el nodo adyacencia
    nuevoArco->setCosto(c);
    nuevoArco->setInfo(memorizarVertice);
    nuevoArco->setProximoNodo(iterVertices->getListaAdyacencia());  // el nuevo nodo de adyacencia apunta al nodo de la lista de adyacencias de la vertice(en caso de no haber nodos, apunta a NULL)
    iterVertices->setListaAdyacencia(nuevoArco);    // El se convierte en el primero
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
    set<pair<VerticeNode<Element>*, VerticeNode<Element>* > > arcosUnicos;   // Este objeto coleccionara los arcos ya anteriormente volteados
    
    // Iteradores
    VerticeNode<Element> *iteradorVertices  = g;    // Iterador de vertices
    ArcNode<Element> *iteradorArcos = NULL, *ant, *nuevoArco, *aux;     // Iterador de arcos, puntero para memorizar el arco anterior y otro para crear el nuevo arco

    // Begin

    // iteramos cada vertice
    while(iteradorVertices){
        iteradorArcos = iteradorVertices->getListaAdyacencia(); 
        ant = NULL;

        // iteramos cada arco
        while(iteradorArcos){
            
            // Auxiliar para tomar un par de vertices
            pair<VerticeNode<Element>*, VerticeNode<Element>* > auxiliar(iteradorVertices,iteradorArcos->getInfo());
            
            // Primero preguntamos si el arco w -> v existe

            // Cuando vayamos iterando por los arcos del los vertices, debemos tener cuidado en cambiar nuevamente las aristas ya cambiadas en pasos anteriores
            
            // En caso de no existir ese caso, se elimina el arco iterArcos y se asigna un nuevo arco otro
            if(arcosUnicos.find(auxiliar) == arcosUnicos.end()){
                
                // Creamos el nuevo arco
                nuevoArco = new ArcNode<Element>(iteradorVertices,0,iteradorArcos->getInfo()->getListaAdyacencia());
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

    VerticeNode<Element> *iterador = g,*ant =NULL;   // Iterador a nodos
    // tambien un puntero ant para apuntar al nodo que le sigue despues del eliminado
    ArcNode<Element> *listaAdy = NULL, *antArco = NULL;    // Para eliminar los nodos de adyacencia

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
        VerticeNode<Element> *del = iterador; // Puntero de eliminacion
        if(ant){
            ant->setProximoNodo(iterador->getProximoNodo());    // cambiamos el puntero al siguiente del eliminado
        }else{
            g->setProximoNodo(iterador->getProximoNodo());
        }
        // Eliminamos la vertice(el metodo destructor de la clase nodoVertice esta programado para eliminar tanto los nodos adyacentes como el mismo)
        // con ello, se elimina los sucesores
        delete del; // liberamos memoria

        nVertices -= 1; // Reducimos la cantidad de vertices
    }
}

template <typename Element>
void Grafo<Element>::eliminarArco(Element v, Element w){

    if(!g) return;  // Caso de que el grafo este vacio

    VerticeNode<Element> *ptrVertice = g; // iterador entre vertices
    ArcNode<Element> *ptrAd = NULL, *ant = NULL; // iterador entre nodos adyacencia

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

    VerticeNode<Element> *iteradorVer = this->g;

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
    VerticeNode<Element> *iterVer = g;
    ArcNode<Element> *iterAd = NULL;

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
    VerticeNode<Element> *iterVer = g;
    ArcNode<Element> *iterAd = NULL;

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

        while(iterAd && iterAd->getInfo()->getInfo() == w)  // Buscar ese arco apuntando
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
list<Element> Grafo<Element>::predecesores(Element e)
{
    if(!g) return list<Element>();    // Devuelve una lista vacia en caso de ser un grafo vacio

    list<Element> result; // Creamos la lista de nodos que tienen direccion V -> e

    VerticeNode<Element> *iterVer = g;
    ArcNode<Element> *iterAdy = NULL;

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
list<Element> Grafo<Element>::sucesores(Element e){
    // Creamos una lista vacia
    list<Element> result;

    if(!g)  return result;   // devuelve lista vacia


    // Declaramos los punteros necesarios
    VerticeNode<Element> *iterVer = g;    // Apuntando al nodo g
    ArcNode<Element> *iterAdy = NULL;

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
    VerticeNode<Element> *iterVertice = g;
    ArcNode<Element> *iterAdy = NULL;
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
    VerticeNode<Element> *act=this->g;
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
    VerticeNode<Element> *act=g;
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
    VerticeNode<Element> *act=g;
    ArcNode<Element> *adyAct;
    map<VerticeNode<Element>*,int> mapa;
    Grafo<int> grafo;
    int i=0;
    
    //crea los vertices mapeados del grafo
    while (act){
        grafo.addVertice(i);
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

    VerticeNode<Element> *iterarVertice = g;
    ArcNode<Element> *iterarAdy = NULL;

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
template<typename Element>
list<int> Grafo<Element>::BFS(Grafo<int> &g){
    list<int> recorrido;
    vector<bool> visitados(g.getNVertices(), false);
    
    for(int i = 0; i < g.getNVertices(); i++){
        if(!visitados[i])
            BFS(g, visitados, recorrido, i);
    }
    return recorrido;
}

template<typename Element>
void Grafo<Element>::BFS(Grafo<int> &g, vector<bool> &visitados, list<int> &recorrido, int nodoInicial){
    queue<int> c;
    list<int> sucesores;
    int v, m;

    visitados[nodoInicial] = true; 
    c.push(nodoInicial);

    while(!c.empty()){
        v = c.front();
        c.pop();

        recorrido.push_back(v);
        sucesores = g.sucesores(v);

        while(!sucesores.empty()){
            m = sucesores.front();    
            if(!visitados[m]){  
                visitados[m] = true;
                c.push(m);
            }
            sucesores.pop_front();
        }
    }
}
template<typename Element>
list<int> Grafo<Element>::DFS(Grafo<int> &g){
    list<int> recorrido;
    bool visitados[g.getNVertices()];

    for(int i = 0; i < g.getNVertices(); i++)
        visitados[i] = false;   // Llenamos el vector de falsos

    DFS(g,g.getFuente(),recorrido,visitados); // Opera la funcion recursiva

    return recorrido;
}
template<typename Element>
void Grafo<Element>::DFS(Grafo<int> &g, int fuente, list<int> &recorrido, bool *visitados){
    list<int> sucesores;
    if(!visitados[fuente-1]){
        int i;

        // Estamos en el recorrido del nodo actual, asi que
        visitados[fuente-1] = true; // se tacha como nodo recorrido
        recorrido.push_back(fuente);    // inserta la fuente en la lista de recorridos

        // tomamos los sucesores de la fuente
        sucesores = g.sucesores(fuente);

        while(!sucesores.empty()){
            DFS(g,sucesores.front(),recorrido,visitados);   // Recursion al primer elemento de los sucesores del siguiente sucesor
            sucesores.pop_front();  // Eliminamos ese sucesor
        }   
    }
}


#endif


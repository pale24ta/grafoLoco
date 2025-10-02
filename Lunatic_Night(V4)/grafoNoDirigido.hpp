#ifndef GRAFONODIR
#define GRAFONODIR

#include "nodoGrafo.hpp"
#include "grafoDirigido.hpp"
#include <iostream>
#include <unordered_map>
#include <set>
#include<list>
#include<queue>
using namespace std;


// Para esta clase, el grafo no dirigido sera hijo del grafo dirigido, aqui la particularidad
// que tendra el grafo no dirigido, es el uso de polimorfismo para clase, los atributos seran compartidos,
// es decir, el acceso de atributos de la clase Grafo esta protegida, o en pocas palabras, la clase 
// Grafo no dirigido tendra acceso a ellas, permitiendo haci una gran facilidad en el polimorfismo de los metodos,
// agregarArcos y eliminar Arcos

template <typename Element>
class GrafoNoDirigido : public Grafo<Element>{

    public:
        GrafoNoDirigido();
        GrafoNoDirigido(const GrafoNoDirigido &target);
        ~GrafoNoDirigido();
        list<Element> getVecinos(Element e);
        void agregarArco(Element v, Element w, float c);    // la insercion de arcos sera diferente ya que tendremos que insertar un nodo adyacencia apuntando al otro
        void eliminarArco(Element v,Element w);     // Eliminar el arco es buscar el vertice inicial y luego el vertice correspondiente O(n + m)
        GrafoNoDirigido<int> getMapGrafo(); //retorna un el mismo grafo con valores mapeados
        list<list<Element> > getArcos();    // Devuelve la lista de arcos del grafo
        
};
template <typename Element>
GrafoNoDirigido<Element>::GrafoNoDirigido(): Grafo<Element>(){}

template <typename Element>
GrafoNoDirigido<Element>::GrafoNoDirigido(const GrafoNoDirigido &target):Grafo<Element>(target){}

template <typename Element>
GrafoNoDirigido<Element>::~GrafoNoDirigido(){
    this->vaciarGrafo();
    this->g = NULL;
    this->mArcos = 0;
    this->nVertices = 0;
}

template <typename Element>
void GrafoNoDirigido<Element>::agregarArco(Element v, Element w, float c){
       
    // En caso de que esos dos arcos ya existan en el grafo, no se opera
    if(this->existeArco(v,w) && this->existeArco(w,v)) return;
    // Para esta union de arcos, hay que hacer tal que v -> w y w -> v

    NodoVertice<Element> *iterVerticeA = this->g, *iterVerticeB = NULL;
    NodoArco<Element> *nuevoArco = NULL;
    Element aux;

    // El primer paso seria encontrar v o w en el grafo, utilizarems iterVerticeA para ello

    while(iterVerticeA && !(iterVerticeA->getInfo() == v || iterVerticeA->getInfo() == w))
        iterVerticeA = iterVerticeA->getProximoNodo();

    // en caso de no haber encontrado la vertice v o w, hay que crearla
    if(!iterVerticeA){
        iterVerticeA = new NodoVertice<Element>(v);   // Este vertice sera v
        
        NodoVertice<Element> *aux = this->g;
        while(aux && aux->getProximoNodo())
            aux =  aux->getProximoNodo();

        if(aux){
            aux->setProximoNodo(iterVerticeA);
        }else{
            iterVerticeA->setProximoNodo(this->g);
            this->g = iterVerticeA;
        }
    
        //mapeamos el vertice
        // this->mapaDeGrafo[v] = this->nVertices;
        this->nVertices += 1;
    }

    aux = iterVerticeA->getInfo();  // guardamos el dato para diferenciarlo con el siguiente

    // iterador b iniciara al inicio tambien
    iterVerticeB = this->g;

    // mientras el puntero no sea null, el iterador no sea ni v ni w ni tampoco el dato anterior capturado en iterVerticeA
    while(iterVerticeB && (!(iterVerticeB->getInfo() == v || iterVerticeB->getInfo() == w) || iterVerticeB->getInfo() == aux))
        iterVerticeB = iterVerticeB->getProximoNodo();
    
    // igual caso si no se encontro la otra vertice se crea
    if(!iterVerticeB){
        NodoVertice<Element> *iterAux = this->g;

        // dependiendo del vertice anterior creada/encontrada/ se crea con el dato del opuesto
        Element e = (aux == w)? v : w;

        iterVerticeB = new NodoVertice<Element>(e);

        // insertamos al final del grafo
        while(iterAux && iterAux->getProximoNodo())
            iterAux = iterAux->getProximoNodo();

        if(iterAux){
            iterAux->setProximoNodo(iterVerticeB);
        }else{
            iterVerticeB->setProximoNodo(this->g);
            this->g = iterVerticeB;
        }

        // lo mapeamos tambien 
        // this->mapaDeGrafo[e] = this->nVertices;
        this->nVertices += 1;
    }

    // una ves encontrado las dos vertices, ahora creamos un arco que apunte de
    // v -> w

    nuevoArco = new NodoArco<Element>(iterVerticeB,c,iterVerticeA->getListaAdyacencia());
    iterVerticeA->setListaAdyacencia(nuevoArco);

    // w -> v
    nuevoArco = new NodoArco<Element>(iterVerticeA,c,iterVerticeB->getListaAdyacencia());
    iterVerticeB->setListaAdyacencia(nuevoArco);
    this->mArcos += 1;
}

template<typename Element>
void GrafoNoDirigido<Element>::eliminarArco(Element v,Element w){     // Eliminar el arco es buscar el vertice inicial y luego el vertice correspondiente O(n + m)
    // Aqui seria mas facil encontrar la vertice v o w, nos apoyamos del arco
    NodoVertice<Element> *iterVer = this->g;
    NodoArco<Element> *iterAdyAct = NULL,*iterAdyAnt = NULL;

    //Buscamos alguna vertice

    while(iterVer && !(iterVer->getInfo() == v || iterVer->getInfo() == w)){
        iterVer = iterVer->getProximoNodo();
    }

    if(iterVer){
        iterAdyAct = iterVer->getListaAdyacencia();
        while(iterAdyAct && !(iterAdyAct->getInfo()->getInfo() == v || iterAdyAct->getInfo()->getInfo() == w)){
            iterAdyAnt = iterAdyAct;
            iterAdyAct = iterAdyAct->getProximoNodo();
        }

        // En caso de ser encontrado
        if(iterAdyAct){
            

            // Verificamos para el caso de que iterAdyAnt no sea NULL
            if(iterAdyAnt)
                iterAdyAnt->setProximoNodo(iterAdyAct->getProximoNodo());   // Cambiamos los punteros
            else
                iterVer->setListaAdyacencia(iterAdyAct->getProximoNodo());

            // Dirigimos el puntero iterVer al w o v utilizando el arco
            iterVer = iterAdyAct->getInfo();

            delete iterAdyAct;  // Eliminamos el nodo
            this->mArcos -= 1;
            
            iterAdyAct = iterVer->getListaAdyacencia();
            iterAdyAnt = NULL;

            // Repetiremos el mismo proceso

            while(iterAdyAct && !(iterAdyAct->getInfo()->getInfo() == v || iterAdyAct->getInfo()->getInfo() == w)){
                iterAdyAnt = iterAdyAct;
                iterAdyAct = iterAdyAct->getProximoNodo();
            }

            if(iterAdyAct){
                if(iterAdyAnt){
                    iterAdyAnt->setProximoNodo(iterAdyAct->getProximoNodo());
                }else{
                    iterVer->setListaAdyacencia(iterAdyAct->getProximoNodo());
                }
                delete iterAdyAct;
                this->mArcos -= 1;
            }

        }
    }
}

template <typename Element>
list<Element> GrafoNoDirigido<Element>::getVecinos(Element e){

    list<Element> vecinos;

    if(!this->g) return vecinos;
    // aqui basta buscar la vertice e


    NodoVertice<Element> *iterVertice = this->g;
    NodoArco<Element> *iterListaAdy = NULL;

    while(iterVertice && iterVertice->getInfo() != e){
        iterVertice = iterVertice->getProximoNodo();
    }

    if(iterVertice){
        iterListaAdy = iterVertice->getListaAdyacencia();
        
        while(iterListaAdy){
            vecinos.push_back(iterListaAdy->getInfo()->getInfo());
            iterListaAdy = iterListaAdy->getProximoNodo();
        }
    }
    return vecinos;
}



#endif

template <typename Element>
inline GrafoNoDirigido<int> GrafoNoDirigido<Element>::getMapGrafo()
{
    NodoVertice<Element> *act= this->g;
    NodoArco<Element> *adyAct;
    map<NodoVertice<Element>*,int> mapa;
    GrafoNoDirigido<int> grafo;
    int i=0;
    
    //crea los vertices mapeados del grafo
    while (act){
        grafo.agregarVertice(i);
        mapa[act]=i;    //crea un mapa que relaciona vertice y su posicion asignada
        act=act->getProximoNodo();
        i++;
    }

    //crea los arcos mapeados del grafo
    act=this->g;
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
inline list<list<Element> > GrafoNoDirigido<Element>::getArcos()
{
    // Para este caso, necesitamos guardar los arcos, sin repetir los mismos arcos, no puede haber en la lista
    // v,w y w,v ; solo uno de ellos
    list<list<Element> > arcos;

    // Usaremos una clase conjunto
    set<pair<Element, Element> > arcosUnicos;

    NodoVertice<Element> *iterVertice = this->g;
    NodoArco<Element> *iterAdy = NULL;

    while(iterVertice){
        iterAdy = iterVertice->getListaAdyacencia();

        while(iterAdy){
            Element v = iterVertice->getInfo();
            Element w = iterAdy->getInfo()->getInfo();

            pair<Element,Element> pares = (v < w)? make_pair(v,w) : make_pair(w,v);

            // en caso de que el arco este en el conjunto, evita repetirlo
            if(arcosUnicos.find(pares) == arcosUnicos.end()){
                arcosUnicos.insert(pares);
                arcos.push_back(list<Element>({pares.first,pares.second}));
            }
            iterAdy = iterAdy->getProximoNodo();
        }

        iterVertice = iterVertice->getProximoNodo();
    }
    return arcos;
}

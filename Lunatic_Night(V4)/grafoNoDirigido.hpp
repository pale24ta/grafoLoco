#ifndef GRAFONODIR 
#define GRAFONODIR

#include "nodoGrafo.hpp"
#include "grafoDirigido.hpp"
#include <iostream>
#include <unordered_map>
#include <set>
#include <list>
#include <queue>
using namespace std;


// Para esta clase, el grafo no dirigido sera hijo del grafo dirigido, aqui la particularidad
// que tendra el grafo no dirigido, es el uso de polimorfismo para clase, los atributos seran compartidos,
// es decir, el acceso de atributos de la clase Grafo esta protegida, o en pocas palabras, la clase 
// Grafo no dirigido tendra acceso a ellas, permitiendo haci una gran facilidad en el polimorfismo de los metodos,
// agregarArcos y eliminar Arcos

template <typename Element>
class GrafoNoDirigido : public Grafo<Element>{
    private:
        NodoVertice<Element>* getPosElement(Element v); //retrona un puntero a la posicion del elemento
        NodoVertice<Element>* getUltimaPos();   //retorna el ultimo nodo insertado
        void getReverse();  // Metodo bloqueado para esta clase
    public:
        GrafoNoDirigido();
        GrafoNoDirigido(const GrafoNoDirigido &target);
        ~GrafoNoDirigido();
        list<Element> getVecinos(Element e);
        void agregarArco(Element v, Element w, float c);    // la insercion de arcos sera diferente ya que tendremos que insertar un nodo adyacencia apuntando al otro
        void agregarArco(Element v, Element w) {agregarArco(v,w,1);}
        void eliminarArco(Element v,Element w);     // Eliminar el arco es buscar el vertice inicial y luego el vertice correspondiente O(n + m)
        GrafoNoDirigido<int> getMapGrafo(); //retorna un el mismo grafo con valores mapeados
        list<list<Element> > getArcos();    // Devuelve la lista de arcos del grafo
        float getPeso();
};

template <typename Element>
float GrafoNoDirigido<Element>::getPeso(){
    return Grafo<Element>::getPeso()/2;
}

template<typename Element>
void GrafoNoDirigido<Element>::getReverse(){
    Grafo<Element>::getReverse();
}

template <typename Element>
GrafoNoDirigido<Element>::GrafoNoDirigido(): Grafo<Element>(){}

template <typename Element>
GrafoNoDirigido<Element>::GrafoNoDirigido(const GrafoNoDirigido &target):Grafo<Element>(target){}

template <typename Element>
GrafoNoDirigido<Element>::~GrafoNoDirigido(){
    this->vaciar();
    this->g = NULL;
    this->mArcos = 0;
    this->nVertices = 0;
}

template <typename Element>
void GrafoNoDirigido<Element>::agregarArco(Element v, Element w, float c){
       
    // En caso de que esos dos arcos ya existan en el grafo, no se opera
    if(this->existeArco(v,w) && this->existeArco(w,v)) return;
    // Para esta union de arcos, hay que hacer tal que v -> w y w -> v

    
    NodoVertice<Element>*vertV,*vertW,*ultPos;
    if (!this->g)   //si el grafo esta vacio, entonces incertas ambaos vertices
    {
        vertV= new NodoVertice<Element>(v);
        vertW= new NodoVertice<Element>(w);
        this->g=vertV;
        vertV->setProximoNodo(vertW);
        this->nVertices=2;
    }else{
        //se busca los vertices en el grafo, si no existen, entonces se incertan al final
            vertV=getPosElement(v); //busca la posicion del vertice
        if(!vertV){
            ultPos=getUltimaPos();  //busca el ultimo vertice del grafo
            vertV= new NodoVertice<Element>(v); //crea el vertice v
            ultPos->setProximoNodo(vertV);      //inserta el vertice al final
            this->nVertices++;                  //aumenta el numero de vertices
        }
        vertW=getPosElement(w);
        if(!vertW){
            ultPos=getUltimaPos();              //busca el ultimo vertice del grafo
            vertW= new NodoVertice<Element>(w); //crea el vertice v
            ultPos->setProximoNodo(vertW);      //inserta el vertice al final
            this->nVertices++;                  //aumenta el numero de vertices
        }
    }
    
    
    //en el primer ciclo crea e inserta el arco v -> w y en el segundo de w -> v
    for (int i = 0; i < 2; i++)
    {
        NodoArco<Element>*nuevoArco,*arcoAnt;
        NodoVertice<Element> *vertA,*vertB;
        switch (i)
        {
        case 0: //se crea un arco de v -> w
            vertA=vertV;    
            vertB=vertW;
            break;
        
        default://w -> v
            vertA=vertW;
            vertB=vertV;
            break;
        }
        //inserta el arco en el primer lugar de la lista de adyacencia
        arcoAnt= vertA->getListaAdyacencia();
        nuevoArco= new NodoArco<Element>(vertB);//se crea el vertice
        nuevoArco->setPeso(c);                  //le asigna el peso del arco
        nuevoArco->setProximoNodo(arcoAnt);     //apunta a la primera posicion
        vertA->setListaAdyacencia(nuevoArco);   //inserta el arco en el primer lugar de la lista de adyacencia
    }
    
    this->mArcos++;
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
    return this->getSucesores(e);
}

template <typename Element>
inline GrafoNoDirigido<int> GrafoNoDirigido<Element>::getMapGrafo()
{
    NodoVertice<Element> *act= this->g;
    NodoArco<Element> *adyAct;
    unordered_map<NodoVertice<Element>*,int> mapa;
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

template <typename Element>
NodoVertice<Element>* GrafoNoDirigido<Element>::getPosElement(Element v){
    if(!this->g) return NULL;
    NodoVertice<Element>* act=this->g;
    bool found=false;
    while (act && !found)
    {
        if(act->getInfo()==v)
            found= true;
        else
            act=act->getProximoNodo();
    }
    return act;
}

template <typename Element>
NodoVertice<Element>* GrafoNoDirigido<Element>::getUltimaPos(){
    if(!this->g) return NULL;
    NodoVertice<Element>* act=this->g;
    while (act && act->getProximoNodo())
    {
        act=act->getProximoNodo();
    }
    return act;
}

#endif

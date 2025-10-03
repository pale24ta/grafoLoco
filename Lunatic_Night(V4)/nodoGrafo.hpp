#ifndef NODOGRAFO
#define NODOGRAFO

// La clase Nodo para grafos

template<typename Element>
class NodoArco;  // Forward declaration, le indica al compilador a la hora de leer la clase NodoVertice que existe otra clase llamada NodoArco

template <class Element>
class NodoVertice{

    private:
        Element info;
        NodoVertice<Element> *prox;   // Apunta a la siguiente vertice (actuando como un nodo de lista)
        NodoArco<Element> *listAdy;  // Lista de apuntadores hacia un vertice correspondiente

    public:
        // Constructores
        NodoVertice(){}  // Vertice vacio
        NodoVertice(Element v): info(v),prox(NULL),listAdy(NULL){}   // Vertice solamente con la informacion
        NodoVertice(Element v, NodoVertice<Element> *vN, NodoArco<Element>* adyN):info(v),prox(vN), listAdy(adyN){} // Vertice con sus atributos
        // Destructor
        ~NodoVertice() // le destructor se encargara de eliminar tanto la lista de nodos adyacencia como la vertice 
        {
            if(listAdy){
                NodoArco<Element> *del = NULL, *act = listAdy; // el puntero borrador y el iterador
                while(act){
                    del = act;  // Apunta al siguiente a eliminar
                    act = act->getProximoNodo();    // desplaza el iterador
                    delete del; // liberamos memoria
                }
            }
            listAdy = NULL; // Por si las moscas
        }

        // Getter y setters
        Element getInfo(){return info;}
        NodoVertice<Element>* getProximoNodo(){return prox;}
        NodoArco<Element>* getListaAdyacencia(){return listAdy;}
        void setInfo(Element e){info = e;}
        void setProximoNodo(NodoVertice<Element> *e){prox = e;}
        void setListaAdyacencia(NodoArco<Element>* lista){listAdy = lista;}
};

// clase nodo de adyacencia 
template <class Element>
class NodoArco{
    
    // atributos
    private:
        NodoVertice<Element> *info;   // este atributo contentra el puntero hacia la vertice que apunta el arco
        float weight;   // el peso de ese arco
        NodoArco<Element> *prox;   // el nodo siguiente de la lista de adyacencia

    public:
        // Constructores
        NodoArco():info(NULL),weight(0.0),prox(NULL){} // Nodo vacio
        NodoArco(NodoVertice<Element> *i): info(i),weight(0.0),prox(NULL){} // Nodo ya apuntando a algun vertice
        NodoArco(NodoVertice<Element> *i, float costo, NodoArco<Element> *prox): info(i),weight(costo),prox(prox){}  // Nodo Completo
        ~NodoArco(){
            weight=0.0;
            info=NULL;
            prox=NULL;
        }
        // getters y setters
        NodoVertice<Element> *getInfo(){return info;}
        NodoArco<Element> *getProximoNodo(){return prox;}
        float getPeso(){return weight;}
        void setInfo(NodoVertice<Element> *vN){info = vN;}
        void setPeso(float c){weight = c;}
        void setProximoNodo(NodoArco<Element> *pN){prox = pN;}
};



#endif

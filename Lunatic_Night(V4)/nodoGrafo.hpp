#ifndef NODOGRAFO
#define NODOGRAFO

// La clase Nodo para grafos

template<typename Element>
class ArcNode;  // Forward declaration, le indica al compilador a la hora de leer la clase NodoVertice que existe otra clase llamada ArcNode

template <class Element>
class VerticeNode{

    private:
        Element info;
        VerticeNode<Element> *prox;   // Apunta a la siguiente vertice (actuando como un nodo de lista)
        ArcNode<Element> *listAdy;  // Lista de apuntadores hacia un vertice correspondiente

    public:
        // Constructores
        VerticeNode(){}  // Vertice vacio
        VerticeNode(Element v): info(v),prox(NULL),listAdy(NULL){}   // Vertice solamente con la informacion
        VerticeNode(Element v, VerticeNode<Element> *vN, ArcNode<Element>* adyN):info(v),prox(vN), listAdy(adyN){} // Vertice con sus atributos
        // Destructor
        ~VerticeNode() // le destructor se encargara de eliminar tanto la lista de nodos adyacencia como la vertice 
        {
            if(listAdy){
                ArcNode<Element> *del = NULL, *act = listAdy; // el puntero borrador y el iterador
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
        VerticeNode<Element>* getProximoNodo(){return prox;}
        ArcNode<Element>* getListaAdyacencia(){return listAdy;}
        void setInfo(Element e){info = e;}
        void setProximoNodo(VerticeNode<Element> *e){prox = e;}
        void setListaAdyacencia(ArcNode<Element>* lista){listAdy = lista;}
};

// clase nodo de adyacencia 
template <class Element>
class ArcNode{
    
    // atributos
    private:
        VerticeNode<Element> *info;   // este atributo contentra el puntero hacia la vertice que apunta el arco
        float weight;   // el peso de ese arco
        ArcNode<Element> *prox;   // el nodo siguiente de la lista de adyacencia

    public:
        // Constructores
        ArcNode():info(NULL),weight(0.0),prox(NULL){} // Nodo vacio
        ArcNode(VerticeNode<Element> *i): info(i),weight(0.0),prox(NULL){} // Nodo ya apuntando a algun vertice
        ArcNode(VerticeNode<Element> *i, float costo, ArcNode<Element> *prox): info(i),weight(costo),prox(prox){}  // Nodo Completo
        ~ArcNode(){
            weight=0.0;
            info=NULL;
            prox=NULL;
        }
        // getters y setters
        VerticeNode<Element> *getInfo(){return info;}
        ArcNode<Element> *getProximoNodo(){return prox;}
        float getCosto(){return weight;}
        void setInfo(VerticeNode<Element> *vN){info = vN;}
        void setCosto(float c){weight = c;}
        void setProximoNodo(ArcNode<Element> *pN){prox = pN;}
};



#endif

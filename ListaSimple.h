#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H
#include "functional"
using namespace std;
template <typename D>
class NodoS{
public:
  D data;
  NodoS* siguiente;

  NodoS(D data, NodoS* siguiente=nullptr):data(data), siguiente(siguiente){}

  D getData(){
      return data;
  }
};

template <typename D>
class ListaS{
    public:
    NodoS<D>* cabeza=nullptr;
    NodoS<D>* ultimo=nullptr;
    int n = 0;

    function<void(D)>agregarInicio=[&](D data){
        NodoS <D>* nodo = new NodoS<D>(data);

        if(this->cabeza==nullptr){
           this->cabeza=ultimo;
           this->ultimo=nodo;
        }
        else{
            nodo->siguiente=cabeza;
            cabeza=nodo;
        }
      n++;
    };

    function<void(D)> agregarFinal=[&](D data){
        NodoS <D>* nodo=new NodoS<D>(data);

        if(this->cabeza==nullptr){
            this->cabeza=ultimo;
            this->ultimo=nodo;
        }
        else{
           ultimo->siguiente=nodo;
           ultimo=nodo;
        }
        n++;
    };

    function<void(int, D)> insertarPosicion=[&](int pos, D data){
        NodoS<D>* nodo =new NodoS<D>(data);
        if(pos==1)
        {
            //como cabeza
            nodo->siguiente=this->cabeza;
            this->cabeza=nodo;
            return;
        }
        pos--;

        NodoS<D>*ptr=this->cabeza;
        while(ptr!=nullptr && --pos)
        {
            ptr=ptr->siguiente;
        }
        if(ptr==nullptr)
        return;

        nodo->siguiente=ptr->siguiente;
        ptr->siguiente=nodo;
    };
};
#endif // LISTASIMPLE_H

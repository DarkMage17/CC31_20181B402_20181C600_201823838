#ifndef LISTADOBLE_H
#define LISTADOBLE_H
#include <functional>
#include "qapplication.h"
#include "string"
using namespace std;

template <typename T>
class Nodo {
public:
    T data;
    Nodo* next;
    Nodo* prev;
    Nodo(T data, Nodo* next=nullptr, Nodo* prev=nullptr): data(data), next(next),prev(prev){}
};

template <typename T>
class Lista{
public:
    Nodo<T>* head = nullptr;
    Nodo<T>* selected = nullptr;
    Nodo<T>* tail = nullptr;

    function <void(T)>append=[&](T data){
        Nodo<T>* nodo = new Nodo<T>(data);

        if(head==nullptr)
        {
          this->head = nodo;
          this->selected = head;
          this->tail = nodo;
          return;
        }

        Nodo<T>* last = this->head;
        while (last->next!=nullptr)
        {
          last = last->next;
        }

        last->next = nodo;
        nodo->prev = last;
        tail = nodo;
    };

    function <void()> eliminar=[&](){
        Nodo<T>* temp = this->selected;
        //verificar si está vacio
        if(temp == nullptr) return;

        //verificar si es el unico nodo
        if(temp->prev == nullptr and temp->next == nullptr){
            this->head = nullptr;
            selected = head;
            free(temp);
            return;
        }

        if(temp->prev!=nullptr){
          temp->prev->next = temp->next;
          this->selected = temp->prev;
        }

        if(temp->next!=nullptr){
          temp->next->prev = temp->prev;
          this->selected = temp->next;
          free(temp);
        }
    };

    function<Nodo<T>(int)> GetPos= [&](int n){
        Nodo<T>* current = this->head;
        for(int i = 0; i < n ;i++)
        {
            if(current->next != nullptr){
                current = current->next;
            }
        }
        return *current;
    };

    Nodo<T> getTail()
    {
        return *tail;
    }

    function<int()>Size=[&](){
        int count = 0;
        Nodo<T>* current = this->head;
        while (current != nullptr)
        {
            count++;
            current = current->next;
        }
        return count;
    };

    function<void()>sgt=[&](){
        if(this->selected->next!=nullptr)
        {
          selected = selected->next;
        }
    };

    function<void()>prev=[&](){
        if(this->selected->prev!=nullptr)
        {
          selected = selected->prev;
        }
    };

   function<bool()>EsVacio=[&](){
       return this->head == nullptr;
   };


   Lista<T> filtrar(QString s, int n)
   {
       Lista<T> filtrada;
       switch (n)
       {
       case 0:
           for(int i=0;i<this->Size();i++)
               if(this->GetPos(i).data.getTitulo().contains(s, Qt::CaseInsensitive))
                   filtrada.append(this->GetPos(i).data);
           break;
       case 1:
           for(int i=0;i<this->Size();i++)
               if(this->GetPos(i).data.getTitulo().startsWith(s, Qt::CaseInsensitive))
                   filtrada.append(this->GetPos(i).data);
           break;
       case 2:
           for(int i=0;i<this->Size();i++)
               if(this->GetPos(i).data.getTitulo().endsWith(s, Qt::CaseInsensitive))
                   filtrada.append(this->GetPos(i).data);
           break;
       case 3:
           for(int i=0;i<this->Size();i++)
               if(GetPos(i).data.getTitulo() == s)
                   filtrada.append(this->GetPos(i).data);
           break;
       case 4:
           for(int i=0;i<this->Size();i++)
               if(!(this->GetPos(i).data.getTitulo().contains(s, Qt::CaseInsensitive)))
                   filtrada.append(this->GetPos(i).data);
           break;
       }
       return filtrada;
   }
};
#endif // LISTADOBLE_H

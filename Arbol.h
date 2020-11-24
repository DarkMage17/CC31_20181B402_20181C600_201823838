#ifndef ARBOL_H
#define ARBOL_H

#include <iostream>
#include <vector>
#include <time.h>
#include <functional>
#include <QTextStream>
#include <QListWidget>

using namespace std;

template <typename T>
class Node{
  public:
  T data;
  Node* left;
  Node* right;
  Node(T data, Node* left = nullptr, Node* right = nullptr): data(data), left(left), right(right){}
};

template <typename OBJ,typename KEY = OBJ>
class BST{
  public:
  Node<OBJ>* root;
  function<KEY(OBJ)> key;

  BST(function<KEY(OBJ)> key = [](OBJ obj){return obj;},Node<OBJ>* root = nullptr):key(key),root(root){}

  Node<OBJ>* find_node(KEY val)
  {
      Node<OBJ>* node_null = nullptr;
      Node<OBJ>* current = this->root;
      while(current != nullptr)
      {
          if(val == key(current->data))
              return current;
          else if (val > key(current->data))
              current = current->right;
          else if (val < key(current->data))
              current = current->left;
      }
      return node_null;
  }

  void add(OBJ val){add(this->root, val);}
  void add(Node<OBJ>*& node, OBJ val){
    Node<OBJ>* new_node = new Node<OBJ>(val);
    if(node == nullptr){
      node = new_node;
      return;
    }
    if(key(val) <= key(node->data)){
      add(node->left, val);
    }else{ //VAL > NODE->DATA
      add(node->right, val);
    }
  }
  void del(OBJ val){del(this->root, val);}
  void del(Node<OBJ>*& node, OBJ val){
    //CASO BASE
    if(node == nullptr) return;

    if(key(val) < key(node->data)){
      del(node->left, val);
    } else if(key(val) > key(node->data)){
      del(node->right, val);
    }else{
      if(node->left == nullptr){//NO TEIENE HIJO IZQUIERDO
        node = node->right;
      } else if(node->right == nullptr){//NO TIENE HIJO DERECHO
        node = node->left;
      }else{
        //TODO: MIN_NODE
        Node<OBJ>* temp = min_node(node->right);
        node->data = temp->data;
        del(node->right, temp->data);
      }
    }
  }

  void inorder(QListWidget* lista){ inorder(lista, this->root);}
  void inorder(QListWidget* lista, Node<OBJ>* node){
    //CASO BASE
    if(node == nullptr) return;
    inorder(lista,node->left);
    lista->addItem(node->data.toString());
    inorder(lista,node->right);
  }

  void postorder(QListWidget* lista){ postorder(lista, this->root);}
  void postorder(QListWidget* lista, Node<OBJ>* node){
    //CASO BASE
    if(node == nullptr) return;
    postorder(lista,node->right);
    lista->addItem(node->data.toString());
    postorder(lista,node->left);
  }
  // %%% %%%
  //Lambda [](Juego j){return j.toString();}
  void inorder_l(function<void(OBJ)> imprimir) { inorder_l(imprimir, this->root);}
  void inorder_l(function<void(OBJ)> imprimir, Node<OBJ>* node){
    if(node == nullptr) return;
    inorder_l(imprimir,node->left);
    imprimir(node->data);
    inorder_l(imprimir,node->right);
  }

  Node<OBJ>* min_node(Node<OBJ>* node){
    if(node->left == nullptr) return node;
    while(node && node->left != nullptr){
      node = node->left;
    }
    return node;
  }
};
#endif // ARBOL_H

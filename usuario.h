#ifndef USUARIO_H
#define USUARIO_H
#include <QApplication>
#include <QFile>
#include "QTextStream"
#include "post.h"
#include "ListaSimple.h"
#include "QDate"

class Usuario
{ 
public:
    Usuario(int id, QString correo, QString nombre, QDate fecha);
    Usuario();
    int getId();
    QString getCorreo();
    QString getNombre();
    QDate getFecha();
    void SeguirAmigo(QString amigo);
    QVector<QString> DevolverAmigos();
    void Publicar(QString text);
    void CargarPublis();
    void CargarAmigos();
    int CantidadPosts();
    ListaS<Post> DevolverLista();
    QString fill_space(QString fill, int n = 15){
        int sep = n-fill.size();
        if(sep % 2 != 0)
            return QString((sep/2),' ') + fill + QString((sep/2)+1,' ');
        return QString((sep/2),' ') + fill + QString((sep/2),' ');
    }

    QString toString(){
       QString a = this->fechaRegistro.toString();
       return fill_space(this->correo,46)+" | "+fill_space(this->nombre,6)+" | "+fill_space(a,15);
    }
private:
    QString correo;
    QVector<QString> Amigos;
    ListaS<Post> Publicaciones;
    QString path = "C:/Users/usuario/Desktop/Git/Data/";
    QDate fechaRegistro;
    int id;
    QString nombre;
    //Stack<Post>Publicaciones;

};

#endif // USUARIO_H

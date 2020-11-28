#ifndef USUARIO_H
#define USUARIO_H
#include <QApplication>
#include <QFile>
#include "QTextStream"
#include "post.h"
#include "ListaSimple.h"
#include "QDate"
#include "QListWidget"

class Usuario
{ 
public:
    Usuario(int id, QString correo, QString nombre, QDate fecha);
    Usuario(int id, int idf);
    Usuario();
    int getId();
    int getIdF();
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
    QString toString()
    {
       return this->nombre;
    }
    void AnadirSiguiendo(int ids);
    void addListaSiguiendo(QListWidget *l);
    QVector<int> siguiendo;
private:
    QString correo;
    QVector<QString> Amigos;
    ListaS<Post> Publicaciones;
    QString path = "D:/Projects/CC31_20181B402_20181C600_201823838/Data/";
    QDate fechaRegistro;
    int id;
    int idf;
    QString nombre;
};

#endif // USUARIO_H

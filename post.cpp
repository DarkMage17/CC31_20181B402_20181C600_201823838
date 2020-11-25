#include "post.h"

Post::Post(int idPublicacion, int idUser, QString Titulo,QString texto, QDate fechaPublicacion, int likes)
{
    this->idPublicacion=idPublicacion;
    this->titulo=Titulo;
    this->texto=texto;
    this->fechaPublicacion=fechaPublicacion;
    this->likes=likes;
    this->idUser=idUser;
}

Post::Post()
{

}
int Post::getIdPub()
{
    return this->idPublicacion;
}
int Post::getLikes()
{
    return this->likes;
}
int Post::getIdUsers()
{
    return this->idUser;
}
QDate Post::getFechaPub()
{
    return this->fechaPublicacion;
}
QString Post::getTexto()
{
    return this->texto;
}
QString Post::getTitulo()
{
    return this->titulo;
}

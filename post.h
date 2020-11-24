#ifndef POST_H
#define POST_H
#include <QApplication>
#include "QDate"

class Post
{
public:
    Post(int idPublicacion,int idUser, QString Titulo,QString texto, QDate fechaPublicacion, int likes);
    int getIdPub();
    int getIdUsers();
    int getLikes();
    QString getTitulo();
    QString getTexto();
    QDate getFechaPub();
    QString fill_space(QString fill, int n = 15){
        int sep = n-fill.size();
        if(sep % 2 != 0)
            return QString((sep/2),' ') + fill + QString((sep/2)+1,' ');
        return QString((sep/2),' ') + fill + QString((sep/2),' ');
    }

    QString toString(){
       return fill_space(this->titulo ,35) + "|" + fill_space(this->fechaPublicacion.toString("yyyy-MM-dd")) + "|" + fill_space(this -> a = QString::number(likes));
    }
protected:
private:
    int idPublicacion;
    int idUser;
    int likes;
    QString texto;
    QString titulo;
    QDate fechaPublicacion;
    QString s;
    QString a;
};

#endif // POST_H

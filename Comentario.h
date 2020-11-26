#ifndef COMENTARIO_H
#define COMENTARIO_H
#include "post.h"
class Comentario : public Post
{
private:
    int idC;
public:
    Comentario()
    {
        texto = "aea";
        fechaPublicacion = QDate::currentDate();
        idC = 1;
        idPublicacion = 1;
    }

    Comentario(int _idC, int _idPublicacion,QDate _fechaPublicacion,QString _texto)
    {
        texto = _texto;
        fechaPublicacion = _fechaPublicacion;
        idC = _idC;
        idPublicacion = _idPublicacion;
    }

    int getIDP()
    {
        return idPublicacion;
    }

    QString getT()
    {
        return texto;
    }

    int getIDC()
    {
        return idC;
    }

    QDate getFechaC()
    {
        return fechaPublicacion;
    }
};

#endif // COMENTARIO_H

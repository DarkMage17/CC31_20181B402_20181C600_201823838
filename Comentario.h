#ifndef COMENTARIO_H
#define COMENTARIO_H
#include "post.h"
class Comentario : public Post
{
public:
    Comentario()
    {
        texto = "aea";
        fechaPublicacion = QDate::currentDate();
        idUser = 1;
        idPublicacion = 1;
    }

    Comentario(int _idUser, int _idPublicacion,QDate _fechaPublicacion,QString _texto)
    {
        texto = _texto;
        fechaPublicacion = _fechaPublicacion;
        idUser = _idUser;
        idPublicacion = _idPublicacion;
    }
};

#endif // COMENTARIO_H

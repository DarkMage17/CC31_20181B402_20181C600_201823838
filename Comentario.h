#ifndef COMENTARIO_H
#define COMENTARIO_H
#include "post.h"
class comentario : public Post
{
private:
    QString fecha;
    QString texto;
};

#endif // COMENTARIO_H

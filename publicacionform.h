#ifndef PUBLICACIONFORM_H
#define PUBLICACIONFORM_H

#include <QWidget>
#include "QDate"
#include "QVector"
#include "Comentario.h"

namespace Ui {
class PublicacionForm;
}

class PublicacionForm : public QWidget
{
    Q_OBJECT

public:
    explicit PublicacionForm(QWidget *parent = nullptr);
    ~PublicacionForm();
    QString texto;
    int likes;
    int compartidos;
    int idU;
    int idPub;
    QDate fechaPub;
    QVector<Comentario> comentarios;
private:
    Ui::PublicacionForm *ui;
};

#endif // PUBLICACIONFORM_H

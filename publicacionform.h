#ifndef PUBLICACIONFORM_H
#define PUBLICACIONFORM_H

#include <QWidget>
#include "QDate"
#include "QVector"
#include "Comentario.h"
#include "post.h"
#include "qtimer.h"


namespace Ui {
class PublicacionForm;
}

class PublicacionForm : public QWidget
{
    Q_OBJECT

public:
    explicit PublicacionForm(QWidget *parent = nullptr);
    Post p;
    QTimer *timer;
    ~PublicacionForm();
    QVector<Comentario> comentarios;
    void Load();
public slots:
    void timing();
private:
    Ui::PublicacionForm *ui;
};

#endif // PUBLICACIONFORM_H

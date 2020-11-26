#ifndef PUBLICACIONFORM_H
#define PUBLICACIONFORM_H

#include <QWidget>
#include "QDate"
#include "QVector"
#include "Comentario.h"
#include "post.h"
#include "qtimer.h"
#include "QListWidget"

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
    Ui::PublicacionForm *ui;
    QListWidget* getList();
public slots:
    void timing();
private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
};

#endif // PUBLICACIONFORM_H

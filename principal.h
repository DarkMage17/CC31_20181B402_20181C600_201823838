#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>
#include "QObject"
#include "usuario.h"
#include "ListaDoble.h"
namespace Ui {
class Principal;
}

class Principal : public QWidget
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = nullptr);
    ~Principal();
    Lista<Usuario*> usuarios2;
    Usuario *logueado = new Usuario();
private slots:
    void on_BtnPost_clicked();

    void on_btnLogOut_clicked();

    void on_btnProfile_clicked();

    void on_btnHomeProf_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Principal *ui;
};

#endif // PRINCIPAL_H

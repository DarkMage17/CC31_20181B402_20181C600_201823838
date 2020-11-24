#include "principal.h"
#include "ui_principal.h"
#include "QApplication"
#include "QFile"
#include "QTextStream"
#include "QMessageBox"
Principal::Principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Principal)

{
    ui->setupUi(this);
    QFile archivo2("C:/Users/JOSUE/Desktop/RedSocial/Data/Post.txt");
    QTextStream lectura(&archivo2);
    if(archivo2.open(QFile::ReadOnly | QFile::Text))
    {
        ui->txtLeerPublis->append("--------------------------------------\n");
        ui->txtLeerPublis->append(lectura.readAll());

    }
    ui->labelUser->setText(logueado->getUsuario());
}

Principal::~Principal()
{
    delete ui;
}

void Principal::on_BtnPost_clicked()
{
    QString post=ui->txtPost->toPlainText();
    QFile archivo("C:/Users/JOSUE/Desktop/RedSocial/Data/Post.txt");
    QTextStream entrada(&archivo);
    if(archivo.open(QFile::Append | QFile::Text))
    {
        entrada <<Qt::endl<< post << Qt::endl<<Qt::endl<<"----------------";
        archivo.flush();
        archivo.close();
    }
    if(archivo.open(QFile::ReadOnly | QFile::Text))
        ui->txtLeerPublis->setText(entrada.readAll());

}

void Principal::on_btnLogOut_clicked()
{
    //close();
    //parentWidget()->show();
}

void Principal::on_btnProfile_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Principal::on_btnHomeProf_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Principal::on_pushButton_9_clicked()
{
    //close();
    //parentWidget()->show();
}

void Principal::on_pushButton_3_clicked()
{
    //for(int i=0; i < usuarios2.Size();i++)
    //{
         //ui->listamigos1->addItem(usuarios2.SetPos(i).data->getUsuario());
    //}
    //ui->labelUser->setText(logueado->getUsuario());
}

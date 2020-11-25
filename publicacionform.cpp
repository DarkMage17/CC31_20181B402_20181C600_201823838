#include "publicacionform.h"
#include "ui_publicacionform.h"

PublicacionForm::PublicacionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PublicacionForm)
{
    ui->setupUi(this);
}

PublicacionForm::~PublicacionForm()
{
    delete ui;
}

#include "publicacionform.h"
#include "ui_publicacionform.h"

PublicacionForm::PublicacionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PublicacionForm)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timing()));
    timer->start(100);
    ui->label->setText(p.getTitulo());
}

PublicacionForm::~PublicacionForm()
{
    delete ui;
}

QListWidget* PublicacionForm::getList()
{
    return ui->listWidget;
}

void PublicacionForm::timing()
{
    ui->label->setText(p.getTitulo());
    ui->textBrowser->setText(p.getTexto());
    ui->label_2->setText("Likes: "+QString::number(p.getLikes()));
    ui->label_3->setText("Date: "+p.getFechaPub().toString("yyyy-MM-dd"));
    timer->stop();
}

void PublicacionForm::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->label_4->setText(item->text());
}

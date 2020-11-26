#include "login.h"
#include "ui_login.h"
#include "usuario.h"
#include "filesystem"
#include "QDir"
#include "QMessageBox"
#include "QTextStream"
#include "ListaSimple.h"

Node<Post>* post_selected = nullptr;
bool inversed = false;
Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    //Arboles Usuarios
    this->BST_usuarios= new BST<Usuario,QString>([](Usuario u){return u.getCorreo();});
    this->BST_nombre= new BST<Usuario,QString>([](Usuario u){return u.getNombre();});
    this->BST_fecha= new BST<Usuario,QDate>([](Usuario u){return u.getFecha();});
    this->BST_id= new BST<Usuario,int>([](Usuario u){return u.getId();});
    //Arboles Publicaciones
    this->BST_idPub=new BST<Post,int>([](Post p){return p.getIdPub();});
    this->BST_idUser=new BST<Post,int>([](Post p){return p.getIdUsers();});
    this->BST_likes=new BST<Post,int>([](Post p){return p.getLikes();});
    this->BST_fechaPub=new BST<Post,QDate>([](Post p){return p.getFechaPub();});
    this->BST_texto=new BST<Post,QString>([](Post p){return p.getTexto();});
    this->BST_titulo=new BST<Post,QString>([](Post p){return p.getTitulo();});
    //Comments
    this->BST_fechaC=new BST<Comentario,QDate>([](Comentario c){return c.getFechaC();});
    this->BST_idC=new BST<Comentario,int>([](Comentario c){return c.getIDC();});
    this->BST_textoC=new BST<Comentario,QString>([](Comentario c){return c.getT();});
    this->BST_idPubC=new BST<Comentario,int>([](Comentario c){return c.getIDP();});
    //followers
    this->BST_idF1= new BST<Usuario,int>([](Usuario u){return u.getId();});
    this->BST_idF2= new BST<Usuario,int>([](Usuario u){return u.getIdF();});
    CargarUsuarios();
    CargarComentarios();
}

Login::~Login()
{
    delete ui;
}


void Login::CargarUsuarios()
{
    QFile file(path + "users.tsv");
    if(file.open(QIODevice::ReadOnly)){ //WriteOnly
        QTextStream in(&file); // in << palabras[1] << "\n";
        in.setCodec("UTF-8");
        while(!in.atEnd()){
            QString linea = in.readLine();
            QStringList palabras = linea.split("\t");
            QDate date = QDate::fromString(palabras[3],"yyyy-MM-dd");
            Usuario *u = new Usuario(palabras[0].toInt(),palabras[1],palabras[2],date);
            usuarios.append(*u);
            AgregarUsuarioBST(*u);
        }
        file.close();
    }
}

void Login::CargarFollowers()
{
    QFile file(path + "followers.tsv");
    if(file.open(QIODevice::ReadOnly)){ //WriteOnly
        QTextStream in(&file); // in << palabras[1] << "\n";
        in.setCodec("UTF-8");
        while(!in.atEnd()){
            QString linea = in.readLine();
            QStringList palabras = linea.split("\t");
            Follower *f = new Follower(palabras[0].toInt(),palabras[1].toInt());
            followers.append(*f);
        }
        file.close();
    }
}

void Login::CargarPubs()
{
    QFile file(path + "publications.tsv");
    if(file.open(QIODevice::ReadOnly)){ //WriteOnly
        QTextStream in(&file); // in << palabras[1] << "\n";
        in.setCodec("UTF-8");
        while(!in.atEnd()){
            QString linea = in.readLine();
            QStringList palabras = linea.split("\t");
            QDate date=QDate::fromString(palabras[4],"yyyy-MM-dd");
            Post *p= new Post(palabras[0].toInt(),palabras[1].toInt(),palabras[2],palabras[3],date,palabras[5].toInt());
            publicaciones.append(*p);
            AgregarPubsBST(*p);
        }
        file.close();
    }
}

void Login::CargarComentarios()
{
    QFile file(path + "comment.tsv");
    if(file.open(QIODevice::ReadOnly)){ //WriteOnly
        QTextStream in(&file); // in << palabras[1] << "\n";
        in.setCodec("UTF-8");
        while(!in.atEnd()){
            QString linea = in.readLine();
            QStringList palabras = linea.split("\t");
            QDate date = QDate::fromString(palabras[2],"yyyy-MM-dd");
            Comentario *c = new Comentario(palabras[0].toInt(),palabras[1].toInt(),date,palabras[3]);
            comentarios.append(*c);
            AgregarComentsBST(*c);
        }
        file.close();
    }
}

void Login::AgregarUsuarioBST(Usuario u)
{
    this->BST_id->add(u);
    this->BST_nombre->add(u);
    this->BST_usuarios->add(u);
    this->BST_fecha->add(u);
}

void Login::AgregarComentsBST(Comentario c)
{
    this->BST_fechaC->add(c);
    this->BST_idPubC->add(c);
    this->BST_textoC->add(c);
    this->BST_idC->add(c);
}

void Login::AgregarPubsBST(Post p)
{
    this->BST_fechaPub->add(p);
    this->BST_titulo->add(p);
    this->BST_likes->add(p);
    this->BST_texto->add(p);
    this->BST_idPub->add(p);
    this->BST_idUser->add(p);
}

void Login::AgregarFollowersBST(Usuario u)
{
    this->BST_idF1->add(u);
    this->BST_idF2->add(u);
}

void Login::AgregarPub()
{
    int idu = logueado->data.getId();
    int idpubl = BST_idPub->max_node()->data.getIdPub();
    idpubl++;
    Post *p = new Post(idpubl,idu,ui->lineEdit_2->text(),ui->EditPublis->toPlainText(),QDate::currentDate(),0);
    if(QFileInfo(path+"publications.tsv").exists()==true && p->getTitulo()!="" && p->getTexto()!=""){
        QFile archivo(path+"publications.tsv");
        if(archivo.open(QFile::Append | QFile::Text)){
            QTextStream salida(&archivo);
            salida<< Qt::endl <<idpubl<<"\t"<<p->getIdUsers()<<"\t"<<p->getTitulo()<<"\t"<<p->getTexto()<<"\t"<<p->getLikes()<<"\t"<<p->getFechaPub().toString("yyyy-MM-dd");
            archivo.flush();
            archivo.close();
            publicaciones.append(*p);
            AgregarPubsBST(*p);
            ui->lineEdit_2->clear();
            ui->EditPublis->clear();
        }
    }
    else
        QMessageBox::information(this,"Advertencia","Llene los espacios en blanco");
}

void Login::ListarOrd()
{
    ui->LUsuariosGlob->clear();
    if(inversed) BST_id->postorder(ui->listWidget);
    else    BST_id->inorder(ui->listWidget);
    inversed = !inversed;
    for(int i=0;i<usuarios.Size();i++)
    {
        ui->LUsuariosGlob->addItem(usuarios.GetPos(i).data.getNombre());
    }
}

void Login::CargarPubsHomePage() // Carga los posts de todos los usuarios
{
    BST_fechaPub->postorder(ui->listWidget);
    BST_fechaPub->CountZero();
    BST_id->postorder(ui->LUsuariosGlob);
    BST_id->CountZero();
}

void Login::BuscarPost(QString titulo)
{
    post_selected = BST_titulo->findNode(titulo);
    if(post_selected != nullptr)
    {
        Post publicacionF = post_selected->data;
        formPub = new PublicacionForm();
        formPub->p = publicacionF;
        formPub->show();
        BST_idPubC->Filtrado(formPub->getList(),publicacionF.getIdPub());
    }
}

void Login::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString Titulo=item->text();
    BuscarPost(Titulo);
}


void Login::on_pushButton_4_clicked()
{
    switch(ui->comboBox->currentIndex())
    {
    case 0:
        ui->listWidget->clear();
        BST_likes->postorder(ui->listWidget);
        BST_likes->CountZero();
        break;
    case 1:
        ui->listWidget->clear();
        BST_fechaPub->postorder(ui->listWidget);
        BST_fechaPub->CountZero();
        break;
    }
}

void Login::on_B_ingresar_clicked()
{
    QString correo = ui->txt_correoLog->text();
    EncontrarUsuario(correo);
    CargarPubs();
    CargarPubsHomePage();
    ui->stackedWidget->setCurrentIndex(2);
    ui->labelUser->setText(logueado->data.getNombre());
    ui->txt_correoLog->setText("");
    ui->txt_nombreReg->setText("");
    ui->txt_correoReg->setText("");
    //CargarPostGlob();
}

void Login::EncontrarUsuario(QString s)
{
    logueado = BST_usuarios->findNode(s);
}

void Login::on_B_registrar_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->txt_correoLog->setText("");
    ui->txt_nombreReg->setText("");
    ui->txt_correoReg->setText("");
}

void Login::on_B_confirmar_clicked()
{
    int idu = BST_id->max_node()->data.getId();
    idu++;
    Usuario *u = new Usuario(idu,ui->txt_correoReg->text(),ui->txt_nombreReg->text(),QDate::currentDate());
    if(QFileInfo(path + "users.tsv").exists() == true && u->getCorreo()!=""){
        QFile archivo(path + "users.tsv");
        if(archivo.open(QFile::Append | QFile::Text)){
            QTextStream salida(&archivo);
            salida<< Qt::endl << u->getId()<<"\t"<<u->getCorreo()<<"\t"<<u->getNombre()<<"\t"<<u->getFecha().toString("yyyy-MM-dd");
            archivo.flush();
            archivo.close();
            usuarios.append(*u);
            AgregarUsuarioBST(*u);
        }
         QMessageBox::information(this,"Information","La cuenta se creó correctamente");
    }
    else
        QMessageBox::warning(this,"Error","Ya existe una cuenta con ese usuario");
    ui->stackedWidget->setCurrentIndex(1);
    ui->txt_correoLog->setText("");
    ui->txt_nombreReg->setText("");
    ui->txt_correoReg->setText("");
}


void Login::on_btnVolverL_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->txt_correoLog->setText("");
    ui->txt_nombreReg->setText("");
    ui->txt_correoReg->setText("");
}


void Login::on_btnLogOut_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->ListAmigosPerfil->clear();
}

void Login::on_BtnProfile_clicked() // Obtiene los amigos del usuario (funcion en usuario.cpp) y los añade a la lista de seguidos
{
    //CargarFollowers();
    ui->ListAmigosPerfil->clear();
    ui->stackedWidget->setCurrentIndex(3);
    BST_idPub->Filtrado2(ui->listWidget_2,logueado->data.getId());
}


void Login::on_btnHome_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->ListAmigosPerfil->clear();
    ui->LaberUserPerfil_2->setText("My Posts");
}

void Login::on_btnLogOut2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->LUsuariosGlob->clear();
    ui->ListAmigosPerfil->clear();
}

void Login::on_btnPost_clicked()
{
    AgregarPub();
}

void Login::on_B_encontrar_clicked()
{
    QString valor = ui->lineEdit->text();
    ui->listWidget->clear();
    int i = ui->comboBox_2->currentIndex();
    Lista<Post> pu;
    pu =  publicaciones.filtrar(valor,i);
    for(int i=0;i< pu.Size();i++)
        ui->listWidget->addItem(pu.GetPos(i).data.getTitulo());
}

void Login::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    QString Titulo=item->text();
    BuscarPost(Titulo);
}

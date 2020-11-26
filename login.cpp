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
    CargarUsuarios();
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
            //Post *p= new Post(palabras[0].toInt(),palabras[1].toInt(),palabras[2],palabras[3],date,palabras[5].toInt());
            AgregarPubsBST(Post(palabras[0].toInt(),palabras[1].toInt(),palabras[2],palabras[3],date,palabras[5].toInt()));
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

void Login::AgregarPubsBST(Post p)
{
    this->BST_fechaPub->add(p);
    this->BST_titulo->add(p);
    this->BST_likes->add(p);
    this->BST_texto->add(p);
    this->BST_idPub->add(p);
    this->BST_idUser->add(p);
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

    //CargarPubsHomePage();
    /*ui->LUsuariosGlob->clear();
    if(inversed) BST_id->postorder(ui->listWidget);
    else    BST_id->inorder(ui->listWidget);
    inversed = !inversed;
    */
}
void Login::on_B_Seguir_clicked()
{
    QString valor = ui->lineEdit->text();
    ui->LUsuariosGlob->clear();
    Lista<Usuario> u = usuarios.filtrar(valor);
    for(int i=0;i< 50;i++)
        ui->LUsuariosGlob->addItem(u.GetPos(i).data.getNombre());
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

/*
void Login::CargarListaUG(QString user) //cargar usuarios en el listbox del homepage
{
    ui->LUsuariosGlob->clear();
    for(int i= 0;i < usuarios.Size();i++)
    {
        if(usuarios.GetPos(i).data.getUsuario() == user)
            continue;
        else
            ui->LUsuariosGlob->addItem(usuarios.GetPos(i).data.getUsuario());
    }
}*/
/*
void Login::CargarUGlob() //cargar usuarios a la hora de iniciar el programa
{
    QFile Archivo(path+"Usuarios.txt");
    if (Archivo.open(QIODevice::ReadOnly))
    {
       QTextStream in(&Archivo);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          Usuario* user = new Usuario(line);
          usuarios.append(*user);
       }
       Archivo.close();
    }
}
*/

/*
void Login::CreacionCuenta(QString correo, QString contra, QString confirm) //creacion de usuario junto con su archivo de texto
{
    QString p1 = path+correo+".txt";
    QString p2 = path+"Usuarios.txt";
    if(QFileInfo(p1).exists() == false && correo != "")
    {
        if(contra == confirm)
        {
            QFile archivo(p1);
            QFile archivo2(p2);
            if(archivo.open(QFile::WriteOnly | QFile::Text))
            {
                QTextStream salida(&archivo);
                salida<<correo<<Qt::endl;
                salida<<contra<<Qt::endl;
                archivo.flush();
                archivo.close();
                Usuario* user = new Usuario(correo);
                usuarios.append(*user);
            }
            if(archivo2.open(QFile::Append | QFile::Text))
            {
                QTextStream salida(&archivo2);
                salida << correo << Qt::endl;
                archivo2.flush();
                archivo2.close();
            }
            QMessageBox::information(this,"Information","La cuenta se creó correctamente");
        }
        else
            QMessageBox::warning(this,"Error","Las casillas de contraseña y confirmacion no coinciden");
    }
    else
        QMessageBox::warning(this,"Error","Ya existe una cuenta con ese usuario");
}
*/
/*
void Login::IngresoCuenta(QString correo, QString password) // Acceso a cuenta existente
{
    QString p1 = path+correo+".txt";
    if(QFileInfo(p1).exists() == true)
    {
        QFile archivo(path+correo+".txt");
        if(archivo.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream entrada(&archivo);
            QString usuario1,pass1;
            entrada >> usuario1;
            entrada >> pass1;
            if(usuario1 == correo && pass1 == password)
            {
                QMessageBox::information(this,"Ingresó","Ingresó correctamente!");
                ui->stackedWidget->setCurrentIndex(2);
                logueado = new Usuario(correo);
                ui->labelUser->setText(logueado->getUsuario());
                ui->LaberUserPerfil->setText(logueado->getUsuario());
                CargarListaUG(logueado->getUsuario());
                logueado->CargarAmigos();
            }
            else
                QMessageBox::warning(this,"Error","Usuario y/o contraseña incorrectas");
            archivo.close();
        }
    }
    else
        QMessageBox::warning(this,"Error","El usuario no existe");
}
*/

/*
void Login::Postear() // Se añade un post a la lista de post globales (funcion en usuario.cpp) y a los del usuario
{
    QString post = ui->EditPublis->toPlainText();
    QFile archivo( path + "Post.txt");
    QTextStream entrada(&archivo);
    if(archivo.open(QFile::Append | QFile::Text))
    {
        entrada << logueado->getUsuario()+"---------------------" << Qt::endl << Qt::endl << post << Qt::endl << Qt::endl;
        archivo.flush();
        archivo.close();
    }
    CargarPostGlob();
    logueado->Publicar(post);
}
*/
/*void Login::Cargar()
{
    for(int i=0;i<usuarios.Size();i++)
    {
        ListaS<Post> lista = usuarios.GetPos(i).data.DevolverLista();
        for(int j=0;j < lista.n; j++)
        {
            publicaciones.append(lista[i]);
        }
    }
}*/
/*
void Login::CargarPostsPerfil(QString u) // Carga los post del usuario logueado
{
    ui->LeerPublisPerfil->clear();
    QFile archivo(path + u +"P.txt");
    QTextStream entrada(&archivo);
    if(archivo.open(QFile::ReadOnly | QFile::Text))
    {
        ui->LeerPublisPerfil->setText(entrada.readAll());
        archivo.close();
    }
}
*/
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

/*
void Login::on_btnLogOut_clicked()
{
    //ui->txtPost->setText("");
    ui->ListAmigosPerfil->clear();
}
*/
void Login::on_BtnProfile_clicked() // Obtiene los amigos del usuario (funcion en usuario.cpp) y los añade a la lista de seguidos
{
    ui->ListAmigosPerfil->clear();
    ui->stackedWidget->setCurrentIndex(3);
    //QVector<QString> v = logueado->DevolverAmigos();
    //for(int i=0;i<v.size();i++)
    //    ui->ListAmigosPerfil->addItem(v[i]);
    //publicacionesVector = BST_idUser->findMultiple(logueado->data.getId());
    //for(int i=0; i<publicacionesVector->size();i++)
    //    ui->listWidget_2->addItem(publicacionesVector[i].data());
}
/*

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
    //ui->txtPost->setText("");
    ui->ListAmigosPerfil->clear();
}

void Login::on_B_Seguir_clicked() // sigue a un usuario y lo añade al bloc de notas del usuario (funcion en usuario.cpp)
{
    QVector <QString> v = logueado->DevolverAmigos();
    if(v.contains(usuarioG) == false)
    {
        logueado->SeguirAmigo(usuarioG);
        QMessageBox::information(this,"Information","Usuario Seguido");
    }
    else
        QMessageBox::warning(this,"Error","Ya sigues a ese usuario");
}

void Login::on_LUsuariosGlob_itemClicked(QListWidgetItem *item)
{
    usuarioG = item->text();
}

void Login::on_ListAmigosPerfil_itemClicked(QListWidgetItem *item)
{
    amigoPerfil = item->text();
}

void Login::on_pushButton_clicked()
{
    ui->LaberUserPerfil_2->setText(amigoPerfil + " Posts");
    CargarPostsPerfil(amigoPerfil);
}

void Login::on_pushButton_2_clicked()
{
    CargarPostsPerfil(logueado->getUsuario());
    ui->LaberUserPerfil_2->setText("My Posts");
}
*/

void Login::on_btnPost_clicked()
{
    AgregarPub();
}

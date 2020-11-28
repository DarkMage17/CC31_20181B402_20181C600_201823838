#include "usuario.h"

Usuario::Usuario(int id, QString correo, QString nombre, QDate fecha)
{
    this->id = id;
    this->correo = correo;
    this->nombre = nombre;
    this->fechaRegistro = fecha;
}

Usuario::Usuario(int id, int idf)
{
    this->id = id;
    this->idf = idf;
}

Usuario::Usuario()
{
}

QString Usuario::getCorreo(){
    return this->correo;
}
QString Usuario::getNombre(){
    return this->nombre;
}
QDate Usuario::getFecha(){
    return this->fechaRegistro;
}
int Usuario::getId()
{
    return this->id;
}

int Usuario::getIdF()
{
    return idf;
}
int Usuario::CantidadPosts()
{
    return Publicaciones.n;
}

ListaS<Post> Usuario::DevolverLista()
{
    return Publicaciones;
}

void Usuario::AnadirSiguiendo(int ids)
{
    siguiendo.append(ids);
}

void Usuario::addListaSiguiendo(QListWidget *l)
{
    for(int i= 0; siguiendo.size();i++)
        l->addItem(QString::number(siguiendo.at(i)));
}

void Usuario::SeguirAmigo(QString amigo) // Añade al amigo a la archivo del usuario
{
    QFile archivo(path+correo+".txt");
    QTextStream salida(&archivo);
    if(archivo.open(QFile::Append | QFile::Text))
    {
        salida << amigo << ",";
        archivo.flush();
        archivo.close();
    }
    Amigos.append(amigo);
}

void Usuario::Publicar(QString text) // Agrega al bloc de notas del usuario y a su lista de posts
{
    QFile archivo2(path + correo + "P.txt");
    QTextStream entrada2(&archivo2);
    if(archivo2.open(QFile::Append | QFile::Text)){
        entrada2<< "---------------------------"<< Qt::endl << text << Qt::endl;
        archivo2.flush();
        archivo2.close();
    }
    //Post *p = new Post(text);
    //Publicaciones.agregarInicio(*p);
}

QVector<QString> Usuario::DevolverAmigos()
{
    return Amigos;
}

void Usuario::CargarAmigos() // carga la lista de amigos del usuario leyendo del txt
{
    QFile archivo(path+correo+".txt");
    QTextStream entrada(&archivo);
    QString amigo;
    QString a;
    QStringList amigotes;
    if(archivo.open(QFile::ReadOnly | QFile::Text))
    {
        entrada>>a;
        entrada>>a;
        entrada>>amigo;
        amigotes = amigo.split(",");
        Amigos = amigotes.toVector();
        archivo.close();
    }
    //agrega un espacio vacío por lo que se remueve para no agregar un espacio demás
    for(int i=0;i<Amigos.size();i++)
        if(Amigos[i] == "")
            Amigos.remove(i);
}



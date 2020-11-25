#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "QObject"
#include "usuario.h"
#include "ListaDoble.h"
#include "principal.h"
#include "QListWidget"
#include "QFileInfo"
#include "Arbol.h"
#include "QDir"
#include "publicacionform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    PublicacionForm* ventana;
    Login(QWidget *parent = nullptr);
    ~Login();
    Lista<Usuario> usuarios;   
    Lista<Post> publicaciones;
    Node<Usuario>* logueado;
    //arboles usuarios
    BST<Usuario, QString>* BST_usuarios;
    BST<Usuario, int>* BST_id;
    BST<Usuario, QDate>* BST_fecha;
    BST<Usuario, QString>* BST_nombre;
    BST<Post, QString>* BST_texto;
    //arboles pubs
    BST<Post, QDate>* BST_fechaPub;
    BST<Post, int>* BST_likes;
    BST<Post, int>* BST_idPub;
    BST<Post, int>* BST_idUser;
    BST<Post, QString>* BST_titulo;
    //proximamente mas
    QString usuarioG, amigoPerfil;
    QString path = "D:/Projects/RedSocial/Data/";
    QVector<Comentario> comentarios;

private slots:
    void AgregarUsuarioBST(Usuario u);
    void AgregarPubsBST(Post p);
    void aea();
    void CargarUsuarios();
    void CargarPubs();
    void CargarComentarios();
    void on_pushButton_4_clicked();
    void ListarOrd();
    void AgregarPub();
    void CargarPubsHomePage();
    void on_B_registrar_clicked();


    void on_B_ingresar_clicked();

    void on_B_Seguir_clicked();

    void EncontrarUsuario(QString s);


private:
    Ui::Login *ui;
    Principal *uiPrincipal;
};
#endif // LOGIN_H

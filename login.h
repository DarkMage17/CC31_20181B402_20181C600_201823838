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
#include "Comentario.h"
#include "follower.h"

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
    //arboles coms
    BST<Comentario, QDate>* BST_fechaC;
    BST<Comentario, int>* BST_idC;
    BST<Comentario, int>* BST_idPubC;
    BST<Comentario, QString>* BST_textoC;
    //followers
    BST<Follower, int>* BST_idF1;
    BST<Follower, int>* BST_idF2;
    //
    QString usuarioG, amigoPerfil;
    QString path = "D:/Projects/CC31_20181B402_20181C600_201823838/Data/";
    QVector<Comentario> comentarios;
    QVector<Follower> followers;
    //QVector<Node<Post>*>* publicacionesVector;
private:
    void BuscarPost(QString titulo);
private slots:
    void AgregarUsuarioBST(Usuario u);
    void AgregarPubsBST(Post p);
    void AgregarComentsBST(Comentario c);
    void AgregarFollowersBST(Follower f);
    void CargarUsuarios();
    void CargarPubs();
    void CargarComentarios();
    void CargarFollowers();
    void on_pushButton_4_clicked();
    void ListarOrd();
    void AgregarPub();
    void CargarPubsHomePage();
    void on_B_registrar_clicked();
    void on_BtnProfile_clicked();
    void on_B_ingresar_clicked();
    void on_B_confirmar_clicked();
    void on_btnVolverL_clicked();
    void EncontrarUsuario(QString s);
    void AgregarFollower(int u, int f);


    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_btnPost_clicked();

    void on_B_encontrar_clicked();

    void on_btnHome_clicked();

    void on_btnLogOut2_clicked();
    void on_btnLogOut_clicked();
    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Login *ui;
    Principal *uiPrincipal;
    enum Columna
    {
        ID, TITULO, FECHA, LIKES
    };
    PublicacionForm *formPub;
};
#endif // LOGIN_H

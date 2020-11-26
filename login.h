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
    QString path = "D:/Projects/CC31_20181B402_20181C600_201823838/Data/";
    QVector<Comentario> comentarios;
    //QVector<Node<Post>*>* publicacionesVector;
private:
    void BuscarPost(QString titulo);
private slots:
    void AgregarUsuarioBST(Usuario u);
    void AgregarPubsBST(Post p);
    void CargarUsuarios();
    void CargarPubs();
    void CargarComentarios();
    void on_pushButton_4_clicked();
    void ListarOrd();
    void AgregarPub();
    void CargarPubsHomePage();
    void on_B_registrar_clicked();
    void on_BtnProfile_clicked();
    void on_B_ingresar_clicked();
    void on_B_confirmar_clicked();
    void on_B_Seguir_clicked();
    void on_btnVolverL_clicked();
    void EncontrarUsuario(QString s);


    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_btnPost_clicked();

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

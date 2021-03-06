QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    follower.cpp \
    main.cpp \
    login.cpp \
    post.cpp \
    publicacionform.cpp \
    usuario.cpp

HEADERS += \
    Arbol.h \
    ListaDoble.h \
    ListaSimple.h \
    comentario.h \
    follower.h \
    interaccion.h \
    login.h \
    post.h \
    publicacionform.h \
    usuario.h

FORMS += \
    login.ui \
    publicacionform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Imagen.qrc

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        album.cpp \
        codigo/lista.cpp \
        codigo/main.cpp \
        codigo/mensaje.cpp \
        codigo/fecha.cpp \
        foto.cpp \
        nodo.cpp

HEADERS += \
    album.h \
    codigo/lista.h \
    codigo/mensaje.h \
    codigo/fecha.h \
    foto.h \
    nodo.h
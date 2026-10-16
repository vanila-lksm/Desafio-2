TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    album.cpp \
    main.cpp \
    mensaje.cpp \
    fecha.cpp \
    foto.cpp \
    relaciones.cpp

HEADERS += \
    album.h \
    lista.h \
    mensaje.h \
    nodo.h \
    fecha.h \
    foto.h \
    relaciones.h
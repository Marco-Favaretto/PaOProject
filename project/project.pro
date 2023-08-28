QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH = C:\Users\favar\Desktop\uni\p2\PaOProject\project\headers

SOURCES += \
    sources\creationdialog.cpp \
    sources\inventario.cpp \
    sources\item.cpp \
    sources\consumable.cpp \
    sources\model.cpp \
    sources\overTime.cpp \
    sources\potion.cpp \
    sources\regular.cpp \
    sources\shield.cpp \
    sources\showaction.cpp \
    sources\showbutton.cpp \
    sources\weapon.cpp \
    main.cpp \
    sources\player.cpp \
    sources\window.cpp

HEADERS += \
    headers\creationdialog.h \
    headers\inventario.h \
    headers\item.h \
    headers\consumable.h \
    headers\model.h \
    headers\overTime.h \
    headers\potion.h \
    headers\regular.h \
    headers\shield.h \
    headers\showaction.h \
    headers\showbutton.h \
    headers\weapon.h \
    headers\player.h \
    headers\window.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

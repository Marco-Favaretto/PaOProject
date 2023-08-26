QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gameoverdialog.cpp \
    inventario.cpp \
    item.cpp \
    consumable.cpp \
    model.cpp \
    overTime.cpp \
    potion.cpp \
    regular.cpp \
    shield.cpp \
    showaction.cpp \
    showbutton.cpp \
    weapon.cpp \
    main.cpp \
    player.cpp \
    window.cpp

HEADERS += \
    gameoverdialog.h \
    inventario.h \
    item.h \
    consumable.h \
    model.h \
    overTime.h \
    potion.h \
    regular.h \
    shield.h \
    showaction.h \
    showbutton.h \
    weapon.h \
    player.h \
    window.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
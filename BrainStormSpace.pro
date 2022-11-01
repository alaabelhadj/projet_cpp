QT       += sql core gui  charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    card.cpp \
    connexion.cpp \
    main.cpp \
    mainwindow.cpp \
    office.cpp \
    officestatistic.cpp \
    popup.cpp \
    popupmodel.cpp \
    user.cpp

HEADERS += \
    card.h \
    connexion.h \
    mainwindow.h \
    office.h \
    officestatistic.h \
    popup.h \
    popupmodel.h \
    user.h

FORMS += \
    card.ui \
    mainwindow.ui \
    popupmodel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    icons.qrc \
    res.qrc \
    res.qrc \
    res.qrc

SUBDIRS += \
    cardTest.pro \
    cardTest.pro

DISTFILES += \
    BrainStormSpace.pro.user \
    brainstorm.png \
    cardTest.pro.user \
    chat-solid.svg \
    like-solid.svg

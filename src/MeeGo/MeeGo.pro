include (../../qt-components.pri)

TEMPLATE = lib
TARGET = meegoplugin
CONFIG += qt plugin
QT += declarative dbus

#contextsubscriber {
#    DEFINES += HAVE_CONTEXTSUBSCRIBER
#    INCLUDEPATH += /home/cmarcelo/Installs/meegosupport/include/contextsubscriber
#    LIBS += -lcontextsubscriber
#}

SOURCES += \
    plugin.cpp \
    mdeclarativestatusbar.cpp \
    mdeclarativescreen.cpp \
    msnapshot.cpp

HEADERS += \
    mdeclarativestatusbar.h \
    mdeclarativescreen.h \
    msnapshot.h

INCLUDEPATH += $$PWD

QML_FILES = \
        qmldir \
        Button.qml \
        ButtonGroup.qml \
        Page.qml \
        Slider.qml \
        TitleBar.qml \
        TitleButton.qml \
        Window.qml

TARGETPATH = com/meego

target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

qmlfiles.files = $$QML_FILES
qmlfiles.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

INSTALLS += target qmlfiles
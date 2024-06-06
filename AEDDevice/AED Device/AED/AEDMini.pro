QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/dashboardform.cpp \
    src/ecginterfacerunner.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/padsattachform.cpp \
    src/splashform.cpp \
    src/systemcheckform.cpp \
    src/environmentform.cpp

HEADERS += \
    src/dashboardform.h \
    src/ecginterfacerunner.h \
    src/mainwindow.h \
    src/padsattachform.h \
    src/splashform.h \
    src/systemcheckform.h \
    src/environmentform.h

FORMS += \
    src/dashboardform.ui \
    src/mainwindow.ui \
    src/padsattachform.ui \
    src/splashform.ui \
    src/systemcheckform.ui \
    src/environmentform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    application.qrc

DISTFILES += \
    src/assets/imgs/spinner.gif

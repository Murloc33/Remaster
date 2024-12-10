QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Manager/dbmanager.cpp \
    Manager/resultmanager.cpp \
    Manager/stagemanager.cpp \
    Model/cbmodel.cpp \
    View/Dialog/diadescription.cpp \
    View/customcheckbox.cpp \
    View/customcombobox.cpp \
    View/stage.cpp \
    main.cpp \
    View/mainwindow.cpp \
    View/Delegate/pbiconswitcher.cpp

HEADERS += \
    Manager/dbmanager.h \
    Manager/resultmanager.h \
    Manager/stagemanager.h \
    Model/cbmodel.h \
    View/Dialog/diadescription.h \
    View/customcheckbox.h \
    View/customcombobox.h \
    View/mainwindow.h \
    View/Delegate/pbiconswitcher.h \
    View/stage.h

FORMS += \
    View/Dialog/diadescription.ui \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
	resources.qrc

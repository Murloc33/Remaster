QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/cbmodel.cpp \
    Manager/dbmanager.cpp \
    View/Dialog/diadescription.cpp \
    View/customcombobox.cpp \
    main.cpp \
    View/mainwindow.cpp \
    View/Delegate/pbiconswitcher.cpp

HEADERS += \
    Model/cbmodel.h \
    Manager/dbmanager.h \
    View/Dialog/diadescription.h \
    View/customcombobox.h \
    View/mainwindow.h \
    View/Delegate/pbiconswitcher.h

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

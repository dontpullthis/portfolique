QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/application.cpp \
    src/db/db.cpp \
    src/project/securities/abstractitem.cpp \
    src/project/securities/category.cpp \
    src/project/securities/security.cpp \
    src/main.cpp \
    src/project/project.cpp \
    src/ui/mainwindow/mainwindow.cpp \
    src/ui/securities_management/securitiesmanagementdialog.cpp \
    src/ui/securities_management/securitytreewidgetitem.cpp

HEADERS += \
    src/application.h \
    src/db/db.h \
    src/project/securities/abstractitem.h \
    src/project/securities/category.h \
    src/project/securities/security.h \
    src/project/project.h \
    src/ui/mainwindow/mainwindow.h \
    src/ui/securities_management/securitiesmanagementdialog.h \
    src/ui/securities_management/securitytreewidgetitem.h

FORMS += \
    src/ui/mainwindow/mainwindow.ui \
    src/ui/securities_management/securitiesmanagementdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore

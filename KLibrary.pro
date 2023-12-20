QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AdminForm.cpp \
    AuthForm.cpp \
    AuthReg.cpp \
    BaseEnterForm.cpp \
    BaseUserForm.cpp \
    ClientForm.cpp \
    InputChecker.cpp \
    PasswordEdit.cpp \
    RegisterForm.cpp \
    entities/Authors.cpp \
    entities/Books.cpp \
    entities/Editions.cpp \
    entities/Genres.cpp \
    entities/Orders.cpp \
    entities/Readers.cpp \
    entities/Entity.cpp \
    entities/Relation.cpp \
    entities/Reviews.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AdminForm.h \
    AuthForm.h \
    AuthReg.h \
    BaseEnterForm.h \
    BaseUserForm.h \
    ClientForm.h \
    Consts.h \
    InputChecker.h \
    PasswordEdit.h \
    RegisterForm.h \
    entities/Authors.h \
    entities/Books.h \
    entities/Editions.h \
    entities/Genres.h \
    entities/Orders.h \
    entities/Readers.h \
    entities/Entity.h \
    entities/Relation.h \
    entities/Reviews.h \
    mainwindow.h

FORMS += \
    AuthReg.ui \
    BaseEnterForm.ui \
    BaseUserForm.ui \
    mainwindow.ui

TRANSLATIONS += \
    KLibrary_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

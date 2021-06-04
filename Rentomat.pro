QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbookdialog.cpp \
    addgamedialog.cpp \
    addmoviedialog.cpp \
    addstockdialog.cpp \
    application.cpp \
    article.cpp \
    articledatabase.cpp \
    book.cpp \
    changepassworddialog.cpp \
    changeusernamedialog.cpp \
    confirmationdeletedialog.cpp \
    confirmborrow.cpp \
    confirmreturn.cpp \
    confirmwatch.cpp \
    deleteitemdialog.cpp \
    deletestockdialog.cpp \
    deleteuserdialog.cpp \
    game.cpp \
    main.cpp \
    movie.cpp \
    stock.cpp \
    stocklocationdialog.cpp \
    user.cpp \
    userdatabase.cpp \
    watched.cpp

HEADERS += \
    addbookdialog.h \
    addgamedialog.h \
    addmoviedialog.h \
    addstockdialog.h \
    application.h \
    article.h \
    articledatabase.h \
    book.h \
    changepassworddialog.h \
    changeusernamedialog.h \
    confirmationdeletedialog.h \
    confirmborrow.h \
    confirmreturn.h \
    confirmwatch.h \
    deleteitemdialog.h \
    deletestockdialog.h \
    deleteuserdialog.h \
    game.h \
    movie.h \
    stock.h \
    stocklocationdialog.h \
    user.h \
    userdatabase.h \
    watched.h

FORMS += \
    addbookdialog.ui \
    addgamedialog.ui \
    addmoviedialog.ui \
    addstockdialog.ui \
    application.ui \
    changepassworddialog.ui \
    changeusernamedialog.ui \
    confirmationdeletedialog.ui \
    confirmborrow.ui \
    confirmreturn.ui \
    confirmwatch.ui \
    deleteitemdialog.ui \
    deletestockdialog.ui \
    deleteuserdialog.ui \
    stocklocationdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

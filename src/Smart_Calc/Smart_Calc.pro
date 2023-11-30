QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    graph.cpp \
    mainwindow.cpp \
    ../s21_calcc.c \
    ../s21_stack.c \
    ../s21_calcX.c \
    qcustomplot.cpp


HEADERS += mainwindow.h \
    graph.h \
    qcustomplot.h \
    stack.h \

FORMS += \
    graph.ui \
    mainwindow.ui

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

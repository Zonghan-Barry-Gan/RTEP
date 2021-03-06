# Qt project file - qmake uses his to generate a Makefile

QT       += core gui network

CONFIG          += qt warn_on debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += /home/barry/c/iir1

LIBS += /home/barry/c/iir1/libiir_static.a


TARGET = QwtExample

greaterThan(QT_MAJOR_VERSION, 4): LIBS += -lqwt-qt5 -lm
lessThan(QT_MAJOR_VERSION, 5): LIBS += -lqwt -lm

HEADERS += window.h adcreader.h

SOURCES += main.cpp window.cpp adcreader.cpp

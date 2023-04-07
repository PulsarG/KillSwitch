QT       += core gui
LIBS += -lcurl
QT += network
QT += core gui network

LIBS += -L"D:\Download\curl-8.0.1_5-win64-mingw\curl-8.0.1_5-win64-mingw\lib" -lcurl
INCLUDEPATH += "D:\Download\curl-8.0.1_5-win64-mingw\curl-8.0.1_5-win64-mingw\include"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

#LIBS+=D:\Download\curl-8.0.1_5-win64-mingw\curl-8.0.1_5-win64-mingw\lib -lcurl
#LIBS+=D:\Download\curl-8.0.1_5-win64-mingw\curl-8.0.1_5-win64-mingw\lib\libcurl.dll.a

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

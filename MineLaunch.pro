QT       += core gui

QT += network

QT += xml

QT +=sql

QT += webenginewidgets

LIBS+= -lssl -lcrypto

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# LIBS += -lqtpop3 -lqtsmtp
INCLUDEPATH += /usr/include/boost
LIBS += -lboost_system -lboost_filesystem -lboost_regex

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += resources/mods/config/config.json

SOURCES += frontend/signin.cpp
SOURCES += frontend/signup.cpp
SOURCES += frontend/dashboard.cpp
SOURCES += frontend/welcome.cpp

HEADERS += frontend/include/signin.hpp
HEADERS += frontend/include/code_submit.hpp
HEADERS += frontend/include/signup.hpp
HEADERS += frontend/include/dashboard.hpp
HEADERS += frontend/include/welcome.hpp
HEADERS += utils/logger.hpp
HEADERS += utils/defines.hpp
HEADERS += utils/validator.hpp
HEADERS += utils/sha256.hpp

SOURCES += backend/server.cpp
SOURCES  += backend/database/sqlite.cpp

HEADERS += backend/include/server.hpp
HEADERS += backend/database/include/sqlite.hpp


SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

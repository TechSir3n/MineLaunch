QT  += core gui

QT += network

QT += xml

QT +=sql

QT += webenginewidgets

LIBS+= -lssl -lcrypto

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
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
SOURCES += frontend/client.cpp
SOURCES += frontend/user_settings.cpp

HEADERS += frontend/include/signin.hpp
HEADERS += frontend/include/user_settings.hpp
HEADERS += frontend/include/code_submit.hpp
HEADERS += frontend/include/signup.hpp
HEADERS += frontend/include/dashboard.hpp
HEADERS += frontend/include/welcome.hpp
HEADERS += frontend/include/client.hpp
HEADERS += frontend/include/handler_signals.hpp

HEADERS += assistance/systeminfo.hpp
HEADERS += assistance/path.hpp
HEADERS += assistance/clearLogs.hpp
HEADERS += utils/logger.hpp
HEADERS += utils/defines.hpp
HEADERS += utils/validator.hpp
HEADERS += utils/hashing.hpp

SOURCES += assistance/path.cpp
SOURCES += backend/server.cpp
SOURCES += backend/dataHandler.cpp
SOURCES += backend/updater_data.cpp
SOURCES += backend/database/sqlite.cpp
SOURCES += backend/launcher/downloader.cpp
SOURCES += backend/launcher/game.cpp
SOURCES += backend/launcher/downloadVersion.cpp
SOURCES += backend/launcher/downloadLibraries.cpp
SOURCES += backend/launcher/downloadClient.cpp
SOURCES += backend/launcher/downloadAssetIndex.cpp
SOURCES += backend/launcher/downloadResources.cpp
SOURCES += backend/launcher/jsonParse.cpp

HEADERS += backend/launcher/include/jsonParse.hpp
HEADERS += backend/launcher/include/downloadLibraries.hpp
HEADERS += backend/launcher/include/downloadClient.hpp
HEADERS += backend/launcher/include/game.hpp
HEADERS += backend/launcher/include/downloadVersion.hpp
HEADERS += backend/launcher/include/factory.hpp
HEADERS += backend/launcher/include/downloader.hpp
HEADERS += backend/launcher/include/launcher.hpp
HEADERS += backend/launcher/include/downloadAssetIndex.hpp
HEADERS += backend/launcher/include/downloadResources.hpp
HEADERS += backend/include/updater_data.hpp
HEADERS += backend/include/dataHandler.hpp
HEADERS += backend/include/server.hpp
HEADERS += backend/include/smtp.hpp
HEADERS += backend/database/include/sqlite.hpp

SOURCES += vendor/SmtpClient/src/smtpmime_global.h
HEADERS += vendor/SmtpClient/src/smtpclient.h
SOURCES += vendor/SmtpClient/src/smtpclient.cpp
HEADERS += vendor/SmtpClient/src/quotedprintable.h
SOURCES += vendor/SmtpClient/src/quotedprintable.cpp
HEADERS += vendor/SmtpClient/src/mimetext.h
SOURCES += vendor/SmtpClient/src/mimetext.cpp
HEADERS+= vendor/SmtpClient/src/mimeqpformatter.h
SOURCES += vendor/SmtpClient/src/mimeqpformatter.cpp
HEADERS += vendor/SmtpClient/src/mimeqpencoder.h
SOURCES += vendor/SmtpClient/src/mimeqpencoder.cpp
HEADERS += vendor/SmtpClient/src/mimepart.h
SOURCES += vendor/SmtpClient/src/mimepart.cpp
HEADERS += vendor/SmtpClient/src/mimemultipart.h
SOURCES += vendor/SmtpClient/src/mimemultipart.cpp
HEADERS += vendor/SmtpClient/src/mimemessage.h
SOURCES += vendor/SmtpClient/src/mimemessage.cpp
HEADERS += vendor/SmtpClient/src/mimeinlinefile.h
SOURCES += vendor/SmtpClient/src/mimeinlinefile.cpp
HEADERS += vendor/SmtpClient/src/mimehtml.h
SOURCES += vendor/SmtpClient/src/mimehtml.cpp
HEADERS += vendor/SmtpClient/src/mimefile.h
SOURCES += vendor/SmtpClient/src/mimefile.cpp
HEADERS += vendor/SmtpClient/src/mimecontentformatter.h
SOURCES += vendor/SmtpClient/src/mimecontentformatter.cpp
HEADERS += vendor/SmtpClient/src/mimecontentencoder.h
SOURCES += vendor/SmtpClient/src/mimecontentencoder.cpp
HEADERS += vendor/SmtpClient/src/mimebytearrayattachment.h
SOURCES += vendor/SmtpClient/src/mimebytearrayattachment.cpp
HEADERS += vendor/SmtpClient/src/mimebase64formatter.h
SOURCES += vendor/SmtpClient/src/mimebase64formatter.cpp
HEADERS += vendor/SmtpClient/src/mimebase64encoder.h
SOURCES += vendor/SmtpClient/src/mimebase64encoder.cpp
HEADERS += vendor/SmtpClient/src/mimeattachment.h
SOURCES += vendor/SmtpClient/src/mimeattachment.cpp
HEADERS += vendor/SmtpClient/src/emailaddress.h
SOURCES += vendor/SmtpClient/src/emailaddress.cpp


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

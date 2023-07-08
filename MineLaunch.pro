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


TRANSLATIONS += \
        translations/launcher_ru.ts \
        translations/launcher_en.ts

tr.commands = lupdate \"$$_PRO_FILE_\" && lrelease \"$$_PRO_FILE_\"
    PRE_TARGETDEPS += tr
    QMAKE_EXTRA_TARGETS += tr

# You can make your code fail to compile if it uses deprecated APIs.

# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += res.qrc

SOURCES += \
    frontend/signin.cpp \
    frontend/signup.cpp \
    frontend/dashboard.cpp \
    frontend/welcome.cpp \
    frontend/client.cpp \
    frontend/user_settings.cpp \
    assistance/path.cpp \
    assistance/custom.cpp \
    backend/server.cpp \
    backend/dataHandler.cpp \
    backend/updater_data.cpp \
    backend/database/sqlite.cpp \
    backend/launcher/downloader.cpp \
    backend/launcher/game.cpp \
    backend/launcher/downloadVersion.cpp \
    backend/launcher/downloadLibraries.cpp \
    backend/launcher/downloadClient.cpp \
    backend/launcher/downloadAssetIndex.cpp \
    backend/launcher/downloadResources.cpp \
    backend/launcher/downloadMod.cpp \
    backend/launcher/jsonParse.cpp \
    vendor/SmtpClient/src/smtpclient.cpp \
    vendor/SmtpClient/src/quotedprintable.cpp \
    vendor/SmtpClient/src/mimetext.cpp \
    vendor/SmtpClient/src/mimeqpformatter.cpp \
    vendor/SmtpClient/src/mimeqpencoder.cpp \
    vendor/SmtpClient/src/mimepart.cpp \
    vendor/SmtpClient/src/mimemultipart.cpp \
    vendor/SmtpClient/src/mimemessage.cpp \
    vendor/SmtpClient/src/mimeinlinefile.cpp \
    vendor/SmtpClient/src/mimehtml.cpp \
    vendor/SmtpClient/src/mimefile.cpp \
    vendor/SmtpClient/src/mimecontentformatter.cpp \
    vendor/SmtpClient/src/mimecontentencoder.cpp \
    vendor/SmtpClient/src/mimebytearrayattachment.cpp \
    vendor/SmtpClient/src/mimebase64formatter.cpp \
    vendor/SmtpClient/src/mimebase64encoder.cpp \
    vendor/SmtpClient/src/mimeattachment.cpp \
    vendor/SmtpClient/src/emailaddress.cpp \
    check/checkAssets.cpp \
    check/checkAssetIndex.cpp \
    check/checkLibraries.cpp \
    check/checkClient.cpp

HEADERS += \
    frontend/include/signin.hpp \
    frontend/include/user_settings.hpp \
    frontend/include/code_submit.hpp \
    frontend/include/signup.hpp \
    frontend/include/dashboard.hpp \
    frontend/include/welcome.hpp \
    frontend/include/client.hpp \
    frontend/include/handler_signals.hpp \
    assistance/systeminfo.hpp \
    assistance/path.hpp \
    assistance/custom.hpp \
    assistance/clearLogs.hpp \
    assistance/logger.hpp \
    assistance/defines.hpp \
    assistance/validator.hpp \
    assistance/hashing.hpp \
    backend/launcher/include/jsonParse.hpp \
    backend/launcher/include/downloadLibraries.hpp \
    backend/launcher/include/downloadClient.hpp \
    backend/launcher/include/game.hpp \
    backend/launcher/include/downloadVersion.hpp \
    backend/launcher/include/factory.hpp \
    backend/launcher/include/downloader.hpp \
    backend/launcher/include/launcher.hpp \
    backend/launcher/include/downloadAssetIndex.hpp \
    backend/launcher/include/downloadResources.hpp \
    backend/launcher/include/downloadMod.hpp \
    backend/include/updater_data.hpp \
    backend/include/dataHandler.hpp \
    backend/include/server.hpp \
    backend/include/smtp.hpp \
    backend/database/include/sqlite.hpp \
    vendor/SmtpClient/src/smtpmime_global.h \
    vendor/SmtpClient/src/smtpclient.h \
    vendor/SmtpClient/src/quotedprintable.h \
    vendor/SmtpClient/src/mimetext.h \
    vendor/SmtpClient/src/mimeqpformatter.h \
    vendor/SmtpClient/src/mimeqpencoder.h \
    vendor/SmtpClient/src/mimepart.h \
    vendor/SmtpClient/src/mimemultipart.h \
    vendor/SmtpClient/src/mimemessage.h \
    vendor/SmtpClient/src/mimeinlinefile.h \
    vendor/SmtpClient/src/mimehtml.h \
    vendor/SmtpClient/src/mimefile.h \
    vendor/SmtpClient/src/mimecontentformatter.h \
    vendor/SmtpClient/src/mimecontentencoder.h \
    vendor/SmtpClient/src/mimebytearrayattachment.h \
    vendor/SmtpClient/src/mimebase64formatter.h \
    vendor/SmtpClient/src/mimebase64encoder.h \
    vendor/SmtpClient/src/mimeattachment.h \
    vendor/SmtpClient/src/emailaddress.h \
    check/include/checkAssets.hpp \
    check/include/checkAssets.hpp \
    check/include/checkAssetIndex.hpp \
    check/include/checkLibraries.hpp \
    check/include/checkClient.hpp


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

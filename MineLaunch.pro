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
    backend/launcher/concurrency.cpp \
    backend/launcher/downloadAssetIndex.cpp \
    backend/launcher/downloadResources.cpp \
    backend/launcher/downloadMod.cpp \
    SmtpClient/src/smtpclient.cpp \
    SmtpClient/src/quotedprintable.cpp \
    SmtpClient/src/mimetext.cpp \
    SmtpClient/src/mimeqpformatter.cpp \
    SmtpClient/src/mimeqpencoder.cpp \
    SmtpClient/src/mimepart.cpp \
    SmtpClient/src/mimemultipart.cpp \
    SmtpClient/src/mimemessage.cpp \
    SmtpClient/src/mimeinlinefile.cpp \
    SmtpClient/src/mimehtml.cpp \
    SmtpClient/src/mimefile.cpp \
    SmtpClient/src/mimecontentformatter.cpp \
    SmtpClient/src/mimecontentencoder.cpp \
    SmtpClient/src/mimebytearrayattachment.cpp \
    SmtpClient/src/mimebase64formatter.cpp \
    SmtpClient/src/mimebase64encoder.cpp \
    SmtpClient/src/mimeattachment.cpp \
    SmtpClient/src/emailaddress.cpp \
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
    backend/launcher/include/downloadLibraries.hpp \
    backend/launcher/include/downloadClient.hpp \
    backend/launcher/include/game.hpp \
    backend/launcher/include/downloadVersion.hpp \
    backend/launcher/include/factory.hpp \
    backend/launcher/include/downloader.hpp \
    backend/launcher/include/launcher.hpp \
    backend/launcher/include/concurrency.hpp \
    backend/launcher/include/downloadAssetIndex.hpp \
    backend/launcher/include/downloadResources.hpp \
    backend/launcher/include/downloadMod.hpp \
    backend/include/updater_data.hpp \
    backend/include/dataHandler.hpp \
    backend/include/server.hpp \
    backend/include/smtp.hpp \
    backend/database/include/sqlite.hpp \
    SmtpClient/src/smtpmime_global.h \
    SmtpClient/src/smtpclient.h \
    SmtpClient/src/quotedprintable.h \
    SmtpClient/src/mimetext.h \
    SmtpClient/src/mimeqpformatter.h \
    SmtpClient/src/mimeqpencoder.h \
    SmtpClient/src/mimepart.h \
    SmtpClient/src/mimemultipart.h \
    SmtpClient/src/mimemessage.h \
    SmtpClient/src/mimeinlinefile.h \
    SmtpClient/src/mimehtml.h \
    SmtpClient/src/mimefile.h \
    SmtpClient/src/mimecontentformatter.h \
    SmtpClient/src/mimecontentencoder.h \
    SmtpClient/src/mimebytearrayattachment.h \
    SmtpClient/src/mimebase64formatter.h \
    SmtpClient/src/mimebase64encoder.h \
    SmtpClient/src/mimeattachment.h \
    SmtpClient/src/emailaddress.h \
    check/include/checkAssets.hpp \
    check/include/checkAssets.hpp \
    check/include/checkAssetIndex.hpp \
    check/include/checkLibraries.hpp \
    check/include/checkClient.hpp \
    exception/exception.hpp


SOURCES += \
    main.cpp \
    minelaunch.cpp

HEADERS += \
    minelaunch.hpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

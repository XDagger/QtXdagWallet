#-------------------------------------------------
#
# Project created by QtCreator 2018-02-28T11:17:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtXdagWallet
TEMPLATE = app

include($$PWD/pri/client.pri)
include($$PWD/pri/dnet.pri)
include($$PWD/pri/dbus.pri)
include($$PWD/pri/ldbus.pri)
include($$PWD/pri/wrapper.pri)

#include headers
INCLUDEPATH += $$PWD\..\xdaglib

#openssl lib dir
SSL_LIB_DIR = /usr/lib

#qt lib dir
QT_LIB_DIR = /opt/Qt5.7.1/5.7/gcc_64/lib
QT_PLUGINS_DIR = /opt/Qt5.7.1/5.7/gcc_64/plugins
#libs
LIBS += -lpthread -lssl -lcrypto

QMAKE_CFLAGS += -DHAVE_STRUCT_TIMESPEC -D_TIMESPEC_DEFINED -DDFSTOOLS -DCHEATCOIN -DNDEBUG -D_CRT_SECURE_NO_WARNINGS -Wall

QMAKE_CXXFLAGS += -DHAVE_STRUCT_TIMESPEC -D_TIMESPEC_DEFINED -DDFSTOOLS -DCHEATCOIN -DNDEBUG -D_CRT_SECURE_NO_WARNINGS -Wall

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES +=\
    XdagWalletProcessThread.cpp \
    QtWalletMain.cpp \
    WalletMain.cpp \
    PwdDialog.cpp \
    PwdLineEdit.cpp \
    XdagMutex.cpp \
    ErrorDialog.cpp

HEADERS  += \
    XdagWalletProcessThread.h \
    QtWalletMain.h \
    PwdDialog.h \
    UiNotifyMessage.h \
    UpdateUiInfo.h \
    XdagCommonDefine.h \
    PwdLineEdit.h \
    XdagMutex.h \
    ErrorDialog.h

FORMS    += qtwalletmain.ui \
    pwddialog.ui \
    errordialog.ui

RESOURCES += \
    resource/resource.qrc

TRANSLATIONS += \
    english.ts \
    chinese.ts \
    russian.ts \
    french.ts \
    germany.ts \
    japanese.ts \
    korean.ts

#copy so to the dest dir
linux {
    EXTRA_BINFILES += \
        $${SSL_LIB_DIR}/libssl.so \
        $${SSL_LIB_DIR}/libcrypto.so \
        $${QT_LIB_DIR}/libQt5Core.so \
        $${QT_LIB_DIR}/libQt5Gui.so \
        $${QT_LIB_DIR}/libQt5Widgets.so \

    EXTRA_PLATFORM_BINFILES += \
        $${QT_PLUGINS_DIR}/platforms/lib*.so \

    debug{
        DESTDIR = $$PWD/debug
        OBJECTS_DIR = $$PWD/debug
        MOC_DIR = $$PWD/debug
        TARGET = xdagwallet
        QMAKE_CLEAN += $$DESTDIR/*.*

        DEBUG_DESTDIR_LINUX = $${DESTDIR}
        DEBUG_DESTDIR_LINUX_PLATFORM = $${DESTDIR}/platforms

        QMAKE_POST_LINK +=$$quote(rm -rf $${DEBUG_DESTDIR_LINUX_PLATFORM}$$escape_expand(\n\t))
        QMAKE_POST_LINK +=$$quote(mkdir $${DEBUG_DESTDIR_LINUX_PLATFORM}$$escape_expand(\n\t))
        QMAKE_POST_LINK +=$$quote(cp -f $${EXTRA_BINFILES} $${DEBUG_DESTDIR_LINUX}$$escape_expand(\n\t))
        QMAKE_POST_LINK +=$$quote(cp -rf $${EXTRA_PLATFORM_BINFILES} $${DEBUG_DESTDIR_LINUX_PLATFORM}$$escape_expand(\n\t))
    }

    release{
        DESTDIR = $$PWD/release
        OBJECTS_DIR = $$PWD/release
        MOC_DIR = $$PWD/release
        TARGET = xdagwallet
        QMAKE_CLEAN += $$DESTDIR/*.*

        RELEASE_DESTDIR_LINUX = $${DESTDIR}
        RELEASE_DESTDIR_LINUX_PLATFORM = $${DESTDIR}/platforms

        QMAKE_POST_LINK +=$$quote(rm -rf $${RELEASE_DESTDIR_LINUX_PLATFORM}$$escape_expand(\n\t))
        QMAKE_POST_LINK +=$$quote(mkdir $${RELEASE_DESTDIR_LINUX_PLATFORM}$$escape_expand(\n\t))
        QMAKE_POST_LINK +=$$quote(cp -f $${EXTRA_BINFILES} $${RELEASE_DESTDIR_LINUX}$$escape_expand(\n\t))
        QMAKE_POST_LINK +=$$quote(cp -rf $${EXTRA_PLATFORM_BINFILES} $${RELEASE_DESTDIR_LINUX_PLATFORM}$$escape_expand(\n\t))
    }


#    release{
#        DESTDIR = $$PWD\release
#        OBJECTS_DIR = $$PWD\release
#        MOC_DIR = $$PWD\release
#        TARGET = xdagwallet
#        QMAKE_CLEAN += $$DESTDIR\*.pdb $$DESTDIR\*.dll $$DESTDIR\*.exe $$DESTDIR\platforms\*.dll

#        RELEASE_DESTDIR_WIN = $${DESTDIR}
#        RELEASE_DESTDIR_WIN_PLATFORM = $${DESTDIR}/platforms
#        RELEASE_DESTDIR_WIN ~= s,/,\\,g
#        RELEASE_DESTDIR_WIN_PLATFORM ~= s,/,\\,g
#        QMAKE_POST_LINK +=$$quote(if not exist $${RELEASE_DESTDIR_WIN_PLATFORM} mkdir $${RELEASE_DESTDIR_WIN_PLATFORM}$$escape_expand(\n\t))
#        QMAKE_POST_LINK +=$$quote(xcopy/e/r/h/y $${PLATFORM_DIC} $${RELEASE_DESTDIR_WIN_PLATFORM}$$escape_expand(\n\t))
#        for(FILE,EXTRA_BINFILES_WIN){
#            QMAKE_POST_LINK +=$$quote(copy $${FILE} $${RELEASE_DESTDIR_WIN}$$escape_expand(\n\t))
#        }

#    }

}

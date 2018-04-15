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

#openssl lib dir
LOCAL_INC_DIR = /usr/local/include
LOCAL_LIB_DIR = /usr/local/lib

#include headers
INCLUDEPATH += $$PWD\..\xdaglib \
                $$LOCAL_INC_DIR

#qt lib dir
QT_LIB_DIR = /opt/Qt5.9.1/5.9.1/gcc_64/lib
QT_PLUGINS_DIR = /opt/Qt5.9.1/5.9.1/gcc_64/plugins
#libs
LIBS += -L$$LOCAL_LIB_DIR -lpthread -lssl -lcrypto

QMAKE_LFLAGS += -Wl,-rpath,./lib
QMAKE_RPATHDIR += ./lib
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
        $${LOCAL_LIB_DIR}/libssl.so \
        $${LOCAL_LIB_DIR}/libcrypto.so \
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

#        DEBUG_DESTDIR_LINUX = $${DESTDIR}
#        DEBUG_DESTDIR_LINUX_PLATFORM = $${DESTDIR}/platforms

#        QMAKE_POST_LINK +=$$quote(rm -rf $${DEBUG_DESTDIR_LINUX_PLATFORM}$$escape_expand(\n\t))
#        QMAKE_POST_LINK +=$$quote(mkdir $${DEBUG_DESTDIR_LINUX_PLATFORM}$$escape_expand(\n\t))
#        QMAKE_POST_LINK +=$$quote(cp -f $${EXTRA_BINFILES} $${DEBUG_DESTDIR_LINUX}$$escape_expand(\n\t))
#        QMAKE_POST_LINK +=$$quote(cp -rf $${EXTRA_PLATFORM_BINFILES} $${DEBUG_DESTDIR_LINUX_PLATFORM}$$escape_expand(\n\t))
    }

    release{
        DESTDIR = $$PWD/release
        OBJECTS_DIR = $$PWD/release
        MOC_DIR = $$PWD/release
        TARGET = xdagwallet
        QMAKE_CLEAN += $$DESTDIR/*.*

#        RELEASE_DESTDIR_LINUX = $${DESTDIR}
#        RELEASE_DESTDIR_LINUX_PLATFORM = $${DESTDIR}/platforms

#        QMAKE_POST_LINK +=$$quote(rm -rf $${RELEASE_DESTDIR_LINUX_PLATFORM}$$escape_expand(\n\t))
#        QMAKE_POST_LINK +=$$quote(mkdir $${RELEASE_DESTDIR_LINUX_PLATFORM}$$escape_expand(\n\t))
#        QMAKE_POST_LINK +=$$quote(cp -f $${EXTRA_BINFILES} $${RELEASE_DESTDIR_LINUX}$$escape_expand(\n\t))
#        QMAKE_POST_LINK +=$$quote(cp -rf $${EXTRA_PLATFORM_BINFILES} $${RELEASE_DESTDIR_LINUX_PLATFORM}$$escape_expand(\n\t))
    }
}

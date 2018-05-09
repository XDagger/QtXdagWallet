# -------------------------------------------------
# QtXdagWallet - QT Version of XDAG Wallet
# Please see our website at <https://xdag.io>
# Maintainer:
# Bill <amazingbill2017@gmail.com>
# earthloong <earthloong@gmail.com>
# (c) 2018 QtXdagWallet Developers
# License terms set in LICENSE
# -------------------------------------------------

exists($${OUT_PWD}/QtXdagWallet.pro) {
    error("You must use shadow build (e.g. mkdir build; cd build; qmake ../QtXdagWallet.pro).")
}

message(Qt version $$[QT_VERSION])

!equals(QT_MAJOR_VERSION, 5) | !greaterThan(QT_MINOR_VERSION, 7) {
    error("Unsupported Qt version, 5.7+ is required")
}

include(QXDAGWalletCommon.pri)

TARGET   = QtXdagWallet
TEMPLATE = app

DebugBuild {
    DESTDIR  = $${OUT_PWD}/debug
} else {
    DESTDIR  = $${OUT_PWD}/release
}

#
# OS Specific settings
#

MacBuild {
    #TODO
    QMAKE_LFLAGS += -Wl,-rpath,./lib
    QMAKE_RPATHDIR += ./lib

    #openssl lib dir
    LOCAL_INC_DIR = /usr/local/include
    LOCAL_LIB_DIR = /usr/local/lib

    #libs
    LIBS += -L$$LOCAL_LIB_DIR -lpthread -lssl -lcrypto

    #qt lib dir
    QT_LIB_DIR = /opt/Qt5.9.1/5.9.1/gcc_64/lib
    QT_PLUGINS_DIR = /opt/Qt5.9.1/5.9.1/gcc_64/plugins

}

iOSBuild {
    #-- TODO: Add iTunesArtwork
}

AndroidBuild {
    #TODO
}

LinuxBuild {
    QMAKE_LFLAGS += -Wl,-rpath,./lib
    QMAKE_RPATHDIR += ./lib

    #openssl lib dir
    SSL_LIB_DIR = /usr/lib

    #libs
    LIBS += -lpthread -lssl -lcrypto

    #qt lib dir
    QT_LIB_DIR = /opt/Qt5.9.1/5.9.1/gcc_64/lib
    QT_PLUGINS_DIR = /opt/Qt5.9.1/5.9.1/gcc_64/plugins
}

WindowsBuild {
    QMAKE_LFLAGS += -STACK:40000000,1000000 -FS

    #libs
    LIBS += -L$$PWD\win64_dependency\lib -llibeay32
    LIBS += -L$$PWD\win64_dependency\lib -lssleay32
    LIBS += -L$$PWD\win64_dependency\lib -lpthreadVC2
    LIBS += -L$$PWD\win64_dependency\lib -lWS2_32
    LIBS += -L$$PWD\win64_dependency\lib -llegacy_stdio_definitions
}

#
# Branding
#
QT       += core widgets

#include
MacBuild {
    #TODO
    INCLUDEPATH += $$PWD/../xdaglib \
                $$LOCAL_INC_DIR
}

LinuxBuild {
    INCLUDEPATH += $$PWD/../xdaglib
}

WindowsBuild {
    INCLUDEPATH += $$PWD/../xdaglib \
                $$PWD/win64_dependency/include
    include($$PWD\pri\win.pri)
}

include($$PWD/pri/client.pri)
include($$PWD/pri/dnet.pri)
include($$PWD/pri/dbus.pri)
include($$PWD/pri/ldbus.pri)
include($$PWD/pri/wrapper.pri)

#include headers
#INCLUDEPATH += $$PWD\..\xdaglib
#INCLUDEPATH += $$PWD\win64_dependency\include

QMAKE_CFLAGS += -DHAVE_STRUCT_TIMESPEC -D_TIMESPEC_DEFINED -DDFSTOOLS -DCHEATCOIN -DNDEBUG -D_CRT_SECURE_NO_WARNINGS -Wall
QMAKE_CXXFLAGS += -DHAVE_STRUCT_TIMESPEC -D_TIMESPEC_DEFINED -DDFSTOOLS -DCHEATCOIN -DNDEBUG -D_CRT_SECURE_NO_WARNINGS -Wall


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=\
    XdagWalletProcessThread.cpp \
    QtWalletMain.cpp \
    WalletMain.cpp \
    PwdDialog.cpp \
    WalletInitWidget.cpp \
    PwdLineEdit.cpp \
    XdagMutex.cpp \
    ErrorDialog.cpp \
    CacheLineEdit.cpp

HEADERS  += \
    XdagWalletProcessThread.h \
    QtWalletMain.h \
    PwdDialog.h \
    WalletInitWidget.h \
    UiNotifyMessage.h \
    UpdateUiInfo.h \
    XdagCommonDefine.h \
    PwdLineEdit.h \
    XdagMutex.h \
    ErrorDialog.h \
    CacheLineEdit.h

FORMS    += qtwalletmain.ui \
    walletinitwidget.ui \
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

#
# others
#
MacBuild {
    #TODO
}

LinuxBuild | MacBuild {
    #copy dll to the dest dir
    EXTRA_BINFILES += \
        $${SSL_LIB_DIR}/libssl.so \
        $${SSL_LIB_DIR}/libcrypto.so \
        $${QT_LIB_DIR}/libQt5Core.so \
        $${QT_LIB_DIR}/libQt5Gui.so \
        $${QT_LIB_DIR}/libQt5Widgets.so \

    EXTRA_PLATFORM_BINFILES += \
        $${QT_PLUGINS_DIR}/platforms/lib*.so \
}

WindowsBuild {
    #copy dll to the dest dir
    EXTRA_BINFILES += \
        $$PWD/win64_dependency/dll/libeay32.dll \
        $$PWD/win64_dependency/dll/libssl32.dll \
        $$PWD/win64_dependency/dll/msvcr100.dll \
        $$PWD/win64_dependency/dll/pthreadVC2.dll \
        $$PWD/win64_dependency/dll/ssleay32.dll \
        $$PWD/win64_dependency/dll/Qt5Core.dll \
        $$PWD/win64_dependency/dll/Qt5Gui.dll \
        $$PWD/win64_dependency/dll/Qt5Widgets.dll \

    PLATFORM_DIC  += $$PWD/win64_dependency/dll/platforms
    PLATFORM_DIC ~= s,/,\\,g

    EXTRA_BINFILES_WIN = $${EXTRA_BINFILES}
    EXTRA_BINFILES_WIN ~= s,/,\\,g

    debug{
        #QMAKE_CLEAN += $$DESTDIR\*.pdb $$DESTDIR\*.dll $$DESTDIR\*.exe $$DESTDIR\platforms\*.dll
        #QMAKE_CLEAN += $$DESTDIR\*.*


        DEBUG_DESTDIR_WIN = $${DESTDIR}
        DEBUG_DESTDIR_WIN_PLATFORM = $${DESTDIR}/platforms
        DEBUG_DESTDIR_WIN ~= s,/,\\,g
        DEBUG_DESTDIR_WIN_PLATFORM ~= s,/,\\,g
        QMAKE_POST_LINK +=$$quote(if not exist $${DEBUG_DESTDIR_WIN_PLATFORM} mkdir $${DEBUG_DESTDIR_WIN_PLATFORM}$$escape_expand(\n\t))
        QMAKE_POST_LINK +=$$quote(xcopy/e/r/h/y $${PLATFORM_DIC} $${DEBUG_DESTDIR_WIN_PLATFORM}$$escape_expand(\n\t))
        for(FILE,EXTRA_BINFILES_WIN){
            QMAKE_POST_LINK +=$$quote(copy $${FILE} $${DEBUG_DESTDIR_WIN}$$escape_expand(\n\t))
        }
    }

    release{
        #QMAKE_CLEAN += $$DESTDIR\*.pdb $$DESTDIR\*.dll $$DESTDIR\*.exe $$DESTDIR\platforms\*.dll

        RELEASE_DESTDIR_WIN = $${DESTDIR}
        RELEASE_DESTDIR_WIN_PLATFORM = $${DESTDIR}/platforms
        RELEASE_DESTDIR_WIN ~= s,/,\\,g
        RELEASE_DESTDIR_WIN_PLATFORM ~= s,/,\\,g
        QMAKE_POST_LINK +=$$quote(if not exist $${RELEASE_DESTDIR_WIN_PLATFORM} mkdir $${RELEASE_DESTDIR_WIN_PLATFORM}$$escape_expand(\n\t))
        QMAKE_POST_LINK +=$$quote(xcopy/e/r/h/y $${PLATFORM_DIC} $${RELEASE_DESTDIR_WIN_PLATFORM}$$escape_expand(\n\t))
        for(FILE,EXTRA_BINFILES_WIN){
            QMAKE_POST_LINK +=$$quote(copy $${FILE} $${RELEASE_DESTDIR_WIN}$$escape_expand(\n\t))
        }

    }
}

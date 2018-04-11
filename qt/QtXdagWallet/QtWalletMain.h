#ifndef QTWALLETMAIN_H
#define QTWALLETMAIN_H

#include "ErrorDialog.h"
#include "PwdDialog.h"
#include "XdagWalletProcessThread.h"
#include "xdagcommondefine.h"

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAction>
#include <QMenu>
#include <QTranslator>

namespace Ui {
class QtWalletMain;
}

class QtWalletMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtWalletMain(QWidget *parent = 0);
    ~QtWalletMain();

    static QString getXdagProgramState(en_xdag_program_state state);

private:
    Ui::QtWalletMain *ui;

    QLabel *m_pLBPool;
    QLineEdit *m_pLEPool;
    QPushButton *m_pPBConnect;
    QPushButton *m_pPBDisConnect;
    QHBoxLayout *m_pHBLPool;

    QLabel *m_pLBBalance;
    QLineEdit *m_pLEBalance;
    QLabel *m_pLBAccount;
    QLineEdit *m_pLEAccount;
    QHBoxLayout *m_pHBLAccount;

    QLabel *m_pLBTransfer;
    QLineEdit *m_pLESendAmount;
    QLabel *m_pLBTo;
    QLineEdit *m_pLERecvAddress;
    QPushButton *m_pPBXfer;
    QHBoxLayout *m_pHBLTransfer;

    //Global VBoxLayout
    QVBoxLayout *m_pVBLGlobal;

    //Language
    QMenu *m_pQMLanguage;
    QAction *m_pQAEnglish;
    QAction *m_pQAChinese;
    QAction *m_pQARussian;
    QAction *m_pQAFrench;
    QAction *m_pQAGermany;
    QAction *m_pQAJanpanese;
    QAction *m_pQAKorean;

    //work threads
    XdagWalletProcessThread *m_pXdagThread;

    //password input dialog
    PwdDialog *m_pDLPwdType;
    ErrorDialog *m_pErrDlg;

    //translator
    QTranslator *m_pTranslator;

    XdagCommonDefine::EN_XDAG_UI_LANG mLanguage;

    void initUI();
    void translateUI(XdagCommonDefine::EN_XDAG_UI_LANG lang);
    void initWorkThread();
    void initSignal();
    void procUpdateUiInfo(UpdateUiInfo info);

private slots:
    void onXdagUpdateUI(UpdateUiInfo info);
    void onXdagProcessStateChange(XDAG_PROCESS_STATE state);
    void onXdagProcessFinished();
    void onBtnConnectClicked();
    void onBtnDisConnectClicked();
    void onButtonXferClicked();
    void onChangeLanguage(QAction *);
    void onAuthRejected();
    void onPwdTyped(QString pwd);
    void onPwdSeted(QString pwd);
    void onPwdReTyped(QString pwd);
    void onRdmTyped(QString rdm);


};

#endif // QTWALLETMAIN_H

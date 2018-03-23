#ifndef WALLETINITTHREAD_H
#define WALLETINITTHREAD_H

#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>

#include "../../xdaglib/wrapper/qtwrapper.h"
#include "../../xdaglib/client/xdagmain.h"
#include "UiNotifyMessage.h"
#include "UpdateUiInfo.h"

static QObject *gCallBackObject;

typedef enum tag_XDAG_PROCESS_STATE{
    XDAG_PROCESS_START,
    XDAG_PROCESS_CONNECTING,
    XDAG_PROCESS_CONNECTED,
    XDAG_PROCESS_CONN_TIMEOUT,
    XDAG_PROCESS_BLOCK_TRANSFERING,
    XDAG_PROCESS_BLOCK_TRANSFERED,
    XDAG_PROCESS_STOP
}XDAG_PROCESS_STATE;

Q_DECLARE_METATYPE(XDAG_PROCESS_STATE)

class XdagWalletProcessThread : public QThread
{
    Q_OBJECT

public:
    explicit XdagWalletProcessThread(QObject *parent);
    ~XdagWalletProcessThread();

    void Stop();
    void Start();
    bool isStopped();

    //move transation state
    void moveStateTo(XDAG_PROCESS_STATE state);

    void setPoolAddr(const char* poolAddr);
    const char* getPoolAddr(void);

    void setMutex(QMutex *mutex);
    QMutex* getMutex(void);

    void setMsgMap(QMap<QString,QString> *map);
    QMap<QString,QString>* getMsgMap();

    void setCondAuthTyped(QWaitCondition *cond);
    QWaitCondition* getCondAuthTyped(void);

    void setCondUiNotified(QWaitCondition *cond);
    QWaitCondition* getCondUiNotified();

    void waitAuthTyped();
    void wakeAuthTyped();

    void setMsgQueue(QQueue<UiNotifyMessage> *msgQueue);

    //emit ui signal
    void emitUISignal(UpdateUiInfo info);

    //for xdag library call back
    static st_xdag_app_msg* XdagWalletProcessCallback(const void *call_back_object,st_xdag_event *event);

    //get state string
    static QString getProcessStateString(XDAG_PROCESS_STATE state);

    //process ui notify message
    void processUiNotifyMessage(UiNotifyMessage &msg);
protected:
    virtual void run();

Q_SIGNALS:
    //emit wallet update ui signal
    void updateUI(UpdateUiInfo info);

    //emit process state change signal
    void stateChange(XDAG_PROCESS_STATE state);

private:
    //Mutex Lock
    QMutex *m_pMutex;
    //Condition wait Authentication information typed
    QWaitCondition *m_pCondAuthTyped;
    //Condition wait ui notify
    QWaitCondition *m_pUiNotified;

    //Msg Map
    QMap<QString,QString> *m_pMsgMap;

    //Msg queue in main loop
    QQueue<UiNotifyMessage> *m_pMsgQueue;

    //flag is need stop
    bool m_bStopped;

    //pool addr
    QString mPoolAddr;

    //current state
    XDAG_PROCESS_STATE mProcessState;
};

#endif // WALLETINITTHREAD_H

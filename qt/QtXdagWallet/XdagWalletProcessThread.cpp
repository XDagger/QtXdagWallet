#include "XdagWalletProcessThread.h"

#include <QMap>


XdagWalletProcessThread::XdagWalletProcessThread(QObject *parent = 0)
    :m_bStopped(true)
{
    qDebug() << "xdag process thread constructor: " << QThread::currentThreadId();
}

XdagWalletProcessThread::~XdagWalletProcessThread()
{
    Stop();
    quit();
    wait();
}

void XdagWalletProcessThread::Start()
{
    //QMutexLocker locker(m_pMutex);
    m_bStopped = false;
    this->start();
}

void XdagWalletProcessThread::Stop()
{
    moveStateTo(XDAG_PROCESS_STOP);
    this->quit();
    m_bStopped = true;
}


bool XdagWalletProcessThread::isStopped()
{
    return m_bStopped;
}

void XdagWalletProcessThread::moveStateTo(XDAG_PROCESS_STATE state)
{
    qDebug() << "xdag process move state from " << getProcessStateString(mProcessState)
             <<" to " << getProcessStateString(state);

    //emit ui to do something
    emit stateChange(state);

    //restrick user's operation
}

void XdagWalletProcessThread::setPoolAddr(const char* poolAddr)
{
    this->mPoolAddr = QString(poolAddr);
}

const char* XdagWalletProcessThread::getPoolAddr()
{
    return this->mPoolAddr.toStdString().c_str();
}

void XdagWalletProcessThread::setMutex(QMutex *mutex){
    this->m_pMutex = mutex;
}

void XdagWalletProcessThread::setCondUiNotified(QWaitCondition *cond)
{
    this->m_pUiNotified = cond;
}

QMutex* XdagWalletProcessThread::getMutex(void){
    return this->m_pMutex;
}

void XdagWalletProcessThread::setMsgMap(QMap<QString, QString> *map)
{
    this->m_pMsgMap = map;
}

QMap<QString, QString>* XdagWalletProcessThread::getMsgMap()
{
    return this->m_pMsgMap;
}

void XdagWalletProcessThread::setCondAuthTyped(QWaitCondition *cond)
{
    this->m_pCondAuthTyped = cond;
}

QWaitCondition *XdagWalletProcessThread::getCondAuthTyped()
{
    return this->m_pCondAuthTyped;
}

void XdagWalletProcessThread::waitAuthTyped()
{
    this->m_pCondAuthTyped->wait(m_pMutex);
}

void XdagWalletProcessThread::wakeAuthTyped()
{
    this->m_pCondAuthTyped->wakeOne();
}

QWaitCondition *XdagWalletProcessThread::getCondUiNotified()
{
    return this->m_pUiNotified;
}

void XdagWalletProcessThread::setMsgQueue(QQueue<UiNotifyMessage> *msgQueue)
{
    this->m_pMsgQueue = msgQueue;
}

void XdagWalletProcessThread::run()
{
    qDebug() << "xdag process thread run thread id: " << QThread::currentThreadId();
    m_bStopped = false;

    /* dump the pool address and keep it always in memory */
    char* address = strdup(mPoolAddr.toStdString().c_str());

    if(xdag_wrapper_log_init() < 0){
        qDebug() << " error while wallet log initialized  ";
        this->Stop();
        return;
    }

    xdag_wrapper_init((void*)this,XdagWalletProcessCallback);
    xdag_global_init();

    if(xdag_main(address) != 0){
        qDebug() << "xdag_main error while wallet initialized  ";
        xdag_wrapper_uninit();
        this->Stop();
        return;
    }

    /* start the main loop of the xdag proccess thread */
    while(!isInterruptionRequested()){
        m_pMutex->lock();

        if(m_pMsgQueue->isEmpty()){
            qDebug() << " wallet process thread waiting for message " << QThread::currentThreadId();
            m_pUiNotified->wait(m_pMutex);
        }

        /* read the ui notify message and process the message*/
        if(isInterruptionRequested()){
            qDebug() << " wallet process thread interrupted by ui " << QThread::currentThreadId();
            xdag_wrapper_uninit();
            this->Stop();
            return;
        }
        /* pop message from the queue and process the message */
        UiNotifyMessage msg = m_pMsgQueue->first();
        m_pMsgQueue->pop_front();

        qDebug() << " receive message from thread : " << msg.msgFromThreadId
                 << " transfer account " << msg.account
                 << " transfer num " << msg.amount
                 << " message type " << msg.msgType;

        m_pMutex->unlock();

        processUiNotifyMessage(msg);
    }
}

void XdagWalletProcessThread::emitUISignal(UpdateUiInfo info)
{
    emit updateUI(info);
}


st_xdag_app_msg* XdagWalletProcessThread::XdagWalletProcessCallback(const void *call_back_object, st_xdag_event* event){

    XdagWalletProcessThread *thread = (XdagWalletProcessThread*)call_back_object;
    QMutex *mutex = thread->getMutex();
    QWaitCondition *condAuthTyped = thread->getCondAuthTyped();

    qDebug() << " xdag process callback current thread id " << QThread::currentThreadId();

    if(NULL == event){
        qDebug() << " event is NULL";
        return NULL;
    }

    st_xdag_app_msg *msg = NULL;
    UpdateUiInfo updateUiInfo;
    switch(event->event_type){

        case en_event_type_pwd:
        {
            qDebug() << " event type need type password current threadid " << QThread::currentThreadId();

            mutex->lock();
            qDebug() << " en_event_type_pwd lock " << QThread::currentThreadId();
            updateUiInfo.event_type = event->event_type;
            updateUiInfo.procedure_type = event->procedure_type;
            thread->emitUISignal(updateUiInfo);

            //wait ui type password
            thread->waitAuthTyped();

            QMap<QString, QString>::iterator it;
            it = thread->getMsgMap()->find("type-passwd");

            if(it != thread->getMsgMap()->end()){
                msg = xdag_malloc_app_msg();
                msg->xdag_pwd = strdup(it->toStdString().c_str());
                thread->getMsgMap()->clear();
            }

            qDebug() << " en_event_type_pwd unlock " << QThread::currentThreadId();
            mutex->unlock();
        }
        return msg;

        case en_event_set_pwd:
        {
            qDebug() << " event type need type password current threadid " << QThread::currentThreadId();

            mutex->lock();
            qDebug() << " en_event_type_pwd lock " << QThread::currentThreadId();
            updateUiInfo.event_type = event->event_type;
            updateUiInfo.procedure_type = event->procedure_type;
            thread->emitUISignal(updateUiInfo);

            //wait ui type password
            thread->waitAuthTyped();

            QMap<QString, QString>::iterator it;
            it = thread->getMsgMap()->find("set-passwd");

            if(it != thread->getMsgMap()->end()){
                msg = xdag_malloc_app_msg();
                msg->xdag_pwd = strdup(it->toStdString().c_str());
                thread->getMsgMap()->clear();
            }

            qDebug() << " en_event_type_pwd unlock " << QThread::currentThreadId();
            mutex->unlock();
        }
        return msg;

        case en_event_retype_pwd:
        {
            qDebug() << " event type need type password current threadid " << QThread::currentThreadId();

            mutex->lock();
            qDebug() << " en_event_type_pwd lock " << QThread::currentThreadId();
            updateUiInfo.event_type = event->event_type;
            updateUiInfo.procedure_type = event->procedure_type;
            thread->emitUISignal(updateUiInfo);

            //wait ui type password
            thread->waitAuthTyped();

            QMap<QString, QString>::iterator it;
            it = thread->getMsgMap()->find("retype-passwd");

            if(it != thread->getMsgMap()->end()){
                msg = xdag_malloc_app_msg();
                msg->xdag_pwd = strdup(it->toStdString().c_str());
                thread->getMsgMap()->clear();
            }

            qDebug() << " en_event_type_pwd unlock " << QThread::currentThreadId();
            mutex->unlock();
        }
        return msg;

        case en_event_set_rdm:
        {
            qDebug() << " event type need type password current threadid " << QThread::currentThreadId();

            mutex->lock();
            qDebug() << " en_event_type_pwd lock " << QThread::currentThreadId();
            updateUiInfo.event_type = event->event_type;
            updateUiInfo.procedure_type = event->procedure_type;
            thread->emitUISignal(updateUiInfo);

            //wait ui type password
            thread->waitAuthTyped();

            QMap<QString, QString>::iterator it;
            it = thread->getMsgMap()->find("type-rdm");

            if(it != thread->getMsgMap()->end()){
                msg = xdag_malloc_app_msg();
                msg->xdag_pwd = strdup(it->toStdString().c_str());
                thread->getMsgMap()->clear();
            }

            qDebug() << " en_event_type_pwd unlock " << QThread::currentThreadId();
            mutex->unlock();
        }
        return msg;

        case en_event_pwd_not_same:
            qDebug() << " event type password not same";
            mutex->lock();
            qDebug() << " en_event_pwd_not_same lock " << QThread::currentThreadId();
            updateUiInfo.event_type = event->event_type;
            updateUiInfo.procedure_type = event->procedure_type;
            thread->emitUISignal(updateUiInfo);
            qDebug() << " en_event_pwd_not_same un lock " << QThread::currentThreadId();
            mutex->unlock();
        return msg;

        case en_event_pwd_error:
            mutex->lock();
            qDebug() << " en_event_pwd_error lock " << QThread::currentThreadId();
            updateUiInfo.event_type = event->event_type;
            updateUiInfo.procedure_type = event->procedure_type;
            thread->emitUISignal(updateUiInfo);
            qDebug() << " en_event_pwd_error un lock " << QThread::currentThreadId();
            mutex->unlock();
        return msg;

        case en_event_open_dnetfile_error:
            qDebug() << " open dnet file error " << event->error_msg;

            mutex->lock();
            qDebug() << " en_event_open_dnetfile_error lock " << QThread::currentThreadId();
            updateUiInfo.event_type = event->event_type;
            updateUiInfo.procedure_type = event->procedure_type;
            thread->emitUISignal(updateUiInfo);
            qDebug() << " en_event_open_dnetfile_error un lock " << QThread::currentThreadId();
            mutex->unlock();
        return NULL;

        case en_event_open_walletfile_error:
            qDebug() << " open dnet file error " << event->error_msg;

            mutex->lock();
            qDebug() << " en_event_open_dnetfile_error lock " << QThread::currentThreadId();
            updateUiInfo.event_type = event->event_type;
            updateUiInfo.procedure_type = event->procedure_type;
            thread->emitUISignal(updateUiInfo);
            qDebug() << " en_event_open_dnetfile_error un lock " << QThread::currentThreadId();
            mutex->unlock();
        return NULL;

        case en_event_load_storage_error:
            qDebug() << " open dnet file error " << event->error_msg;

            mutex->lock();
            qDebug() << " en_event_load_storage_error lock " << QThread::currentThreadId();
            updateUiInfo.event_type = event->event_type;
            updateUiInfo.procedure_type = event->procedure_type;
            thread->emitUISignal(updateUiInfo);
            qDebug() << " en_event_load_storage_error un lock " << QThread::currentThreadId();
            mutex->unlock();
        return NULL;

        //transfer error notify
        case en_event_balance_too_small:
        case en_event_invalid_recv_address:
        case en_event_nothing_transfer:
            mutex->lock();
            qDebug() << " error while transfer xdag lock" << QThread::currentThreadId();
            updateUiInfo.event_type = event->event_type;
            updateUiInfo.procedure_type = event->procedure_type;
            thread->emitUISignal(updateUiInfo);
            qDebug() << " error while transfer xdag unlock " << QThread::currentThreadId();
            mutex->unlock();
        return NULL;

        case en_event_update_state:
            updateUiInfo.event_type = event->event_type;
            updateUiInfo.procedure_type = event->procedure_type;
            updateUiInfo.address = QString(event->address);
            updateUiInfo.balance = QString(event->balance);
            updateUiInfo.state = QString(event->state);
            updateUiInfo.xdag_program_state = event->xdag_program_state;
            updateUiInfo.balance_state = event->xdag_balance_state;
            updateUiInfo.address_state = event->xdag_address_state;
            thread->emitUISignal(updateUiInfo);
        return NULL;

        case en_event_xdag_log_print:
            qDebug() << event->app_log_msg;
        return NULL;

        default:
            qDebug() << " unknow event type : " << event->event_type;
        return NULL;
    }

    return NULL;
}

QString XdagWalletProcessThread::getProcessStateString(XDAG_PROCESS_STATE state)
{
    switch(state){
        case XDAG_PROCESS_START:
        return "start";

        case XDAG_PROCESS_CONNECTING:
        return "connecting";

        case XDAG_PROCESS_CONNECTED:
        return "connected";

        case XDAG_PROCESS_CONN_TIMEOUT:
        return "connect time out";

        case XDAG_PROCESS_BLOCK_TRANSFERING:
        return "block transfering";

        case XDAG_PROCESS_BLOCK_TRANSFERED:
        return "block transfered";

        case XDAG_PROCESS_STOP:
        return "stop";

        default:
            return "unkown state";
    }

    return "unkown state";
}

void XdagWalletProcessThread::processUiNotifyMessage(UiNotifyMessage & msg)
{
    switch(msg.msgType){

        case UiNotifyMessage::EN_DO_XFER_XDAG:
            xdag_send_coin(msg.amount,msg.account);
        break;

        case UiNotifyMessage::EN_QUIT_XDAG:

        break;
    }
}

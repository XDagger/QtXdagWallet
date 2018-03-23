#ifndef XDAGMUTEX_H
#define XDAGMUTEX_H

#include <QMutex>
#include <QString>

class XdagMutex : public QMutex
{
public:
    XdagMutex();

    void lock(const char* lockFile = __FILE__,int lockLine = __LINE__);
    //bool tryLock(int timeout = 0);
    void unlock(const char* unlockFile = __FILE__,int unlockLine = __LINE__);
private:
    QString lockFile;
    int     lockLine;
    QString unlockFile;
    int     unlockLine;
};

#endif // XDAGMUTEX_H

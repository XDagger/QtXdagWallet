#include "XdagMutex.h"

XdagMutex::XdagMutex()
{

}

void XdagMutex::lock(const char* lockFile,int lockLine)
{
    this->lockFile = lockFile;
    this->lockLine = lockLine;

    QMutex::lock();
}

void XdagMutex::unlock(const char* unlockFile,int unlockLine)
{
    this->unlockFile = unlockFile;
    this->unlockLine = unlockLine;

    QMutex::unlock();
}

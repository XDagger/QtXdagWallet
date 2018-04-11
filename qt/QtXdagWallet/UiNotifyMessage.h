#ifndef UINOTIFYMESSAGE_H
#define UINOTIFYMESSAGE_H

#include <QThread>

class UiNotifyMessage
{
public:
    enum EN_UI_NOTIFY_MSG_TYPE{
        EN_DO_XFER_XDAG = 1,
        EN_QUIT_XDAG = 2
    };

    EN_UI_NOTIFY_MSG_TYPE msgType;
    Qt::HANDLE msgFromThreadId;
    char* account;
    char* amount;

    operator QVariant() const;
};

Q_DECLARE_METATYPE(UiNotifyMessage)

#endif // UINOTIFYMESSAGE_H

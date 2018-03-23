#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "../../xdaglib/wrapper/qtwrapper.h"

namespace Ui {
class ErrorDialog;
}

class ErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorDialog(QWidget *parent = 0,en_xdag_event_type type = en_event_unkown);
    ~ErrorDialog();

    static QString getTextFromDlgType(en_xdag_event_type type);

private:
    Ui::ErrorDialog *ui;
    QLabel *m_pLBText;
    QPushButton *m_pBtnOK;
    QVBoxLayout *m_pVBLGlobal;
    en_xdag_event_type mDlgType;

private slots:
    void onBtnClicked();
};

#endif // ERRORDIALOG_H

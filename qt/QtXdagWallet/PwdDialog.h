#ifndef PWDDIALOG_H
#define PWDDIALOG_H

#include "ErrorDialog.h"
#include "PwdLineEdit.h"

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegExp>

namespace Ui {
class PwdDialog;
}

typedef enum tag_PWD_DLG_TYPE{
    DLG_TYPE_PWD,
    DLG_SET_PWD,
    DLG_RETYPE_PWD,
    DLG_TYPE_RDM
}PWD_DLG_TYPE;

class PwdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PwdDialog(QWidget *parent = 0,PWD_DLG_TYPE type = DLG_TYPE_PWD);
    ~PwdDialog();
    void closeDialog();

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

signals:
    void sendTypePwd(QString pwd);
    void sendSetPwd(QString pwd);
    void sendRetypePwd(QString pwd);
    void sendRdm(QString rdm);

private:
    Ui::PwdDialog *ui;

    QLabel *m_pLable;
    PwdLineEdit *m_pLEPwd;
    QPushButton *m_pPBOK;
    QHBoxLayout *m_pHBLInputPwd;
    QHBoxLayout *m_pHBLButton;
    QVBoxLayout *m_pVBLGlobal;

    PWD_DLG_TYPE mDlgType;
    ErrorDialog *m_pErrDlg;

    QRegExp mPwdRegExp;
    const QString mPwdExp = "^(?![0-9]+$)(?![a-zA-Z]+$)[0-9A-Za-z]{8,16}$";

private slots:
    void onBtnOKClicked();
};

#endif // PWDDIALOG_H

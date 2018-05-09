#ifndef WALLETINITWIDGET_H
#define WALLETINITWIDGET_H

#include <QWidget>

namespace Ui {
class WalletInitWidget;
}

class WalletInitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WalletInitWidget(QWidget *parent = 0);
    ~WalletInitWidget();

private:
    Ui::WalletInitWidget *ui;
};

#endif // WALLETINITWIDGET_H

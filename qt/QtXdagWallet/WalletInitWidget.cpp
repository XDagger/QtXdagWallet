#include "WalletInitWidget.h"
#include "ui_walletinitwidget.h"

WalletInitWidget::WalletInitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WalletInitWidget)
{
    ui->setupUi(this);
}

WalletInitWidget::~WalletInitWidget()
{
    delete ui;
}

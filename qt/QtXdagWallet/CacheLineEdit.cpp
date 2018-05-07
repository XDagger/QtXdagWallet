#include "CacheLineEdit.h"
#include <QApplication>
#include <QCompleter>
#include <QDesktopWidget>

CacheLineEdit::CacheLineEdit(QWidget *parent)
   : QLineEdit(parent)
{
    QCompleter *completer = new QCompleter(this);
    listModel = new QStringListModel(valueList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModel(listModel);
    this->setCompleter(completer);
    connect(this, SIGNAL(editingFinished()), this, SLOT(editComplete()));
    connect(this, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
    connect(this,SIGNAL(pressed()),this,SLOT(editClicked()));
}

void CacheLineEdit::setNormal()
{
    setText("");
}

void CacheLineEdit::setSearching()
{
}

void CacheLineEdit::addValue(const QString &value)
{
    valueList.append(value);
    listModel->setStringList(valueList);
}

void CacheLineEdit::focusInEvent(QFocusEvent *event)
{
    emit pressed();
    QLineEdit::focusInEvent(event);
}

void CacheLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
}

void CacheLineEdit::editComplete()
{
    QString text = this->text();
    if(QString::compare(text, QString("")) != 0) {
        bool flag = valueList.contains(text, Qt::CaseInsensitive);
        if(!flag) {
            addValue(text);
        }
    }
}

void CacheLineEdit::onTextChanged(QString text)
{
    emit searchTextChanged(text);
}

void CacheLineEdit::editClicked()
{
    this->setSearching();
}

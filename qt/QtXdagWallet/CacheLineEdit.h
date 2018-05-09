#ifndef CACHELINEEDIT_H
#define CACHELINEEDIT_H

#include <QLineEdit>
#include <QPushButton>
#include <QtGui>

class CacheLineEdit : public QLineEdit
{
    Q_OBJECT

 public:
    explicit CacheLineEdit(QWidget *parent = 0);
    void setNormal();
    void setSearching();
    void addValue(const QString &value);

protected:
   void focusInEvent(QFocusEvent *event);
   void focusOutEvent(QFocusEvent *event);

 signals:
    void pressed();
    void searchTextChanged(QString);

private slots:
    void editComplete();
    void onTextChanged(QString text);
    void editClicked();

private:
    QStringList valueList;
    QStringListModel *listModel;
};

#endif // CACHELINEEDIT_H

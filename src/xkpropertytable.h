#ifndef XKPROPERTYTABLE_H
#define XKPROPERTYTABLE_H

#include <QDockWidget>
#include <QTableWidget>
#include <QFileInfo>
#include <QDateTime>

class XkPropertyTable : public QDockWidget
{
    Q_OBJECT
public:
    explicit XkPropertyTable(const QString &tittleName, QDockWidget *parent = 0);
    void InitPropertyTable();
    
signals:
    
public slots:
public:
    void  UpdateFileProperty(QString);
private:
    QTableWidget * pTableWidget;
    
};

#endif // XKPROPERTYTABLE_H

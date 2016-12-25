#include "xkpropertytable.h"

XkPropertyTable::XkPropertyTable(const QString &tittleName, QDockWidget *parent)
  : QDockWidget(tittleName,parent)
{
    pTableWidget = new QTableWidget;
            this->setStyleSheet("color:blue;"); //绿色字体黑色背景

    QWidget* lTitleBar = this->titleBarWidget();
     QWidget* lEmptyWidget = new QWidget();
     this->setTitleBarWidget(lEmptyWidget);
     delete lTitleBar;
}

void XkPropertyTable::InitPropertyTable()
{
    pTableWidget->setColumnCount(1);
    pTableWidget->setRowCount(5);
    QStringList m_headers;
    m_headers<<"  文件名   "
                            <<"   大小   "
                           <<" 创建时间"
                           <<" 访问时间"
                           <<"   权限   ";
   pTableWidget->setVerticalHeaderLabels(m_headers);
    //m_pTableWidget->horizontalHeader()->hideSection(0);

   QStringList m_horhead;
   m_horhead<<"contents";
   pTableWidget->setHorizontalHeaderLabels(m_horhead);

    this->setWidget(pTableWidget);

}

void XkPropertyTable::UpdateFileProperty(QString mfilename)
{
     QFileInfo   mCurrentFileInfo = QFileInfo(mfilename);
    QString m_filename=mCurrentFileInfo.completeBaseName();
    QString m_filesize ="";
    qint64 m_size = mCurrentFileInfo.size();
     float m_size_float=0.0;
    if(m_size <1000)                      {  m_size_float = m_size;   m_filesize= QString("%1 Byte").arg(m_size_float) ;}
    else  if ( m_size <1000000)     {  m_size_float = (float)(m_size) /1000.0;     m_filesize= QString("%1 KB").arg(m_size_float) ;    }
    else  if( m_size < 1000000000) { m_size_float = (float)(m_size) /1000000.0;          m_filesize= QString("%1 MB").arg(m_size_float) ;   }
    else   { m_size_float = (float)(m_size) /1000000000.0;       m_filesize= QString("%1 GB").arg(m_size_float) ;}

    QString m_filecreat_time = mCurrentFileInfo.created().toString(("yyyy-MM-dd hh:mm:ss"));
    QString m_fileread_time = mCurrentFileInfo.lastRead().toString("yyyy-MM-dd hh:mm:ss");

      QString m_file_authority ="";
   if(mCurrentFileInfo.isReadable())
       m_file_authority += " readable ";
   if(mCurrentFileInfo.isWritable())
       m_file_authority += ", writable";
   if(mCurrentFileInfo.isExecutable())
       m_file_authority += ", exeable";

    pTableWidget->setItem(0, 0, new QTableWidgetItem(m_filename));
    pTableWidget->setItem(0, 1, new QTableWidgetItem(m_filesize));
    pTableWidget->setItem(0, 2, new QTableWidgetItem(m_filecreat_time));
    pTableWidget->setItem(0, 3, new QTableWidgetItem(m_fileread_time));
    pTableWidget->setItem(0, 4, new QTableWidgetItem(m_file_authority));
}

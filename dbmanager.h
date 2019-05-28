#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "noteitem.h"

#include <qstring.h>
#include <QtSql/QSqlDatabase>


class DbManager
{
public:
    DbManager();
    DbManager(const QString& path);
    bool AddNote(const QString& note);
    bool DeleteNote(int id);
    QStringList PrintNotes();
    void Disconnect();
    void DownloadItems(QVector<NoteItem*> &vector);
    // bool isConnect(); /*{ return m_db.isOpen(); }*/
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H

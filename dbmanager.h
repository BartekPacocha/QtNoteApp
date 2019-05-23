#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <qstring.h>
#include <QtSql/QSqlDatabase>


class DbManager
{
public:
    DbManager();
    DbManager(const QString& path);
    bool AddNote(const QString& note);
    QStringList PrintNotes();
    void Disconnect();
    bool isConnect() {return m_db.isOpen(); }
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H

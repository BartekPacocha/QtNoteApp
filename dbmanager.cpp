#include "dbmanager.h"
#include "noteitem.h"
#include <qstring.h>
#include <qdebug.h>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>

DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(!m_db.open()) {
        qDebug() << "Error: connection with database fail";
    }
    else {
        qDebug() << "Database: connected ok";
    }
}

void DbManager::Disconnect()
{
    if(m_db.open()) {
        m_db.close();
        qDebug() << "Database: disconnected ok";
    }
}

bool DbManager::AddNote(const QString &note)
{
    bool result = false;

    QSqlQuery query;
    query.prepare("INSERT INTO notes (note) VALUES (:note)");
    query.bindValue(":note", note);
    if(query.exec()) {
        result = true;
        qDebug() << "Database: Query: add note succes";
    } else {
        qDebug() << "Database: Query: add note unsucces: " << query.lastError();
    }

    return result;
}

QStringList DbManager::PrintNotes()
{
    QStringList list;
    QSqlQuery query("SELECT * FROM notes");
    auto idNote = query.record().indexOf("note");
    auto idId = query.record().indexOf("id");
    while (query.next())
    {
       auto note = query.value(idNote).toString();
       list.append(note);
       qDebug() << note;
    }

    return list;
}

bool DbManager::DeleteNote()
{
    return true;
}

void DownloadItems(QVector<NoteItem> &vector)
{
    //
}

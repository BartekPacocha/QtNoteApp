#ifndef NOTEITEM_H
#define NOTEITEM_H

#include <qstring.h>


class NoteItem
{
public:
    NoteItem();
    NoteItem(int id, QString note);
    void SetId(int id) { Id = id; }
    int GetId() { return Id; }
    QString GetStringId() { return QString::number(Id); }
    void SetNote(QString note) { Note = note; }
    QString GetNote() { return Note; }
private:
    int Id;
    QString Note;
};

#endif // NOTEITEM_H

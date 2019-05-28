#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <dbmanager.h>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DbManager* db = nullptr;
    QVector<NoteItem*> vector;

private slots:

    void on_pbAdd_clicked();

    void on_pbDelete_clicked();

    void on_leText_returnPressed();

    void createActions();

    QString getFileName() { return fileName; }

    void setFileName(QString name) { fileName = name; }

    void on_lwMain_itemClicked(QListWidgetItem *item);

    void on_twMain_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    QStringListModel *model;
    QStringList List;
    void AddItem();
    bool save();
    void dbConnect();
    void dbDisconnect();
    void exitApp();
    void dbPrint();
    void FillVector();
    void PrintItem(NoteItem *item);
    void RemoveAllRow();
    bool DeleteItem(int id);
    QString fileName;
};

#endif // MAINWINDOW_H

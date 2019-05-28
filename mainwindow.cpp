#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include <QMessageBox>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
    ui->twMain->hideColumn(0);
    ui->twMain->horizontalHeader()->setStretchLastSection(true);

    dbConnect();
    FillVector();
    dbPrint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbAdd_clicked()
{
    AddItem();
}

void MainWindow::on_pbDelete_clicked()
{
    auto t = ui->twMain;
    if(t->currentItem() != nullptr)
    {
        auto id = t->item(t->currentRow(), 0)->text();
        if(DeleteItem(id.toInt())) {
            RemoveAllRow();
            FillVector();
            dbPrint();
        }

        // db->DeleteNote();
    }
}

bool MainWindow::DeleteItem(int id)
{
    if(db)
        if(db->DeleteNote(id))
            return true;

     return false;
}

void MainWindow::RemoveAllRow()
{
    auto c = ui->twMain->rowCount();
    while (c >= 0) {
        ui->twMain->removeRow(c-1);
        c--;
    }
}

void MainWindow::on_leText_returnPressed()
{
    if(ui->leText->text() != "")
    {
        AddItem();
    }
}

void MainWindow::AddItem()
{
    // Add to db
    auto text = ui->leText->text();
    if(db && text.count() > 0)
        db->AddNote(text);
    // Refresh view
    FillVector();
    dbPrint();
}

void MainWindow::PrintItem(NoteItem *item)
{
    auto t = ui->twMain;
    t->insertRow(t->rowCount());
    t->setItem(t->rowCount()-1, 0, new QTableWidgetItem(item->GetStringId()));
    t->setItem(t->rowCount()-1, 1, new QTableWidgetItem(item->GetNote()));
}

void MainWindow::createActions()
{
    connect(ui->actionZapisz, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::dbConnect);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::dbDisconnect);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exitApp);
    connect(ui->actionPrint_records, &QAction::triggered, this, &MainWindow::dbPrint);
    connect(ui->actionFill_vector, &QAction::triggered, this, &MainWindow::FillVector);
    connect(ui->actionDelete_all_rows, &QAction::triggered, this, &MainWindow::RemoveAllRow);
}

bool MainWindow::save()
{
    // check if file exist

    return true;
}

void MainWindow::dbConnect()
{
    const QString p = "/home/bartek/Database/note.db";
    db = new DbManager(p);
}

void MainWindow::dbDisconnect()
{
    if(db){
        db->Disconnect();
    }
}

void MainWindow::exitApp()
{
    QCoreApplication::quit();
}

void MainWindow::dbPrint()
{
    if(vector.count() > 0) {
        NoteItem *item;
        foreach (item, vector) {
            PrintItem(item);
        }
    }
}

void MainWindow::on_lwMain_itemClicked(QListWidgetItem *item)
{
    qDebug() << item->text();
}

void MainWindow::on_twMain_cellClicked(int row, int column)
{
    auto t = ui->twMain;
    auto id = t->item(row, 0)->text();
    qDebug() << id;
}

void MainWindow::FillVector()
{
    if (db) {
        vector.clear();
        db->DownloadItems(vector);
    }
}

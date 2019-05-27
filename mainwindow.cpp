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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbAdd_clicked()
{
    if(ui->leText->text() != "")
    {
        // add to database
        if(db){
            if(db->isConnect()) {
                db->AddNote(ui->leText->text());
            }
             AddItem();
        } else {
            qDebug() << "Adding to db failed";
        }

    }
}

void MainWindow::on_pbDelete_clicked()
{
    if(ui->lwMain->currentItem() != NULL)
    {
        int row = ui->lwMain->currentRow();
        ui->lwMain->takeItem(row);
        db->DeleteNote();
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
    ui->lwMain->addItem(ui->leText->text());
    ui->leText->clear(); // TODO: clear in other function
}

void MainWindow::createActions()
{
    connect(ui->actionZapisz, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::dbConnect);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::dbDisconnect);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exitApp);
    connect(ui->actionPrint_records, &QAction::triggered, this, &MainWindow::dbPrint);
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
    if(db){
        ui->lwMain->clear();
        ui->lwMain->addItems(db->PrintNotes());
    }
}

void MainWindow::on_lwMain_itemClicked(QListWidgetItem *item)
{
    qDebug() << item->text();;
}

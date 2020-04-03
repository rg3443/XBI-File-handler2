#include "cmaintab.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStringList>
#include "ui_mainwindow.h"
#include "cpsqldatabase.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <fstream>
#include "FileSys/cfilesystem.h"
#include <QSqlQuery>

CMainTab::CMainTab(CModel* model, QWidget *parent) : QWidget(parent)
{

    this->model = model;
    //QLabel * lab = new QLabel("choose directory");
   // QStringList fileList = QFileDialog::getOpenFileNames(0,"Выберите директорию","","*.xbi");
    //QVBoxLayout * box = new QVBoxLayout;
    slayout = new QGridLayout(this);
    //buttonsList.push_back(new QPushButton("выбор директории",this));
    QPushButton * directoryChooseB = new QPushButton("выбор директории",this);
   // buttonsList.push_back(new QPushButton("новый файл",this));
    QPushButton * newFileB = new QPushButton("новый файл",this);
    //buttonsList.push_back(new QPushButton("открыть файл",this));
    QPushButton * openFileB = new QPushButton("открыть файл",this);
    //buttonsList.push_back(new QPushButton("открыть узел",this));
    QPushButton * openChainB = new QPushButton("открыть узел",this);
    //buttonsList.push_back(new QPushButton("выбор файлов",this));
    QPushButton * chooseFilesB = new QPushButton("выбор файлов",this);

   // buttonsList.push_back(new QPushButton("новый обьект",this));
    QPushButton * newRow = new QPushButton("новый обьект",this);
    QPushButton * newChainB = new QPushButton("создать узел",this);


    newFileName = new QLineEdit(this);
    newChainName = new QLineEdit(this);


    fileList = new QComboBox(this);
    chainList = new QComboBox(this);


    tableView[0] = new QTableWidget(this);
    tableView[0]->setColumnCount(4);
    tableView[0]->setShowGrid(true);
    tableView[0]->setSelectionMode(QAbstractItemView::SingleSelection);
    QStringList columnNames;
    columnNames.push_back(QString("Имя"));
    columnNames.push_back(QString("Родитель"));
    columnNames.push_back(QString("Размер Поля"));
    columnNames.push_back(QString("Описание"));
    tableView[0]->setHorizontalHeaderLabels(columnNames);


    connect(directoryChooseB,SIGNAL(released()),this,SLOT(OpenDirectory()));
    connect(newFileB,SIGNAL(released()),this,SLOT(NewFile()));
    connect(openFileB,SIGNAL(released()),this,SLOT(OpenFile()));
    connect(openChainB,SIGNAL(released()),this,SLOT(OpenChain()));
    connect(chooseFilesB,SIGNAL(released()),this,SLOT(OpenFiles()));
    connect(newRow,SIGNAL(released()),this,SLOT(AddObjectInToChain()));
    connect(newChainB,SIGNAL(released()),this,SLOT(AddChain()));


    slayout->addWidget(directoryChooseB,0,1); slayout->addWidget(chooseFilesB,0,2);
    slayout->addWidget(tableView[0],1,0); slayout->addWidget(newRow,0,0);
    slayout->addWidget(newFileName,2,0); slayout->addWidget(newFileB,2,1); slayout->addWidget(fileList,2,2); slayout->addWidget(openFileB,2,3);
    slayout->addWidget(newChainName,3,0); slayout->addWidget(newChainB,3,1); slayout->addWidget(chainList,3,2); slayout->addWidget(openChainB,3,3);

    setLayout(slayout);
}
void CMainTab::OpenDirectory()
{
    model->LoadWorkbanchDirectoryPath(QFileDialog::getExistingDirectory(0,"Выберите директорию",""));
}

void CMainTab::OpenFiles()
{
    model->LoadFileNames(QFileDialog::getOpenFileNames(0,"Выберите файлы","","*.xbi"));
    QStringList fileNames = model->GetFileNames();
    for(int i=0;i<fileNames.size();i++) {
        fileList->addItem(fileNames[i]);
    }
}

void CMainTab::NewFile()
{
    CFileSystemm fs;
    QString filePath = model->GetWorkbanchDirectoryPath() + "/" + newFileName->text();
    fs.Open(filePath);
    cout << filePath.toStdString() << endl;
    if(fs.is_open()) {
        model->NewFile(filePath.toStdString(),newFileName->text().toStdString());
        newFileName->clear();
        cout << "file created" << endl;
    } else {
        cout << "failed to create file" << endl;
    }
    fs.Close();
}

void CMainTab::OpenFile()
{
    QString filePath = fileList->currentText();
    model->OpenFile(filePath);
    QStringList chainNames = model->GetChainNames(filePath);
    cout << chainNames.size() << endl;
    chainList->clear();
    for (int i=0;i<chainNames.size();i++) {
        chainList->addItem(chainNames[i]);
    }
}


void CMainTab::OpenChain()
{
    CPSQLDatabase * connTool = model->GetConnectionTool();
    QVariant chainName = chainList->currentText();
    model->FillTableWidget(tableView[0],chainName.toString());


    /*
    QSqlQuery query(command);
    connTool->ExecCommand(command.toStdString());
    for(int i=0;query.next();i++) {
        tableView[0]->insertRow(i);
        tableView[0]->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));

        QTableWidgetItem *item = new QTableWidgetItem();
        item->data(Qt::CheckStateRole);

        if(query.value(1).toInt() == 1){
            item->setCheckState(Qt::Checked);
        } else {
            item->setCheckState(Qt::Unchecked);
        }
        tableView[0]->setItem(i,1,item);
        tableView[0]->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        tableView[0]->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
    }
    tableView[0]->resizeColumnsToContents();
    */
}

void CMainTab::AddChain()
{
    model->AddNewChainToFile(fileList->currentText(),newChainName->text());
    newChainName->clear();
}

void CMainTab::AddObjectInToChain()
{
    //tableView[0]->insertRow(model->Get);
}

void CMainTab::DeleteFile()
{

}

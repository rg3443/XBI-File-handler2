#include "cmodel.h"
#include <QTableWidgetItem>
#include <QTextCodec>

CModel::CModel()
{

}

void CModel::NewFile(string path,string name)
{
    CFileSystemm fs;
    fs.Open(path);
    fs.Write(name);
    XBIfile newFile; newFile.Init(name,path);
    xbiFileList.push_back(newFile);
    fs.Close();
}

void CModel::OpenFile(QString path)
{
    XBIfile openedFile;
    CFileSystemm fs;
    cout << path.toStdString() << endl;
    fs.Open(path);
    QByteArray data = fs.Read();
    QString text = QString::fromStdString(data.toStdString());
    QString buf;
    int lineCounter = 0;
    for(int i=0;i<text.size();i++) {
        if(text[i] != '\n') {
            buf = buf + text[i];
        } else if(text[i] == '\n') {
            lineCounter++;
            if(lineCounter == 1) {  //первая строка в файле == имя файла без пути
                openedFile.Init(buf.toStdString(),path.toStdString());
                cout << "name was readed" << endl;
            } else if(lineCounter > 1) {                //последующие строки == имена узлов для создания/открытия таблиц в бд
                openedFile.AddChain(buf.toStdString());
                string command = "create table " + buf.toStdString() + "(Имя text,Родитель boolean, Размер_поля integer, Описание text);";
                connectionTool->ExecCommand(command);
                cout << "chain was added" << endl;
            }
            cout << buf.toStdString() << endl;
            buf.clear();
            cout << "symbol#" << i << endl;
        }
    }
    xbiFileList.push_back(openedFile);
    fs.Close();
}

void CModel::AddNewChainToFile(string filePath,string chainName)
{
    for(int i=0;i<xbiFileList.size();i++) {
        if(xbiFileList[i].GetPath() == filePath) {
            xbiFileList[i].AddChain(chainName);
            CFileSystemm fs;
            fs.Open(filePath);
            string buf = "\n" + chainName;
            fs.Write(buf);
            string command = "create table "+chainName+"(Имя text,Родитель boolean, Размер_поля integer, Описание text);";
            connectionTool->ExecCommand(command);
        }
    }
}

void CModel::FillTableWidget(QTableWidget *table,QString chainName)
{
    chainName.resize(chainName.size()-1);

    connectionTool->SelectFromTable(chainName.toStdString());
    for(int x=0;x<connectionTool->GetColumnsAmmount();x++) {
        table->insertRow(x);
        cout << connectionTool->GetRowAmmount() << endl;
        for(int y=0;y<connectionTool->GetRowAmmount();y++) {
            QString item(connectionTool->GetData(y,x).c_str());
            cout << "field|x" << x << "|y" << y <<"|data == " << item.toStdString() << endl;
            table->setItem(x,y,new QTableWidgetItem(item));
        }
    }
    table->resizeColumnsToContents();
}


void CModel::DeleteFile(int id)
{
    xbiFileList.erase( xbiFileList.begin()+id );
}

XBIfile* CModel::GetFile(int id)
{
    return &xbiFileList[id];
}

void CModel::LoadFileNames(QStringList fileNames)
{
    this->fileNames = fileNames;
    for(int i=0;i<fileNames.end()-fileNames.begin();i++)
    {
        XBIfile file; file.Init("this function do not working",fileNames[i].toStdString());
        xbiFileList.push_back( file );
    }
    this->ConsoleShowFileNames();
    for(int i=0; i<fileNames.size();i++)
    {
        cout << i <<  "---------------" << endl;
        cout << xbiFileList[i].GetPath() << endl;
        for(int chainID=0;chainID<xbiFileList[i].GetChainSize();chainID++) {
            cout << xbiFileList[i].GetChain(chainID)->GetField(0)->name << endl;
        }
    }

}

void CModel::ConsoleShowFileNames()
{
    for(int i=0;i<fileNames.end()-fileNames.begin();i++)
    {
        cout << fileNames[i].toStdString() << endl;
    }
}

QStringList CModel::GetChainNames(QString filePath)
{
    QStringList chainNames;
    for(int fileID=0;fileID<xbiFileList.size();fileID++) {
        if(xbiFileList[fileID].GetPath().c_str() == filePath)
        for(int chainID=0;chainID<xbiFileList[fileID].GetChainSize();chainID++) {
            chainNames.push_back(xbiFileList[fileID].GetChain(chainID)->GetName().c_str());
        }
    }
    return chainNames;
}

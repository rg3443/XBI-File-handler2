/*

 * Demo of libpq.

 * Build: g++ libpq-demo.cc -o libpq-demo -lpq

 * Run: ./libpq-demo

 */



//#include <arpa/inet.h>
#include <QApplication>
#include <iostream>
#include <libpq-fe.h>
#include <sstream>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
#include "cpsqldatabase.h"
#include "mainwindow.h"
#include "cpresenter.h"
#include "FileSys/cfilesystem.h"
#include <QByteArray>
/*
 *
 * Turn host byte sequence to network byte sequence.
 */


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // CFileSystem ttest;
   // ttest.Open("xbitest.xbi");
  //  ttest.Write("test epta\naga");
  //  QByteArray arr = ttest.Read();
    CPSQLDatabase db;

    db.Connect("postgres","[eqdgbplt1337","postgres","127.0.0.1","5432");
    db.SelectFromTable("heh");
  //  MainWindow app;
   // app.show();
    CPresenter prog;
    prog.Init();
    prog.Run();
    return a.exec();
}

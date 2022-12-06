#include "connexion.h"
#include "mainwindow.h"
#include "QMessageBox"
#include "QDebug"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;

  QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
  db=QSqlDatabase::addDatabase("QODBC");
  db.setDatabaseName("datasource");
  db.setUserName("system");
  db.setPassword("admin");
  db.open();

          w.show();
            return a.exec();



}

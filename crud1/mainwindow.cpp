#include <QString>
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QIntValidator>
#include <QMessageBox>
#include <QSqlError>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "customer.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(tmp.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}









void MainWindow::on_pushButton_clicked()
{
    QString nom=ui->name_edit->text();
    QString prenom=ui->last_name_edit->text();
    QString mail=ui->email_edit->text();
    QString addres=ui->adress_edit->text();
    int numero=ui->phone_edit->text().toInt();
   customer c  ( nom, prenom, mail, addres, numero )

 //(QString nom,QString prenom,QString mail, addres, numero );
;
    QSqlQuery query;

    bool test= c.ajout();
    if (test)
    {
       ui->tableView->setModel(tmp.afficher());
       QMessageBox::information(nullptr, QObject::tr("CORRECT !"),
                   QObject::tr("Create successful.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else

       QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                   QObject::tr("create  failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}








void MainWindow::on_PushButton1_clicked()
{
    int num =ui->lineEdit->text().toInt();
    bool test =tmp.supprimer(num);
    if (test)
    {
 ui->tableView->setModel(tmp.afficher());

       QMessageBox::information(nullptr, QObject::tr("CORRECT !"),
                   QObject::tr("delete sucessful \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else

       QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                   QObject::tr("delete failed \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_2_clicked()
{
    int numero=ui->phone_edit_2->text().toInt();
        QString name=ui->name_edit_2->text();
        QString lastname=ui->last_name_edit_2->text();
         QString email=ui->email_edit_2->text();
          QString address=ui->adress_edit_2->text();


        customer c(name,lastname,email,address,numero);
        bool test=c.modifier(numero);
        ui->tableView->setModel(tmp.afficher());
     if(test){

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("modification effectué \n""Click Cancel to exit"),QMessageBox::Cancel);
    }else{
         QMessageBox::information(nullptr,QObject::tr("OK"),
                                  QObject::tr("modification non effectué \n""Click Cancel to exit"),QMessageBox::Cancel);

}
}

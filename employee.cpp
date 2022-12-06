#include "employee.h"
Employee::Employee(QString CIN,QString Nom, QString Prenom,QString Mail,  QString Tel,QString Age)
{
    this->CIN = CIN;
    this->Nom = Nom;
    this->Prenom = Prenom;
    this->Mail = Mail;
   this->Tel = Tel;
    this->Age=Age;
}
bool Employee::ajouteremployee()
{
    QSqlQuery query;

    query.prepare("insert into Employeees (CIN, Nom, Prenom, Mail,  Tel, Age)" "values (:CIN, :Nom, :Prenom, :Mail, :Tel,:Age)");

    query.bindValue(":CIN",CIN);
    query.bindValue(":Nom",Nom);
    query.bindValue(":Prenom",Prenom);
    query.bindValue(":Mail",Mail);
    query.bindValue(":Tel",Tel);
    query.bindValue(":Age",Age);

    return query.exec();

}

QSqlQueryModel * Employee::afficherEMPLOYEE()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Employeees");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("MAIL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("TEL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("AGE"));


    return model;


}

bool Employee::modifierEMPLOYEE(QString CIN, QString Nom, QString Prenom, QString Mail, QString Tel,QString Age)
{
    QSqlQuery query;
    query.prepare("UPDATE Employeees SET CIN= :CIN,Nom= :Nom,Prenom= :Prenom,Mail= :Mail,Tel= :Tel,Age=:Age Where CIN= :CIN");
    query.bindValue(":CIN",CIN);
    query.bindValue(":Nom",Nom);
    query.bindValue(":Prenom",Prenom);
    query.bindValue(":Mail",Mail);
    query.bindValue(":Tel",Tel);
    query.bindValue(":Age",Age);
    return query.exec();
}

bool Employee::supprimerEMPLOYEE(QString CIN)
{
    QSqlQuery query;
    query.prepare("Delete from Employeees where CIN= :CIN");
    query.bindValue(":CIN",CIN);
    return query.exec();
}
QSqlQueryModel * Employee::cherchercinEMPLOYEE(QString CIN)
{
QSqlQueryModel * model = new QSqlQueryModel();
QSqlQuery query;
query.prepare("select * from Employeees WHERE CIN like '%"+CIN+"%'");

query.exec();
model ->setQuery(query);
model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("MAIL"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("TEL"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("AGE"));

return model;
}


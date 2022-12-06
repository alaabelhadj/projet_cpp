#ifndef EMPLOYEE_H
#define EMPLOYEE_H


#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include<qdatetimeedit.h>
#include<qdatetime.h>
#include <QVariant>
#include <QComboBox>

class Employee
{
    QString CIN,Nom,Prenom,Mail,Tel,Age;
public:
    Employee(){};
    Employee(QString,QString,QString,QString,QString,QString);

    QString getCIN(){return CIN;}
    QString getNom(){return Nom;};
    QString getPrenom(){return Prenom;}
    QString getMail(){return Mail;}
    QString getTel(){return Tel;}
    QString getAge(){return Age;}


    void setCIN (QString c ){CIN=c;}
    void setNom(QString n){Nom=n;}
    void setPrenom(QString p){Prenom=p;}
    void setMail(QString m){ Mail=m;}
    void setTel(QString t){Tel=t;}
    void setSalaire(QString a){Age=a;}


    bool ajouteremployee();
    QSqlQueryModel * afficherEMPLOYEE();
    bool modifierEMPLOYEE(QString,QString,QString,QString,QString,QString);
    bool supprimerEMPLOYEE(QString);
    QSqlQueryModel * cherchercinEMPLOYEE(QString CIN);

};

#endif // EMPLOYEE_H

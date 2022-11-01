#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string.h>
#include <iostream>
#include <QSqlQuery>
#include<QString>
#include <QObject>
#include<vector>
#include <QSqlQueryModel>
#include <list>
class customer
{
private :
    int number;
    QString name,lastname,address,email;

public:

    customer();

    customer(QString nom,QString prenom,QString mail,QString addres,int numero );

    bool ajout();
       QSqlQueryModel *afficher();
        bool modifier (int num);
        bool supprimer (int number);
};


#endif // CUSTOMER_H

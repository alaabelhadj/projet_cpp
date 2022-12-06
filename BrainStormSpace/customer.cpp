#include "customer.h"
#include <QString>

customer::customer()
{

}
customer::customer(QString nom,QString prenom,QString mail,QString addres,int numero)

{
        this->name=nom;
        this->lastname=prenom;

         this->email=mail;
         this->address=addres;
         this->number=numero;
    }
bool customer::ajout()

{
    QSqlQuery query;
        query.prepare("INSERT INTO customer (NAME,LAST_NAME,EMAIL,ADRESS,CIN_CLIENT) "
                    "VALUES (:name, :last_name, :email,:adress,:CIN_CLIENT)");
        query.bindValue(":name",name);
        query.bindValue(":last_name",lastname);
        query.bindValue(":email", email);
        query.bindValue(":adress",address );
        query.bindValue(":CIN_CLIENT", number);

    return query.exec();
}
QSqlQueryModel *customer::afficher()
{
QSqlQueryModel*model =new QSqlQueryModel();

     model->setQuery("SELECT* FROM customer ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("name"));
     model->setHeaderData(1, Qt::Horizontal,QObject::tr("last_name"));
     model->setHeaderData(2, Qt::Horizontal,QObject::tr("email"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("adress"));
     model->setHeaderData(4, Qt::Horizontal,QObject::tr("CIN_CLIENT"));

return model;
}
 bool customer::supprimer(int number)
{
     QSqlQuery query;
 QString num=QString::number(number);
     query.prepare("DELETE FROM customer where  CIN_CLIENT=:CIN_CLIENT");

     query.bindValue(":CIN_CLIENT",num );

 return query.exec();


}
 bool customer::modifier(int num){

     QSqlQuery query;
         QString res=QString::number(num);


           query.prepare("update customer""  set NAME=:name, LAST_NAME=:last_name, EMAIL=:email,ADRESS=:adress,CIN_CLIENT=:CIN_CLIENT where CIN_CLIENT ='"+res+"' ");


                 query.bindValue(":CIN_CLIENT", res);
                 query.bindValue(":name",name);
                 query.bindValue(":last_name",lastname);
                 query.bindValue(":email", email);
                 query.bindValue(":adress",address );


             return query.exec();

 }



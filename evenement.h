#ifndef EVENEMENT_H
#define EVENEMENT_H


#include <QString>
#include <string.h>
#include <iostream>
#include <QSqlQuery>

#include <QtDebug>
#include <QObject>
#include<vector>
#include <QSqlQueryModel>
#include <list>

class evenement
{
private:
    int ID_EVENEMENT,NBR_PARTICIPANT,PRIX;
   QString  NOM,TYPE,DATE_EVE,CIN_CLIENT;
public:
   evenement(){
       this->ID_EVENEMENT=0;
       this->NBR_PARTICIPANT=0;
       this->PRIX=0;
       this->NOM="";
       this->TYPE="";
       this->DATE_EVE="";
       this->CIN_CLIENT="";
   }
   evenement(int ID_EVENEMENT,int NBR_PARTICIPANT,int PRIX,QString NOM,QString TYPE,QString DATE_EVE,QString CIN_CLIENT)
   {
       this->ID_EVENEMENT=ID_EVENEMENT;
       this->NBR_PARTICIPANT=NBR_PARTICIPANT;
       this->PRIX=PRIX;
       this->NOM=NOM;
       this->TYPE=TYPE;
       this->DATE_EVE=DATE_EVE;
       this->CIN_CLIENT=CIN_CLIENT;
   }

    bool ajouter();
    bool modifier();
    QSqlQueryModel*  afficher();
    bool supprimer(int id);
    bool searsh_date(QString date_selected);

    QSqlQueryModel* historiqueByCin(QString);
    int get_ID_EVENEMENT(){return  ID_EVENEMENT;}
    int get_NBR_PARTICIPANT(){return  NBR_PARTICIPANT;}
    QString get_NOM(){return  NOM;}
    QString get_TYPE(){return  TYPE;}
    QString get_CIN(){return  CIN_CLIENT;}
    QSqlQueryModel *recherche(QString rech);
    void statistics(int tab[]);

};


#endif // EVENEMENT_H

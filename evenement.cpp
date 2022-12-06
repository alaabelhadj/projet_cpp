#include "evenement.h"
#include "QDate"
#include "QMessageBox"


bool evenement::ajouter()
{

   // QDate date=QDate::fromString(DATE_EVE,"dd-MM-yyyy");

    QSqlQuery query;
     query.prepare( "INSERT INTO EVENEMENT (ID_EVENEMENT, NOM, TYPE , DATE_EVE, PRIX, NBR_PARTICIPANT) "
                       "VALUES (:ID_EVENEMENT, :NOM, :TYPE , :DATE_EVE, :PRIX, :NBR_PARTICIPANT)" );
         query.bindValue(":ID_EVENEMENT",ID_EVENEMENT);
         query.bindValue(":NOM",NOM);
         query.bindValue(":TYPE",TYPE);
         query.bindValue(":DATE_EVE",DATE_EVE);
         query.bindValue(":PRIX",PRIX);
         query.bindValue(":NBR_PARTICIPANT",NBR_PARTICIPANT);

return query.exec();
}

bool evenement::modifier()
{

    QSqlQuery query;
   query.prepare( "UPDATE EVENEMENT SET ID_EVENEMENT=:ID_EVENEMENT , NOM=:NOM , TYPE=:TYPE , DATE_EVE=:DATE_EVE , PRIX=:PRIX ,"
                  " NBR_PARTICIPANT=:NBR_PARTICIPANT WHERE ID_EVENEMENT=:ID_EVENEMENT ");
   query.bindValue(":ID_EVENEMENT",ID_EVENEMENT);
   query.bindValue(":NOM",NOM);
   query.bindValue(":TYPE",TYPE);
   query.bindValue(":DATE_EVE",DATE_EVE);
   query.bindValue(":PRIX",PRIX);
   query.bindValue(":NBR_PARTICIPANT",NBR_PARTICIPANT);


return query.exec();
}



QSqlQueryModel* evenement::afficher()
{
 QSqlQueryModel *model = new QSqlQueryModel();

model->setQuery("select * from EVENEMENT order by ID_EVENEMENT ASC ");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EVENEMENT"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_EVE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("NBR_PARTICIPANT"));
return model;

}

bool evenement::supprimer(int id)
{
    QSqlQuery query;
         query.prepare(" Delete from evenement where ID_EVENEMENT=:ID_EVENEMENT");
         query.bindValue(0, id);

        return query.exec();
}


bool evenement::searsh_date(QString date_selected)
{
    QSqlQuery query;

    query.prepare("select ID_EVENEMENT,NOM,TYPE,NBR_PARTICIPANT from evenement where DATE_EVE='"+date_selected+"'");
      QMessageBox::information(nullptr,"test",date_selected);
      if(query.exec())
      {
          while(query.next())
          {
            ID_EVENEMENT=query.value(0).toInt();
            NOM = query.value(1).toString();
            TYPE = query.value(2).toString();
            NBR_PARTICIPANT = query.value(3).toInt();
          }

      }


}

QSqlQueryModel* evenement::historiqueByCin(QString date)
{

            QSqlQuery query;

         //query.bindValue(":CIN_CLIENT", CIN_CLIENT);
         QSqlQueryModel *model = new QSqlQueryModel();

        model->setQuery(" select * from evenement where DATE_EVE like '"+date+"%'");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EVENEMENT"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_EVE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("NBR_PARTICIPANT"));

         return model;
}
QSqlQueryModel * evenement::recherche(QString rech)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from EVENEMENT where ID_EVENEMENT like '%"+rech+"%' or NBR_PARTICIPANT like '%"+rech+"%' or PRIX like '%"+rech+"%'or NOM like '%"+rech+"%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_EVENEMENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NBR_PARTICIPANT"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRIX"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("NOM"));
    return model;
}

void evenement::statistics(int *tab)
{
    QSqlQuery query;
    query.prepare("select sum(PRIX) from EVENEMENT where DATE_EVE like '%2022' ");
    if(query.exec())
    {
        while (query.next())
        {

             tab[0]=query.value(0).toInt();
        }
    }

    QSqlQuery query1;
    query1.prepare("select sum(PRIX) from EVENEMENT where DATE_EVE like '%2021' ");
    if(query1.exec())
    {
        while (query1.next())
        {

             tab[1]=query1.value(0).toInt();
        }
    }

}

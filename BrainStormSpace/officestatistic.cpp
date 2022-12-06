#include "officestatistic.h"
#include "QSqlQuery"
int OfficeStatistic:: getEarnings()
{ int somme=0;
  QSqlQuery query;
  query.prepare("SELECT sum(price_office) FROM office ");
  if(query.exec())
    {
      while (query.next())
        {
          somme=query.value(0).toInt();
        }
    }
  return somme;
}
float OfficeStatistic:: getAvrage()
{ int somme=0;
  QSqlQuery query;
  query.prepare("SELECT avg(price_office) FROM office ");
  if(query.exec())
    {
      while (query.next())
        {
          somme=query.value(0).toInt();
        }
    }
  return somme;
}

int OfficeStatistic:: getAvailabiltyOn()
{
  int somme=0;
    QSqlQuery query;
    query.prepare("SELECT count(status_office) FROM office WHERE (status_office like 'available')  ");
    if(query.exec())
      {
        while (query.next())
          {
            somme=query.value(0).toInt();
          }
      }
    return somme;
}


int OfficeStatistic:: getAvailibiltyOff()
{
  int somme=0;
    QSqlQuery query;
    query.prepare("SELECT count(status_office) FROM office WHERE (status_office like 'not available')  ");
    if(query.exec())
      {
        while (query.next())
          {
            somme=query.value(0).toInt();
          }
      }
    return somme;
}
int OfficeStatistic::getOfficeFirstMonth(QString &name)
{
  int somme=0;

    QSqlQuery query ,query2;
    query.prepare("SELECT max(price_office) FROM office WHERE (date_office like '06/%')  ");
    if(query.exec())
      {
        while (query.next())
          {
            somme=query.value(0).toInt();
          }
         QString somme1= QString::number(somme);
          query2.prepare("SELECT name_office form office where price_office='"+somme1+"'");
          if(query.exec())
            {
              while (query.next())
                {
                 name=query2.value(0).toString();
                }
            }
      }
    return somme;
}
int OfficeStatistic::getOfficeSecondMonth(QString &name)
{int somme=0;
  QSqlQuery query,query2;
   query.prepare("SELECT max(price_office) FROM office WHERE (date_office like '07/%')  ");
  if(query.exec())
    { while (query.next())
        {
          somme=query.value(0).toInt();
        }
       QString somme1= QString::number(somme);
        query2.prepare("SELECT name_office form office where price_office='"+somme1+"'");
        if(query.exec())
          {
            while (query.next())
              {
               name=query2.value(0).toString();
              }
          }
    }
  return somme;}
int OfficeStatistic::getOfficeThirdMonth(QString &name)
{int somme=0;
  QSqlQuery query,query2;
  query.prepare("SELECT max(price_office) FROM office WHERE (date_office like '08/%')  ");
  if(query.exec())
    {
      while (query.next())
        {
          somme=query.value(0).toInt();
        }
       QString somme1= QString::number(somme);
        query2.prepare("SELECT name_office form office where price_office='"+somme1+"'");
        if(query.exec())
          {
            while (query.next())
              {
               name=query2.value(0).toString();
              }
          }
    }
  return somme;}

int OfficeStatistic::getOfficeFirstMonthWorst(QString &name)
{int somme=0;
  QSqlQuery query,query2;
  query.prepare("SELECT min(price_office) FROM office WHERE (date_office like '06/%')  ");
  if(query.exec())
    {
      while (query.next())
        {
          somme=query.value(0).toInt();
        }
       QString somme1= QString::number(somme);
        query2.prepare("SELECT name_office form office where price_office='"+somme1+"'");
        if(query.exec())
          {
            while (query.next())
              {
               name=query2.value(0).toString();
              }
          }
    }
  return somme;}
int OfficeStatistic::getOfficeSecondMonthWorst(QString &name)
{int somme=0;
  QSqlQuery query,query2;
  query.prepare("SELECT min(price_office) FROM office WHERE (date_office like '07/%')  ");
  if(query.exec())
    {
      while (query.next())
        {
          somme=query.value(0).toInt();
        }
       QString somme1= QString::number(somme);
        query2.prepare("SELECT name_office form office where price_office='"+somme1+"'");
        if(query.exec())
          {
            while (query.next())
              {
               name=query2.value(0).toString();
              }
          }
    }
  return somme;}


int OfficeStatistic::getOfficeThirdMonthWorst(QString &name)
{int somme=0;
  QSqlQuery query,query2;
  query.prepare("SELECT min(price_office) FROM office WHERE (date_office like '08/%')  ");
  if(query.exec())
    {
      while (query.next())
        {
          somme=query.value(0).toInt();
        }
       QString somme1= QString::number(somme);
        query2.prepare("SELECT name_office form office where price_office='"+somme1+"'");
        if(query.exec())
          {
            while (query.next())
              {
               name=query2.value(0).toString();
              }
          }
    }
  return somme;}



#include "reservation.h"
#include "QSqlQuery"
#include "mainwindow.h"
#include "list"
#include "QMessageBox"
#include <QDate>
Reservation::Reservation()
{
  this->id_office_reservation="";
  this->cin_client="";
  this->check_in_reservation="";
  this->check_out_reservation="";
  this->id_reservation="";
}
Reservation::Reservation(QString id_reservation,QString id_office_reservation,QString cin_client_reservation,QString check_in_reservation,QString check_out_reservation,QString name_office)
{
  this->id_reservation=id_reservation;
  this->id_office_reservation=id_office_reservation;
  this->cin_client=cin_client_reservation;
  this->check_in_reservation=check_in_reservation;
  this->check_out_reservation=check_out_reservation;
  this->name_office=name_office;

}

std::list<Reservation*>Reservation:: getAllOfficesReservation(){
        std::list<Reservation*> result ;
        QString name_office_reservation="";
        QSqlQuery query;

        query.exec("SELECT r.*, o.name_office FROM reservation r, Office o where r.id_office = o.id_office;");
        while (query.next())
       {

             QString check_in_reservation = query.value(1).toString();
             QString id_reservation = query.value(0).toString();
             QString cin_client_reservation =  query.value(4).toString();
             QString check_out_reservation = query.value(2).toString();
             QString id_office_reservation =  query.value(3).toString();
             name_office_reservation =  query.value(5).toString();
             Reservation * reservation = new Reservation(id_reservation,id_office_reservation,cin_client_reservation,check_in_reservation,check_out_reservation,name_office_reservation);
             result.insert(result.begin(), reservation);
        }

  return  result;
}
bool Reservation::deleteReservationById()
{
    QSqlQuery query;
    query.prepare("DELETE FROM reservation WHERE id_reservation=:id_reservation");
    query.bindValue(0,id_reservation);
    return query.exec();
}
bool Reservation::add_reservation_database()
{
  QDate Date=QDate::fromString(check_out_reservation,"dd-MM-yyyy");
  QDate Date2=QDate::fromString(check_in_reservation,"dd-MM-yyyy");
  QSqlQuery query;
  query.prepare("INSERT INTO reservation (id_reservation, check_in, check_out ,id_office, cin_reservation ) "
                "VALUES ( id_reservation.nextval, :check_in, :check_out,:id_office,:cin_reservation)");
  query.bindValue(":id_reservation",1);
  query.bindValue(":check_in",Date2);
  query.bindValue(":check_out",Date);
  query.bindValue(":id_office",id_office_reservation.toInt());
  query.bindValue(":cin_reservation",cin_client.toInt());
  QString slelect=(check_out_reservation);

  return query.exec();
}
bool Reservation::edit_reservation_database()
{
  QSqlQuery query;
  QDate Date=QDate::fromString(check_out_reservation,"dd-MM-yyyy");
  QDate Date2=QDate::fromString(check_in_reservation,"dd-MM-yyyy");
  query.prepare("UPDATE reservation SET  check_in=:check_in, check_out=:check_out ,cin_reservation=:cin_reservation WHERE id_reservation='"+id_reservation+"' "  );
  query.bindValue(":id_reservation",id_reservation);
  query.bindValue(":check_in",Date2);
  query.bindValue(":check_out",Date);
  query.bindValue(":id_office",id_office_reservation);
  query.bindValue(":cin_reservation",cin_client);

  return query.exec();
}

std::list<Reservation*> Reservation::date_check(QDate v_date1, QDate v_date2, std::list<Reservation*> reservation_list  )
{
        std::list<Reservation*> result ;

        QSqlQuery query;

        query.prepare("Select * from reservation  WHERE ((id_office='"+id_office_reservation+"') AND ( (check_in BETWEEN (:v_checkIn) AND (:v_checkOut)) OR (check_out BETWEEN (:v_checkIn) AND (:v_checkOut)) ))");
        query.bindValue(":v_checkIn",v_date1);
        query.bindValue(":v_checkOut",v_date2);
        QString check_in_reservation;
        query.exec();
         while (query.next())
        {
           check_in_reservation = query.value(1).toString();
           QString id_reservation = query.value(0).toString();
           QString cin_client_reservation =  query.value(4).toString();
           QString check_out_reservation = query.value(2).toString();
           QString id_office_reservation =  query.value(3).toString();

         Reservation * reservation = new Reservation(id_reservation,id_office_reservation,cin_client_reservation,check_in_reservation,check_out_reservation,"");
         result.insert(result.begin(), reservation);
        }
return  result;

}

std::list<Reservation*> Reservation::getReservationByOfficesId(QString id_office)
{

      std::list<Reservation*> result ;
      QSqlQuery query;
      query.exec("SELECT r.*, o.name_office FROM reservation r, Office o where r.id_office = o.id_office and  id_office='"+id_office+"'");
      while (query.next())
        {
            QString check_in_reservation = query.value(1).toString();
            QString id_reservation = query.value(0).toString();
            QString cin_client_reservation =  query.value(4).toString();
            QString check_out_reservation = query.value(2).toString();
            QString id_office_reservation =  query.value(3).toString();
            QString name_office_reservation= query.value(5).toString();
            Reservation * reservation = new Reservation(id_reservation,id_office_reservation,cin_client_reservation,check_in_reservation,check_out_reservation,name_office_reservation);
            result.insert(result.begin(), reservation);

        }
      return result;
}

std::list<Reservation*> Reservation::getSearchReservation(QString name)
{
      std::list<Reservation*> result ;
      QSqlQuery query;
      query.prepare("Select  * from reservation r , office o where r.id_office= o.id_office and o.name_office like'%"+name+"%'");
      if(query.exec())
      {
             while (query.next())
           {
               QString check_in_reservation = query.value(1).toString();
               QString id_reservation = query.value(0).toString();
               QString cin_client_reservation =  query.value(4).toString();
               QString check_out_reservation = query.value(2).toString();
               QString id_office_reservation =  query.value(3).toString();
               QString name_office_reservation =  query.value(6).toString();
               Reservation * reservation = new Reservation(id_reservation,id_office_reservation,cin_client_reservation,check_in_reservation,check_out_reservation,name_office_reservation);
               result.insert(result.begin(), reservation);
           }
       }
      return result;
}

bool Reservation::searchOfficeByName(QString namedonne)
{


  QSqlQuery query;
  QString select="Select  * from reservation r , office o where r.Id_office= o.id_office and o.name_office like'%"+namedonne+"%'";
  query.prepare(select);
  return query.exec();
}

bool Reservation::update_status(QString id_office)
{
    QSqlQuery query;
    query.prepare("update office set status_office= 'not available' where id_office='"+id_office+"';");
    return query.exec();
}

QString Reservation::getMonthcheck_in(QString id_office)
{

      QSqlQuery query;
      query.exec("select extract(month from check_in)from reservation where id_office='"+id_office+"' and  id_reservation='"+id_reservation+"'");
      QString check_in;
      while (query.next())
      {       check_in =query.value(0).toString();
              QString ch=""+check_in;
      }
      return check_in;
}
QString Reservation::getMonthcheck_out(QString id_office)
{

      QSqlQuery query;
      query.exec("select extract(month from check_out)from reservation where id_office='"+id_office+"'and  id_reservation='"+id_reservation+"'");
      QString check_in;
  while (query.next())
  {
      check_in =query.value(0).toString();
  }
  return check_in;
}

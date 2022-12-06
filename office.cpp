#include "office.h"
#include "QSqlQuery"
#include "QtDebug"
#include "QDebug"
#include "QObject"
#include"QMessageBox"
#include <mainwindow.h>
 Office::Office(QString idOffice,QString image,QString description,QString price,QString name,QString space,QString postion,QString status,QString type,QString date)
{
  this->idOffice=idOffice;
  this->image = image;
  this->description = description;
  this->price =price;
   this->postion=postion;
   this->space=space;
   this->name=name;
   this->status=status;
   this->type=type;
   this->date=date;
}

QString Office:: getImage()
{
  return this->image;
}
void  Office:: setImage(QString value)
{
  this->image = value;
}
QString  Office:: getDescription(){
  return this->description;
}
void  Office:: setDescription(QString value)
{
  this->description = value;
}
QString  Office:: getPrice()
{
  return this->price;
}
void  Office:: setPrice(QString value)
{
  this->price = value;
}

QString Office:: getIdOffice(){
  return this->idOffice;
}
void Office:: setIdOffice(QString value)
{
   this->idOffice = value;
}
void Office::setNameOffice(QString value)
{
  this->name=value;
}
QString Office::getNameOffice()
{
   return this->name;
}
QString Office::getPostionOffice()
{
   return this->postion;
}
void Office::setPositionOffice(QString value)
{
  this->postion=value;
}
QString Office::getSpaceOffice()
{
   return this->space;
}
void Office::setSpaceOffice(QString value)
{
  this->space=value;
}
QString Office::getStatusOffice(){
  return this->status;
}

void Office::setStatusOffice(QString value){
  this->status=value;
}

QString Office::getDateOffice(){
  return this->date;
}

void Office::setDateOffice(QString value){
  this->date=value;
}

QString Office::getTypeOffice(){
  return this->type;
}

void Office::setTypeOffice(QString value){
  this->type=value;
}


bool Office::add_office_database()
{
  QSqlQuery query;
  query.prepare("INSERT INTO office (id_office, name_office, description_office ,price_office, image_office, position_office, space_office, type_office , status_office , date_office ) "
                "VALUES ( id_office.nextval, :name_office, :description_office,:price_office,:image_office,:position_office,:space_office,:type_office,:status_office,:date_office)");
  query.bindValue(":name_office",name);
  query.bindValue(":description_office",description);
  query.bindValue(":price_office",price);
  query.bindValue(":image_office",image);
  query.bindValue(":position_office",postion);
  query.bindValue(":space_office",space);
  query.bindValue(":status_office",status);
  query.bindValue(":type_office",type);
  query.bindValue(":date_office",date);
  return query.exec();
}
bool Office::edit_office_database()
{
  QSqlQuery query;
  query.prepare("UPDATE office SET  name_office=:name_office, description_office=:description_office ,price_office=:price_office, image_office=:image_office, position_office=:position_office ,"
                " space_office=:space_office , type_office=:type_office, status_office=:status_office ,date_office=:date_office WHERE id_office='"+idOffice+"' "  );
  query.bindValue(":name_office",name);
  query.bindValue(":description_office",description);
  query.bindValue(":price_office",price);
  query.bindValue(":image_office",image);
  query.bindValue(":position_office",postion);
  query.bindValue(":space_office",space);
  query.bindValue(":status_office",status);
  query.bindValue(":type_office",type);
  query.bindValue(":date_office",date);
  return query.exec();
}
std::list<Office*> Office::getAllOffices(){
  std::list<Office*> result ;
  QSqlQuery query;
      query.exec("SELECT * FROM office");
      while (query.next()) {
            QString name = query.value(1).toString();

            QString officeID = query.value(0).toString();
            QString image =  query.value(4).toString();
           QString description = query.value(2).toString();
           QString price =  query.value(3).toString();
           QString position= query.value(5).toString();
           QString space= query.value(6).toString();
           QString status= query.value(8).toString();
           QString type= query.value(7).toString();
           QString date= query.value(9).toString();

           Office * office = new Office(officeID,image,description,price,name,space,position,status,type,date);
           result.insert(result.begin(), office);
        }
  return  result;
}
bool Office::deleteOfficeById()
{
    QSqlQuery query;
    query.prepare("DELETE FROM office WHERE id_office=:idOffice");
    query.bindValue(0,idOffice);
    return query.exec();
}
bool Office::searchOfficeByName(QString namedonne)
{

  QString s=name.at(0)+'%';
  QSqlQuery query;
  QString select="SELECT * FROM office WHERE name_office like '"+namedonne+"'";
  //QMessageBox::information(nullptr,"test",select);
  query.prepare(select);
  return query.exec();
}
bool Office::searchOfficeByWord(){
  QString s=name.at(0)+'%';
  QSqlQuery query;
  QString select="SELECT * FROM office WHERE name_office like '"+s+"'";
  //QMessageBox::information(nullptr,"test",select);
  query.prepare(select);
  return query.exec();
}
std::list<Office*> Office::getSearchOffices(QString namedonne){
  std::list<Office*> result ;
  QSqlQuery query;

      query.prepare("SELECT * FROM office where name_office like '%"+namedonne+"%'");
      if(query.exec()){
             while (query.next()) {
            QString name = query.value(1).toString();

            QString officeID = query.value(0).toString();
            QString image =  query.value(4).toString();
           QString description = query.value(2).toString();
           QString price =  query.value(3).toString();
           QString position= query.value(5).toString();;
           QString space= query.value(6).toString();;
           QString status= query.value(8).toString();
           QString type= query.value(7).toString();
           QString date= query.value(9).toString();

           Office * office = new Office(officeID,image,description,price,name,position,space,status,type,date);
            result.insert(result.begin(), office);
        }
        }
/* QString status;
  QString date;
  QString type;
  qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
  Office * office = new Office(id_office,image,description,price,name,position,space,status,type,date);

  Office stock(id_office,image,description,price,name,position,space,status,type,date);*/
  return  result;
}

std::list<Office*>Office:: getOfficesByPriceASC()
{
  std::list<Office*> result ;
  QSqlQuery query;
      query.exec("SELECT * FROM office ORDER BY PRICE_OFFICE ASC ");
      while (query.next())
        {
           QString name = query.value(1).toString();
           QString officeID = query.value(0).toString();
           QString image =  query.value(4).toString();
           QString description = query.value(2).toString();
           QString price =  query.value(3).toString();
           QString position= query.value(5).toString();;
           QString space= query.value(6).toString();;
           QString status= query.value(8).toString();
           QString type= query.value(7).toString();
           QString date= query.value(9).toString();

           Office * office = new Office(officeID,image,description,price,name,position,space,status,type,date);
            result.insert(result.begin(), office);
        }
  return  result;

}

std::list<Office*> Office:: getOfficesByPriceDESC()
{
  std::list<Office*> result ;
  QSqlQuery query;
      query.exec("SELECT * FROM office ORDER BY PRICE_OFFICE DESC ");
      while (query.next())
        {
           QString name = query.value(1).toString();
           QString officeID = query.value(0).toString();
           QString image =  query.value(4).toString();
           QString description = query.value(2).toString();
           QString price =  query.value(3).toString();
           QString position= query.value(5).toString();;
           QString space= query.value(6).toString();;
           QString status= query.value(8).toString();
           QString type= query.value(7).toString();
           QString date= query.value(9).toString();

           Office * office = new Office(officeID,image,description,price,name,position,space,status,type,date);
            result.insert(result.begin(), office);
        }
  return  result;

}
std::list<Office*> Office::  getOfficesByTypeOpen(){
  std::list<Office*> result ;
  QSqlQuery query;
  QString select="SELECT * FROM office WHERE type_office = 'open area'";
  //QMessageBox::information(nullptr,"test",select);
   query.prepare(select);
   query.exec();
   while (query.next())
     {
        QString name = query.value(1).toString();
        QString officeID = query.value(0).toString();
        QString image =  query.value(4).toString();
        QString description = query.value(2).toString();
        QString price =  query.value(3).toString();
        QString position= query.value(5).toString();;
        QString space= query.value(6).toString();;
        QString status= query.value(8).toString();
        QString type= query.value(7).toString();
        QString date= query.value(9).toString();

        Office * office = new Office(officeID,image,description,price,name,position,space,status,type,date);
         result.insert(result.begin(), office);
     }
return  result;


}

std::list<Office*> Office::  getOfficesByTypeClose()
{
  std::list<Office*> result ;
  QSqlQuery query;
  QString select="SELECT * FROM office WHERE type_office = 'office'";
  //QMessageBox::information(nullptr,"test",select);
   query.prepare(select);
   query.exec();
   while (query.next())
     {
        QString name = query.value(1).toString();
        QString officeID = query.value(0).toString();
        QString image =  query.value(4).toString();
        QString description = query.value(2).toString();
        QString price =  query.value(3).toString();
        QString position= query.value(5).toString();;
        QString space= query.value(6).toString();;
        QString status= query.value(8).toString();
        QString type= query.value(7).toString();
        QString date= query.value(9).toString();

        Office * office = new Office(officeID,image,description,price,name,position,space,status,type,date);
         result.insert(result.begin(), office);
     }
return  result;
}
std::list<Office*> Office::getOfficesByStatusAvailable()
{
  std::list<Office*> result ;
  QSqlQuery query;
  QString select="SELECT * FROM office WHERE status_office = 'available'";
  //QMessageBox::information(nullptr,"test",select);
   query.prepare(select);
   query.exec();
   while (query.next())
     {
        QString name = query.value(1).toString();
        QString officeID = query.value(0).toString();
        QString image =  query.value(4).toString();
        QString description = query.value(2).toString();
        QString price =  query.value(3).toString();
        QString position= query.value(5).toString();;
        QString space= query.value(6).toString();;
        QString status= query.value(8).toString();
        QString type= query.value(7).toString();
        QString date= query.value(9).toString();

        Office * office = new Office(officeID,image,description,price,name,position,space,status,type,date);
         result.insert(result.begin(), office);
     }
return  result;

}

std::list<Office*> Office:: getOfficesByStatusNotAvailable()
{
  std::list<Office*> result ;
  QSqlQuery query;
  QString select="SELECT * FROM office WHERE status_office = 'not available'";
  //QMessageBox::information(nullptr,"test",select);
   query.prepare(select);
   query.exec();
   while (query.next())
     {
        QString name = query.value(1).toString();
        QString officeID = query.value(0).toString();
        QString image =  query.value(4).toString();
        QString description = query.value(2).toString();
        QString price =  query.value(3).toString();
        QString position= query.value(5).toString();;
        QString space= query.value(6).toString();;
        QString status= query.value(8).toString();
        QString type= query.value(7).toString();
        QString date= query.value(9).toString();

        Office * office = new Office(officeID,image,description,price,name,position,space,status,type,date);
         result.insert(result.begin(), office);
     }
return  result;
}
std::list<Office*> Office:: getOfficesBySpaceDESC()
{
  std::list<Office*> result ;
  QSqlQuery query;
      query.exec("SELECT * FROM office ORDER BY SPACE_OFFICE DESC ");
      while (query.next())
        {
           QString name = query.value(1).toString();
           QString officeID = query.value(0).toString();
           QString image =  query.value(4).toString();
           QString description = query.value(2).toString();
           QString price =  query.value(3).toString();
           QString position = query.value(5).toString();;
           QString space = query.value(6).toString();;
           QString status = query.value(8).toString();
           QString type = query.value(7).toString();
           QString date = query.value(9).toString();

           Office * office = new Office(officeID,image,description,price,name,position,space,status,type,date);
            result.insert(result.begin(), office);
        }
  return  result;


}

std::list<Office*> Office:: getOfficesBySpaceASC()
{ std::list<Office*> result ;
  QSqlQuery query;
      query.exec("SELECT * FROM office ORDER BY SPACE_OFFICE ASC ");
      while (query.next())
        {
           QString name = query.value(1).toString();
           QString officeID = query.value(0).toString();
           QString image =  query.value(4).toString();
           QString description = query.value(2).toString();
           QString price =  query.value(3).toString();
           QString position= query.value(5).toString();;
           QString space= query.value(6).toString();;
           QString status= query.value(8).toString();
           QString type= query.value(7).toString();
           QString date= query.value(9).toString();

           Office * office = new Office(officeID,image,description,price,name,position,space,status,type,date);
            result.insert(result.begin(), office);
        }
  return  result;
}

std::list<Office*> Office:: getFiltredOffices(QString type,QString price,QString space,QString availabilty)
{
  std::list<Office*> result ;




  QSqlQuery query;
  QString select="SELECT * FROM office where type_office='"+type+"' and status_office='"+availabilty+"' ORDER BY price_office"+price+",space_office "+space+" ";
  //QMessageBox::information(nullptr,"test",select);
      query.exec(select);
      while (query.next())
        {
           QString name = query.value(1).toString();
           QString officeID = query.value(0).toString();
           QString image =  query.value(4).toString();
           QString description = query.value(2).toString();
           QString price =  query.value(3).toString();
           QString position= query.value(5).toString();;
           QString space= query.value(6).toString();;
           QString status= query.value(8).toString();
           QString type= query.value(7).toString();
           QString date= query.value(9).toString();

           Office * office = new Office(officeID,image,description,price,name,position,space,status,type,date);
            result.insert(result.begin(), office);
        }
  return  result;
}


Office  * Office:: getOfficeByID(QString id_office)
{
 Office  *office;
  QSqlQuery query;
      query.exec("SELECT * FROM office where id_office='"+id_office+"'");
      while (query.next())
        {
this->idOffice = query.value(0).toString();
this->date=query.value(9).toString();
this->image=query.value(4).toString();
this->status= query.value(8).toString();
this->space=query.value(6).toString();
this->type=query.value(7).toString();
this->price=query.value(3).toString();
this->postion= query.value(5).toString();
this->name=query.value(1).toString();
this->description=query.value(2).toString();

          office = new Office(idOffice,image,description,price,name,postion,space,status,type,date);
        }
//QMessageBox::information(nullptr,"test",query.value(2).toString());

  return  office;


}

bool Office::add_office_alarm()
{

  QSqlQuery query;
  QDate CurrantDate = QDate::currentDate();
  QDateTime currantTiem=QDateTime::currentDateTime();
  query.prepare("INSERT INTO ALARM (alarm_id, id_office,DATE_ACTIVATION,TIEM) "
                "VALUES ( alarm_id.nextval, :id_office,:DATE_ACTIVATION,:TIEM)");
  query.bindValue(":id_office",113);
  query.bindValue(":DATE_ACTIVATION",CurrantDate);
  query.bindValue(":TIEM",currantTiem.toString());
//QMessageBox::information(nullptr,"test",CurrantDate.toString());
  return query.exec();
}

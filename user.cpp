#include "user.h"
#include "QSqlQuery"
#include "QtDebug"
#include "QDebug"
#include "QObject"
User::User()
{ Id=0;
  Username="";
  Password="";
  Email="";
  Phone_Number=0;
}
User::User(QString username,QString password,QString email ,int phone_number)
{ //this->Id=id;
  this->Username=username;
  this->Password=password;
  this->Email=email;
  this->Phone_Number=phone_number;
}
bool User::Add_new(){
  QSqlQuery query;

  QString Phone_Number_string=QString::number(Phone_Number);

  query.prepare("INSERT INTO admin (user_id, user_name, password , phone_number, email) " "VALUES ( user_id.nextval, :user_name, :password ,:phone_number,:email)");

  query.bindValue(":user_name",Username);
  query.bindValue(":password",Password);
  query.bindValue(":phone_number",Phone_Number_string);
  query.bindValue(":email",Email);
  return query.exec();
}
bool User::login_user(QString user, QString password){
  QSqlQuery query;

          QString select ="select * from admin where user_name='"+user+"' and password='"+password+"'";

          query.prepare(select);
        if(query.exec())
        {
          int count=0;

           while(query.next())
           {
               count++;
           }
         printf("count: %d \n",count);
          if(count!=0)
          {
              return true;
          }
          else if(count==0)
          {
              return false;
          }

        }
}

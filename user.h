#ifndef USER_H
#define USER_H
#include "QSqlQueryModel"
#include"QString"
class User
{
private:
  int Id;
  int Phone_Number;
  QString Email;
  QString Username,Password;
public:
  User();
  User(QString,QString,QString,int);
  QString GetUsername(){return Username;}
  QString GetPassword(){return Password;}
  //int GetId(){return Id ;}
  int GetPhone_Number(){return Phone_Number;}
  QString GetEmail(){return Email;}
  //void SetId(int id){this->Id=id;}
  void SetUsername(QString username){this->Username=username;}
  void SetEmail(QString email){this->Email=email;}
  void SetPhone_Number(int phone_number){this->Phone_Number=phone_number;}
  void SetPassword(QString password){this->Password=password;}
  bool Add_new();
  bool login_user(QString user,QString password);
};

#endif // USER_H

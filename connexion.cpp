#include "connexion.h"

connexion::connexion()
{}

bool connexion::ouvrirConnexion(){
    db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("datasource");//inserer le nom de la source de donnÃ©es ODBC
    db.setUserName("system");//inserer nom de l'utilisateur
    db.setPassword("0000");//inserer mot de passe de cet utilisateur


if (db.open() == true){
    return true;
  }
else{
    return  false;
  }

}

void connexion::fermerConnexion()
{db.close();}

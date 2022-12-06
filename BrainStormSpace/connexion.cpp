#include "connexion.h"

connexion::connexion()
{}

bool connexion::ouvrirConnexion(){
    db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_2A");//inserer le nom de la source de donnÃ©es ODBC
    db.setUserName("system");//inserer nom de l'utilisateur
    db.setPassword("adminadmin");//inserer mot de passe de cet utilisateur


if (db.open() == true){
    return true;
  }
else{
    return  false;
  }

}

void connexion::fermerConnexion()
{db.close();}

#ifndef OFFICE_H
#define OFFICE_H
#include "QString"
#include "list"
class Office
{
public:
  Office(QString idOffice,QString image,QString description,QString price,QString name,QString space,QString postion,QString status,QString type,QString date);
  Office();

  QString getIdOffice();

  void setIdOffice(QString value);

  QString getImage();

  void setImage(QString value);

  QString getDescription();

  void setDescription(QString value);

  QString getPrice();

  void setPrice(QString value);

  QString getNameOffice();

  void setNameOffice(QString value);

  QString getPostionOffice();

  void setPositionOffice(QString value);

  QString getSpaceOffice();

  void setSpaceOffice(QString value);

  QString getStatusOffice();

  void setStatusOffice(QString value);

  QString getDateOffice();

  void setDateOffice(QString value);

  QString getTypeOffice();

  void setTypeOffice(QString value);

  bool edit_office_database();

  bool add_office_database();

  std::list<Office*> getAllOffices();

  std::list<Office*> getOfficesByPriceASC();

  std::list<Office*> getOfficesByPriceDESC();

  std::list<Office*> getOfficesByTypeOpen();

  std::list<Office*> getOfficesByTypeClose();

  std::list<Office*> getOfficesByStatusAvailable();

  std::list<Office*> getOfficesByStatusNotAvailable();

  std::list<Office*> getOfficesBySpaceDESC();

  std::list<Office*> getOfficesBySpaceASC();

  std::list<Office*> getFiltredOffices(QString,QString,QString,QString);

  bool deleteOfficeById();

  bool searchOfficeByName(QString namedonne);

  bool searchOfficeByWord();

  Office  * getOfficeByID(QString );

  std::list<Office*> getSearchOffices(QString namedonne);

  bool add_office_alarm();

private:
  QString idOffice;
  QString image;
  QString description;
  QString price;
  QString name;
  QString postion;
  QString space;
  QString status;
  QString type;
  QString date;

};

#endif // OFFICE_H

#ifndef POPUPMODEL_H
#define POPUPMODEL_H

#include <QWidget>

namespace Ui {
  class PopUpModel;
}

class PopUpModel : public QWidget
{
  Q_OBJECT

public:
  explicit PopUpModel(QWidget *parent = nullptr);
  ~PopUpModel();


  QString getIcon();
  QString getTitel();
  QString getDescription();
  void setIcon(QString icon);
  void setTitel(QString title);
  void setDescription(QString description);

private:
  Ui::PopUpModel *ui;
  QString icon;
  QString title;
  QString description;
};

#endif // POPUPMODEL_H

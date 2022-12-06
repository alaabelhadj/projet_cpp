#include "mainwindow.h"
#include "card.h"
#include "office.h"
#include "ui_mainwindow.h"
#include "officestatistic.h"
#include "QSqlDatabase"
#include "user.h"
#include"QSqlQuery"
#include "popupmodel.h"
#include"QString"
#include <cstring>
#include "reservation.h"
#include "availableofficecard.h"
#include "reservationcard.h"
#include "arduino.h"
#include "evenement.h"
#include "customer.h"
#include "webaxwidget.h"
#include "qrcode.h"
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include<QTextStream>
#include<QTextDocument>
#include <QSqlQueryModel>
#include "employee.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{

  ui->setupUi(this);
  //----------------------------------------------Arduino Inmplimentation-----------------------------

    int  ret=arduino.connect_arduino();
    switch(ret)
      {
        case(0):
                qDebug()<<"arduino is available and connected to :"<<arduino.getarduino_port_name();

        break;
      case(1):
              qDebug()<<"arduino is available but not  connected to :"<<arduino.getarduino_port_name();

      break;
      case(-1):
              qDebug()<<"arduino is available and connected to :";

      break;
      }
      QObject::connect(arduino.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
  //----------------------------------------------Fin Ardiuno----------------------------------------
  ui->BackgroundRM->setVisible(false);
  ui->QlineStatOffice->setStyleSheet("background-color:transparent;");
  ui->body->setCurrentIndex(0);
  ui->add_office_widget->setVisible(false);
  ui->id_wtf->setVisible(false);
  ui->pop_up_Sign_Up_STK->setVisible(false);
  ui->BackgroundEM->setVisible(false);
  ui->check_cercle_ASC->setVisible(false);
  ui->check_cercle_DESC->setVisible(false);
  ui->check_cercle_available->setVisible(false);
  ui->check_cercle_not_available->setVisible(false);
  ui->check_cercle_All->setVisible(true);
  ui->check_cercle_openArea->setVisible(false);
  ui->check_cercle_office->setVisible(false);
  ui->check_cercle_heighest->setVisible(false);
  ui->check_cercle_lowest->setVisible(false);
  ui->wornning1->setVisible(false);
  ui->BackgroundCM->setVisible(false);
  ui->BackgroundEEM->setVisible(false);
  ui->wornning2->setVisible(false);
  ui->id_prank->setVisible(true);
  ui->space_line_edit->setValidator(new QIntValidator(0,999999999,this));
  ui->Price_line_edit->setValidator(new QIntValidator(0,999999999,this));
  ui->space_line->setValidator(new QIntValidator(0,999999999,this));
  ui->Price_line->setValidator(new QIntValidator(0,999999999,this));
  ui->number_SingUp->setValidator(new QIntValidator(0,999999999,this));
  ui->check_cercle_ASC_2->setVisible(false);
  ui->check_cercle_DESC_2->setVisible(false);
  ui->test_on->setVisible(false);
  ui->test_off->setVisible(false);
  ui->check_cercle_available_2->setVisible(false);
  ui->check_cercle_not_available_2->setVisible(false);
  ui->check_cercle_All_2->setVisible(true);
  ui->check_cercle_openArea_2->setVisible(false);
  ui->check_cercle_office_2->setVisible(false);
  ui->check_cercle_heighest_2->setVisible(false);
  ui->check_cercle_lowest_2->setVisible(false);
 // ui->omg->setVisible(false);
  setReservation.erase(setReservation.begin(),setReservation.end());
  dataSet.erase(dataSet.begin(),dataSet.end()) ;
  qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
  qDeleteAll(ui->scrollAreaWidgetContents_7->findChildren<ReservationCard *>(QString(), Qt::FindDirectChildrenOnly));
  Office * office;
  dataSet = office->getAllOffices();
  DrawOfficeCard();
  update_label();



  //----------------------Integration avec Evenement tache-------------------------------------------------
  evenement e(0,0,0,"","","","");
   QSqlQueryModel *model =e.afficher();

      ui->Event_table_view->setModel(model);
  //----------------------Integration avec Evenement tache-------------------------------------------------

}

MainWindow::~MainWindow()
{
  delete ui;
}
//---------------Ardiuno------------------
void MainWindow::update_label()
{
  data=arduino.read_from_arduino();
  if(data=="1")
    {
      ui->test_on->setText("ON");
      Office *office;
      office->add_office_alarm();
      ui->add_office_widget->setVisible(true);
      Failed_PopUp("         Warnning your office is under attack");
      arduino.write_to_arduino("0");
    }
  else if(data=="0")
    {
     ui->test_off->setText("Off");
    }
  else if(data=="2")
    {
      ui->add_office_widget->setVisible(true);
      SuccessPopUp("        You Are Welcome to you r Office !!");
    }

}
void MainWindow:: on_open_clicked()
{
  arduino.write_to_arduino("1");
}

void MainWindow:: on_close_clicked()
{
  arduino.write_to_arduino("0");
}
//--------------------------------------------DrowFonction-----------------------------------
void MainWindow::DrawOfficeCard()
{

  std::list<Office*>::iterator it1;
  std::list<Office*>::iterator it;
  for (it = dataSet.begin(); it != dataSet.end(); ++it){
      Card *card = new Card();
      card->setOfficeID((*it)->getIdOffice());
      card->setNameOffice((*it)->getNameOffice());
      card->setOfficePrice((*it)->getPrice());
      card->setSpaceOffice((*it)->getSpaceOffice());
      card->setPositionOffice((*it)->getPostionOffice());
      card->setTypeOffice((*it)->getTypeOffice());
      card->setDateOffice((*it)->getDateOffice());
      card->setOfficeDescription((*it)->getDescription());
      card->setOfficeImage((*it)->getImage());
      card->setStatusOffice((*it)->getStatusOffice());

      connect(card,SIGNAL(sendData(Office)),this,SLOT(recieveData(Office)));
       ui->CardsLayout->addWidget(card);

    }

}
//-----------------------------------------Style Line Edit--------------------------------------------------------
void stylee(QLineEdit *e,QLabel *icone,QString url,QString styleSheet)
{
  e->setStyleSheet(styleSheet);
  QPixmap img(url);
  icone->clear();
  icone->setPixmap(img);
}
//----------------------------------------------SuccessPopUp-------------------------------------------------------------------------
void MainWindow:: SuccessPopUp(QString descrip)
{
  qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
  QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/success_icon.png";
  QString title="Success !";
  QString description=descrip;
  PopUpModel *pop = new PopUpModel();
  pop->setIcon(icon);
  pop->setTitel(title);
  pop->setDescription(description);
  ui->CardsLayout_2->addWidget(pop);
  ui->popup_stacked_widget->setCurrentIndex(1);
}
//---------------------------------------------FailedPopUp---------------------------------------------------------------------------
void MainWindow:: Failed_PopUp(QString descrip)
{
  qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
  QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/failed_icon.png";
  QString title="Failed !";
  QString description=descrip;
  PopUpModel *pop = new PopUpModel();
  pop->setIcon(icon);
  pop->setTitel(title);
  pop->setDescription(description);
  ui->CardsLayout_2->addWidget(pop);


  ui->popup_stacked_widget->setCurrentIndex(1);
}
//----------------------------------------------StyleDash-----------------------------------------------------------------------------
void MainWindow:: stylee_border(QPushButton *e,QLabel *icone,QString url,QString name)
{
  //QString url = R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeUsed.png)";
  QPixmap img(url);
  icone->clear();
  icone->setPixmap(img);
  QFont font = QFont (name);
  e->setFont(font);

}
//----------------------------------------------DrawReservationCard--------------------------------------------------------------------
void MainWindow::DrawReservationCard(){
std::list<Reservation*>::iterator it;
for (it = setReservation.begin(); it != setReservation.end(); ++it){
    ReservationCard *card = new ReservationCard();
    card->setIdReservation((*it)->getIdReservation());
    card->setIdOfficeReservation((*it)->getIdOfiiceReservation());
    card->setCINReservation((*it)->getCinClientReservation());
    card->setCheckInReservation((*it)->getCheckInReservation());
    card->setCheckOutReservation((*it)->getCheckOutReservation());
    card->setNameOfficeReservation((*it)->getNameOfficeReservation());
          connect(card,SIGNAL(sendDataReservation(Reservation)),this,SLOT(recieveDataReservation(Reservation)));

     ui->CardsLayout_4->addWidget(card);
  }
     ui->body->setCurrentIndex(4);
}
//----------------------------------------------------StyleForLineEdit-----------------------------------------------------------------
void MainWindow::on_office_Name_line_textChanged(const QString &arg1)
{
  stylee(ui->office_Name_line,ui->officeName_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nameOffice_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}
void MainWindow::on_office_Name_line_editingFinished()
{
  stylee(ui->office_Name_line,ui->officeName_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nameOffice_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}
void MainWindow::on_space_line_textChanged(const QString &arg1)
{
  stylee(ui->space_line,ui->space_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/space_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}
void MainWindow::on_space_line_editingFinished()
{
  stylee(ui->space_line,ui->space_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/space_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}
void MainWindow::on_position_line_textChanged(const QString &arg1)
{
stylee(ui->position_line,ui->position_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/position_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}
void MainWindow::on_position_line_editingFinished()
{
  stylee(ui->position_line,ui->position_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/position_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}
void MainWindow::on_Price_line_textChanged(const QString &arg1)
{
  stylee(ui->Price_line,ui->price_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/dollar_iconeBlue.png","border-bottom: 1.5px solid #4A8292;border-radius:unset;");
}
void MainWindow::on_Price_line_editingFinished()
{
    stylee(ui->Price_line,ui->price_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/dollar_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_type_line_textChanged(const QString &arg1)
{
   stylee(ui->type_line,ui->type_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/type_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_type_line_editingFinished()
{
  stylee(ui->type_line,ui->type_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/type_grey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_date_line_textChanged(const QString &arg1)
{
   stylee(ui->date_line,ui->date_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/date_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_date_line_editingFinished()
{
  stylee(ui->date_line,ui->date_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/date_grey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_description_line_textChanged(const QString &arg1)
{
  stylee(ui->description_line,ui->description_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/description_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}
void MainWindow::on_description_line_editingFinished()
{
  stylee(ui->description_line,ui->description_icone,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/description_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}
void MainWindow::on_Username_textChanged(const QString &arg1)
{
      stylee(ui->Username,ui->usernameIconeGrey,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}
void MainWindow::on_Username_editingFinished()
{
    stylee(ui->Username,ui->usernameIconeGrey,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_black_24dp.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_password_textChanged(const QString &arg1)
{
     ui->password->setStyleSheet("border-bottom: 1.5px solid #4A8292;");
}

void MainWindow::on_password_editingFinished()
{
     ui->password->setStyleSheet("border-bottom: 1.5px solid #d9d9d9;");
}
void MainWindow::on_Username_SingUp_textChanged(const QString &arg1)
{
  stylee(ui->Username_SingUp,ui->usernameIcone_SingUp,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_Username_SingUp_editingFinished()
{

  stylee(ui->Username_SingUp,ui->usernameIcone_SingUp,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_black_24dp.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}
void MainWindow::on_password_SingUp_textChanged(const QString &arg1)
{
   ui->password_SingUp->setStyleSheet("border-bottom: 1.5px solid #4A8292;");
}

void MainWindow::on_password_SingUp_editingFinished()
{
    ui->password_SingUp->setStyleSheet("border-bottom: 1.5px solid #d9d9d9;");
}
void MainWindow::on_email_SingUp_textChanged(const QString &arg1)
{

  stylee(ui->email_SingUp,ui->emailIcone_SingUp,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/email_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_email_SingUp_editingFinished()
{

  stylee(ui->email_SingUp,ui->emailIcone_SingUp,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/email_grey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}

void MainWindow::on_number_SingUp_textChanged(const QString &arg1)
{

  stylee(ui->number_SingUp,ui->numberIcone_SingUp,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/phone_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_number_SingUp_editingFinished()
{
  stylee(ui->number_SingUp,ui->numberIcone_SingUp,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/phone_grey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}
void MainWindow::on_office_Name_line_edit_textChanged(const QString &arg1)
{

  stylee(ui->office_Name_line_edit,ui->officeName_icone_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nameOffice_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_office_Name_line_edit_editingFinished()
{
  stylee(ui->office_Name_line_edit,ui->officeName_icone_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nameOffice_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}
//-------****************************************************
void MainWindow::on_space_line_edit_textChanged(const QString &arg1)
{
  stylee(ui->space_line_edit,ui->space_icone_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/space_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}
void MainWindow::on_space_line_edit_editingFinished()
{
  stylee(ui->space_line_edit,ui->space_icone_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/space_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}
void MainWindow::on_position_line_edit_textChanged(const QString &arg1)
{
stylee(ui->position_line_edit,ui->position_icone_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/position_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}
void MainWindow::on_position_line_edit_editingFinished()
{
  stylee(ui->position_line_edit,ui->position_icone_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/position_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}
void MainWindow::on_Price_line_edit_textChanged(const QString &arg1)
{
  stylee(ui->Price_line_edit,ui->price_icone_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/dollar_iconeBlue.png","border-bottom: 1.5px solid #4A8292;border-radius:unset;");
}
void MainWindow::on_Price_line_edit_editingFinished()
{
    stylee(ui->Price_line_edit,ui->price_icone_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/dollar_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_type_line_edit_textChanged(const QString &arg1)
{
   stylee(ui->type_line_edit,ui->type_icon_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/type_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_type_line_edit_editingFinished()
{
  stylee(ui->type_line_edit,ui->type_icon_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/type_grey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_date_line_edit_textChanged(const QString &arg1)
{
   stylee(ui->date_line_edit,ui->date_icon_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/date_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_date_line_edit_editingFinished()
{
  stylee(ui->date_line_edit,ui->date_icon_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/date_grey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_description_line_edit_textChanged(const QString &arg1)
{
  stylee(ui->description_line_edit,ui->description_icone_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/description_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}
void MainWindow::on_description_line_edit_editingFinished()
{
  stylee(ui->description_line_edit,ui->description_icone_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/description_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}
void MainWindow::on_Cin_LineEdit_textChanged(const QString &arg1)
{
  stylee(ui->Cin_LineEdit,ui->Cin_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nameOffice_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}
void MainWindow::on_Cin_LineEdit_editingFinished()
{
  stylee(ui->Cin_LineEdit,ui->Cin_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nameOffice_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}
void MainWindow::on_Cin_LineEdit_edit_textChanged(const QString &arg1)
{
  stylee(ui->Cin_LineEdit_edit,ui->Cin_icon_2,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nameOffice_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}
void MainWindow::on_Cin_LineEdit_edit_editingFinished()
{
  stylee(ui->Cin_LineEdit_edit,ui->Cin_icon_2,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nameOffice_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_Event_id_line_edit_textChanged(const QString &arg1)
{
stylee(ui->Event_id_line_edit,ui->event_id_icon_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nameOffice_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_Event_id_line_edit_editingFinished()
{
  stylee(ui->Event_id_line_edit,ui->event_id_icon_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nameOffice_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_Event_name_line_edit_textChanged(const QString &arg1)

{
  stylee(ui->Event_name_line_edit,ui->event_name_icon_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_name1.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_Event_name_line_edit_editingFinished()
{
  stylee(ui->Event_name_line_edit,ui->event_name_icon_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_name2.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_participant_line_edit_textChanged(const QString &arg1)
{
  stylee(ui->participant_line_edit,ui->event_participant_icon_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nbr_part_1.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_participant_line_edit_editingFinished()
{
  stylee(ui->participant_line_edit,ui->event_participant_icon_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nbr_part_2.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow:: on_price_event_line_edit_textChanged(const QString &arg1)
{
  stylee(ui->price_event_line_edit,ui->event_price_icon_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/dollar_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow:: on_price_event_line_edit_editingFinished()
{
  stylee(ui->price_event_line_edit,ui->event_price_icon_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/dollar_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow:: on_type_event_line_editt_textChanged(const QString &arg1)
{
  stylee(ui->type_event_line_editt,ui->type_event_icon_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/type_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow:: on_type_event_line_editt_editingFinished()
{
  stylee(ui->type_event_line_editt,ui->type_event_icon_edit,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/type_grey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}


//-------------------------------------
void MainWindow:: on_Event_id_line_add_textChanged(const QString &arg1)
{
  stylee(ui->Event_id_line_add,ui->event_id_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nameOffice_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow:: on_Event_id_line_add_editingFinished()
{
  stylee(ui->Event_id_line_add,ui->event_id_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nameOffice_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_Event_name_line_add_textChanged(const QString &arg1)
{
  stylee(ui->Event_name_line_add,ui->event_name_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_name1.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_Event_name_line_add_editingFinished()
{
  stylee(ui->Event_name_line_add,ui->event_name_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_name2.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_participant_line_add_textChanged(const QString &arg1)
{
  stylee(ui->participant_line_add,ui->event_participant_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nbr_part_1.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_participant_line_add_editingFinished()
{
  stylee(ui->participant_line_add,ui->event_participant_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/nbr_part_2.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_price_event_line_add_textChanged(const QString &arg1)
{
  stylee(ui->price_event_line_add,ui->event_price_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/dollar_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow:: on_price_event_line_add_editingFinished()
{
  stylee(ui->price_event_line_add,ui->event_price_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/dollar_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow:: on_type_event_line_textChanged(const QString &arg1)
{
  stylee(ui->type_event_line,ui->type_event_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/type_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow:: on_type_event_line_editingFinished()
{
  stylee(ui->type_event_line,ui->type_event_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/type_grey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}


void MainWindow:: on_name_client_line_add_textChanged(const QString &arg1)
{ stylee(ui->name_client_line_add,ui->name_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/name_1.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}
void MainWindow::on_name_client_line_add_editingFinished()
{ stylee(ui->name_client_line_add,ui->name_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/name_2.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}
void MainWindow::on_Last_name_client_line_add_textChanged(const QString &arg1)
{ stylee(ui->Last_name_client_line_add,ui->lastname_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/last_name_1.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_Last_name_client_line_add_editingFinished()
{ stylee(ui->Last_name_client_line_add,ui->lastname_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/last_name_2.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_email_line_add_textChanged(const QString &arg1)
{ stylee(ui->email_line_add,ui->email_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_email_line_add_editingFinished()
{ stylee(ui->email_line_add,ui->email_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_black_24dp.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_adress_line_add_textChanged(const QString &arg1)
{ stylee(ui->adress_line_add,ui->adress_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/position_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_adress_line_add_editingFinished()
{ stylee(ui->adress_line_add,ui->adress_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/position_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_Cin_client_line_add_textChanged(const QString &arg1)
{ stylee(ui->Cin_client_line_add,ui->cin_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/cin_2.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_Cin_client_line_add_editingFinished()
{ stylee(ui->Cin_client_line_add,ui->cin_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/cin_1.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_Cin_client_line_edit_textChanged(const QString &arg1)
{
  stylee(ui->Cin_client_line_edit,ui->cin_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/cin_2.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_Cin_client_line_edit_editingFinished()
{
  stylee(ui->Cin_client_line_edit,ui->cin_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/cin_1.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_name_client_line_edit_textChanged(const QString &arg1)
{
  stylee(ui->name_client_line_edit,ui->name_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/name_1.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_name_client_line_edit_editingFinished()
{
  stylee(ui->name_client_line_edit,ui->name_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/name_2.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}

void MainWindow::on_Last_name_client_line_edit_textChanged(const QString &arg1)
{
  stylee(ui->Last_name_client_line_edit,ui->lastname_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/last_name_1.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_Last_name_client_line_edit_editingFinished(){
  stylee(ui->Last_name_client_line_edit,ui->lastname_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/last_name_2.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_email_client_line_edit_textChanged(const QString &arg1)
{
  stylee(ui->email_client_line_edit,ui->email_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow::on_email_client_line_edit_editingFinished(){
  stylee(ui->email_client_line_edit,ui->email_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_black_24dp.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_adress_line_edit_textChanged(const QString &arg1){
  stylee(ui->adress_line_edit,ui->adress_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/position_iconeBlue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow:: on_adress_line_edit_editingFinished(){
  stylee(ui->adress_line_edit,ui->adress_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/position_iconeGrey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}
void MainWindow:: on_Cin_client_line_delete_textChanged(const QString &arg1){
   stylee(ui->Cin_client_line_delete,ui->cin_delete_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/cin_2.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow:: on_Cin_client_line_delete_editingFinished(){
  stylee(ui->Cin_client_line_delete,ui->cin_delete_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/cin_1.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}

//----------Fonctions---------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_visibilityBtn_clicked()
{
  if(ui->checkBox->isTristate() == true){
      ui->visibilityBtn->setStyleSheet("background-image: url('C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/visibility.png');background-repeat: no-repeat;");
      ui->password->setEchoMode(QLineEdit::Normal);
  }else{
      ui->visibilityBtn->setStyleSheet("background-image: url('C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/visibilityOff.png');background-repeat: no-repeat;");
    ui->password->setEchoMode(QLineEdit::Password);
    }
  ui->checkBox->setTristate(!ui->checkBox->isTristate());
}

void MainWindow::on_SingUpBtn_clicked()
{
    ui->loginForm->setCurrentIndex(1);
}

void MainWindow::on_visibilityBtn_SingUp_clicked()
{
  if(ui->checkBox_SingUp->isTristate() == true){
      ui->visibilityBtn_SingUp->setStyleSheet("background-image: url('C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/visibility.png');background-repeat: no-repeat;");
      ui->password_SingUp->setEchoMode(QLineEdit::Normal);
  }else{
      ui->visibilityBtn_SingUp->setStyleSheet("background-image: url('C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/visibilityOff.png');background-repeat: no-repeat;");
    ui->password_SingUp->setEchoMode(QLineEdit::Password);
    }
  ui->checkBox_SingUp->setTristate(!ui->checkBox_SingUp->isTristate());
}


void MainWindow::on_SingUpBtn_3_clicked()
{
    ui->loginForm->setCurrentIndex(0);
}

void MainWindow::on_LoginButton_clicked()
{
  QString user=ui->Username->text();
      QString password=ui->password->text();
      QSqlQuery query;
       User P1;
       bool login , check=true;
       login=P1.login_user(user,password);
      if(login)
      {
          ui->mainWidget->setCurrentIndex(1);
          check=false;
          dataSet.erase(dataSet.begin(),dataSet.end()) ;
          qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
          Office * office;
          dataSet = office->getAllOffices();
          DrawOfficeCard();
      }
      else
        {
          check=true;
        }
      if(check){
          arduino.write_to_arduino("2");
          ui->pop_up_Sign_Up_STK->setVisible(true);
          qDeleteAll(ui->scrollAreaWidgetContents_3->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
          ui->popup_stacked_widget_2->setCurrentIndex(1);
          QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/failed_icon.png";
          QString title="  Failed !";
          QString description="The UserName Or Password Are Not Correct  !!";
          PopUpModel *pop = new PopUpModel();
          pop->setIcon(icon);
          pop->setTitel(title);
          pop->setDescription(description);
          ui->CardsLayout_3->addWidget(pop);
        }
      else{
          ui->Login->setVisible(false);
          ui->pop_up_Sign_Up_STK->setVisible(false);
        }
}
void MainWindow:: on_logout_clicked()
{
      ui->mainWidget->setCurrentIndex(0);
      ui->pop_up_Sign_Up_STK->setVisible(false);


}
//------------------------------------------------------------------------------------------------------Styling button clicked dashBord-----------------
void MainWindow::on_Reservation_Btn_clicked()
{
  ui->BackgroundRM->setVisible(true);
  ui->BackgroundOM->setVisible(false);
  ui->BackgroundEM->setVisible(false);
  ui->BackgroundCM->setVisible(false);
  ui->BackgroundEEM->setVisible(false);
  ui->body->setCurrentIndex(4);
  stylee_border(ui->Reservation_Btn,ui->Reservation_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_used.png)","Segoe UI ");
   stylee_border(ui->Display_offices_Reservation_btn,ui->display_offices_icone_res,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUsed.png)","Segoe UI ");
  stylee_border(ui->Display_offices_Btn,ui->display_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
   stylee_border(ui->Statistics_offices_Btn,ui->statistics_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUnused.png)","Segoe UI Light");
   stylee_border(ui->Office_Btn,ui->office_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeAnusued.png)","Segoe UI Light");
   stylee_border(ui->Event_Btn,ui->Event_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->display_event_btn,ui->Event_Display_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_event_grey.png)","Segoe UI Light");
   stylee_border(ui->Event_history_Btn,ui->Event_history_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_history_grey.png)","Segoe UI Light");
   stylee_border(ui->Client_Managment_Btn,ui->Client_Managment_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Display_Client_Btn,ui->Display_client_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Employe_Btn,ui->Employe_mangement_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_employe_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->Display_employe_Btn,ui->Display_employe_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/employe_grey_icon.png)","Segoe UI Light");

    setReservation.erase(setReservation.begin(),setReservation.end()) ;
    qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
    qDeleteAll(ui->scrollAreaWidgetContents_7->findChildren<ReservationCard *>(QString(), Qt::FindDirectChildrenOnly));
    Reservation * reservation;
    setReservation = reservation->getAllOfficesReservation();
    DrawReservationCard();

}
void MainWindow:: on_Display_offices_Reservation_btn_clicked()
{
  ui->BackgroundRM->setVisible(true);
  ui->BackgroundOM->setVisible(false);
  ui->BackgroundEM->setVisible(false);
  ui->BackgroundCM->setVisible(false);
  ui->BackgroundEEM->setVisible(false);
  ui->body->setCurrentIndex(4);
   stylee_border(ui->Reservation_Btn,ui->Reservation_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_used.png)","Segoe UI ");
   stylee_border(ui->Display_offices_Reservation_btn,ui->display_offices_icone_res,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUsed.png)","Segoe UI ");
   stylee_border(ui->Display_offices_Btn,ui->display_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
   stylee_border(ui->Statistics_offices_Btn,ui->statistics_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUnused.png)","Segoe UI Light");
   stylee_border(ui->Office_Btn,ui->office_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeAnusued.png)","Segoe UI Light");
   stylee_border(ui->Event_Btn,ui->Event_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->display_event_btn,ui->Event_Display_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_event_grey.png)","Segoe UI Light");
   stylee_border(ui->Event_history_Btn,ui->Event_history_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_history_grey.png)","Segoe UI Light");
   stylee_border(ui->Client_Managment_Btn,ui->Client_Managment_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Display_Client_Btn,ui->Display_client_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Employe_Btn,ui->Employe_mangement_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_employe_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->Display_employe_Btn,ui->Display_employe_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/employe_grey_icon.png)","Segoe UI Light");
  //---------------------------------------------------------------------------------------------------


  setReservation.erase(setReservation.begin(),setReservation.end()) ;
  qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
  qDeleteAll(ui->scrollAreaWidgetContents_7->findChildren<ReservationCard *>(QString(), Qt::FindDirectChildrenOnly));
  Reservation * reservation;
  setReservation = reservation->getAllOfficesReservation();
  std::list<Reservation*>::iterator it1;
  std::list<Reservation*>::iterator it;

  for (it = setReservation.begin(); it != setReservation.end(); ++it){
 ReservationCard *card = new ReservationCard();
      card->setIdReservation((*it)->getIdReservation());
      card->setIdOfficeReservation((*it)->getIdOfiiceReservation());
      card->setCINReservation((*it)->getCinClientReservation());
      card->setCheckInReservation((*it)->getCheckInReservation());
      card->setCheckOutReservation((*it)->getCheckOutReservation());
      card->setNameOfficeReservation((*it)->getNameOfficeReservation());

            connect(card,SIGNAL(sendDataReservation(Reservation)),this,SLOT(recieveDataReservation(Reservation)));

       ui->CardsLayout_4->addWidget(card);

    }

}
void MainWindow:: on_Event_history_Btn_clicked()
{
  ui->BackgroundRM->setVisible(false);
  ui->BackgroundOM->setVisible(false);
  ui->BackgroundEM->setVisible(true);
  ui->BackgroundCM->setVisible(false);
  ui->BackgroundEEM->setVisible(false);
  ui->body->setCurrentIndex(6);
   stylee_border(ui->Display_offices_Btn,ui->display_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
   stylee_border(ui->Statistics_offices_Btn,ui->statistics_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUnused.png)","Segoe UI Light");
   stylee_border(ui->Reservation_Btn,ui->Reservation_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_unused.png)","Segoe UI Light");
   stylee_border(ui->Office_Btn,ui->office_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeAnusued.png)","Segoe UI Light");
   stylee_border(ui->Display_offices_Reservation_btn,ui->display_offices_icone_res,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
   stylee_border(ui->Event_Btn,ui->Event_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_white_icon.png)","Segoe UI");
   stylee_border(ui->display_event_btn,ui->Event_Display_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_event_grey.png)","Segoe UI Light");
   stylee_border(ui->Event_history_Btn,ui->Event_history_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_history_white.png)","Segoe UI ");
   stylee_border(ui->Client_Managment_Btn,ui->Client_Managment_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Display_Client_Btn,ui->Display_client_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Employe_Btn,ui->Employe_mangement_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_employe_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->Display_employe_Btn,ui->Display_employe_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/employe_grey_icon.png)","Segoe UI Light");
   evenement e(0,0,0,"","","","");
    QSqlQueryModel *model =e.afficher();

       ui->tableView_historique->setModel(model);
       ui->tableView_historique->setModel(model);
       QBarSet *set0=new QBarSet("Levels");


                *set0 <<6<<5<<4<<3<<2<<0<<1;


                QBarSeries *Series=new QBarSeries();
                Series->append(set0);


                QChart *chart=new QChart();
                chart->addSeries(Series);
                chart->setTitle("Prices");
                //no animation
                chart->setAnimationOptions(QChart::AllAnimations);
                QStringList categories;
                categories<<"2013"<<"2014"<<"2015"<<"2016"<<"2017";
               QBarCategoryAxis *axis=new  QBarCategoryAxis();
               axis->append(categories);
               chart->createDefaultAxes();
               //chart->setAxisX(axis,Series);
               chart->legend()->setVisible(true);
               chart->legend()->setAlignment(Qt::AlignBottom);


               QChartView *chartview=new QChartView(chart) ;
               chartview->setRenderHint(QPainter::Antialiasing);

               QVBoxLayout *layout2 = new QVBoxLayout(ui->QBarAxe);
               layout2->addWidget(chartview);
}
void MainWindow:: on_display_event_btn_clicked()
{
  ui->BackgroundRM->setVisible(false);
  ui->BackgroundOM->setVisible(false);
  ui->BackgroundEM->setVisible(true);
  ui->BackgroundCM->setVisible(false);
  ui->BackgroundEEM->setVisible(false);
  ui->body->setCurrentIndex(5);
   stylee_border(ui->Display_offices_Btn,ui->display_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
   stylee_border(ui->Statistics_offices_Btn,ui->statistics_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUnused.png)","Segoe UI Light");
   stylee_border(ui->Reservation_Btn,ui->Reservation_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_unused.png)","Segoe UI Light");
   stylee_border(ui->Office_Btn,ui->office_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeAnusued.png)","Segoe UI Light");
   stylee_border(ui->Display_offices_Reservation_btn,ui->display_offices_icone_res,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
   stylee_border(ui->Event_Btn,ui->Event_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_white_icon.png)","Segoe UI");
   stylee_border(ui->display_event_btn,ui->Event_Display_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_event_white.png)","Segoe UI");
   stylee_border(ui->Event_history_Btn,ui->Event_history_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_history_grey.png)","Segoe UI Light");
   stylee_border(ui->Client_Managment_Btn,ui->Client_Managment_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Display_Client_Btn,ui->Display_client_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Employe_Btn,ui->Employe_mangement_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_employe_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->Display_employe_Btn,ui->Display_employe_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/employe_grey_icon.png)","Segoe UI Light");
   evenement e(0,0,0,"","","","");
    QSqlQueryModel *model =e.afficher();

       ui->Event_table_view->setModel(model);
       ui->Event_table_view->setModel(model);
       ui->id_value->setText("");
       ui->name_value->setText("");
       ui->participant_number_value->setText("");
       ui->type_value->setText("");
}

void MainWindow:: on_Event_Btn_clicked()
{

  ui->BackgroundRM->setVisible(false);
  ui->BackgroundOM->setVisible(false);
  ui->BackgroundEM->setVisible(true);
  ui->BackgroundCM->setVisible(false);
  ui->BackgroundEEM->setVisible(false);
  ui->body->setCurrentIndex(5);
   stylee_border(ui->Display_offices_Btn,ui->display_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
   stylee_border(ui->Statistics_offices_Btn,ui->statistics_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUnused.png)","Segoe UI Light");
   stylee_border(ui->Reservation_Btn,ui->Reservation_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_unused.png)","Segoe UI Light");
   stylee_border(ui->Office_Btn,ui->office_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeAnusued.png)","Segoe UI Light");
   stylee_border(ui->Display_offices_Reservation_btn,ui->display_offices_icone_res,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
   stylee_border(ui->Event_Btn,ui->Event_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_white_icon.png)","Segoe UI");
   stylee_border(ui->display_event_btn,ui->Event_Display_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_event_white.png)","Segoe UI");
   stylee_border(ui->Event_history_Btn,ui->Event_history_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_history_grey.png)","Segoe UI Light");
   stylee_border(ui->Client_Managment_Btn,ui->Client_Managment_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Display_Client_Btn,ui->Display_client_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Employe_Btn,ui->Employe_mangement_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_employe_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->Display_employe_Btn,ui->Display_employe_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/employe_grey_icon.png)","Segoe UI Light");
   evenement e(0,0,0,"","","","");
    QSqlQueryModel *model =e.afficher();

       ui->Event_table_view->setModel(model);
       ui->id_value->setText("");
       ui->name_value->setText("");
       ui->participant_number_value->setText("");
       ui->type_value->setText("");
}
void MainWindow::on_Office_Btn_clicked()
{

  ui->BackgroundRM->setVisible(false);
  ui->BackgroundOM->setVisible(true);
  ui->BackgroundEM->setVisible(false);
  ui->BackgroundCM->setVisible(false);
  ui->BackgroundEEM->setVisible(false);
  ui->body->setCurrentIndex(0);
   stylee_border(ui->Display_offices_Btn,ui->display_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUsed.png)","Segoe UI ");
   stylee_border(ui->Statistics_offices_Btn,ui->statistics_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUnused.png)","Segoe UI Light");
   stylee_border(ui->Reservation_Btn,ui->Reservation_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_unused.png)","Segoe UI Light");
   stylee_border(ui->Office_Btn,ui->office_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeUsed.png)","Segoe UI");
   stylee_border(ui->Display_offices_Reservation_btn,ui->display_offices_icone_res,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
   stylee_border(ui->Event_Btn,ui->Event_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->display_event_btn,ui->Event_Display_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_event_grey.png)","Segoe UI Light");
   stylee_border(ui->Event_history_Btn,ui->Event_history_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_history_grey.png)","Segoe UI Light");
   stylee_border(ui->Employe_Btn,ui->Employe_mangement_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_employe_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->Display_employe_Btn,ui->Display_employe_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/employe_grey_icon.png)","Segoe UI Light");
    //Creation des cards
    setReservation.erase(setReservation.begin(),setReservation.end());
    dataSet.erase(dataSet.begin(),dataSet.end()) ;
    qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
    qDeleteAll(ui->scrollAreaWidgetContents_7->findChildren<ReservationCard *>(QString(), Qt::FindDirectChildrenOnly));
    Office * office;
    dataSet = office->getAllOffices();

    DrawOfficeCard();
}

void MainWindow:: on_Client_Managment_Btn_clicked()
{
  ui->BackgroundRM->setVisible(false);
  ui->BackgroundOM->setVisible(false);
  ui->BackgroundCM->setVisible(true);
  ui->BackgroundEM->setVisible(false);
  ui->BackgroundEEM->setVisible(false);
  ui->body->setCurrentIndex(7);
   stylee_border(ui->Display_offices_Btn,ui->display_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUsed.png)","Segoe UI Light ");
   stylee_border(ui->Statistics_offices_Btn,ui->statistics_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUnused.png)","Segoe UI Light");
   stylee_border(ui->Reservation_Btn,ui->Reservation_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_unused.png)","Segoe UI Light");
   stylee_border(ui->Office_Btn,ui->office_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeUsed.png)","Segoe UI Light");
   stylee_border(ui->Display_offices_Reservation_btn,ui->display_offices_icone_res,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
   stylee_border(ui->Event_Btn,ui->Event_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->display_event_btn,ui->Event_Display_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_event_grey.png)","Segoe UI Light");
   stylee_border(ui->Event_history_Btn,ui->Event_history_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_history_grey.png)","Segoe UI Light");
   stylee_border(ui->Client_Managment_Btn,ui->Client_Managment_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/client_white_icon.png)","Segoe UI ");
   stylee_border(ui->Display_Client_Btn,ui->Display_client_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_client_white_icon.png)","Segoe UI ");
   stylee_border(ui->Employe_Btn,ui->Employe_mangement_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_employe_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->Display_employe_Btn,ui->Display_employe_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/employe_grey_icon.png)","Segoe UI Light");
   QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                          QCoreApplication::organizationName(), QCoreApplication::applicationName());

       ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
       ui->table_client->setModel(tmp.afficher());

      //----------------------------Pie---------------
       QPieSeries *series1 = new QPieSeries();

       series1->append("local",250);

       series1->append("foreign",60);

       QChart * chart1=new QChart();

       chart1->addSeries(series1);

       chart1->setTitle("stats");

       QChartView * chartView1=new QChartView(chart1);

       chartView1->setRenderHints(QPainter::Antialiasing);
       QVBoxLayout *layout1 = new QVBoxLayout(ui->pie_client);
       layout1->addWidget(chartView1);

}

void MainWindow:: on_Display_Client_Btn_clicked()
{

  ui->BackgroundRM->setVisible(false);
  ui->BackgroundOM->setVisible(false);
  ui->BackgroundCM->setVisible(true);
  ui->BackgroundEM->setVisible(false);
  ui->BackgroundEEM->setVisible(false);
  ui->body->setCurrentIndex(7);
   stylee_border(ui->Display_offices_Btn,ui->display_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUsed.png)","Segoe UI Light ");
   stylee_border(ui->Statistics_offices_Btn,ui->statistics_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUnused.png)","Segoe UI Light");
   stylee_border(ui->Reservation_Btn,ui->Reservation_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_unused.png)","Segoe UI Light");
   stylee_border(ui->Office_Btn,ui->office_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeUsed.png)","Segoe UI Light");
   stylee_border(ui->Display_offices_Reservation_btn,ui->display_offices_icone_res,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
   stylee_border(ui->Event_Btn,ui->Event_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->display_event_btn,ui->Event_Display_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_event_grey.png)","Segoe UI Light");
   stylee_border(ui->Event_history_Btn,ui->Event_history_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_history_grey.png)","Segoe UI Light");
   stylee_border(ui->Client_Managment_Btn,ui->Client_Managment_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/client_white_icon.png)","Segoe UI ");
   stylee_border(ui->Display_Client_Btn,ui->Display_client_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_client_white_icon.png)","Segoe UI ");
   stylee_border(ui->Employe_Btn,ui->Employe_mangement_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_employe_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->Display_employe_Btn,ui->Display_employe_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/employe_grey_icon.png)","Segoe UI Light");
   QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                          QCoreApplication::organizationName(), QCoreApplication::applicationName());

       ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
       ui->table_client->setModel(tmp.afficher());

      //----------------------------Pie---------------
       QPieSeries *series1 = new QPieSeries();

       series1->append("local",250);

       series1->append("foreign",60);

       QChart * chart1=new QChart();

       chart1->addSeries(series1);

       chart1->setTitle("stats");

       QChartView * chartView1=new QChartView(chart1);

       chartView1->setRenderHints(QPainter::Antialiasing);
       QVBoxLayout *layout1 = new QVBoxLayout(ui->pie_client);
       layout1->addWidget(chartView1);

}
void MainWindow:: on_Employe_Btn_clicked()
{
  ui->BackgroundRM->setVisible(false);
  ui->BackgroundOM->setVisible(false);
  ui->BackgroundCM->setVisible(false);
  ui->BackgroundEM->setVisible(false);
  ui->BackgroundEEM->setVisible(true);
  ui->body->setCurrentIndex(8);
   stylee_border(ui->Display_offices_Btn,ui->display_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUsed.png)","Segoe UI Light ");
   stylee_border(ui->Statistics_offices_Btn,ui->statistics_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUnused.png)","Segoe UI Light");
   stylee_border(ui->Reservation_Btn,ui->Reservation_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_unused.png)","Segoe UI Light");
   stylee_border(ui->Office_Btn,ui->office_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeUsed.png)","Segoe UI Light");
   stylee_border(ui->Display_offices_Reservation_btn,ui->display_offices_icone_res,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
   stylee_border(ui->Event_Btn,ui->Event_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->display_event_btn,ui->Event_Display_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_event_grey.png)","Segoe UI Light");
   stylee_border(ui->Event_history_Btn,ui->Event_history_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_history_grey.png)","Segoe UI Light");
   stylee_border(ui->Client_Managment_Btn,ui->Client_Managment_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Display_Client_Btn,ui->Display_client_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Employe_Btn,ui->Employe_mangement_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_employe_white_icon.png)","Segoe UI");
   stylee_border(ui->Display_employe_Btn,ui->Display_employe_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/employe_white_icon.png)","Segoe UI");
    ui->tableView_employee->setModel(tempemployee.afficherEMPLOYEE());
}

void MainWindow:: on_Display_employe_Btn_clicked()
{
  ui->BackgroundRM->setVisible(false);
  ui->BackgroundOM->setVisible(false);
  ui->BackgroundCM->setVisible(false);
  ui->BackgroundEM->setVisible(false);
  ui->BackgroundEEM->setVisible(true);
  ui->body->setCurrentIndex(8);
   stylee_border(ui->Display_offices_Btn,ui->display_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUsed.png)","Segoe UI Light ");
   stylee_border(ui->Statistics_offices_Btn,ui->statistics_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUnused.png)","Segoe UI Light");
   stylee_border(ui->Reservation_Btn,ui->Reservation_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_unused.png)","Segoe UI Light");
   stylee_border(ui->Office_Btn,ui->office_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeUsed.png)","Segoe UI Light");
   stylee_border(ui->Display_offices_Reservation_btn,ui->display_offices_icone_res,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
   stylee_border(ui->Event_Btn,ui->Event_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->display_event_btn,ui->Event_Display_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_event_grey.png)","Segoe UI Light");
   stylee_border(ui->Event_history_Btn,ui->Event_history_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_history_grey.png)","Segoe UI Light");
   stylee_border(ui->Client_Managment_Btn,ui->Client_Managment_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/client_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->Display_Client_Btn,ui->Display_client_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Employe_Btn,ui->Employe_mangement_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_employe_white_icon.png)","Segoe UI");
   stylee_border(ui->Display_employe_Btn,ui->Display_employe_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/employe_white_icon.png)","Segoe UI");
    ui->tableView_employee->setModel(tempemployee.afficherEMPLOYEE());
    QBarSet *set0=new QBarSet("Levels");


             *set0 <<6<<5<<4<<3<<2<<0<<1;


             QBarSeries *Series=new QBarSeries();
             Series->append(set0);


             QChart *chart=new QChart();
             chart->addSeries(Series);
             chart->setTitle("Prices");
             //no animation
             chart->setAnimationOptions(QChart::AllAnimations);
             QStringList categories;
             categories<<"2013"<<"2014"<<"2015"<<"2016"<<"2017";
            QBarCategoryAxis *axis=new  QBarCategoryAxis();
            axis->append(categories);
            chart->createDefaultAxes();
            //chart->setAxisX(axis,Series);
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);


            QChartView *chartview=new QChartView(chart) ;
            chartview->setRenderHint(QPainter::Antialiasing);

            QVBoxLayout *layout2 = new QVBoxLayout(ui->stats);
            layout2->addWidget(chartview);
}

void MainWindow::on_Statistics_offices_Btn_clicked()
{
  ui->BackgroundRM->setVisible(false);
  ui->BackgroundOM->setVisible(true);
  ui->BackgroundEM->setVisible(false);
  ui->BackgroundCM->setVisible(false);
  ui->BackgroundEEM->setVisible(false);
  stylee_border(ui->Statistics_offices_Btn,ui->statistics_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUsed.png)","Segoe UI ");
  stylee_border(ui->Office_Btn,ui->office_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeUsed.png)","Segoe UI ");
  stylee_border(ui->Display_offices_Btn,ui->display_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
  stylee_border(ui->Reservation_Btn,ui->Reservation_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_unused.png)","Segoe UI Light");
  stylee_border(ui->Display_offices_Reservation_btn,ui->display_offices_icone_res,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
  stylee_border(ui->Event_Btn,ui->Event_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_grey_icon.png)","Segoe UI Light");
  stylee_border(ui->display_event_btn,ui->Event_Display_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_event_grey.png)","Segoe UI Light");
  stylee_border(ui->Event_history_Btn,ui->Event_history_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_history_grey.png)","Segoe UI Light");
  stylee_border(ui->Client_Managment_Btn,ui->Client_Managment_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/client_grey_icon.png)","Segoe UI Light ");
  stylee_border(ui->Display_Client_Btn,ui->Display_client_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_client_grey_icon.png)","Segoe UI Light ");
  stylee_border(ui->Employe_Btn,ui->Employe_mangement_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_employe_grey_icon.png)","Segoe UI Light");
  stylee_border(ui->Display_employe_Btn,ui->Display_employe_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/employe_grey_icon.png)","Segoe UI Light");
  ui->body->setCurrentIndex(1);

 // create statistic
    QLineSeries *series = new QLineSeries();
   // statistic implementation for Qline stat office
   // y Axe
   series->append(0,6);
   series->append(2,4);
   series->append(3,8);
   series->append(7,4);
   series->append(10,5);
 // X Axe
   *series << QPointF(11,1) << QPointF(13,3) << QPointF(17,3) << QPointF(18,3) <<QPointF(20,2);
 QChart *chart = new QChart();
 chart->legend()->hide();
 chart->addSeries(series);
 chart->createDefaultAxes();
 chart->setTitle("Line Chart Offices");

 QChartView * chartView=new QChartView(chart);

 chartView->setRenderHints(QPainter::Antialiasing);
 QVBoxLayout *layout = new QVBoxLayout(ui->QlineStatOffice);
 layout->addWidget(chartView);
 OfficeStatistic office1;
 float moy=office1.getAvrage();
 QPieSeries *series1 = new QPieSeries();

 series1->append("Open Area",300);

 series1->append("Avrage Earnnings",moy);

 QChart * chart1=new QChart();

 chart1->addSeries(series1);

 chart1->setTitle("stats");

 QChartView * chartView1=new QChartView(chart1);

 chartView1->setRenderHints(QPainter::Antialiasing);
 QVBoxLayout *layout1 = new QVBoxLayout(ui->QPieStatOffice);
 layout1->addWidget(chartView1);
 //---------------------------------------------------------------------------------------

 QString earnings =QString::number(office1.getEarnings());
 QString availabiltyon =QString::number(office1.getAvailabiltyOn());
 QString availabiltyoff =QString::number(office1.getAvailibiltyOff());
 QString name1,name2,name3,name4,name5,name6;
 int somme1,somme2,somme3,somme4,somme5,somme6;
 ui->earning_sum->setText(earnings);
 ui->available_offices->setText(availabiltyon);
 ui->Not_available_offices->setText(availabiltyoff);
 somme1=office1.getOfficeFirstMonth(name1);
 somme2=office1.getOfficeSecondMonth(name2);
 somme3=office1.getOfficeThirdMonth(name3);
 QString sommest =QString::number(somme1);
  QString sommest1 =QString::number(somme2);
 QString sommest2 =QString::number(somme3);
 somme4=office1.getOfficeFirstMonth(name4);
 somme5=office1.getOfficeSecondMonth(name5);
 somme6=office1.getOfficeThirdMonth(name6);
 QString sommest3 =QString::number(somme4);
  QString sommest4 =QString::number(somme5);
 QString sommest5 =QString::number(somme6);
 ui->green_price_best->setText(sommest);
 ui->green_price_best2->setText(sommest1);
 ui->green_price_best3->setText(sommest2);
 ui->red_label_worst->setText(sommest3);
 ui->red_price_worst2->setText(sommest4);
 ui->red_price_worst3->setText(sommest5);
 ui->office_name_best1->setText(name1);
 ui->office_name_best2->setText(name2);
 ui->office_name_best3->setText(name3);
 ui->office_name_worst1->setText(name4);
 ui->office_name_worst2->setText(name5);
 ui->office_name_worst3->setText(name1);
}

void MainWindow::on_Display_offices_Btn_clicked()
{ //
  ui->BackgroundRM->setVisible(false);
  ui->BackgroundOM->setVisible(true);
  ui->BackgroundEM->setVisible(false);
  ui->BackgroundCM->setVisible(false);
  ui->BackgroundEEM->setVisible(false);
  ui->BackgroundCM->setVisible(false);
  ui->BackgroundEEM->setVisible(false);
  ui->body->setCurrentIndex(0);
   stylee_border(ui->Display_offices_Btn,ui->display_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUsed.png)","Segoe UI ");
   stylee_border(ui->Statistics_offices_Btn,ui->statistics_offices_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/statistics_iconeUnused.png)","Segoe UI Light");
   stylee_border(ui->Reservation_Btn,ui->Reservation_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/reservation_unused.png)","Segoe UI Light");
   stylee_border(ui->Office_Btn,ui->office_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/officeUsed.png)","Segoe UI");
   stylee_border(ui->Display_offices_Reservation_btn,ui->display_offices_icone_res,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_iconeUnused.png)","Segoe UI Light ");
   stylee_border(ui->Event_Btn,ui->Event_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->display_event_btn,ui->Event_Display_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_event_grey.png)","Segoe UI Light");
   stylee_border(ui->Event_history_Btn,ui->Event_history_Icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/event_history_grey.png)","Segoe UI Light");
   stylee_border(ui->Client_Managment_Btn,ui->Client_Managment_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Display_Client_Btn,ui->Display_client_icone,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_client_grey_icon.png)","Segoe UI Light ");
   stylee_border(ui->Employe_Btn,ui->Employe_mangement_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/display_employe_grey_icon.png)","Segoe UI Light");
   stylee_border(ui->Display_employe_Btn,ui->Display_employe_icon,R"(C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/employe_grey_icon.png)","Segoe UI Light");

  setReservation.erase(setReservation.begin(),setReservation.end());
  dataSet.erase(dataSet.begin(),dataSet.end()) ;
  qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
  qDeleteAll(ui->scrollAreaWidgetContents_7->findChildren<ReservationCard *>(QString(), Qt::FindDirectChildrenOnly));
  Office * office;
  dataSet = office->getAllOffices();

  DrawOfficeCard();
}
void MainWindow::recieveDataReservation(Reservation reservation){
  Office *office = new Office("","","","","","","","","","") ;
  office = office->getOfficeByID(reservation.getIdOfiiceReservation());
  ui->body->setCurrentIndex(2);

  ui->title_office_2->setText(reservation.getNameOfficeReservation());

  ui->description_text_office_Reservation->setText(office->getDescription());
  ui->space_description_office_reservation->setText(office->getPostionOffice());
  ui->price_office_reservation->setText(office->getPrice());
  ui->position_description_office_reservation->setText(office->getSpaceOffice());

  QString check_in=reservation.getMonthcheck_in(reservation.getIdOfiiceReservation());
  QString check_out =reservation.getMonthcheck_out(reservation.getIdOfiiceReservation());
  QString s=""+check_in;


  QString url1("C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/red_cercle_res.png");
  QPixmap img1(url1);
  ui->availblity_circle->setPixmap(url1);
  QString url2("C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/tiem_circle.png");
  QPixmap img2(url2);
  ui->availblity_circle->setPixmap(url2);
  ui->january_icon_reservation->setPixmap(url2);
  ui->february_icon_reservation->setPixmap(url2);
  ui->march_icon_reservation->setPixmap(url2);
  ui->april_icon_reservation->setPixmap(url2);
  ui->may_icon_2->setPixmap(url2);
  ui->month_res_6->setPixmap(url2);
  ui->july_icon_reservation->setPixmap(url2);
  ui->august_icon_reservation->setPixmap(url2);
  ui->september_icon_2->setPixmap(url2);
  ui->octobre_icon_2->setPixmap(url2);
  ui->novembre_icon_2->setPixmap(url2);
  ui->december_icon_reservation->setPixmap(url2);
  QList<QLabel *> allWidgets = ui->description_office_container->findChildren<QLabel *>("month");
  QList<QLabel*>::iterator it;
  int m1=1,m2=2,m3=3,m4=4,m5=5,m6=6,m7=7,m8=8,m9=9,m10=10,m11=11,m12=12;
  for(int i=check_in.toInt();i<=check_out.toInt();i++)
    {

            if(i==1)
            {
              ui->january_icon_reservation->setPixmap(url1);
            }

          if(i==2)
            {
              ui->february_icon_reservation->setPixmap(url1);
            }
          if(i==3)
            {
              ui->march_icon_reservation->setPixmap(url1);
            }
          if(i==4)
            {
              ui->april_icon_reservation->setPixmap(url1);
            }
          if(i==5)
            {
              ui->may_icon_2->setPixmap(url1);
            }
          if(i==6)
            {
              ui->month_res_6->setPixmap(url1);
            }
          if(i==m7)
            {
              ui->july_icon_reservation->setPixmap(url1);
            }
          if(i==m8)
            {
              ui->august_icon_reservation->setPixmap(url1);
            }
          if(i==m9)
            {
              ui->september_icon_2->setPixmap(url1);
            }
          if(i==m10)
            {
              ui->octobre_icon_2->setPixmap(url1);
            }
          if(i==m11)
            {
              ui->novembre_icon_2->setPixmap(url1);
            }
          if(i==m12)
            {
              ui->december_icon_reservation->setPixmap(url1);
            }


    }

}
//-------------------------------------------------------------------End Of Styiling-----------------------------------------------------
void MainWindow::recieveData(Office office)
{

    ui->body->setCurrentIndex(3);
    //ui->idOffice->setText(str);
    //ui->id_wtf->setVisible(true);
    ui->id_wtf->setText(office.getIdOffice());
    ui->title_office->setText(office.getNameOffice());
    ui->description_text_office->setText(office.getDescription());
    ui->space_description_office->setText(office.getSpaceOffice());
    ui->position_description_office->setText(office.getPostionOffice());
    ui->price_office->setText(office.getPrice());

    if(office.getStatusOffice()=="not available"){
        QString url("C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/red_circle.png");
        QPixmap img(url);
        ui->availblity_circle->setPixmap(url);
        QString url1("C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/red_circle.png");
        QPixmap img1(url1);
        ui->availblity_circle->setPixmap(url);
        int check_in=0,check_out=0;
        check_in;
        QList<QLabel *> allWidgets = ui->description_office_container->findChildren<QLabel *>("");
        QList<QLabel*>::iterator it;
        for(int i=check_in;i<check_out;i++)
          {

            for (it = allWidgets.begin(); it != allWidgets.end(); it++) {
                if ((*it)->objectName() == "month"+i)  // here, objectName is not working!!
                {
                    (*it)->setPixmap(url);
                }
            }
          }
      }
     if(office.getStatusOffice()=="available"){
        QString url("C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/green_cricle.png");
        QPixmap img(url);
        ui->availblity_circle->setPixmap(url);

      }

}
void MainWindow::on_exit_add_office_clicked()
{
    ui->add_office_widget->setVisible(false);
}

void MainWindow::on_pushButton_clicked()
{
     ui->add_office_widget->setVisible(true);
}

void MainWindow::on_exit_button_clicked()
{
    ui->add_office_widget->setVisible(false);
}


void MainWindow::on_add_office_btn_clicked()
{
      ui->add_office_widget->setVisible(true);
      ui->popup_stacked_widget->setCurrentIndex(0);
}
void MainWindow::on_exit_add_popup_clicked()
{
    ui->add_office_widget->setVisible(false);
}
void MainWindow::on_add_office_button_clicked()
{
  qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
  qDeleteAll(ui->scrollAreaWidgetContents_7->findChildren<ReservationCard *>(QString(), Qt::FindDirectChildrenOnly));
  QString id_office;
  QString image = "C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/offcie.jpg";//we have to make url line in the pop up widget
  QString description=ui->description_line->text();
  QString price=ui->Price_line->text();
  QString name=ui->office_Name_line->text();
  QString space=ui->space_line->text();
  QString position=ui->position_line->text();
  QString status="available";
  QString type=ui->type_line->text();
  if(ui->type_line->text()== ""){
        type="office";
    }
  QString date=ui->date_line->text();
  Office * office = new Office(id_office,image,description,price,name,space,position,status,type,date);
  Office stock(id_office,image,description,price,name,space,position,status,type,date);
  bool check=stock.add_office_database();
  if(check)
    {
      SuccessPopUp("The product have been added to this staging \n                    table successfully");
      dataSet.insert(dataSet.begin(), office);
      DrawOfficeCard();
      ui->description_line->setText("");
      ui->Price_line->setText("");
      ui->office_Name_line->setText("");
      ui->space_line->setText("");
      ui->position_line->setText("");
      ui->type_line->setText("");
    }
  else{
     Failed_PopUp("The product haven't been added to this staging \n                    table successfully");
     ui->description_line->setText("");
     ui->Price_line->setText("");
     ui->office_Name_line->setText("");
     ui->space_line->setText("");
     ui->position_line->setText("");
     ui->type_line->setText("");
    }

}

void MainWindow::on_GoBackButton_clicked()
{
    ui->body->setCurrentIndex(0);
}
void MainWindow::on_omg_clicked()
{
   ui->body->setCurrentIndex(5);
}

void MainWindow::exit_add_popup_add_reservation_edit_clicked()
{
    ui->add_office_widget->setVisible(false);
}

void MainWindow::on_SingUpBtn1_clicked()
{
  ui->loginForm->setCurrentIndex(0);
  QString username=ui->Username_SingUp->text();
  QString password=ui->password_SingUp->text();
  int phone_number=ui->number_SingUp->text().toInt();
  QString email=ui->email_SingUp->text();
  bool verfy=EmailCheck(email);
  if(verfy)
  {
        User stock(username,password,email,phone_number);
        bool check=stock.Add_new();
        if(check){
            ui->pop_up_Sign_Up_STK->setVisible(true);
            qDeleteAll(ui->scrollAreaWidgetContents_3->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
            ui->popup_stacked_widget_2->setCurrentIndex(1);
            QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/success_icon.png";
            QString title="Success !";
            QString description="The User Have Been Added To This Staging \n                    Table Successfully";
            PopUpModel *pop = new PopUpModel();
            pop->setIcon(icon);
            pop->setTitel(title);
            pop->setDescription(description);
            ui->CardsLayout_3->addWidget(pop);
          }
        else
          {
            ui->pop_up_Sign_Up_STK->setVisible(true);
            qDeleteAll(ui->scrollAreaWidgetContents_3->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
            ui->popup_stacked_widget_2->setCurrentIndex(1);
            QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/failed_icon.png";
            QString title="  Failed !";
            QString description="The UserName Or Password Are Not Correct  !!";
            PopUpModel *pop = new PopUpModel();
            pop->setIcon(icon);
            pop->setTitel(title);
            pop->setDescription(description);
            ui->CardsLayout_3->addWidget(pop);
          }
    }
  else
    {
      ui->pop_up_Sign_Up_STK->setVisible(true);
      qDeleteAll(ui->scrollAreaWidgetContents_3->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
      ui->popup_stacked_widget_2->setCurrentIndex(1);
      QString icon="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/failed_icon.png";
      QString title="  Failed !";
      QString description="The UserName Or Password Are Not Correct  !!";
      PopUpModel *pop = new PopUpModel();
      pop->setIcon(icon);
      pop->setTitel(title);
      pop->setDescription(description);
      ui->CardsLayout_3->addWidget(pop);
    }
}
void MainWindow::on_edit_office_button_more_clicked()
{
   ui->add_office_widget->setVisible(true);
   ui->popup_stacked_widget->setCurrentIndex(2);
}
void MainWindow::on_exit_add_popup_edit_clicked()
{
  ui->add_office_widget->setVisible(false);
}
void MainWindow::on_edit_office_button_clicked()
{

  qDeleteAll(ui->scrollAreaWidgetContents_7->findChildren<ReservationCard *>(QString(), Qt::FindDirectChildrenOnly));
  QString id_office=ui->id_wtf->text();
  QString image="C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/office.png";
  QString name=ui->office_Name_line_edit->text();
  QString space=ui->space_line_edit->text();
  QString position=ui->position_line_edit->text();
  QString price=ui->Price_line_edit->text();
  QString description=ui->description_line_edit->text();
  QString status="available";
  QString date=ui->date_line_edit->text();
  QString type=ui->type_line_edit->text();
  qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
  Office * office = new Office(id_office,image,description,price,name,space,position,status,type,date);
  Office stock(id_office,image,description,price,name,position,space,status,type,date);

  bool check=stock.edit_office_database();
  if(check){
      SuccessPopUp("The Product Have Been Edited In This Staging \n                    Table Successfully");
    }
  else{
      Failed_PopUp("The Product Haven't Been Edited In This Staging \n                    Table Successfully");

    }
  DrawOfficeCard();

}
void MainWindow::on_delete_office_button_more_clicked()
{

  qDeleteAll(ui->scrollAreaWidgetContents_7->findChildren<ReservationCard *>(QString(), Qt::FindDirectChildrenOnly));
  ui->add_office_widget->setVisible(true);
  QString id_office=ui->id_wtf->text();
  QString image;
  QString name;
  QString space;
  QString position;
  QString price;
  QString description;
  QString status;
  QString date;
  QString type;
  qDeleteAll(ui->scrollAreaWidgetContents_3->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
  Office * office = new Office(id_office,image,description,price,name,position,space,status,type,date);
  Office stock(id_office,image,description,price,name,position,space,status,type,date);
  bool check=stock.deleteOfficeById();
  if(check){
     SuccessPopUp("The Product Have Been Deleted In This Staging \n                    Table Successfully");
      dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
      Office * office;
      dataSet = office->getAllOffices();
      DrawOfficeCard();
      }
  else{
     Failed_PopUp("The Product Haven't Been Deleted In This Staging \n                    Table Successfully");
    }
}
void MainWindow::on_search_button_office_clicked()
{
  QString id_office=ui->id_wtf->text();
  QString image;
  QString name=ui->search_line_office->text();
  QString space;//=ui->space_line_3->text();
  QString position;//=ui->position_line_3->text();
  QString price;//ui->Price_line_3->text();
  QString description;//ui->description_line_3->text();
  QString status;
  QString date;
  QString type;
  Office * office = new Office(id_office,image,description,price,name,position,space,status,type,date);
  Office stock(id_office,image,description,price,name,position,space,status,type,date);
  if(name!=""){   //if the search is not  empty!! we are going to display the recomended one else we are going to display all the offices
  bool check=stock.searchOfficeByName(name);
  if(check){
      dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
      Office * office;
      dataSet = office->getSearchOffices(name);
      DrawOfficeCard();
    }
  else{
     Failed_PopUp("You have to check your Connection with Data base !!");
    }
}
  else
    {
      dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
      Office * office;
      dataSet = office->getAllOffices();
      DrawOfficeCard();
      }
}
void MainWindow:: on_search_line_office_textChanged(const QString &arg1){
  QString id_office=ui->id_wtf->text();
  QString image;
  QString name=ui->search_line_office->text();
  QString space;
  QString position;
  QString price;
  QString description;
  QString status;
  QString date;
  QString type;
  Office * office = new Office(id_office,image,description,price,name,position,space,status,type,date);
  Office stock(id_office,image,description,price,name,position,space,status,type,date);
  if(name!="")
    {   //if the search is not  empty!! we are going to display the recomended one else we are going to display all the offices
        bool check=stock.searchOfficeByName(name);
            if(check)
              {
                setReservation.erase(setReservation.begin(),setReservation.end()) ;
                qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
                Office * office;
                dataSet = office->getSearchOffices(arg1);
                DrawOfficeCard();
              }
    }
  else
    {
      dataSet.erase(dataSet.begin(),dataSet.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
      Office * office;
      dataSet = office->getAllOffices();
      DrawOfficeCard();
    }
}
void MainWindow:: on_GoBack_area_add_office_clicked()
{
    ui->add_office_widget->setVisible(false);
    ui->popup_stacked_widget->setCurrentIndex(0);
}

void MainWindow ::on_GoBack_area_Sign_Up_clicked()
{
  ui->pop_up_Sign_Up_STK->setVisible(false);
}
void MainWindow:: on_print_pdf_office_clicked()
{
  QString id=ui->id_wtf->text();
  QString name=ui->title_office->text();
  QString description=ui->description_text_office->text();
  QString space=ui->space_description_office->text();
  QString position=ui->position_description_office->text();
  QString price=ui->price_office->text();
  QString BankOffer=ui->bankOffer_description_office->text();
  QFile file("C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/"+name+" "+id+""".pdf");
  QPdfWriter pdf("C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/"+name+" "+id+".pdf");
  QPainter painter(&pdf);
  painter.setPen(Qt::black);
  painter.drawText(4000,400,"receipt N°:  "+id+"" );
  painter.drawText(3500,1300,"Office Name: "+name+"" );
  painter.drawText(3500,1700,"Description :"+description+"  " );
  painter.drawText(3500,2100,"Space :  "+space+"" );
  painter.drawText(3500,2500,"Position: :  "+position+"" );
  painter.drawText(3500,2900,"BankOffer : "+BankOffer+"" );
  painter.drawText(3500,3300,"The sum is :  "+price+"" );
  painter.end();
}


void MainWindow::on_lowest_button_clicked()
{
    ui->check_cercle_heighest->setVisible(false);
    ui->check_cercle_lowest->setVisible(true);
    price_office = " ASC ";
    dataSet.erase(dataSet.begin(),dataSet.end()) ;
    qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
    Office * office;
    dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
    DrawOfficeCard();
}

void MainWindow:: on_heighest_button_clicked()
{
    ui->check_cercle_heighest->setVisible(true);
    ui->check_cercle_lowest->setVisible(false);
    price_office = " DESC ";
    dataSet.erase(dataSet.begin(),dataSet.end()) ;
    qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
    Office * office;
    dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
    DrawOfficeCard();
}
void MainWindow ::on_open_area_button_clicked()
{   ui->check_cercle_openArea->setVisible(true);
    ui->check_cercle_office->setVisible(false);
    type_office = " open area ";
    dataSet.erase(dataSet.begin(),dataSet.end()) ;
    qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
    Office * office;
    dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
    DrawOfficeCard();

}

void MainWindow::on_office_button_clicked()
{
    ui->check_cercle_openArea->setVisible(false);
    ui->check_cercle_office->setVisible(true);
    type_office = "office";
    dataSet.erase(dataSet.begin(),dataSet.end()) ;
    qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
    Office * office;
    dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
    DrawOfficeCard();
}
void MainWindow:: on_available_button_clicked()
{
  ui->check_cercle_available->setVisible(true);
  ui->check_cercle_not_available->setVisible(false);
  ui->check_cercle_All->setVisible(false);
  availibity_office = "available";
  dataSet.erase(dataSet.begin(),dataSet.end()) ;
  qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
  Office * office;
  dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
  DrawOfficeCard();
}

void MainWindow:: on_not_available_button_clicked()
{

    ui->check_cercle_available->setVisible(false);
    ui->check_cercle_not_available->setVisible(true);
    ui->check_cercle_All->setVisible(false);
    availibity_office = "not available";
    dataSet.erase(dataSet.begin(),dataSet.end()) ;
    qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
    Office * office;
    dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
    DrawOfficeCard();
}
void MainWindow:: on_asc_button_clicked()
{
    ui->check_cercle_ASC->setVisible(true);
    ui->check_cercle_DESC->setVisible(false);
    space_office = " ASC ";
    dataSet.erase(dataSet.begin(),dataSet.end()) ;
    qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
    Office * office;
    dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
    DrawOfficeCard();
}
void MainWindow:: on_desc_button_clicked()
{
  ui->check_cercle_ASC->setVisible(false);
  ui->check_cercle_DESC->setVisible(true);
  space_office = " DESC ";
   dataSet.erase(dataSet.begin(),dataSet.end()) ;
   qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
   Office * office;
   dataSet = office->getFiltredOffices(type_office,space_office,price_office,availibity_office);
   //dataSet = office->getOfficesBySpaceDESC();
   DrawOfficeCard();

}
bool MainWindow:: EmailCheck (QString email)
{
  if((email.contains('@'))&& (email.toStdString().length()>5)&& (email.contains('@'))){
      return true ;
    }
  else
    return false;
}
void MainWindow::on_add_reservation_button_clicked()
{
 setReservation.erase(setReservation.begin(),setReservation.end()) ;
 qDeleteAll(ui->scrollAreaWidgetContents_7->findChildren<ReservationCard *>(QString(), Qt::FindDirectChildrenOnly));
 QString day1=ui->DayCheckIn->text();
 QString year1=ui->YearCheckIn->text();
 QString month1=ui->MonthCheckin_lineEdit->text() ;
 QString day2=ui->DayCheckOut_LineEdit->text();
 QString checkIn= day1+"-"+month1+"-"+year1;
 QString year2=ui->YearCheckOut_lineEdit->text();
 QString month2=ui->MonthCheckOut->text();
 QString checkOut= day2+"-"+month2+"-"+year2 ;
 QString id_reservation;
 QString id_office = setectedIdOffice;//we have to make url line in the pop up widget
 QString cin_client=ui->Cin_LineEdit->text();

 QString name_office="";
  Reservation * reservation = new Reservation(id_reservation,id_office,cin_client,checkIn,checkOut,name_office);
  Reservation stock(id_reservation,id_office,cin_client,checkIn,checkOut,name_office);


  QDate Date=QDate::fromString(checkIn,"dd-MM-yyyy");
  QDate Date2=QDate::fromString(checkOut,"dd-MM-yyyy");
  std::list<Reservation*> reservationListByOffice=stock.getReservationByOfficesId(setectedIdOffice);
  std::list<Reservation*>::iterator it1;
  std::list<Reservation*> listCheck=stock.date_check(Date,Date2,reservationListByOffice);
  int test = 0 ;
  for (it1=listCheck.begin();it1!=listCheck.end();++it1)
     {
       test = 1;
     }
  if(test == 0)
    {
      bool check=stock.add_reservation_database();
      stock.update_status(setectedIdOffice);
      if(check)
      {

        SuccessPopUp("The product have been added to this staging \n                    table successfully");
        setReservation = reservation->getAllOfficesReservation();
        DrawReservationCard();
      }
      else
      {
        Failed_PopUp("The product haven't been added to this staging \n                    table successfully");
      }

}
  //when the date is not available.

  else
    {
      ui->wornning1->setVisible(true);
      ui->wornning2->setVisible(true);
    }
}
void MainWindow:: on_edit_reservation_clicked()
{

  setReservation.erase(setReservation.begin(),setReservation.end()) ;
  qDeleteAll(ui->scrollAreaWidgetContents_7->findChildren<ReservationCard *>(QString(), Qt::FindDirectChildrenOnly));
  QString day1=ui->DayCheckIn_2->text();
  QString year1=ui->YearCheckIn_2->text();
  QString month1=ui->MonthCheckin_lineEdit_2->text() ;
  QString day2=ui->DayCheckOut_LineEdit_2->text();
  QString checkIn= day1+"-"+month1+"-"+year1;
  QString year2=ui->YearCheckOut_lineEdit_2->text();
  QString month2=ui->MonthCheckOut_2->text();
  QString checkOut= day2+"-"+month2+"-"+year2 ;
  QString id_reservation=ui->id_prank->text();
  QString id_office=setectedIdOffice;
  QString cin_client=ui->Cin_LineEdit_edit->text();


  QString name_office="";
   Reservation * reservation = new Reservation(id_reservation,id_office,cin_client,checkIn,checkOut,name_office);
   Reservation stock(id_reservation,id_office,cin_client,checkIn,checkOut,name_office);

  QDate Date=QDate::fromString(checkIn,"dd-MM-yyyy");
  QDate Date2=QDate::fromString(checkOut,"dd-MM-yyyy");
  std::list<Reservation*> reservationListByOffice=stock.getReservationByOfficesId(setectedIdOffice);
  std::list<Reservation*>::iterator it1;
  std::list<Reservation*> listCheck=stock.date_check(Date,Date2,reservationListByOffice);
  int test = 0 ;
  for (it1=listCheck.begin();it1!=listCheck.end();++it1)
     {
       test = 1;
     }
  if(test == 0)
    {
           bool check=stock.edit_reservation_database();
             if(check)
               {
                 SuccessPopUp("The Product Have Been Edited In This Staging \n                    Table Successfully");
                 qDeleteAll(ui->scrollAreaWidgetContents_7->findChildren<ReservationCard *>(QString(), Qt::FindDirectChildrenOnly));
                  setReservation = reservation->getAllOfficesReservation();
                  DrawReservationCard();
               }
              else
                {
                  Failed_PopUp("The Product Haven't Been Edited In This Staging \n                    Table Successfully");
                }



}
  else
    {
      ui->wornning1->setVisible(true);
      ui->wornning2->setVisible(true);
    }
}

void MainWindow:: on_delete_reservation_clicked()
{

  QString id_reservation=ui->id_prank->text();
  QString id_office="";
  QString cin_client="";
  QString check_in="";
  QString check_out="";
 ui->add_office_widget->setVisible(true);
   qDeleteAll(ui->scrollAreaWidgetContents_2->findChildren<PopUpModel *>(QString(), Qt::FindDirectChildrenOnly));
   QString name_office="";
    Reservation * reservation = new Reservation(id_reservation,id_office,cin_client,check_in,check_out,name_office);
    Reservation stock(id_reservation,id_office,cin_client,check_in,check_out,name_office);

  bool check=stock.deleteReservationById();
  if(check){
      SuccessPopUp("The Product Have Been Edited In This Staging \n                    Table Successfully");

      setReservation.erase(setReservation.begin(),setReservation.end()) ;
      qDeleteAll(ui->scrollAreaWidgetContents->findChildren<Card *>(QString(), Qt::FindDirectChildrenOnly));
      qDeleteAll(ui->scrollAreaWidgetContents_7->findChildren<ReservationCard *>(QString(), Qt::FindDirectChildrenOnly));
      Reservation * reservation;
      setReservation = reservation->getAllOfficesReservation();
      DrawReservationCard();
    }

  else{
      Failed_PopUp("The Product Haven't Been Edited In This Staging \n                    Table Successfully");

    }
}
void MainWindow:: recieveID(QString id,QString name){
  selectNameOffice = name;
  setectedIdOffice = id;
}
void MainWindow:: on_add_reservation_btn_clicked()
{
   ui->add_office_widget->setVisible(true);
   ui->popup_stacked_widget->setCurrentIndex(3);
   //std::list<Office*>::iterator it1;
  qDeleteAll(ui-> scrollAreaWidgetContents_listOfiice->findChildren< AvailableOfficeCard *>(QString(), Qt::FindDirectChildrenOnly));   std::list<Office*>::iterator it;
   for (it = dataSet.begin(); it != dataSet.end(); ++it){
       AvailableOfficeCard *card = new AvailableOfficeCard();
       card->SetOfficeName((*it)->getNameOffice());
        card->id = (*it)->getIdOffice();
        card->name = (*it)->getNameOffice();
        connect(card,SIGNAL(sendData(QString,QString)),this,SLOT(recieveID(QString,QString)));
        ui->CardsLayout_5->addWidget(card);
}
}
void MainWindow:: on_GoNextbtn_clicked()
{

  ui->popup_stacked_widget->setCurrentIndex(4);
}

void MainWindow:: on_exit_add_popup_add_reservation_clicked()
{
  ui->add_office_widget->setVisible(false);
}

void MainWindow::on_exit_popup_reservation_clicked()
{
  ui->add_office_widget->setVisible(false);

}
void MainWindow::on_edit_reservation_more_clicked()
{
  ui->add_office_widget->setVisible(true);
  ui->popup_stacked_widget->setCurrentIndex(5);
  qDeleteAll(ui-> scrollAreaWidgetContents_listOfiice_edit->findChildren< AvailableOfficeCard *>(QString(), Qt::FindDirectChildrenOnly));   std::list<Office*>::iterator it;
   for (it = dataSet.begin(); it != dataSet.end(); ++it){
       AvailableOfficeCard *card = new AvailableOfficeCard();
       card->SetOfficeName((*it)->getNameOffice());
        card->id = (*it)->getIdOffice();
        card->name = (*it)->getNameOffice();
        connect(card,SIGNAL(sendData(QString,QString)),this,SLOT(recieveID(QString,QString)));
        ui->CardsLayout_6->addWidget(card);
}
}

void MainWindow::on_GoNextbtn_edit_clicked()
{
  ui->wornning1_2->setVisible(false);
  ui->wornning2_2->setVisible(false);
  ui->popup_stacked_widget->setCurrentIndex(6);
}
void MainWindow::on_exit_add_popup_add_reservation_edit_clicked()
{
  ui->add_office_widget->setVisible(false);

}

void MainWindow:: on_search_line_office_3_textChanged(const QString &arg1){
        QString id_office=ui->id_wtf->text();
        QString id_reservation="";
        QString name=ui->search_line_office_3->text();
        QString cin_client="";
        QString check_out="";
        QString check_in="";
        QString name_office="";
         Reservation * reservation = new Reservation(id_reservation,id_office,cin_client,check_in,check_out,name_office);
         Reservation stock(id_reservation,id_office,cin_client,check_in,check_out,name_office);

      //if the search is not  empty!! we are going to display the recomended one else we are going to display all the offices
        bool check=stock.searchOfficeByName(name);
            if(check)
              {
                setReservation.erase(setReservation.begin(),setReservation.end()) ;
                qDeleteAll(ui->scrollAreaWidgetContents_7->findChildren<ReservationCard *>(QString(), Qt::FindDirectChildrenOnly));
                Reservation * office;
                setReservation = office->getSearchReservation(arg1);
                DrawReservationCard();
              }
}
//---------------------------------------------------Intergration Event----------------------------------------------------------------------
void MainWindow:: on_refresh_button_clicked()
{
  evenement e(0,0,0,"","","","");
   QSqlQueryModel *model =e.afficher();

      ui->Event_table_view->setModel(model);
}
void MainWindow:: on_exit_add_popup_edit_event_clicked()
{
  ui->add_office_widget->setVisible(false);
}
void MainWindow:: on_add_event_btn_clicked()
{
 ui->add_office_widget->setVisible(true);
  ui->popup_stacked_widget->setCurrentIndex(7);
}

void MainWindow:: on_add_event_button_clicked()
{
  ui->add_office_widget->setVisible(true);
  int ID_EVENEMENT,NBR_PARTICIPANT,PRIX;
 QString  NOM,TYPE,DATE_EVE,CIN_CLIENT;

 ID_EVENEMENT=ui->Event_id_line_add->text().toInt();
 NBR_PARTICIPANT=ui->participant_line_add->text().toInt();
 PRIX=ui->price_event_line_add->text().toInt();

 NOM=ui->Event_name_line_add->text();
 TYPE=ui->type_event_line->text();
 DATE_EVE=ui->dateEdit_Event_add->text();


 evenement e(ID_EVENEMENT,NBR_PARTICIPANT,PRIX,NOM,TYPE,DATE_EVE,CIN_CLIENT);
 bool test=e.ajouter();
   if(test)
   {
       SuccessPopUp("The Event Informations have been Added in this staging \n                    table successfully");
       evenement e(0,0,0,"","","","");
        QSqlQueryModel *model =e.afficher();

           ui->Event_table_view->setModel(model);
   }
   else
   {
       Failed_PopUp("The Client Haven't Been Added In This Staging \n                    Table Successfully");

   }
}


void MainWindow::on_edit_event_clicked()
{
  ui->add_office_widget->setVisible(true);
  ui->popup_stacked_widget->setCurrentIndex(8);
}
void MainWindow :: on_edit_event_button_clicked()
{
  ui->add_office_widget->setVisible(true);
  int ID_EVENEMENT,NBR_PARTICIPANT,PRIX;
 QString  NOM,TYPE,DATE_EVE,CIN_CLIENT;

 ID_EVENEMENT=ui->Event_id_line_edit->text().toInt();
 NBR_PARTICIPANT=ui->participant_line_edit->text().toInt();
 PRIX=ui->price_event_line_edit->text().toInt();

 NOM=ui->Event_name_line_edit->text();
 TYPE=ui->type_event_line_editt->text();
 DATE_EVE=ui->dateEdit_Event_Edit->text();

 evenement e(ID_EVENEMENT,NBR_PARTICIPANT,PRIX,NOM,TYPE,DATE_EVE,CIN_CLIENT);
 bool test=e.modifier();
   if(test)
   {
       SuccessPopUp("The Event Informations have been Modified in this staging \n                    table successfully");
       evenement e(0,0,0,"","","","");
        QSqlQueryModel *model =e.afficher();

           ui->Event_table_view->setModel(model);
   }
   else
   {
       Failed_PopUp("The Event Informations haven't been Modified In this staging \n                    table successfully");

   }
}
void  MainWindow:: on_delete_event_btn_clicked()
{
  int id=ui->Id_event_line_delete->text().toInt();

  evenement e(0,0,0,"","","","");
  bool test=e.supprimer(id);
    if(test)
    {
        SuccessPopUp("The Event have been Deleted From this staging \n                    table successfully");
        evenement e(0,0,0,"","","","");
         QSqlQueryModel *model =e.afficher();

            ui->Event_table_view->setModel(model);
    }
    else
    {
        Failed_PopUp("The Event haven't been Deleted From this staging \n                    table successfully");
    }

}
void MainWindow :: on_delete_event_clicked()
{
  ui->add_office_widget->setVisible(true);
  ui->popup_stacked_widget->setCurrentIndex(12);
}
void MainWindow:: on_exit_delete_event_clicked()
{
  ui->add_office_widget->setVisible(false);
}
void MainWindow:: on_cancel_btn_event_clicked()
{
  ui->add_office_widget->setVisible(false);
}
void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
     QString date_string=date.toString();
     QString day_string=QString::number(date.day());
     if(day_string.length()==1){
         day_string="0"+day_string;
       }
       QString month_string=QString::number(date.month());
       if(month_string.length()==1){
           month_string="0"+month_string;
         }
       QMessageBox::information(nullptr,"test",month_string);

       QString year_string=QString::number(date.year());

       QString date_selected=day_string+"/"+month_string+"/"+year_string ;

       evenement e(0,0,0,"","","","");

       e.searsh_date(date_selected);
       QMessageBox::information(nullptr,"test",date_selected);
      QString ID_EVENEMENT_string=QString::number(e.get_ID_EVENEMENT());
      QString NBR_PARTICIPANT_string=QString::number(e.get_NBR_PARTICIPANT());
QMessageBox::information(nullptr,"test",ID_EVENEMENT_string);
      ui->id_value->setText(ID_EVENEMENT_string);
      ui->name_value->setText(e.get_NOM());

      ui->type_value->setText(e.get_TYPE());
      ui->participant_number_value->setText(NBR_PARTICIPANT_string);

}
void MainWindow::on_search_historique_line_textChanged(const QString &arg1)
{

      evenement e(0,0,0,"","","",ui->search_historique_line->text());
       QSqlQueryModel *model =e.historiqueByCin(arg1);

          ui->tableView_historique->setModel(model);

}
void MainWindow:: on_pdf_button_historique_clicked()
{


  QString strStream;
              QTextStream out(&strStream);

              const int rowCount = ui->tableView_historique->model()->rowCount();
              const int columnCount = ui->tableView_historique->model()->columnCount();

              out <<  "<html>\n"
                  "<head>\n"
                  "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                  <<  QString("<title>%1</title>\n").arg("col1")
                  <<  "</head>\n"
                  "<body bgcolor=#ffffff link=#5000A0>\n"
                  "<table border=1 cellspacing=0 cellpadding=2>\n";

              // headers
              out << "<thead><tr bgcolor=#f0f0f0>";
              for (int column = 0; column < columnCount; column++)
                  if (!ui->tableView_historique->isColumnHidden(column))
                      out << QString("<th>%1</th>").arg(ui->tableView_historique->model()->headerData(column, Qt::Horizontal).toString());
              out << "</tr></thead>\n";

              // data table
              for (int row = 0; row < rowCount; row++) {
                  out << "<tr>";
                  for (int column = 0; column < columnCount; column++) {
                      if (!ui->tableView_historique->isColumnHidden(column)) {
                          QString data = ui->tableView_historique->model()->data(ui->tableView_historique->model()->index(row, column)).toString().simplified();
                          out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                      }
                  }
                  out << "</tr>\n";
              }
              out <<  "</table>\n"
                  "</body>\n"
                  "</html>\n";

              QTextDocument *document = new QTextDocument();
              document->setHtml(strStream);

              QPrinter printer;

              QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
              if (dialog->exec() == QDialog::Accepted) {
                  document->print(&printer);
              }

              delete document;

}
void MainWindow:: on_exit_add_popup_edit_event_2_clicked()
{
  ui->add_office_widget->setVisible(false);
}

//---------------------------------------------------Integration Avec Client ------------------------------------------------------------------



void MainWindow:: on_add_client_Btn_clicked()
{
    ui->add_office_widget->setVisible(true);
    ui->popup_stacked_widget->setCurrentIndex(9);
}

void MainWindow:: on_add_client_button_clicked()
{
  ui->add_office_widget->setVisible(true);
  QString nom=ui->name_client_line_add->text();
  QString prenom=ui->Last_name_client_line_add->text();
  QString mail=ui->email_line_add->text();
  QString addres=ui->adress_line_add->text();
  int numero=ui->Cin_client_line_add->text().toInt();
 customer c  ( nom, prenom, mail, addres, numero );
  QSqlQuery query;

  bool test= c.ajout();
  if (test)
  {
     ui->table_client->setModel(tmp.afficher());
     SuccessPopUp("The client have been added to this staging \n                    table successfully");
  }
  else

     {
      Failed_PopUp("The client haven't been added to this staging \n                    table successfully");
    }
}
void MainWindow:: on_exit_client_add_clicked()
{
  ui->add_office_widget->setVisible(false);
}
void MainWindow:: on_edit_client_clicked()
{ ui->add_office_widget->setVisible(true);
  ui->popup_stacked_widget->setCurrentIndex(10);
}
void MainWindow:: on_edit_client_Btn_clicked()
{
  ui->add_office_widget->setVisible(true);
  int numero=ui->Cin_client_line_edit->text().toInt();
          QString name=ui->name_client_line_edit->text();
          QString lastname=ui->Last_name_client_line_edit->text();
           QString email=ui->email_client_line_edit->text();
            QString address=ui->adress_line_edit->text();
          customer c(name,lastname,email,address,numero);
          bool test=c.modifier(numero);
          ui->table_client->setModel(tmp.afficher());
       if(test){

          SuccessPopUp("The client Informations have been Modified in this staging \n                    table successfully");
      }
       else
        {
           Failed_PopUp("The client Informations haven't been Modified in this staging \n                    table successfully");

        }
}
void MainWindow:: on_exit_client_edit_clicked()
{
  ui->add_office_widget->setVisible(false);
}
void MainWindow:: on_search_line_client_textChanged(const QString &arg1)
{
  QSqlQueryModel * modal= new QSqlQueryModel ();
  QSqlQuery*qry=new QSqlQuery();
  QString text=ui->search_line_client->text();
  QString cin;
  QString adress;
   QString email ;
   QString last_name;
   QString name ;
  if(text.isEmpty())
  {
      tmp.afficher();

  }
  else
  {
      qry->prepare("select * from CUSTOMER where cin_client like '%"+text+"%'");
      qry->exec();
      modal->setQuery(*qry);

      if(qry->exec()){
             while (qry->next()) {
             name = qry->value(0).toString();

            //QString officeID = qry.value(0).toString();
            //QString image =  qry.value(4).toString();
            last_name = qry->value(1).toString();
            email =  qry->value(2).toString();
            adress= qry->value(3).toString();
           cin= qry->value(4).toString();
               }
        }
           //QString status= query.value(8).toString();
           //QString type= query.value(7).toString();
           //QString date= query.value(9).toString();
      ui->table_client->setModel(modal);
  }

  // qr code

      int scale=5;
          int levelIndex = 1;
          int versionIndex = 0;
          bool bExtent = true;
          int maskIndex = -1;
          QString encodeString ="name:"+ name+"\n"+"Last_name:"+last_name+"\n"+"Email:"+email+"\n"+"Adress"+adress+"\n"+"Cin:"+cin;

          successfulEncoding = qrEncode.EncodeData( levelIndex, versionIndex, bExtent, maskIndex, encodeString.toUtf8().data() );



          int qrImageSize = qrEncode.m_nSymbleSize ;


          encodeImageSize = qrImageSize + ( QR_MARGIN * 2 );
          QImage encodeImage( encodeImageSize, encodeImageSize, QImage::Format_Mono );
          encodeImage.fill( 1 );


          for ( int i = 0; i < qrImageSize; i++ )
              for ( int j = 0; j < qrImageSize; j++ )
                  if ( qrEncode.m_byModuleData[i][j] )
                      encodeImage.setPixel( i + QR_MARGIN, j + QR_MARGIN, 0 );

          ui->QRCodeLabel->setPixmap( QPixmap::fromImage( encodeImage ) );

          ui->QRCodeLabel->setScaledContents(true);

          //ui->save->setEnabled( successfulEncoding );
}

void MainWindow:: on_delete_client_btn_clicked()
{
  ui->add_office_widget->setVisible(true);
  int num =ui->Cin_client_line_delete->text().toInt();
      bool test =tmp.supprimer(num);
      if (test)
      {
   ui->table_client->setModel(tmp.afficher());

    SuccessPopUp("The Client Have Been Deleted In This Staging \n                    Table Successfully");

      }
      else

        {
          Failed_PopUp("The Client Haven't Been Deleted In This Staging \n                    Table Successfully");
        }

}
void  MainWindow:: on_cancel_btn_client_clicked()
{
  ui->add_office_widget->setVisible(false);
}

void MainWindow:: on_exit_client_delete_clicked()
{
  ui->add_office_widget->setVisible(false);

}

void MainWindow:: on_delete_client_clicked()
{
  ui->add_office_widget->setVisible(true);
  ui->popup_stacked_widget->setCurrentIndex(11);
}

void MainWindow:: on_pdf_client_clicked()
{
  QString strStream;
      QTextStream out(&strStream);

      const int rowCount = ui->table_client->model()->rowCount();
      const int columnCount = ui->table_client->model()->columnCount();

      out <<  "<html>\n"
          "<head>\n"
          "<meta Content=\"Text/html; charset=Windows-1251\">\n"
          <<  QString("<title>%1</title>\n").arg("col1")
          <<  "</head>\n"
          "<body bgcolor=#ffffff link=#5000A0>\n"
          "<table border=1 cellspacing=0 cellpadding=2>\n";

      // headers
      out << "<thead><tr bgcolor=#f0f0f0>";
      for (int column = 0; column < columnCount; column++)
          if (!ui->table_client->isColumnHidden(column))
              out << QString("<th>%1</th>").arg(ui->table_client->model()->headerData(column, Qt::Horizontal).toString());
      out << "</tr></thead>\n";

      // data table
      for (int row = 0; row < rowCount; row++) {
          out << "<tr>";
          for (int column = 0; column < columnCount; column++) {
              if (!ui->table_client->isColumnHidden(column)) {
                  QString data = ui->table_client->model()->data(ui->table_client->model()->index(row, column)).toString().simplified();
                  out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
              }
          }
          out << "</tr>\n";
      }
      out <<  "</table>\n"
          "</body>\n"
          "</html>\n";

      QTextDocument *document = new QTextDocument();
      document->setHtml(strStream);

      QPrinter printer;

      QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
      if (dialog->exec() == QDialog::Accepted) {
          document->print(&printer);
      }

      delete document;
}
//---------------------------------------------------------------------------------Integration avec Employee---------------------------------------
void MainWindow:: on_add_employe_Btn_clicked()
{
  ui->add_office_widget->setVisible(true);
  ui->popup_stacked_widget->setCurrentIndex(13);
}

void MainWindow:: on_add_employe_button_clicked()
{
  ui->add_office_widget->setVisible(true);
  QString CIN = ui->Cin_employe_line_add->text();
      QString Nom = ui->name_employe_line_add->text();
      QString Prenom = ui->Last_name_employe_line_add->text();
      QString Mail = ui->email_employe_line_add->text();
      QString Tel = ui->phone_employe_line_add->text();
      QString Age = ui->age_employe_line_add->text();


   Employee C(CIN,Nom,Prenom,Mail,Tel,Age);
      bool test = C.ajouteremployee();
      if(test)
      {
          SuccessPopUp("The Employee Have Been Added In This Staging \n                    Table Successfully");

          ui->tableView_employee->setModel(tempemployee.afficherEMPLOYEE());
          ui->Cin_employe_line_add->clear();
          ui->name_employe_line_add->clear();
          ui->Last_name_employe_line_add->clear();
          ui->email_employe_line_add->clear();
          ui->phone_employe_line_add->clear();
          ui->age_employe_line_add->clear();




      }else{
          Failed_PopUp("The Employee Haven't Been Added In This Staging \n                    Table Successfully"); }
}

void MainWindow:: on_exit_employe_add_clicked()
{
  ui->add_office_widget->setVisible(false);
}
void MainWindow:: on_exit_employe_edit_clicked()
{
  ui->add_office_widget->setVisible(false);
}

void MainWindow:: on_edit_employe_button_clicked()
{ ui->add_office_widget->setVisible(true);
  QString CIN = ui->Cin_employe_line_edit->text();
      QString Nom = ui->name_employe_line_edit->text();
      QString Prenom = ui->Last_name_employe_edit->text();
      QString Mail = ui->email_employe_line_edit->text();
      QString Tel = ui->phone_employe_line_edit->text();
      QString Salaire= ui->age_employe_line_edit->text();



      Employee C(CIN,Nom,Prenom,Mail,Tel,Salaire);
       bool test=C.modifierEMPLOYEE(CIN,Nom,Prenom,Mail,Tel,Salaire);
      if(test)
      {
          SuccessPopUp("The Employee Have Been Modified In This Staging \n                    Table Successfully");

          ui->tableView_employee->setModel(tempemployee.afficherEMPLOYEE());
          ui->Cin_employe_line_edit->clear();
          ui->name_employe_line_edit->clear();
          ui->Last_name_employe_edit->clear();
          ui->email_employe_line_edit->clear();
          ui->phone_employe_line_edit->clear();
          ui->age_employe_line_edit->clear();
      }

      else {

          Failed_PopUp("The Employee Haven't Been Modified In This Staging \n                    Table Successfully");

}
}
void MainWindow:: on_exit_delete_employe_clicked(){
  ui->add_office_widget->setVisible(false);
}

void MainWindow:: on_delete_employe_btn_clicked(){
  ui->add_office_widget->setVisible(true);
  QString CIN = ui->Id_employe_line_delete->text();
      Employee temp;

      bool test=temp.supprimerEMPLOYEE(CIN);
      if(test)
      {
          ui->tableView_employee->setModel(tempemployee.afficherEMPLOYEE());
          SuccessPopUp("The Employee Have Been Deleted In This Staging \n                    Table Successfully");

      }else{
          Failed_PopUp("The Employee Haven't Been Deleted From This Staging \n                    Table Successfully");

}
}
void MainWindow:: on_cancel_btn_employe_clicked(){
  ui->add_office_widget->setVisible(false);
}

void MainWindow:: on_delete_employe_clicked(){
  ui->add_office_widget->setVisible(true);
  ui->popup_stacked_widget->setCurrentIndex(15);
}

void MainWindow:: on_edit_employe_clicked()
{
  ui->add_office_widget->setVisible(true);
  ui->popup_stacked_widget->setCurrentIndex(14);
}
void MainWindow::on_Cin_employe_line_add_textChanged(const QString &arg1)
{
  stylee(ui->Cin_employe_line_add,ui->cin_employe_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/cin_2.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow:: on_Cin_employe_line_add_editingFinished()
{
  stylee(ui->Cin_employe_line_add,ui->cin_employe_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/cin_1.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow:: on_name_employe_line_add_textChanged(const QString &arg1)
{
  stylee(ui->name_employe_line_add,ui->adress_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/name_1.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow:: on_name_employe_line_add_editingFinished()
{
  stylee(ui->name_employe_line_add,ui->name_employe_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/name_2.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow::on_Last_name_employe_line_add_textChanged(const QString &arg1)
{
  stylee(ui->Last_name_employe_line_add,ui->lastname_employe_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/last_name_1.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow:: on_Last_name_employe_line_add_editingFinished()
{
  stylee(ui->Last_name_employe_line_add,ui->lastname_employe_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/last_name_2.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow:: on_email_employe_line_add_textChanged(const QString &arg1)
{
  stylee(ui->email_employe_line_add,ui->email_employe_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow:: on_email_employe_line_add_editingFinished()
{
  stylee(ui->email_employe_line_add,ui->email_employe_add_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_black_24dp.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow:: on_phone_employe_line_add_textChanged(const QString &arg1)
{
  stylee(ui->phone_employe_line_add,ui->phone_number_employe_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/phone_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow:: on_phone_employe_line_add_editingFinished()
{
  stylee(ui->phone_employe_line_add,ui->phone_number_employe_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/phone_grey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow:: on_age_employe_line_add_textChanged(const QString &arg1)
{
  stylee(ui->age_employe_line_add,ui->age_employe_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/age_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow:: on_age_employe_line_add_editingFinished()
{
  stylee(ui->age_employe_line_add,ui->age_employe_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/age_grey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");
}

void MainWindow:: on_Cin_employe_line_edit_textChanged(const QString &arg1)
{
  stylee(ui->Cin_employe_line_edit,ui->cin_employe_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/cin_2.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");

}

void MainWindow:: on_Cin_employe_line_edit_editingFinished()
{
  stylee(ui->Cin_employe_line_edit,ui->cin_employe_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/cin_1.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}

void MainWindow:: on_name_employe_line_edit_textChanged(const QString &arg1)
{
  stylee(ui->name_employe_line_edit,ui->name_employe_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/name_1.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");

}

void MainWindow:: on_name_employe_line_edit_editingFinished()
{
  stylee(ui->name_employe_line_edit,ui->name_employe_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/name_2.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}

void MainWindow:: on_Last_name_employe_edit_textChanged(const QString &arg1)
{
  stylee(ui->Last_name_employe_edit,ui->lastname_employe_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/last_name_1.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");

}

void MainWindow:: on_Last_name_employe_edit_editingFinished()
{
  stylee(ui->Last_name_employe_edit,ui->lastname_employe_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/last_name_2.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}

void MainWindow:: on_email_employe_line_edit_textChanged(const QString &arg1)
{
  stylee(ui->email_employe_line_edit,ui->email_employe_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");

}

void MainWindow:: on_email_employe_line_edit_editingFinished()
{
  stylee(ui->email_employe_line_edit,ui->email_employe_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/alternate_email_black_24dp.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}

void MainWindow:: on_phone_employe_line_edit_textChanged(const QString &arg1)
{
  stylee(ui->phone_employe_line_edit,ui->phone_number_employe_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/phone_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");

}

void MainWindow:: on_phone_employe_line_edit_editingFinished()
{
  stylee(ui->phone_employe_line_edit,ui->phone_number_employe_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/phone_blue.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}

void MainWindow:: on_age_employe_line_edit_textChanged(const QString &arg1)
{
  stylee(ui->age_employe_line_edit,ui->age_employe_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/age_blue.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");

}

void MainWindow:: on_age_employe_line_edit_editingFinished()
{
  stylee(ui->age_employe_line_edit,ui->age_employe_edit_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/age_grey.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}

void MainWindow:: on_Id_employe_line_delete_textChanged(const QString &arg1)
{
  stylee(ui->Id_employe_line_delete,ui->cin_employe_delete_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/cin_2.png","border-bottom: 1.5px solid #4A8292; border-radius:unset;");
}

void MainWindow:: on_Id_employe_line_delete_editingFinished()
{
  stylee(ui->Id_employe_line_delete,ui->cin_employe_delete_icon,"C:/Users/Mon Pc/Desktop/Qt projects/BrainStormSpace/img/cin_1.png","border-bottom: 1.5px solid #d9d9d9; border-radius:unset;");

}

void MainWindow:: on_search_line_employe_textChanged(const QString &arg1)

{

  Employee e(ui->search_line_employe->text(),"","","","","");
 // QString Numero= ui->search_line_employe->text() ;
  QSqlQueryModel *model =tempemployee.cherchercinEMPLOYEE(arg1);

     ui->tableView_employee->setModel(model);

}

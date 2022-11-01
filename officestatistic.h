#ifndef OFFICESTATISTIC_H
#define OFFICESTATISTIC_H
#include<QString>
#include <QChartView>
#include<QtCharts>
#include<QChart>
 void stylee(QLineEdit *e,QLabel *icone,QString url,QString styleSheet);
 void styleeFinished(QLineEdit *e,QLabel *icone,QString url);
class OfficeStatistic
{
public:
int getEarnings();
 int getAvailabiltyOn();
 int getAvailibiltyOff();
 int getOfficeFirstMonth(QString &name);
 int getOfficeSecondMonth(QString &name);
 int getOfficeThirdMonth(QString &name);
 int getOfficeFirstMonthWorst(QString &name);
 int getOfficeSecondMonthWorst(QString &name);
 int getOfficeThirdMonthWorst(QString &name);
};

#endif // OFFICESTATISTIC_H

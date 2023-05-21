#ifndef RESETSTATE_H
#define RESETSTATE_H

#include <QLineEdit>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QDate>

void resetStateEmpl(QLineEdit *lastname, QLineEdit *firstname, QLineEdit *surname, QComboBox *gender,
                    QLineEdit *seniority, QDateTimeEdit *hire_date, QLineEdit *phone, QComboBox *position, QComboBox *department)
{
    lastname->setText("");
    firstname->setText("");
    surname->setText("");
    gender->setCurrentIndex(0);
    seniority->setText("");
    hire_date->setDate(QDate::currentDate());
    phone->setText("");
    position->setCurrentIndex(0);
    department->setCurrentIndex(0);
}

void resetStatePos(QLineEdit *posName, QLineEdit *salaryEdit)
{
    posName->setText("");
    salaryEdit->setText("");
}

#endif // RESETSTATE_H

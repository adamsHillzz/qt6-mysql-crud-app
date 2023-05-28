#ifndef RESETSTATE_H
#define RESETSTATE_H

#include <QLineEdit>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QDate>

void resetStateEmpl(QLineEdit *lastname, QLineEdit *firstname, QLineEdit *surname, QComboBox *gender,
                    QDateTimeEdit *hire_date, QLineEdit *phone, QComboBox *position, QComboBox *department)
{
    lastname->setText("");
    firstname->setText("");
    surname->setText("");
    gender->setCurrentIndex(0);
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

void resetStateDep(QLineEdit *depName, QLineEdit *officeEdit, QLineEdit *depPhone)
{
    depName->setText("");
    officeEdit->setText("");
    depPhone->setText("");
}

void resetStateDoc(QDateEdit *docDate, QLineEdit *docNumber, QComboBox *docComBox)
{
    docDate->setDate(QDate::currentDate());
    docNumber->setText("");
    docComBox->setCurrentIndex(0);
}

#endif // RESETSTATE_H

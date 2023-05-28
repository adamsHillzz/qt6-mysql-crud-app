#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QTableView>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QDataWidgetMapper>
#include <QComboBox>
#include <QtSql>


class DbController
{
public:
    DbController();
    void showError(const QSqlError &err);

    // set ComboBox relation
    void setComBoxValue(QComboBox *posComBox, QComboBox *depComBox);
    int getComBoxIndex(QComboBox *comBox);
    // seach in table
    void seachInTable(QSqlRelationalTableModel *model, QString attribute, int mode);
    // insert employee in database
    QSqlError insertNewEployee(QSqlQuery &q, QString lastname, QString firstname, QString surname, QVariant gender,
                               QDate hire_date, QString phone, int position, int department);
    QSqlError insertNewPosition(QSqlQuery &q, QString posName, int salary);
    QSqlError insertNewDepartment(QSqlQuery &q, QString depName, int officeNum, int depPhone);
    QSqlError insertNewDocument(QSqlQuery &q, QDate dataDoc, QString docNumber, int emplIndex);
    QSqlQuery* GetEmplDetailsFoID(QString id);
    // remove record from database and table
    void removeRecord(QTableView *tableView, QModelIndexList listMode);
    QSqlError updateRecordEmpl(QSqlQuery &q, QString lastname, QString firstname, QString surname, QVariant gender,
                                QDate hire_date, QString phone, int position, int department, QString idRec);
    QSqlError updateRecordPos(QSqlQuery &q, QString posName, int salary, QString idRec);
    QSqlError updateRecordDep(QSqlQuery &q, QString depName, int officeNum, int depPhone, QString idRec);
    QSqlError updateRecordDoc(QSqlQuery &q, QDate dataDoc, QString docNumber, int emplIndex, QString idRec);
private:
    QSqlRelationalTableModel *model;
    int positionIdx, departmentIdx, supervisorIdx;
};

#endif // DBCONTROLLER_H

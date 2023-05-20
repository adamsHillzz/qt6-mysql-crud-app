#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QTableView>
#include <QStandardItemModel>
#include <QDataWidgetMapper>
#include <QComboBox>
#include <QtSql>

class DbController
{
public:
    DbController();
    ~DbController();
    // set table
    void setEmoloyeeDetail(QTableView *tableView);
    void setPositionDetail(QTableView *tableView);
    void setDepartmentDetail(QTableView *tableView);
    // set ComboBox relation
    void setComBoxValue(QComboBox *posComBox, QComboBox *depComBox);
    int getComBoxIndex(QComboBox *comBox);
    // seach in table
    void seachInTable(QString attribute, int mode);
    // insert employee in database
    QSqlError insertNewEployee(QSqlQuery &q, QString lastname, QString firstname, QString surname, QVariant gender,
                    int seniority, QDate hire_date, QString phone, int position, int department);
    QSqlQuery* GetEmplDetailsFoID(QString id);
    // remove record from database and table
    void removeRecord(QTableView *tableView, QModelIndexList listMode);
    QSqlError updateRecord(QSqlQuery &q, QString lastname, QString firstname, QString surname, QVariant gender,
                           int seniority, QDate hire_date, QString phone, int position, int department, QString idRec);
private:
    QSqlRelationalTableModel *model;
    void showError(const QSqlError &err);
    int positionIdx, departmentIdx, supervisorIdx;
};

#endif // DBCONTROLLER_H

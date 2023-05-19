#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QTableView>
#include <QComboBox>
#include <QtSql>

class DbController
{
public:
    int positionIdx, departmentIdx, supervisorIdx;
    // set table
    void setEmoloyeeDetail(QTableView *tableView);
    void setPositionDetail(QTableView *tableView);
    void setDepartmentDetail(QTableView *tableView);
    // set ComboBox relation
    void setComBoxValue(QComboBox *posComBox, QComboBox *depComBox);
    // seach in table
    void seachInTable(QString attribute, int mode);
    // insert employee in database
    void insertEployee();

    ~DbController();
private:
    QSqlRelationalTableModel *model;
};

#endif // DBCONTROLLER_H

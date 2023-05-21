#include "initdb.h"
#include "dbcontroller.h"
#include "dbquerys.h"

#include <QtSql>
#include <QTableView>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>

DbController::DbController()
{
    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError)
        showError(err);
}

void DbController::DbController::showError(const QSqlError &err)
{
    QMessageBox::critical(nullptr, "Unable to initialize Database",
                          "Error initializing database: " + err.text());
}

void DbController::setComBoxValue(QComboBox *posComBox, QComboBox *depComBox)
{
    posComBox->setModel(model->relationModel(positionIdx));
    posComBox->setModelColumn(model->relationModel(positionIdx)->fieldIndex("position_name"));
    depComBox->setModel(model->relationModel(departmentIdx));
    depComBox->setModelColumn(model->relationModel(departmentIdx)->fieldIndex("department_name"));
}

int DbController::getComBoxIndex(QComboBox *comBox)
{
    int row = comBox->currentIndex();
    QModelIndex idx = comBox->model()->index(row, 0);
    QVariant data = comBox->model()->data(idx);
    return data.toInt();
}

void DbController::seachInTable(QSqlRelationalTableModel *model, QString attribute, int mode)
{
    switch (mode) {
    case 1:
        if (attribute != "")
            model->setFilter("lastname LIKE '" + attribute + "' OR name LIKE '" + attribute + '\'');
        else
            model->setFilter("");
        break;
    case 2:
        if (attribute != "")
            model->setFilter("position_name LIKE '" + attribute + "' OR salary LIKE '" + attribute + '\'');
        else
            model->setFilter("");
        break;
    case 3:
        if (attribute != "")
            model->setFilter("department_name LIKE '" + attribute + '\'');
        else
            model->setFilter("");
        break;
    default:
        break;
    }
}

QSqlError DbController::insertNewEployee(QSqlQuery &q, QString lastname, QString firstname, QString surname, QVariant gender,
                                         QDate hire_date, QString phone, int position, int department)
{
    if (!q.prepare(INSERT_EMPLOYEE_SQL))
        return q.lastError();

    q.addBindValue(lastname);
    q.addBindValue(firstname);
    q.addBindValue(surname);
    q.addBindValue(gender);
    q.addBindValue(hire_date);
    q.addBindValue(phone);
    q.addBindValue(position);
    q.addBindValue(department);
    q.exec();

    return QSqlError();
}

QSqlError DbController::insertNewPosition(QSqlQuery &q, QString posName, int salary)
{
    if (!q.prepare(INSERT_POSITION_SQL))
        return q.lastError();

    q.addBindValue(posName);
    q.addBindValue(salary);
    q.exec();

    return QSqlError();
}

QSqlError DbController::insertNewDepartment(QSqlQuery &q, QString depName, int officeNum, int depPhone)
{
    if (!q.prepare(INSERT_DEPARTMENT_SQL))
        return q.lastError();

    q.addBindValue(depName);
    q.addBindValue(officeNum);
    q.addBindValue(depPhone);
    q.exec();

    return QSqlError();
}

QSqlError DbController::insertNewDocument(QSqlQuery &q, QDate dataDoc, QString docNumber, int rate, int salary)
{
    if (!q.prepare(INSERT_DOCUMENT_SQL))
        return q.lastError();

    q.addBindValue(dataDoc);
    q.addBindValue(docNumber);
    q.addBindValue(rate);
    q.addBindValue(salary);
    q.exec();

    return QSqlError();
}

void DbController::removeRecord(QTableView *tableView, QModelIndexList listMode)
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(tableView->model());

    for (int i = 0; i < listMode.count(); i++)
    {
        //int mainId = model->data(model->index(listMode.at(i).row(), 0)).toInt();
       model->removeRow(listMode.at(i).row());
    }

    model->submitAll();
}

QSqlError DbController::updateRecordEmpl(QSqlQuery &q, QString lastname, QString firstname, QString surname, QVariant gender,
                                         QDate hire_date, QString phone, int position, int department, QString idRec)
{
    if (!q.prepare(UPDATE_EMPLOYEE_SQL))
        return q.lastError();

    q.addBindValue(lastname);
    q.addBindValue(firstname);
    q.addBindValue(surname);
    q.addBindValue(gender);
    q.addBindValue(hire_date);
    q.addBindValue(phone);
    q.addBindValue(position);
    q.addBindValue(department);
    q.addBindValue(idRec);
    q.exec();

    return QSqlError();
}

QSqlError DbController::updateRecordPos(QSqlQuery &q, QString posName, int salary, QString idRec)
{
    if (!q.prepare(UPDATE_POSITION_SQL))
        return q.lastError();

    q.addBindValue(posName);
    q.addBindValue(salary);
    q.addBindValue(idRec);
    q.exec();

    return QSqlError();
}

QSqlError DbController::updateRecordDep(QSqlQuery &q, QString depName, int officeNum, int depPhone, QString idRec)
{
    if (!q.prepare(UPDATE_DEPARTMENT_SQL))
        return q.lastError();

    q.addBindValue(depName);
    q.addBindValue(officeNum);
    q.addBindValue(depPhone);
    q.addBindValue(idRec);
    q.exec();

    return QSqlError();
}

QSqlError DbController::updateRecordDoc(QSqlQuery &q, QDate dataDoc, QString docNumber, int rate, int salary, QString idRec)
{
    if (!q.prepare(UPDATE_SALARY_SQL))
        return q.lastError();

    q.addBindValue(dataDoc);
    q.addBindValue(docNumber);
    q.addBindValue(rate);
    q.addBindValue(salary);
    q.addBindValue(idRec);
    q.exec();

    return QSqlError();
}

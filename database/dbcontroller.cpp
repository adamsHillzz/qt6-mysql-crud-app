#include "dbcontroller.h"

#include <QtSql>
#include <QTableView>
#include <QComboBox>


void DbController::setEmoloyeeDetail(QTableView *tableView)
{
    model = new QSqlRelationalTableModel(tableView);

    model->setTable("employees");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    positionIdx = model->fieldIndex("position");
    departmentIdx = model->fieldIndex("department");

    model->setRelation(positionIdx, QSqlRelation("positions", "id_pos", "position_name"));
    model->setRelation(departmentIdx, QSqlRelation("departments", "id_dep", "department_name"));

    model->setHeaderData(model->fieldIndex("lastname"), Qt::Horizontal, QTableView::tr("Фамилие"));
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, QTableView::tr("Имя"));
    model->setHeaderData(model->fieldIndex("surname"), Qt::Horizontal, QTableView::tr("Отчество"));
    model->setHeaderData(model->fieldIndex("gender"), Qt::Horizontal, QTableView::tr("Пол"));
    model->setHeaderData(model->fieldIndex("seniority"), Qt::Horizontal, QTableView::tr("Стаж"));
    model->setHeaderData(model->fieldIndex("hire_data"), Qt::Horizontal, QTableView::tr("Дата приема"));
    model->setHeaderData(model->fieldIndex("phone"), Qt::Horizontal, QTableView::tr("Телефон"));
    model->setHeaderData(positionIdx, Qt::Horizontal, QTableView::tr("Должность"));
    model->setHeaderData(departmentIdx, Qt::Horizontal, QTableView::tr("Отдел"));

    if (!model->select())
        qDebug() << model->lastError();

    tableView->setModel(model);
    tableView->setColumnHidden(model->fieldIndex("id_empl"), true);

    for (int i = 0; i < model->columnCount(); i++)
        tableView->setColumnWidth(i, 135);
}

void DbController::setPositionDetail(QTableView *tableView)
{
    model = new QSqlRelationalTableModel(tableView);

    model->setTable("positions");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(model->fieldIndex("position_name"), Qt::Horizontal, QTableView::tr("Должность"));
    model->setHeaderData(model->fieldIndex("salary"), Qt::Horizontal, QTableView::tr("Оклад"));

    if (!model->select())
        qDebug() << model->lastError();

    tableView->setModel(model);

    for (int i = 0; i < model->columnCount(); i++)
        tableView->setColumnWidth(i, 135);
}

void DbController::setDepartmentDetail(QTableView *tableView)
{
    model = new QSqlRelationalTableModel(tableView);

    model->setTable("departments");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    supervisorIdx = model->fieldIndex("supervisor");
    model->setRelation(supervisorIdx, QSqlRelation("employees", "id_empl", "lastname"));

    model->setHeaderData(model->fieldIndex("department_name"), Qt::Horizontal, QTableView::tr("Название отдела"));
    model->setHeaderData(model->fieldIndex("office_num"), Qt::Horizontal, QTableView::tr("Кабинет начальника"));
    model->setHeaderData(model->fieldIndex("department_phone"), Qt::Horizontal, QTableView::tr("Телефон отдела"));
    model->setHeaderData(supervisorIdx, Qt::Horizontal, QTableView::tr("Начальник отдела"));

    if (!model->select())
        qDebug() << model->lastError();

    tableView->setModel(model);

    for (int i = 0; i < model->columnCount(); i++)
        tableView->setColumnWidth(i, 135);
}

void DbController::setComBoxValue(QComboBox *posComBox, QComboBox *depComBox)
{
    posComBox->setModel(model->relationModel(positionIdx));
    posComBox->setModelColumn(model->relationModel(positionIdx)->fieldIndex("position_name"));
    depComBox->setModel(model->relationModel(departmentIdx));
    depComBox->setModelColumn(model->relationModel(departmentIdx)->fieldIndex("department_name"));
}

void DbController::seachInTable(QString attribute, int mode)
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

DbController::~DbController() {
    delete model;
}

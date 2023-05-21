#include "mainwindow.h"

#include "utils/validation.h"
#include "utils/activebutton.h"
#include "utils/resetstate.h"
#include "./ui_mainwindow.h"

#include <QtSql>
#include <QMessageBox>
#include <QRadioButton>
#include <QPushButton>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!QSqlDatabase::drivers().contains("QMYSQL"))
        QMessageBox::critical(this, "Unable to load database",
                              "This demo needs the MySql driver");

    if (ui->set_empl_table->isChecked())
        setEmoloyeeDetail(ui->recordTable);

    ui->seachStackedWidget->setCurrentIndex(0);

    activeButton(ui->seachStackedWidget, ui->delete_rec, ui->edit_rec);

    ui->genderComBox->addItem("мужской");
    ui->genderComBox->addItem("женский");

    connect(ui->delete_rec, &QPushButton::clicked, this, &MainWindow::delete_row_in_table);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete mapper;
}

void MainWindow::on_set_empl_table_clicked()
{
    if (Qt::Checked)
        setEmoloyeeDetail(ui->recordTable);
}


void MainWindow::on_set_pos_table_clicked()
{
    if (Qt::Checked)
        setPositionDetail(ui->recordTable);
}


void MainWindow::on_set_dep_table_clicked()
{
    if (Qt::Checked)
        setDepartmentDetail(ui->recordTable);
}

void MainWindow::on_seach_in_table_returnPressed()
{
    if (ui->set_empl_table->isChecked())
        dbController.seachInTable(model, ui->seach_in_table->text(), 1);
    else if (ui->set_pos_table->isChecked())
        dbController.seachInTable(model, ui->seach_in_table->text(), 2);
    else
        dbController.seachInTable(model, ui->seach_in_table->text(), 3);
}


void MainWindow::on_seach_rec_btn_clicked()
{
    ui->seachStackedWidget->setCurrentIndex(0);

    activeButton(ui->seachStackedWidget, ui->delete_rec, ui->edit_rec);
    setEmoloyeeDetail(ui->recordTable);

    if (ui->set_empl_table->isChecked())
        setEmoloyeeDetail(ui->recordTable);
    else if (ui->set_dep_table->isChecked())
        setDepartmentDetail(ui->recordTable);
    else setPositionDetail(ui->recordTable);
}

void MainWindow::on_add_new_rec_clicked()
{    
    ui->seachStackedWidget->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(0);

    activeButton(ui->seachStackedWidget, ui->delete_rec, ui->edit_rec);

    ui->hireDataEdit->setDate(QDate::currentDate());

    setEmoloyeeDetail(ui->empl_table);

    setComBoxValue(ui->posComBox, ui->depComBox);
}

void MainWindow::on_save_in_empl_table_clicked()
{
    validation(ui->lastnameEdit, ui->firstnameEdit, ui->surnameEdit, ui->seniorityEdit, ui->phoneEdit);

    if (!validCheck)
    {
        QMessageBox msg;
        msg.setWindowTitle("Внимание");
        msg.setIcon(QMessageBox::Warning);
        msg.setText("Пожалуйста заполните все поля");
        msg.exec();
    } else
    {
        int posIndex = getComBoxIndex(ui->posComBox);
        int depIndex = getComBoxIndex(ui->depComBox);

        qDebug() << posIndex;
        qDebug() << depIndex;

        dbController.insertNewEployee(q, ui->lastnameEdit->text(), ui->firstnameEdit->text(), ui->surnameEdit->text(),
                                      ui->genderComBox->currentText(), ui->seniorityEdit->text().toInt(),
                                      ui->hireDataEdit->date(), ui->phoneEdit->text(), posIndex, depIndex);
        setEmoloyeeDetail(ui->empl_table);

        resetStateEmpl(ui->lastnameEdit, ui->firstnameEdit, ui->surnameEdit,
                       ui->genderComBox, ui->seniorityEdit,
                       ui->hireDataEdit, ui->phoneEdit, ui->posComBox, ui->depComBox);
    };
}

void MainWindow::delete_row_in_table()
{
    QItemSelectionModel *selectMode = ui->empl_table->selectionModel();

    if (ui->tabWidget->currentIndex() == 1)
        selectMode = ui->pos_table->selectionModel();
    if (ui->tabWidget->currentIndex() == 2)
//        selectMode = ui->emplTable->selectionModel();
        qDebug() << "dep";

    QModelIndexList listMode = selectMode->selectedRows();
    qDebug() << "list: " << listMode.size();
    if (listMode.count() == 0)
    {
        QMessageBox::information(NULL, tr("Внимание"), tr("Выберите хотя бы одну строку для удаления!"), QMessageBox::Yes);
    } else
    {
        QMessageBox::information(NULL, tr("Внимание"), tr("Вы действидельно хотите удалить запись?"), QMessageBox::Yes, QMessageBox::No);
        if (QMessageBox::Yes) {
            if (ui->tabWidget->currentIndex() == 0) {
                dbController.removeRecord(ui->empl_table, listMode);
                resetStateEmpl(ui->lastnameEdit, ui->firstnameEdit, ui->surnameEdit,
                               ui->genderComBox, ui->seniorityEdit,
                               ui->hireDataEdit, ui->phoneEdit, ui->posComBox, ui->depComBox);
            }
            if (ui->tabWidget->currentIndex() == 1)
                 dbController.removeRecord(ui->pos_table, listMode);
                 resetStatePos(ui->posEdit, ui->salaryEdit);
        }
    }
}

void MainWindow::setEmoloyeeDetail(QTableView *tableView)
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

    if (tableView->objectName() == "empl_table")
    {
        mapper = new QDataWidgetMapper(this);
        mapper->setModel(model);

        mapper->addMapping(ui->lastnameEdit, model->fieldIndex("lastname"));
        mapper->addMapping(ui->firstnameEdit, model->fieldIndex("name"));
        mapper->addMapping(ui->surnameEdit, model->fieldIndex("surname"));
        mapper->addMapping(ui->genderComBox, model->fieldIndex("gender"));
        mapper->addMapping(ui->seniorityEdit, model->fieldIndex("seniority"));
        mapper->addMapping(ui->hireDataEdit, model->fieldIndex("hire_data"));
        mapper->addMapping(ui->phoneEdit, model->fieldIndex("phone"));
        mapper->addMapping(ui->posComBox, positionIdx);
        mapper->addMapping(ui->depComBox, departmentIdx);

        connect(ui->empl_table->selectionModel(),
                &QItemSelectionModel::currentRowChanged,
                mapper,
                &QDataWidgetMapper::setCurrentModelIndex
                );
    };
}

void MainWindow::setPositionDetail(QTableView *tableView)
{
    model = new QSqlRelationalTableModel(tableView);

    model->setTable("positions");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(model->fieldIndex("position_name"), Qt::Horizontal, QTableView::tr("Должность"));
    model->setHeaderData(model->fieldIndex("salary"), Qt::Horizontal, QTableView::tr("Оклад"));

    if (!model->select())
        qDebug() << model->lastError();

    tableView->setModel(model);
    tableView->setColumnHidden(model->fieldIndex("id_pos"), true);

    for (int i = 0; i < model->columnCount(); i++)
        tableView->setColumnWidth(i, 135);

    if (tableView->objectName() == "pos_table")
    {
        mapper = new QDataWidgetMapper(this);
        mapper->setModel(model);
        mapper->addMapping(ui->posEdit, model->fieldIndex("position_name"));
        mapper->addMapping(ui->salaryEdit, model->fieldIndex("salary"));

        connect(ui->pos_table->selectionModel(),
                &QItemSelectionModel::currentRowChanged,
                mapper,
                &QDataWidgetMapper::setCurrentModelIndex
                );
    };
}

void MainWindow::setDepartmentDetail(QTableView *tableView)
{
    model = new QSqlRelationalTableModel(tableView);

    model->setTable("departments");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(model->fieldIndex("department_name"), Qt::Horizontal, QTableView::tr("Название отдела"));
    model->setHeaderData(model->fieldIndex("office_num"), Qt::Horizontal, QTableView::tr("Кабинет начальника"));
    model->setHeaderData(model->fieldIndex("department_phone"), Qt::Horizontal, QTableView::tr("Телефон отдела"));

    if (!model->select())
        qDebug() << model->lastError();

    tableView->setModel(model);

    for (int i = 0; i < model->columnCount(); i++)
        tableView->setColumnWidth(i, 135);
}

void MainWindow::setComBoxValue(QComboBox *posComBox, QComboBox *depComBox)
{
    posComBox->setModel(model->relationModel(positionIdx));
    posComBox->setModelColumn(model->relationModel(positionIdx)->fieldIndex("position_name"));
    depComBox->setModel(model->relationModel(departmentIdx));
    depComBox->setModelColumn(model->relationModel(departmentIdx)->fieldIndex("department_name"));
}

int MainWindow::getComBoxIndex(QComboBox *comBox)
{
    int row = comBox->currentIndex();
    QModelIndex idx = comBox->model()->index(row, 0);
    QVariant data = comBox->model()->data(idx);
    return data.toInt();
}

void MainWindow::on_edit_rec_clicked()
{
    if (ui->tabWidget->currentIndex() == 0)
    {
        validation(ui->lastnameEdit, ui->firstnameEdit, ui->surnameEdit, ui->seniorityEdit, ui->phoneEdit);

        if (!validCheck)
        {
            QMessageBox msg;
            msg.setWindowTitle("Внимание");
            msg.setIcon(QMessageBox::Warning);
            msg.setText("Для того чтобы изменить запись сначало выберите её, щелкнув по ячейке таблице");
            msg.exec();
        } else {
            int posIndex = getComBoxIndex(ui->posComBox);
            int depIndex = getComBoxIndex(ui->depComBox);

            dbController.updateRecordEmpl(q, ui->lastnameEdit->text(), ui->firstnameEdit->text(), ui->surnameEdit->text(),
                                      ui->genderComBox->currentText(), ui->seniorityEdit->text().toInt(),
                                      ui->hireDataEdit->date(), ui->phoneEdit->text(), posIndex, depIndex, idRec);
            setEmoloyeeDetail(ui->empl_table);

            resetStateEmpl(ui->lastnameEdit, ui->firstnameEdit, ui->surnameEdit,
                           ui->genderComBox, ui->seniorityEdit,
                           ui->hireDataEdit, ui->phoneEdit, ui->posComBox, ui->depComBox);
        }
    } else if (ui->tabWidget->currentIndex() == 1)
    {
        validation(ui->posEdit, ui->salaryEdit);

        if (!validCheck)
        {
            QMessageBox msg;
            msg.setWindowTitle("Внимание");
            msg.setIcon(QMessageBox::Warning);
            msg.setText("Для того чтобы изменить запись сначало выберите её, щелкнув по ячейке таблице");
            msg.exec();
        } else
        {
            dbController.updateRecordPos(q, ui->posEdit->text(), ui->salaryEdit->text().toInt(), idRec);
            setPositionDetail(ui->pos_table);

            resetStatePos(ui->posEdit, ui->salaryEdit);
        }
    }
}

void MainWindow::on_save_in_pos_table_clicked()
{
    validation(ui->posEdit, ui->salaryEdit);

    if (!validCheck)
    {
        QMessageBox msg;
        msg.setWindowTitle("Внимание");
        msg.setIcon(QMessageBox::Warning);
        msg.setText("Пожалуйста заполните все поля");
        msg.exec();
    } else
    {
        dbController.insertNewPosition(q, ui->posEdit->text(), ui->salaryEdit->text().toInt());
        setPositionDetail(ui->pos_table);

        resetStatePos(ui->posEdit, ui->salaryEdit);
    };
}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    setEmoloyeeDetail(ui->empl_table);

    if (index == 1)
    {
        setPositionDetail(ui->pos_table);
    }
}


void MainWindow::on_empl_table_clicked(const QModelIndex &index)
{
   idRec = ui->empl_table->model()->index(index.row(), 0).data().toString();
}


void MainWindow::on_pos_table_clicked(const QModelIndex &index)
{
   idRec = ui->pos_table->model()->index(index.row(), 0).data().toString();
}


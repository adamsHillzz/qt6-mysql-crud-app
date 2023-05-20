#include "mainwindow.h"

#include "utils/validation.h"
#include "utils/activebutton.h"
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
        dbController.setEmoloyeeDetail(ui->recordTable);

    ui->seachStackedWidget->setCurrentIndex(0);

    activeButton(ui->seachStackedWidget, ui->delete_rec, ui->edit_rec);

    ui->genderComBox->addItem("мужской");
    ui->genderComBox->addItem("женский");

    connect(ui->delete_rec, &QPushButton::clicked, this, &MainWindow::delete_row_in_table);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_set_empl_table_clicked()
{
    if (Qt::Checked)
        dbController.setEmoloyeeDetail(ui->recordTable);
}


void MainWindow::on_set_pos_table_clicked()
{
    if (Qt::Checked)
        dbController.setPositionDetail(ui->recordTable);
}


void MainWindow::on_set_dep_table_clicked()
{
    if (Qt::Checked)
        dbController.setDepartmentDetail(ui->recordTable);
}

void MainWindow::on_seach_in_table_returnPressed()
{
    if (ui->set_empl_table->isChecked())
        dbController.seachInTable(ui->seach_in_table->text(), 1);
    else if (ui->set_pos_table->isChecked())
        dbController.seachInTable(ui->seach_in_table->text(), 2);
    else
        dbController.seachInTable(ui->seach_in_table->text(), 3);
}


void MainWindow::on_seach_rec_btn_clicked()
{
    ui->seachStackedWidget->setCurrentIndex(0);

    activeButton(ui->seachStackedWidget, ui->delete_rec, ui->edit_rec);

    if (ui->set_empl_table->isChecked())
        dbController.setEmoloyeeDetail(ui->recordTable);
    else if (ui->set_dep_table->isChecked())
        dbController.setDepartmentDetail(ui->recordTable);
    else dbController.setPositionDetail(ui->recordTable);
}

void MainWindow::on_add_new_rec_clicked()
{    
    ui->seachStackedWidget->setCurrentIndex(1);

    activeButton(ui->seachStackedWidget, ui->delete_rec, ui->edit_rec);

    ui->hireDataEdit->setDate(QDate::currentDate());

    dbController.setEmoloyeeDetail(ui->emplTable);
    // ComboBox set value
    dbController.setComBoxValue(ui->posComBox, ui->depComBox);
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
        int posIndex = dbController.getComBoxIndex(ui->posComBox);
        int depIndex = dbController.getComBoxIndex(ui->depComBox);

        dbController.insertNewEployee(q, ui->lastnameEdit->text(), ui->firstnameEdit->text(), ui->surnameEdit->text(),
                                      ui->genderComBox->currentText(), ui->seniorityEdit->text().toInt(),
                                      ui->hireDataEdit->date(), ui->phoneEdit->text(), posIndex, depIndex);
        dbController.setEmoloyeeDetail(ui->emplTable);
    };
}

void MainWindow::delete_row_in_table()
{
    QItemSelectionModel *selectMode = ui->emplTable->selectionModel();

    if (ui->tabWidget->currentIndex() == 1)
//        selectMode = ui->emplTable->selectionModel();
        qDebug() << "pos";
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
        if (QMessageBox::Yes)
            dbController.removeRecord(ui->emplTable, listMode);
    }
}

void MainWindow::on_edit_rec_clicked()
{
    validation(ui->lastnameEdit, ui->firstnameEdit, ui->surnameEdit, ui->seniorityEdit, ui->phoneEdit);

    if (!validCheck)
    {
        QMessageBox msg;
        msg.setWindowTitle("Внимание");
        msg.setIcon(QMessageBox::Warning);
        msg.setText("Для того чтобы изменить запись щелкните по ячейке таблице двойным кликом");
        msg.exec();
    } else {
        int posIndex = dbController.getComBoxIndex(ui->posComBox);
        int depIndex = dbController.getComBoxIndex(ui->depComBox);

        dbController.updateRecord(q, ui->lastnameEdit->text(), ui->firstnameEdit->text(), ui->surnameEdit->text(),
                                      ui->genderComBox->currentText(), ui->seniorityEdit->text().toInt(),
                                      ui->hireDataEdit->date(), ui->phoneEdit->text(), posIndex, depIndex, idRec);
        dbController.setEmoloyeeDetail(ui->emplTable);
    }
}


void MainWindow::on_emplTable_doubleClicked(const QModelIndex &index)
{
    idRec = ui->emplTable->model()->index(index.row(), 0).data().toString();
    QSqlQuery* q = dbController.GetEmplDetailsFoID(idRec);

    QString gender = q->value("gender").toString();

    if (gender == "мужской")
        ui->genderComBox->setCurrentIndex(0);
    else
        ui->genderComBox->setCurrentIndex(1);

    ui->lastnameEdit->setText(q->value("lastname").toString());
    ui->firstnameEdit->setText(q->value("name").toString());
    ui->surnameEdit->setText(q->value("surname").toString());
    ui->hireDataEdit->setDate(q->value("hire_data").toDate());
    ui->phoneEdit->setText(q->value("phone").toString());
    ui->seniorityEdit->setText(q->value("seniority").toString());
    ui->posComBox->setCurrentIndex(q->value("position").toInt() - 1);
    ui->depComBox->setCurrentIndex(q->value("department").toInt() - 1);
}


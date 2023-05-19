#include "mainwindow.h"

#include "database/initdb.h"
#include "utils/validation.h"
#include "./ui_mainwindow.h"

#include <QtSql>
#include <QMessageBox>
#include <QRadioButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!QSqlDatabase::drivers().contains("QMYSQL"))
        QMessageBox::critical(this, "Unable to load database",
                              "This demo needs the MySql driver");

    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError)
        showError(err);

    if (ui->set_empl_table->isChecked())
        dbController.setEmoloyeeDetail(ui->recordTable);

    ui->seachStackedWidget->setCurrentIndex(0);

    ui->genderComBox->addItem("мужской");
    ui->genderComBox->addItem("женский");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                          "Error initializing database: " + err.text());
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
}

void MainWindow::on_add_new_rec_clicked()
{    
    ui->seachStackedWidget->setCurrentIndex(1);
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

    };
}


#include "coeffwindow.h"
#include "ui_coeffwindow.h"

CoeffWindow::CoeffWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoeffWindow)
{
    ui->setupUi(this);
    model = new QSqlRelationalTableModel(ui->coeff_table);

    model->setTable("rates");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    if (!model->select())
        qDebug() << model->lastError();

    ui->coeff_table->setModel(model);
}

CoeffWindow::~CoeffWindow()
{
    delete ui;
}


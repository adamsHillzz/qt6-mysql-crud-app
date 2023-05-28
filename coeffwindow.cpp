#include "coeffwindow.h"
#include "database/dbquerys.h"
#include "ui_coeffwindow.h"

CoeffWindow::CoeffWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CoeffWindow)
{
    ui->setupUi(this);

    setCoeffDetails();
}

CoeffWindow::~CoeffWindow()
{
    delete ui;
    delete mapper;
}

void CoeffWindow::on_save_coeff_clicked()
{
    if(ui->stageEdit->text() == "" || ui->coeffEdit->text() == "")
    {
        QMessageBox msg;
        msg.setWindowTitle("Внимание");
        msg.setIcon(QMessageBox::Warning);
        msg.setText("Пожалуйста заполните все поля");
        msg.exec();
    } else
    {
        insertCoeff(ui->stageEdit->text(), ui->coeffEdit->text());
        setCoeffDetails();

        ui->stageEdit->setText("");
        ui->coeffEdit->setText("");
    }
}

void CoeffWindow::setCoeffDetails()
{
    model = new QSqlRelationalTableModel(ui->coeff_table);

    model->setTable("rates");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(model->fieldIndex("stage"), Qt::Horizontal, QTableView::tr("Стаж"));
    model->setHeaderData(model->fieldIndex("coeff"), Qt::Horizontal, QTableView::tr("Ставка"));

    if (!model->select())
        qDebug() << model->lastError();

    ui->coeff_table->setModel(model);
    ui->coeff_table->setColumnHidden(model->fieldIndex("id_rate"), true);

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->addMapping(ui->stageEdit, model->fieldIndex("stage"));
    mapper->addMapping(ui->coeffEdit, model->fieldIndex("coeff"));

    connect(ui->coeff_table->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            mapper,
            &QDataWidgetMapper::setCurrentModelIndex
            );
}

QSqlError CoeffWindow::insertCoeff(QString stageValue, QString coeffValue)
{
    QSqlQuery q;
    if (!q.prepare(INSERT_COEFF_SQL))
        return q.lastError();

    q.addBindValue(stageValue);
    q.addBindValue(coeffValue);
    q.exec();

    return QSqlError();
}

QSqlError CoeffWindow::updateCoeff(QString stageValue, QString coeffValue, QString idRec)
{
    QSqlQuery q;
    if (!q.prepare(UPDATE_COEFF_SQL))
        return q.lastError();

    q.addBindValue(stageValue);
    q.addBindValue(coeffValue);
    q.addBindValue(idRec);
    q.exec();

    return QSqlError();
}

void CoeffWindow::removeCoeff(QTableView *tableView, QModelIndexList listMode)
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(tableView->model());

    for (int i = 0; i < listMode.count(); i++)
    {
        model->removeRow(listMode.at(i).row());
    }

    model->submitAll();
}


void CoeffWindow::on_coeff_table_clicked(const QModelIndex &index)
{
    idRec = ui->coeff_table->model()->index(index.row(), 0).data().toString();
}


void CoeffWindow::on_edit_coeff_clicked()
{
    if(ui->stageEdit->text() == "" || ui->coeffEdit->text() == "")
    {
        QMessageBox msg;
        msg.setWindowTitle("Внимание");
        msg.setIcon(QMessageBox::Warning);
        msg.setText("Пожалуйста заполните все поля");
        msg.exec();
    } else
    {
        updateCoeff(ui->stageEdit->text(), ui->coeffEdit->text(), idRec);
        setCoeffDetails();

        ui->stageEdit->setText("");
        ui->coeffEdit->setText("");
    }
}


void CoeffWindow::on_delete_coeff_clicked()
{
    QItemSelectionModel *selectMode = ui->coeff_table->selectionModel();

    selectMode = ui->coeff_table->selectionModel();

    QModelIndexList listMode = selectMode->selectedRows();
    qDebug() << "list: " << listMode.size();

    if (listMode.count() == 0)
    {
        QMessageBox::information(NULL, tr("Внимание"), tr("Выберите хотя бы одну строку для удаления!"), QMessageBox::Yes);
    } else
    {
        QMessageBox::information(NULL, tr("Внимание"), tr("Вы действидельно хотите удалить запись?"), QMessageBox::Yes, QMessageBox::No);
        if (QMessageBox::Yes) {
            removeCoeff(ui->coeff_table, listMode);

            ui->stageEdit->setText("");
            ui->coeffEdit->setText("");
        }
    }
}


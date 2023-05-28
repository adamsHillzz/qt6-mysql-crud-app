#ifndef COEFFWINDOW_H
#define COEFFWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QTableView>
#include <QMessageBox>
#include <QDataWidgetMapper>

namespace Ui {
class CoeffWindow;
}

class CoeffWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CoeffWindow(QWidget *parent = nullptr);
    ~CoeffWindow();

private slots:
    void on_save_coeff_clicked();

    void on_coeff_table_clicked(const QModelIndex &index);

    void on_edit_coeff_clicked();

    void on_delete_coeff_clicked();

private:
    void setCoeffDetails();
    QString idRec;
    QSqlError insertCoeff(QString stageValue, QString coeffValue);
    QSqlError updateCoeff(QString stageValue, QString coeffValue, QString idRec);
    void removeCoeff(QTableView *tableView, QModelIndexList listMode);
    QDataWidgetMapper *mapper = new QDataWidgetMapper();
    QSqlRelationalTableModel *model;
    Ui::CoeffWindow *ui;
};

#endif // COEFFWINDOW_H

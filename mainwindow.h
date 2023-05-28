#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database/dbcontroller.h"

#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_set_empl_table_clicked();

    void on_set_pos_table_clicked();

    void on_set_dep_table_clicked();

    void on_seach_in_table_returnPressed();

    void on_seach_rec_btn_clicked();

    void on_add_new_rec_clicked();

    //void getIndexRow(const QModelIndex &index);

    void delete_row_in_table();

    void on_edit_rec_clicked();

    void on_save_in_empl_table_clicked();

    void on_save_in_pos_table_clicked();

    void on_save_in_dep_table_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_empl_table_clicked(const QModelIndex &index);

    void on_pos_table_clicked(const QModelIndex &index);

    void on_dep_table_clicked(const QModelIndex &index);

    void on_doc_table_clicked(const QModelIndex &index);

    void on_save_in_doc_table_clicked();

    void on_open_coeff_window_clicked();

private:
    void setEmoloyeeDetail(QTableView *tableView);
    void setDocumentDetail(QTableView *tableView, QComboBox *docComBox);
    void setPositionDetail(QTableView *tableView);
    void setDepartmentDetail(QTableView *tableView);
    QSqlQueryModel* getStatementDetail();
    void setComBoxValue(QComboBox *posComBox, QComboBox *depComBox);
    int getComBoxIndex(QComboBox *comBox);
    int positionIdx, departmentIdx, salaryIdx, employeeIdx;
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper = new QDataWidgetMapper();
    DbController dbController;
    QString idRec;
    QSqlQuery q;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

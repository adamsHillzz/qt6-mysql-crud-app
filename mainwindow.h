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

    void on_save_in_empl_table_clicked();

private:
    DbController dbController;
    void showError(const QSqlError &err);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

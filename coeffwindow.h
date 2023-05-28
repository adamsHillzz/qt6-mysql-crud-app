#ifndef COEFFWINDOW_H
#define COEFFWINDOW_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class CoeffWindow;
}

class CoeffWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CoeffWindow(QWidget *parent = nullptr);
    ~CoeffWindow();

private:
    QSqlRelationalTableModel *model;
    Ui::CoeffWindow *ui;
};

#endif // COEFFWINDOW_H

#ifndef ACTIVEBUTTON_H
#define ACTIVEBUTTON_H

#include <QPushButton>
#include <QStackedWidget>

void activeButton(QStackedWidget *qStackWidget, QPushButton *deleteBtn, QPushButton *EditBtn)
{
    if (qStackWidget->currentIndex() == 0 || qStackWidget->currentIndex() == 2)
    {
        deleteBtn->setEnabled(false);
        EditBtn->setEnabled(false);
    } else {
        deleteBtn->setEnabled(true);
        EditBtn->setEnabled(true);
    }
}

#endif // ACTIVEBUTTON_H

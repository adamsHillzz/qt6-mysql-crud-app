#ifndef VALIDATIONEDIT_H
#define VALIDATIONEDIT_H

#include <QLineEdit>

bool validCheck;

template<typename Arg>
void validation(Arg lineEdit)
{
    lineEdit->text() != "" ? validCheck = true : validCheck = false;
}

template<typename Arg, typename... Args>
void validation(Arg arg, Args... args)
{
    if (dynamic_cast<QLineEdit *>(arg) != NULL)
    {
        arg->text() != "" ? validCheck = true : validCheck = false;

        validation(arg);
        validation(args...);
    };
}

#endif // VALIDATIONEDIT_H

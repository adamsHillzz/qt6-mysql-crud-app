#ifndef DBQUERY_H
#define DBQUERY_H

#include <QLatin1String>

const auto INSERT_EMPLOYEE_SQL = QLatin1String(R"(
    insert into employees(lastname, name, surname, gender, seniority, hire_data, phone, position, department) values(?, ?, ?, ?, ?, ?, ?, ?, ?);
)");

const auto DELETE_EMPLOYEE_SQL = QLatin1String(R"(
    delete from employees whe
)");

#endif // DBQUERY_H

#ifndef DBQUERY_H
#define DBQUERY_H

#include <QLatin1String>

const auto INSERT_EMPLOYEE_SQL = QLatin1String(R"(
    insert into employees(lastname, name, surname, gender, seniority, hire_data, phone, position, department) values(?, ?, ?, ?, ?, ?, ?, ?, ?);
)");

const auto SELECT_EMPLOYEE_SQL = QLatin1String(R"(
    select id_empl, lastname, name, surname, gender, seniority, hire_data, phone, position, department FROM employees where id_empl = ?;
)");

const auto UPDATE_EMPLOYEE_SQL = QLatin1String(R"(
    update employees set lastname = ?, name = ?, surname = ?, gender = ?, seniority = ?, hire_data = ?, phone = ?, position = ?, department = ? where id_empl = ?;
)");


#endif // DBQUERY_H

#ifndef DBQUERY_H
#define DBQUERY_H

#include <QLatin1String>

const auto INSERT_EMPLOYEE_SQL = QLatin1String(R"(
    insert into employees(lastname, name, surname, gender, hire_data, phone, position, department) values(?, ?, ?, ?, ?, ?, ?, ?);
)");

const auto INSERT_POSITION_SQL = QLatin1String(R"(
    insert into positions(position_name, salary) values(?, ?);
)");

const auto INSERT_DEPARTMENT_SQL = QLatin1String(R"(
    insert into departments(department_name, office_num, department_phone) values(?, ?, ?);
)");

const auto INSERT_DOCUMENT_SQL = QLatin1String(R"(
    insert into statement(data_doc, doc_number, employee) values(?, ?, ?);
)");

const auto INSERT_COEFF_SQL = QLatin1String(R"(
    insert into rates(stage, coeff) values(?, ?);
)");

const auto UPDATE_EMPLOYEE_SQL = QLatin1String(R"(
    update employees set lastname = ?, name = ?, surname = ?, gender = ?, hire_data = ?, phone = ?, position = ?, department = ? where id_empl = ?;
)");

const auto UPDATE_POSITION_SQL = QLatin1String(R"(
    update positions set position_name = ?, salary = ? where id_pos = ?;
)");

const auto UPDATE_DEPARTMENT_SQL = QLatin1String(R"(
    update departments set department_name = ?, office_num = ?, department_phone = ? where id_dep = ?;
)");

const auto UPDATE_SALARY_SQL = QLatin1String(R"(
    update statement set data_doc = ?, doc_number = ?, employee = ? where id_doc = ?;
)");

const auto UPDATE_COEFF_SQL = QLatin1String(R"(
    update rates set stage = ?, coeff = ? where id_rate = ?;
)");

#endif // DBQUERY_H

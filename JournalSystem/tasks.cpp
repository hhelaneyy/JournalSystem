#include <iostream>
#include <string>
#include <iomanip>
#include <format>
#include <sqlite3.h>

void init_db() {
	sqlite3* DB = nullptr;
	char* errorMessage;

	if (sqlite3_open("journal.db", &DB) != SQLITE_OK) {
		std::cerr << "Ошибка подключения к БД: " << sqlite3_errmsg(DB);
		return;
	}

	std::string sql = "CREATE TABLE IF NOT EXISTS groups(" 
		"id INT PRIMARY KEY NOT NULL,"
		"name TEXT NOT NULL);";
	std::string sql2 = "CREATE TABLE IF NOT EXISTS students("
		"id INT PRIMARY KEY NOT NULL,"
		"name TEXT NOT NULL,"
		"group_id INT NOT NULL);";
	std::string sql3 = "CREATE TABLE IF NOT EXISTS subjects("
		"id INT PRIMARY KEY NOT NULL,"
		"name TEXT NOT NULL);";
	std::string sql4 = "CREATE TABLE IF NOT EXISTS grades("
		"id INT PRIMARY KEY NOT NULL,"
		"student_id INT NOT NULL,"
		"subject_id INT NOT NULL,"
		"value INT NOT NULL,"
		"attempt INT NOT NULL);";

	int rc = sqlite3_exec(DB, sql.c_str(), nullptr, nullptr, &errorMessage);
	int rc2 = sqlite3_exec(DB, sql2.c_str(), nullptr, nullptr, &errorMessage);
	int rc3 = sqlite3_exec(DB, sql3.c_str(), nullptr, nullptr, &errorMessage);
	int rc4 = sqlite3_exec(DB, sql4.c_str(), nullptr, nullptr, &errorMessage);

	if (rc != SQLITE_OK && rc2 != SQLITE_OK && rc3 != SQLITE_OK && rc4 != SQLITE_OK) {
		std::cerr << "Error SQL: " << errorMessage << std::endl;
		sqlite3_free(errorMessage);
	}

	sqlite3_close(DB);
}

void add_group() {
	sqlite3* DB;
	std::string name;
	int id;

	if (sqlite3_open("journal.db", &DB) != SQLITE_OK) {
		std::cerr << "Ошибка подключения к БД: " << sqlite3_errmsg(DB);
		return;
	}

	std::cout << "Введите номер группы: ";
	std::cin >> id;
	std::cin.ignore();
	std::cout << "Введите название группы: ";
	getline(std::cin, name);

	sqlite3_stmt* stmt;
	const char* sql = "INSERT INTO groups (id, name) VALUES (?, ?);";

	sqlite3_prepare_v2(DB, sql, -1, &stmt, 0);

	sqlite3_bind_int(stmt, 1, id);
	sqlite3_bind_text(stmt, 2, name.c_str(), -1 ,SQLITE_TRANSIENT);

	if (sqlite3_step(stmt) == SQLITE_DONE) {
		std::cout << "Успех! Группа создана." << std::endl;
	}
	else {
		std::cout << "Возникла неизвестная ошибка: Не удалось создать группу.\nВозможно, группа с таким номером уже создана." << std::endl;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}

void del_group() {
	sqlite3* DB;
	int id;

	if (sqlite3_open("journal.db", &DB) != SQLITE_OK) {
		std::cerr << "Ошибка подключения к БД: " << sqlite3_errmsg(DB);
		return;
	}

	std::cout << "Введите номер группы: ";
	std::cin >> id;
	std::cin.ignore();

	sqlite3_stmt* stmt;
	const char* sql = "DELETE FROM groups WHERE id = ?;";

	sqlite3_prepare_v2(DB, sql, -1, &stmt, 0);
	sqlite3_bind_int(stmt, 1, id);

	if (sqlite3_step(stmt) == SQLITE_DONE) {
		if (sqlite3_changes(DB) > 0) {
			std::cout << "Успех! Группа удалена." << std::endl;
		}
		else {
			std::cout << "Возникла ошибка: Не удалось удалить группу.\nВозможно, группа с таким номером не существует." << std::endl;
		}
	}
	else {
		std::cout << "Возникла неизвестная ошибка: Не удалось удалить группу." << std::endl;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}

void get_groups() {
	sqlite3* DB;
	if (sqlite3_open("journal.db", &DB) != SQLITE_OK) {
		std::cerr << "Ошибка открытия БД" << std::endl;
		return;
	}

	const char* sql = "SELECT * FROM groups;";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(DB, sql, -1, &stmt, 0) != SQLITE_OK) {
		std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(DB) << std::endl;
		sqlite3_close(DB);
		return;
	}

	std::cout << "\n" << std::left
		<< std::setw(8) << "ID группы"
		<< std::setw(20) << "Название группы" << std::endl;

	std::cout << std::string(71, '-') << std::endl;

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		std::cout << std::left
			<< std::setw(8) << sqlite3_column_int(stmt, 0)
			<< std::setw(20) << (const char*)sqlite3_column_text(stmt, 1) << std::endl;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}

void add_student() {
	sqlite3* DB;
	std::string name;
	int gid, id;

	if (sqlite3_open("journal.db", &DB) != SQLITE_OK) {
		std::cerr << "Ошибка подключения к БД: " << sqlite3_errmsg(DB);
		return;
	}


	std::cout << "Введите номер группы: ";
	std::cin >> gid;
	std::cin.ignore();
	std::cout << "Введите ID студента: ";
	std::cin >> id;
	std::cin.ignore();
	std::cout << "Введите студента: ";
	getline(std::cin, name);

	sqlite3_stmt* stmt;
	const char* sql = "INSERT INTO students (id, name, group_id) VALUES (?, ?, ?);";
	sqlite3_stmt* stmt2;
	const char* sql2 = "SELECT * FROM groups WHERE id=?;";

	sqlite3_prepare_v2(DB, sql, -1, &stmt, 0);
	sqlite3_prepare_v2(DB, sql2, -1, &stmt2, 0);
	sqlite3_bind_int(stmt2, 1, gid);

	if (sqlite3_step(stmt2) == SQLITE_ROW) {
		sqlite3_bind_int(stmt, 1, id);
		sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 3, gid);

		if (sqlite3_step(stmt) == SQLITE_DONE) {
			std::cout << "Успех! Студент добавлен в группу с ID: " << gid << std::endl;
		}
		else {
			std::cout << "Возникла неизвестная ошибка: Не удалось создать студента.\nВозможно, студент с таким номером уже создан." << std::endl;
		}
	}
	else {
		std::cout << "Возникла неизвестная ошибка: Не удалось создать студента." << std::endl;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}

void del_student() {
	sqlite3* DB;
	int id;

	if (sqlite3_open("journal.db", &DB) != SQLITE_OK) {
		std::cerr << "Ошибка подключения к БД: " << sqlite3_errmsg(DB);
		return;
	}

	std::cout << "Введите ID студента: ";
	std::cin >> id;
	std::cin.ignore();

	sqlite3_stmt* stmt;
	const char* sql = "DELETE FROM students WHERE id = ?;";

	sqlite3_prepare_v2(DB, sql, -1, &stmt, 0);
	sqlite3_bind_int(stmt, 1, id);

	if (sqlite3_step(stmt) == SQLITE_DONE) {
		if (sqlite3_changes(DB) > 0) {
			std::cout << "Успех! Студент удалён." << std::endl;
		}
		else {
			std::cout << "Возникла ошибка: Не удалось удалить студента.\nВозможно, студента с таким ID не существует." << std::endl;
			std::cout << "\nНажмите Enter, чтобы продолжить...";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
		}
	}
	else {
		std::cout << "Возникла неизвестная ошибка: Не удалось удалить студента." << std::endl;
		std::cout << "\nНажмите Enter, чтобы продолжить...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}

void get_students() {
	sqlite3* DB;
	if (sqlite3_open("journal.db", &DB) != SQLITE_OK) {
		std::cerr << "Ошибка открытия БД" << std::endl;
		return;
	}

	const char* sql = "SELECT * FROM students;";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(DB, sql, -1, &stmt, 0) != SQLITE_OK) {
		std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(DB) << std::endl;
		sqlite3_close(DB);
		return;
	}

	std::cout << "\n" << std::left
		<< std::setw(8) << "ID студента"
		<< std::setw(8) << "ФИО"
		<< std::setw(15) << "ID группы" << std::endl;

	std::cout << std::string(71, '-') << std::endl;

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		std::cout << std::left
			<< std::setw(8) << sqlite3_column_int(stmt, 0)
			<< std::setw(20) << (const char*)sqlite3_column_text(stmt, 1)
			<< std::setw(8) << sqlite3_column_int(stmt, 2) << std::endl;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}

void add_subject() {
	sqlite3* DB;
	std::string subject;
	int id;

	if (sqlite3_open("journal.db", &DB) != SQLITE_OK) {
		std::cerr << "Ошибка подключения к БД: " << sqlite3_errmsg(DB);
		return;
	}


	std::cout << "Введите ID предмета: ";
	std::cin >> id;
	std::cin.ignore();
	std::cout << "Введите название предмета: ";
	getline(std::cin, subject);

	sqlite3_stmt* stmt;
	const char* sql = "INSERT INTO subjects (id, name) VALUES (?, ?);";

	sqlite3_prepare_v2(DB, sql, -1, &stmt, 0);

	sqlite3_bind_int(stmt, 1, id);
	sqlite3_bind_text(stmt, 2, subject.c_str(), -1, SQLITE_TRANSIENT);

	if (sqlite3_step(stmt) == SQLITE_DONE) {
		std::cout << "Успех! Предмет добавлен." << std::endl;
	}
	else {
		std::cout << "Возникла неизвестная ошибка: Не удалось создать студента.\nВозможно, студент с таким номером уже создан." << std::endl;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}

void del_subject() {
	sqlite3* DB;
	int id;

	if (sqlite3_open("journal.db", &DB) != SQLITE_OK) {
		std::cerr << "Ошибка подключения к БД: " << sqlite3_errmsg(DB);
		return;
	}

	std::cout << "Введите ID студента: ";
	std::cin >> id;
	std::cin.ignore();

	sqlite3_stmt* stmt;
	const char* sql = "DELETE FROM students WHERE id = ?;";

	sqlite3_prepare_v2(DB, sql, -1, &stmt, 0);
	sqlite3_bind_int(stmt, 1, id);

	if (sqlite3_step(stmt) == SQLITE_DONE) {
		if (sqlite3_changes(DB) > 0) {
			std::cout << "Успех! Студент удалён." << std::endl;
		}
		else {
			std::cout << "Возникла ошибка: Не удалось удалить студента.\nВозможно, студента с таким ID не существует." << std::endl;
			std::cout << "\nНажмите Enter, чтобы продолжить...";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
		}
	}
	else {
		std::cout << "Возникла неизвестная ошибка: Не удалось удалить студента." << std::endl;
		std::cout << "\nНажмите Enter, чтобы продолжить...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}

void get_subjects() {
	sqlite3* DB;
	if (sqlite3_open("journal.db", &DB) != SQLITE_OK) {
		std::cerr << "Ошибка открытия БД" << std::endl;
		return;
	}

	const char* sql = "SELECT * FROM students;";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(DB, sql, -1, &stmt, 0) != SQLITE_OK) {
		std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(DB) << std::endl;
		sqlite3_close(DB);
		return;
	}

	std::cout << "\n" << std::left
		<< std::setw(8) << "ID студента"
		<< std::setw(8) << "ФИО"
		<< std::setw(15) << "ID группы" << std::endl;

	std::cout << std::string(71, '-') << std::endl;

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		std::cout << std::left
			<< std::setw(8) << sqlite3_column_int(stmt, 0)
			<< std::setw(20) << (const char*)sqlite3_column_text(stmt, 1)
			<< std::setw(8) << sqlite3_column_int(stmt, 2) << std::endl;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
}
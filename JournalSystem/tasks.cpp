#include <iostream>
#include <string>
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
	else {
		std::cout << "Working" << std::endl;
	}
	sqlite3_close(DB);
}
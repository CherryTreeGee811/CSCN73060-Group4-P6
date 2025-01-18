#pragma once
#include <sqlite3.h>
#include <string>
#include "crow_all.h"


class Database {
    public:
        Database(const std::string& db_name);
        ~Database();

        void createBookTable(void);
        void seedBookTableWithSampleData(void);
        crow::json::wvalue getBooks(void);
        crow::json::wvalue addBook(const crow::request& book);

    private:
        sqlite3* db;
};
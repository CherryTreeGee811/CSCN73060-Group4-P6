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
        crow::json::wvalue getBooks(int page, const int limit);
        crow::json::wvalue addBook(const crow::request& book);
        crow::json::wvalue updateBook(const crow::request& book, const int id);
        crow::json::wvalue deleteBook(const int id);
        crow::json::wvalue updateBookDescription(const crow::request& book, const int id);

    private:
        sqlite3* db;
};
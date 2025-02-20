#include <sqlite3.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "crow_all.h"
#include "../../include/utils/db_utils.h"


Database::Database(const std::string& db_name) {
    if(sqlite3_open(db_name.c_str(), &db)) {
        fprintf(stderr, "Can't open sqlite database: %s\n", sqlite3_errmsg(db));
    }
    else {
        createBookTable();
        seedBookTableWithSampleData();
    }
}


Database::~Database() {
    sqlite3_close(db);
}
        

void Database::createBookTable(void) {
    const char* query = "CREATE TABLE IF NOT EXISTS BOOKS("
                        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "TITLE TEXT NOT NULL,"
                        "AUTHOR TEXT,"
                        "DESCRIPTION TEXT);";
    char *errMsg = 0;

    if (sqlite3_exec(db, query, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "Error creating BOOKS table: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}


void Database::seedBookTableWithSampleData(void) {
    const char* query = "INSERT INTO BOOKS (TITLE, AUTHOR, DESCRIPTION)"
                        "VALUES('Learn French Easy', 'Jean Leblanc', 'Learn basic sentences for day to day conversations'),"
                        "('Learn Spanish Easy', 'Juan Ramos', 'Be able to explore the world and converse with people who speak spanish');";
    char *errMsg = 0;
    if (sqlite3_exec(db, query, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "Error seeding BOOKS table with sample data: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}


crow::json::wvalue Database::getBooks(int page, const int limit) {
    // Calculate offset
    int offset = (page - 1) * limit;
    const char* query = "SELECT * FROM BOOKS LIMIT ? OFFSET ?;";
    sqlite3_stmt* statement;
    std::vector<crow::json::wvalue> books;
    if(sqlite3_prepare_v2(db, query, -1, &statement, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(statement, 1, limit);
        sqlite3_bind_int(statement, 2, offset);
        
        while(sqlite3_step(statement) == SQLITE_ROW) {
            crow::json::wvalue book;
            book["ID"] = sqlite3_column_int(statement, 0);
            book["TITLE"] = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
            book["AUTHOR"] = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
            book["DESCRIPTION"] = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
            books.push_back(std::move(book));
        }
        sqlite3_finalize(statement);
    }
    crow::json::wvalue json = std::move(books);
    return json;
}


crow::json::wvalue Database::addBook(const crow::request& book) {
    auto request = crow::json::load(book.body);
    std::string title = request["TITLE"].s();
    std::string author = request["AUTHOR"].s();
    std::string description = request["DESCRIPTION"].s();
    const char* query = "INSERT INTO BOOKS (TITLE, AUTHOR, DESCRIPTION) VALUES (?,?,?)";
    sqlite3_stmt* statement;
    if(sqlite3_prepare_v2(db, query, -1, &statement, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, title.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, author.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 3, description.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(statement) != SQLITE_DONE) {
            return crow::json::wvalue{{"status", "Error inserting book"}};
        }
    }

    sqlite3_finalize(statement);
    crow::json::wvalue json = {{"status", "success"}};
    return json;
}

crow::json::wvalue Database::updateBook(const crow::request& book, const int id) {
    auto request = crow::json::load(book.body);
    std::string title = request["TITLE"].s();
    std::string author = request["AUTHOR"].s();
    std::string description = request["DESCRIPTION"].s();
    const char* query = "UPDATE BOOKS SET TITLE = ?, AUTHOR = ?, DESCRIPTION = ? WHERE ID = ?";
    sqlite3_stmt* statement;
    if(sqlite3_prepare_v2(db, query, -1, &statement, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, title.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, author.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 3, description.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(statement, 4, id);
        if (sqlite3_step(statement) != SQLITE_DONE) {
            return crow::json::wvalue{{"status", "Error updating book"}};
        }
    }

    sqlite3_finalize(statement);
    crow::json::wvalue json = {{"status", "success"}};
    return json;
}

crow::json::wvalue Database::deleteBook(const int id) {
    const char* query = "DELETE FROM BOOKS WHERE ID = ?";
    sqlite3_stmt* statement;
    if(sqlite3_prepare_v2(db, query, -1, &statement, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(statement, 1, id);
        if (sqlite3_step(statement) != SQLITE_DONE) {
            return crow::json::wvalue{{"status", "Error deleting book"}};
        }
    }

    sqlite3_finalize(statement);
    crow::json::wvalue json = {{"status", "success"}};
    return json;
}

crow::json::wvalue Database::updateBookDescription(const crow::request& book, const int id) {
    auto request = crow::json::load(book.body);
    std::string description = request["DESCRIPTION"].s();
    const char* query = "UPDATE BOOKS SET DESCRIPTION = ? WHERE ID = ?";
    sqlite3_stmt* statement;
    if(sqlite3_prepare_v2(db, query, -1, &statement, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, description.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(statement, 2, id);
        if (sqlite3_step(statement) != SQLITE_DONE) {
            return crow::json::wvalue{{"status", "Error updating book description"}};
        }
    }

    sqlite3_finalize(statement);
    crow::json::wvalue json = {{"status", "success"}};
    return json;
}
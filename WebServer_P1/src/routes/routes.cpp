#include "../../include/routes/routes.h"
#include "crow_all.h"
#include <sqlite3.h>
#include "../../include/utils/db_utils.h"


void setupRoutes(crow::SimpleApp& app, Database& db) {
    CROW_ROUTE(app, "/")
        ([&db]() {
            crow::json::wvalue response;
            response = db.getBooks();
            return response;
        });
    CROW_ROUTE(app, "/add").methods("POST"_method)
        ([&db](const crow::request& book) {
            crow::json::wvalue response;
            response = db.addBook(book);
            return response;
        });
}
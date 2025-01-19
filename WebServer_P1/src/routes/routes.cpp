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
    CROW_ROUTE(app, "/update/<int>").methods("PUT"_method)
        ([&db](const crow::request& book, const int& id) {
            crow::json::wvalue response;
            response = db.updateBook(book, id);
            return response;
        });
    CROW_ROUTE(app, "/delete/<int>").methods("DELETE"_method)
        ([&db](const int& id) {
            crow::json::wvalue response;
            response = db.deleteBook(id);
            return response;
        });
    CROW_ROUTE(app, "/redescribe/<int>").methods("PATCH"_method)
        ([&db](const crow::request& book, const int& id) {
            crow::json::wvalue response;
            response = db.updateBookDescription(book, id);
            return response;
        });
    CROW_ROUTE(app, "/health").methods("GET"_method)
        ([]() {
            crow::json::wvalue response;
            response["status"] = "healthy";
            return response;
        });
    
}
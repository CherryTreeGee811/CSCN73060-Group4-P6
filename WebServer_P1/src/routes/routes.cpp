#include "../../include/routes/routes.h"
#include "crow_all.h"
#include <sqlite3.h>
#include "../../include/utils/db_utils.h"


void setupRoutes(crow::SimpleApp& app, Database& db) {
    CROW_ROUTE(app, "/")
        ([&db](crow::request pageNumber) {      
            crow::json::wvalue response;
            
            // Specify how many books should be displayed on the page
            const int limit = 10;
            int page = 1;

            // Get page value from url if it is specified as a parameter
            if (pageNumber.url_params.get("page") != nullptr) {
                page = std::stoi(pageNumber.url_params.get("page"));
                
                if (page < 1) {
                    // If page is less than 1 this is incorrect
                    // We'll ignore if this is the case and make the page number 1
                    page = 1;
                }
            }
            response = db.getBooks(page, limit);
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
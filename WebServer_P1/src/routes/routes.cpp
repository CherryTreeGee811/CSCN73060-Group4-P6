#include "../include/routes/routes.h"
#include "crow_all.h"

void setupRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/")
        ([]() {
            crow::json::wvalue response;
            response["message"] = "Welcome to Crow!";
            return response;
        });
}

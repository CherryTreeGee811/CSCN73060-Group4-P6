#include "crow_all.h"
#include "../include/routes/routes.h"
#include "../include/utils/db_utils.h"
#include <sqlite3.h>


int main(void) {
    crow::SimpleApp app;
    Database db("library.db");

    // Register routes
    setupRoutes(app, db);

    // Start the server
    app.bindaddr("0.0.0.0").port(8080).multithreaded().run();

    return 0;
}

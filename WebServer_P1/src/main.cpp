#include "crow_all.h"
#include "../include/routes/routes.h"

int main() {
    crow::SimpleApp app;

    // Register routes
    setupRoutes(app);

    // Start the server
    app.bindaddr("127.0.0.1").port(8080).multithreaded().run();
}

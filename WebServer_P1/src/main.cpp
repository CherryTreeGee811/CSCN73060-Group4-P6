#include "crow_all.h"
#include "../include/routes/routes.h"

int main(void) {
    crow::SimpleApp app;

    // Register routes
    setupRoutes(app);

    // Start the server
    app.bindaddr("0.0.0.0").port(8080).multithreaded().run();

    return 0;
}

#pragma once

#include "crow_all.h"
#include "../utils/db_utils.h"

// Function to set up example routes
void setupRoutes(crow::SimpleApp& app, Database& db);

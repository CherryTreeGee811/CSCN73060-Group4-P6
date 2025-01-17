#pragma once

#include "crow_all.h"
#include <string>

// Utility function to create a JSON response
crow::json::wvalue createJsonResponse(const std::string& message, int code);

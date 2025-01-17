#include "utils/json_utils.h"
#include "crow_all.h"

crow::json::wvalue createJsonResponse(const std::string& message, int code) {
    crow::json::wvalue response;
    response["message"] = message;
    response["code"] = code;
    return response;
}

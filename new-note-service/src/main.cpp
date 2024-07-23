#include <httplib.h>
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>
#include <aws/core/Aws.h>

#include "../include/database.hpp"
#include "../include/new_note_service.hpp"
#include "../include/yandex_object_storage.hpp"

std::string getEnvVar(const std::string &key) {
    const char *val = std::getenv(key.c_str());
    if (val == nullptr) {
        throw std::runtime_error("Environment variable " + key + " not set");
    }
    return std::string(val);
}

int main() {
    try {
        YAML::Node config = YAML::LoadFile("./config/config.yaml");
 
        std::string db_host = config["db"]["host"].as<std::string>();
        int db_port = config["db"]["port"].as<int>();
        std::string db_user = getEnvVar("DB_USER");
        std::string db_password = getEnvVar("DB_PASSWORD");
        std::string db_name = config["db"]["name"].as<std::string>();
        std::string redis_host = config["redis"]["host"].as<std::string>();
        int redis_port = config["redis"]["port"].as<int>();
 
        Database db(db_host, db_port, db_user, db_password, db_name);
        YandexObjectStorage yandex("your-bucket-name");
        NewNoteService newNoteService(db, yandex, "http://hash-service:8080");
 
        httplib::Server svr;
 
        svr.Post("/notes", [&](const httplib::Request &req, httplib::Response &res) {
            try {
                std::string text = req.body;
                std::string hash = newNoteService.createNote(text);
                res.set_content(hash, "text/plain");
                spdlog::info("Note created with hash: {}", hash);
            } catch (const std::exception &e) {
                res.status = 500;
                res.set_content(e.what(), "text/plain");
                spdlog::error("Error creating note: {}", e.what());
            }
        });
 
        svr.listen("0.0.0.0", 8080);
    } catch (const std::exception &e) {
        spdlog::error("Error initializing application: {}", e.what());
        return 1;
    }
    return 0;
}

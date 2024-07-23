#include "../include/new_note_service.hpp"

NewNoteService::NewNoteService(Database &db, YandexObjectStorage &yandex, const std::string &hashServiceUrl)
    : db(db), yandex(yandex), hashServiceUrl(hashServiceUrl) {}
 
std::string NewNoteService::createNote(const std::string &text) {
    try {
        std::string hash = requestHash();
        std::string url = yandex.uploadText(text, hash);
        db.storeUrl(hash, url);
        return hash;
    } catch (const std::exception &e) {
        spdlog::error("Error creating note: {}", e.what());
        throw;
    }
}
 
std::string NewNoteService::requestHash() {
    try {
        httplib::Client cli("http://hash-service:8080");
        auto res = cli.Get("/hash");
        if (res && res->status == 200) {
            return res->body;
        } else {
            throw std::runtime_error("Failed to get hash from hash-service");
        }
    } catch (const std::exception &e) {
        spdlog::error("Error requesting hash: {}", e.what());
        throw;
    }
}
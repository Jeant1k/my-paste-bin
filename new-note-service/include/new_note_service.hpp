#pragma once

#include <string>
#include <httplib.h>
#include <spdlog/spdlog.h>

#include "database.hpp"
#include "yandex_object_storage.hpp"

class NewNoteService {
public:
    NewNoteService(Database &db, YandexObjectStorage &yandex, const std::string &hashServiceUrl);
    std::string createNote(const std::string &text);

private:
    Database &db;
    YandexObjectStorage& yandex;
    std::string hashServiceUrl;

    std::string requestHash();
};

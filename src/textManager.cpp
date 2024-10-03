#include "textManager.h"

#include <utility>
#include <fstream>
#include <iostream>

textManager::textManager() {
    lang = language::ENGLISH;
    file = "../resources/messages.json";
}

textManager::textManager(std::string file, language l) {
    lang = l;
    this->file = std::move(file);
}

void textManager::setLanguage(language l) {
    lang = l;
}

std::string textManager::getMessage(const char *id) {
    switch (lang) {
        case language::ENGLISH:
            return getMessage(id, "en");
        case language::RUSSIAN:
            return getMessage(id, "ru");
    }
}

std::string textManager::getMessage(const char *id, const char *lang) {
    std::ifstream fileStream(file);
    nlohmann::json j;
    fileStream >> j;
    for (auto &el: j["messages"]) {
        std::cout << el["id"] << std::endl;
        if (el["id"] == id) {
            return el[lang];
        }
    }
    throw std::runtime_error("Key not found");
}
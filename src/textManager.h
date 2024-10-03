#ifndef PHYS_LAB_1_TEXTMANAGER_H
#define PHYS_LAB_1_TEXTMANAGER_H

#include <string>
#include "../lib/json.hpp"

enum class language {
    ENGLISH,
    RUSSIAN
};

class textManager {
 private:
    std::string file;
    language lang;
public:
    textManager();
    textManager(std::string file, language l);
    ~textManager() = default;

    void setLanguage(language l);
    std::string getMessage(const char* id);
    std::string getMessage(const char* id, const char* lang);
};


#endif //PHYS_LAB_1_TEXTMANAGER_H

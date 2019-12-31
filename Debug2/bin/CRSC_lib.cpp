#include "CRSC_lib.h"

// Проверить файл на существование
int CRSC_CheckFile(const char* path) {
    std::ifstream file;
    file.open(path);
    if (!file) return 0;
    file.close();
    return 1;
}

// Создать файл и записать туда строку
std::ofstream CRSC_CreateAndWrite(const char* path, std::string elem) {
    std::ofstream file;
    file.open(path, std::ofstream::app);
    file << elem << std::endl;
    file.close();
    return file;
}

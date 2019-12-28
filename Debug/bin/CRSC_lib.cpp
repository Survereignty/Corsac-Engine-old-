#include "CRSC_lib.h"

// Получить ключ ini строчки
std::string getKeyIni(std::string s)
{
    std::string l = "";
    for(int i = 0; s[i] != '='; i++){
        l += s[i];
    }
    return l;
}

// Получить значение ini строчки
std::string getValueIni(std::string s)
{
    std::string l = "";
    for(int i = 0; s[i]; i++) {
        if(s[i] == '='){
            for(i++ ;s[i];i++){
                l += s[i];
            }
            break;
        }
    }
    return l;
}

// Проверить файл на существование
int CRSC_CheckIni(const char* path) {
    std::ifstream file;
    file.open(path);
    if (!file) return 1;
    file.close();
    return 0;
}

// Создать файл и записать туда vector<std::string>
std::ofstream CRSC_CreateAndWrite(const char* path, std::vector<std::string> elems) {
    std::ofstream file (path);
    for (std::string elem : elems) {
        file << elem << std::endl;
    }
    file.close();
    return file;
}

// Прочитать ini файл
std::map <std::string, std::string> CRSC_ReadIni(const char* path) {
    std::ifstream file;
    std::map <std::string, std::string> data;
    file.open(path);
    if (!file) {
        return data;
    }
    std::string s, key, value;
        while(std::getline(file, s))
        {
            if (s.find('['))
            {
                value = getValueIni(s);
                key = getKeyIni(s);

                data[key] = value;
            }
        }
    file.close();
    return data;
}

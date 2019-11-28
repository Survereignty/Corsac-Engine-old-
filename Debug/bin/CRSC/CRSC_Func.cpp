#include "CRSC_Func.h"

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

// Установить ошибку
void CRSC_setLog(
    // Текст
    const char* value,
    // Тип важности
    typeLog     type,
    // Тип библеотеки
    typeLib     typeL
) {
    std::ifstream  file;
    char *gamePath = SDL_GetBasePath();
    const char* path = strcat(gamePath, "Debug.log");
    file.open(path);
    if (!file)  {
        std::ofstream file (path);
    }
    file.close();

    std::ofstream Debug (path, std::ios::app);

    std::string text = (const char*) value;
    std::string err;

    time_t now = time(0);
    char* dt = ctime(&now);

    if (typeL == SDL) {
        err = SDL_GetError();
    } else if (typeL == MIX) {
        err = Mix_GetError();
    } else if (typeL == IMG) {
        err = IMG_GetError();
    }

    if (type == INFO) {
        std::cout << "[INFO] " + text + err << std::endl;
    } else if (type == WARNING) {
        std::cout << "[WARNING] " + text + err << std::endl;
        Debug << dt << "[WARNING] " + text + err << std::endl;
    } else if (type == ERROR) {
        std::cout << "[ERROR] " + text + err << std::endl;
        Debug << dt << "[ERROR] " + text + err << std::endl;
    } else if (type == CRASH) {
        std::cout << "[CRASH] " + text + err << std::endl;
        Debug << dt << "[CRASH] " + text + err << std::endl;
    } else if (type == CLOSE) {
        std::cout << "[CLOSE] " + text + err << std::endl;
    } else if (type == LOADING) {
        std::cout << "[LOADING...] " + text + err << std::endl;
    } else if (type == COMPLETED) {
        std::cout << "[COMPLETED] " + text + err << std::endl;
    }
    Debug.close();
}

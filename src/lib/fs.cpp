#include "lib/fs.h"

#ifdef UNIX_OS
std::vector<std::string> getFileListOfDirectory(const char* dir) {
    DIR *_dir;
    struct dirent *ent;
    std::vector<std::string> files;

    if ((_dir = opendir(dir)) != NULL) {
        while ((ent = readdir(_dir)) != NULL) {
            if (std::string(ent->d_name) != "." && std::string(ent->d_name) != "..")
                files.push_back(ent->d_name);
        }

        closedir(_dir);
    } else {
        std::cout << "Could not read files from directory: " << dir << std::endl;
    }
   
    return files;
}
#else
std::vector<std::string> getFileListOfDirectory(const char* dir) {
    WIN32_FIND_DATA data;
    std::vector<std::string> files;

    std::string _dir = dir;
    std::string path = _dir + "\\*";

    HANDLE hFind = FindFirstFile(path.c_str(), &data);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                files.push_back(data.cFileName);
        } while (FindNextFile(hFind, &data) != 0);

        FindClose(hFind);
    } else {
        std::cout << "Could not read files from directory: " << dir << std::endl;
    }
    
    return files;
}
#endif
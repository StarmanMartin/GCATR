//
// Created by Martin on 30.09.2018.
//

#include "FileManager.h"

#include <sys/stat.h>
#include <iostream>
#include <fstream>

namespace std_m {

    FileManager &FileManager::getInstance() {
        static FileManager _instance;

        return _instance;
    }


    bool FileManager::is_file(const std::string &path) {
        struct stat buf{};
        stat(path.c_str(), &buf);
        return S_ISREG(buf.st_mode); // NOLINT
    }

    bool FileManager::is_dir(const std::string &path) {
        struct stat buf{};
        stat(path.c_str(), &buf);
        return S_ISDIR(buf.st_mode); // NOLINT
    }

    std::string
    FileManager::write_file(const std::string &filePath, const std::string &ext, const std::string &content) {
        std::string totalFilePath = filePath + ext;
        int file_idx = 1;
        while (this->is_file(totalFilePath)) { // File already exists;
            totalFilePath = filePath + "_" + std::to_string(file_idx++) + ext;
        }

        std::ofstream myfile;
        myfile.open(totalFilePath);
        myfile << content;
        myfile.close();
        return totalFilePath;
    }

}
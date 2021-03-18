//
// Created by Martin on 30.09.2018.
//

#ifndef GCATCPP_FILEMANAGER_H
#define GCATCPP_FILEMANAGER_H

#include <string>
#include "AbstractErrorManager.h"

namespace std_m {
    class FileManager : public err::AbstractErrorManager {
    public:
        static FileManager &getInstance();

        bool is_file(const std::string &path);

        bool is_dir(const std::string &path);


        std::string write_file(const std::string &filePath, const std::string &ext, const std::string &content);

    private:
        explicit FileManager() = default;
    };

}
#endif //GCATCPP_FILEMANAGER_H

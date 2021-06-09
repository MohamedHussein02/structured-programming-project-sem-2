//
// Created by hussein on 09/06/2021.
//

#ifndef UNTITLED_FILE_IO_UTILS_H
#define UNTITLED_FILE_IO_UTILS_H
#include <unistd.h>

bool isFileExist (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}
#endif //UNTITLED_FILE_IO_UTILS_H

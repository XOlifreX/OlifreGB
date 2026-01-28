#pragma once
#ifndef FS_H
#define FS_H

#ifdef UNIX_OS
#include <dirent.h>
#else
#include <windows.h>
#endif
#include <iostream>
#include <vector>
#include <string>

extern std::vector<std::string> getFileListOfDirectory(const char* dir);

#endif // FS_UNIX
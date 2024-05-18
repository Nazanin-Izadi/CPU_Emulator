#pragma once

#include <string>
#include <vector>
#include <fstream>

class FileLoader {
public:
    FileLoader(std::string const& path);

    std::vector<std::string> readAll();

private:
    std::string path_;
    std::ifstream file_;
};

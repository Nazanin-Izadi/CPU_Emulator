#include "file_loader.hh"

FileLoader::FileLoader(std::string const& path)
    : path_(path),
    file_(path_)
{
}

std::vector<std::string> FileLoader::readAll()
{
    if (!file_.is_open()) {
        throw std::runtime_error("Couldn't find the file :( ");
    }

    std::vector<std::string> result;

    for (std::string line; std::getline(file_, line);) {
        result.push_back(line);
    }

    return result;
}

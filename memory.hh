#pragma once

#include <vector>
#include <cstdint>

class Memory {
public:
    Memory(size_t const mem_size);

    uint8_t* allocate();

    uint8_t at(size_t const index) const;
    uint8_t& at(size_t const index);

    size_t size() const;
    size_t usage() const;

private:
    std::vector<uint8_t> memory_;
};
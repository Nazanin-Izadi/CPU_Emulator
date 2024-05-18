#include "memory.hh"

Memory::Memory(size_t const mem_size)
{
    memory_.reserve(mem_size);
}

uint8_t* Memory::allocate()
{
    memory_.push_back(uint8_t());
    return &memory_[memory_.size() - 1];
}

uint8_t Memory::at(size_t const index) const
{
    return memory_.at(index);
}
uint8_t& Memory::at(size_t const index)
{
    return memory_.at(index);
}

size_t Memory::size() const
{
    return memory_.capacity();
}
size_t Memory::usage() const
{
    return memory_.size();
}
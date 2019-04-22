// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef STATICALLOCATOR_H
#define STATICALLOCATOR_H

#include <unordered_map>

#include "IAllocator.h"

#include "OCcore_export.h"

class OCCORE_EXPORT RawPoolAllocator : public IAllocator
{
    uint8_t* _mem;
    size_t _currentOffset;

    std::unordered_map<size_t, size_t> _pointerMap; // pointer, size

public:
    explicit RawPoolAllocator(size_t pageSize);
    ~RawPoolAllocator();

    void* Allocate(size_t size /*, size_t align*/) override;
    void Deallocate(void* p) override;
    size_t allocated_size(void* p) override;
};

#endif // STATICALLOCATOR_H

// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef IALLOCATOR_H
#define IALLOCATOR_H

#include <cstdlib>

// Reference: http://bitsquid.blogspot.de/2010/09/custom-memory-allocation-in-c.html
class IAllocator
{
public:
    virtual ~IAllocator();

    virtual void *Allocate(size_t size /*, size_t align*/) = 0;
    virtual void Deallocate(void *p) = 0;
    virtual size_t allocated_size(void *p) = 0;
};

#endif // IALLOCATOR_H

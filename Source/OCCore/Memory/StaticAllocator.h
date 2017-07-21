#ifndef STATICALLOCATOR_H
#define STATICALLOCATOR_H

#include <unordered_map>

#include "OCCore_export.h"

// TODO: Move to separate file
//Reference: http://bitsquid.blogspot.de/2010/09/custom-memory-allocation-in-c.html
class OCCORE_EXPORT IAllocator
{
public:
	virtual ~IAllocator()
	{
	}

	virtual void *Allocate(size_t size/*, size_t align*/) = 0;
	virtual void Deallocate(void *p) = 0;
	virtual size_t allocated_size(void *p) = 0;
};

class OCCORE_EXPORT RawPoolAllocator : public IAllocator
{
    uint8_t* _mem;
	size_t _currentOffset;

	std::unordered_map<size_t, size_t> _pointerMap;	//pointer, size

public:
	explicit RawPoolAllocator(size_t pageSize);
	~RawPoolAllocator();

	void* Allocate(size_t size/*, size_t align*/) override;
	void Deallocate(void* p) override;
	size_t allocated_size(void* p) override;
};

#endif //STATICALLOCATOR_H

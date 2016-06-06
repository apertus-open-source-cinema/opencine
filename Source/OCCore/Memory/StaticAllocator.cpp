#include "StaticAllocator.h"

RawPoolAllocator::RawPoolAllocator(size_t pageSize) :
	_currentOffset(0)
{
	_mem = new unsigned char[pageSize];
}

void* RawPoolAllocator::Allocate(size_t size/*, size_t align*/)
{
	_pointerMap.insert(std::pair<size_t, size_t>(_currentOffset, size));
	
	void* ptr = _mem + _currentOffset;
	_currentOffset += size;

	return ptr;
}

void RawPoolAllocator::Deallocate(void* p)
{
}
size_t RawPoolAllocator::allocated_size(void* p)
{
	return 0;
}


#pragma once
#include <cstdint>

#include "OCCore_export.h"

class OCCORE_EXPORT IHashGenerator
{
public:
	virtual ~IHashGenerator() = default;

	virtual void Initialize() = 0;
	virtual void Update(void* data, unsigned int length) = 0;
    virtual uint64_t Retrieve() = 0;
};

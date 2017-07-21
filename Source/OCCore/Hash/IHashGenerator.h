// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

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

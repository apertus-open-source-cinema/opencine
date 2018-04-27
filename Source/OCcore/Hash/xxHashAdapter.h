// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef XXHASHADAPTER_H
#define XXHASHADAPTER_H

#include "IHashGenerator.h"

#include <xxHash/xxhash.h>

#include "OCcore_export.h"
#include <cassert>

class OCCORE_EXPORT xxHashAdapter : public IHashGenerator
{
	XXH64_state_s* _hashState = nullptr;
	unsigned long long _seed = 0xCFFA8DB881BC3A3DULL;

public:
	void Initialize()
	{
		if (_hashState != nullptr)
		{
			XXH64_freeState(_hashState);
		}

		_hashState = XXH64_createState();
		XXH64_reset(_hashState, _seed);
	}

	void Update(void* data, unsigned int length)
	{
		if (_hashState == nullptr)
		{
			assert("Hash state is not initialized. Call Initialize() first.");
			return;
		}

		XXH64_update(_hashState, data, length);
	}

    uint64_t Retrieve()
	{
		return XXH64_digest(_hashState);
	}
};

#endif //XXHASHADAPTER_H

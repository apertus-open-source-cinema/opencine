// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCcore
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#include "IFrameProcessor.h"

using namespace OC::DataProvider;

// Moved methods to .cpp to prevent vtable warnings
IFrameProcessor::~IFrameProcessor() {}

void IFrameProcessor::SetData(uint8_t *, OCImage &, ImageFormat) {}

void IFrameProcessor::SetData(uint16_t*, OCImage &) {}



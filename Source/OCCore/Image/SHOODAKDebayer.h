// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / OCBackup
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#ifndef SHOODAKDEBAYER_H
#define SHOODAKDEBAYER_H

#include "IFrameProcessor.h"
#include "OCImage.h"

#include "OCCore_export.h"

namespace OC
{
	namespace DataProvider
	{
		class OCCORE_EXPORT SHOODAKDebayer : public IFrameProcessor
		{
			unsigned short* redChannel;
			unsigned short* greenChannel;
			unsigned short* blueChannel;

			unsigned int _width;
			unsigned int _height;

			unsigned int colorOffsets[8] = { 1, 1, 1, 1, 1, 1, 1, 1 }; //R G1 G2 B, first: row, second: column

			//Caution: Experimental values, XYXY, right angle, 1st relative to origin, 2nd to 1st one
			//Offset example:
			//	B -> currently processed blue pixel
			//	G, R -> pixel pair selected by random offset pair
			//
			//  r G R
			//	g B g
			//  r g r
			//
			//TODO: Investigate better solutions later, e.g. convolution kernels
			int randomOffsets[32] = { 0, -1, -1,  0, //top, top-left
									  0, -1,  1,  0, //top, top-right
									  1,  0,  0, -1, //right, top-right
									  1,  0,  0,  1, //right, bottom-right
									  0,  1, -1,  0, //bottom, bottom-left
									  0,  1,  1,  0, //bottom, bottom-right
									 -1,  0,  0, -1, //left, top-left
									 -1,  0,  0,  1 //left, bottom-left
			};

			// Maybe absolute values would save performance
			int randomAbsoluteOffsets[32] = { 0, -1, -1, -1, //top, top-left
											  0, -1,  1, -1, //top, top-right
											  1,  0,  1, -1, //right, top-right
											  1,  0,  1,  1, //right, bottom-right
											  0,  1, -1,  1, //bottom, bottom-left
											  0,  1,  1,  1, //bottom, bottom-right
											 -1,  0, -1, -1, //left, top-left
											 -1,  0, -1,  1 //left, bottom-left
			};

		public:
			SHOODAKDebayer(OCImage& image);

			void Process() override;
			unsigned short* GetDataRed() override;
			unsigned short* GetDataGreen() override;
			unsigned short* GetDataBlue() override;

			void BilinearFilterGreen() const;
			void BilinearFilterRed() const;
			void BilinearFilterBlue() const;

			void SetColorOffsets(BayerPattern pattern);

			void SelectRandomPixels();
		};
	}
}

#endif //SHOODAKDEBAYER_H

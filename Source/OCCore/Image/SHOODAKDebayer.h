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

			//Caution: Experimental values for now, X and Y, possibly that 4 values are required to describe both offsets
			//Offset example:
			//	B -> currently processed blue pixel
			//	G, R -> pixel pair selected by random offset pair
			//
			//  r G R
			//	g B g
			//  r g r
			//
			//TODO: Expand the list, investigate better solutions later, e.g. convolution kernels
			int randomOffsets [] = { -1, -1,	//top-left
									  1,  1,	//top-right
									 -1,  1,	//bottom-left
									  1, -1 };	//bottom-right

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
		};
	}
}

#endif //SHOODAKDEBAYER_H

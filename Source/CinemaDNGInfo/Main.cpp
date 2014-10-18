#include <iostream>
#include <memory>

#include "../CinemaDNGDecoder/CinemaDNGDecoder.h"

#include <libraw/libraw.h>

int main()
{
    std::cout << "CinemaDNG information" << std::endl << "--------------------" << std::endl;

    std::unique_ptr<CinemaDNGDecoder> cdDecoder(new CinemaDNGDecoder());
	CinemaDNGFile* file = cdDecoder->LoadFile("000100.dng");

    std::cout << "Width: " << file->GetWidth() << std::endl;
    std::cout << "Height: " << file->GetHeight() << std::endl;

  LibRaw iProcessor;
  iProcessor.open_file("000100.dng");

	// The metadata are accessible through <a href="API-datastruct-eng.html">data fields of the class</a>
        printf("Image size: %d x %d\n",iProcessor.imgdata.sizes.width,iProcessor.imgdata.sizes.height);
        //printf("Image size (raw): %d x %d\n",iProcessor.imgdata.sizes.raw_width,iProcessor.imgdata.sizes.raw_height);
        printf("Colors: %d\n",iProcessor.imgdata.idata.colors);
        std::cout << "Filters: " << iProcessor.imgdata.idata.filters << std::endl;

        // Let us unpack the image
        iProcessor.unpack();

        // Convert from imgdata.rawdata to imgdata.image:
        iProcessor.raw2image();

        // And let us print its dump; the data are accessible through <a href="API-datastruct-eng.html">data fields of the class</a>
        //for(unsigned int i = 0;i < iProcessor.imgdata.sizes.iwidth *  iProcessor.imgdata.sizes.iheight; i++)
        //   printf("i=%d R=%d G=%d B=%d G2=%d\n",
        //                i,
        //                iProcessor.imgdata.image[i][0],
        //                iProcessor.imgdata.image[i][1],
        //                iProcessor.imgdata.image[i][2],
        //                iProcessor.imgdata.image[i][3]
        //        );

        // Finally, let us free the image processor for work with the next image
        iProcessor.recycle();

	return 0;
}

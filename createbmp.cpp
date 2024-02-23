/*
    Program for creating .bmp file manualy.
*/

#include <cstdint> // integers of specific size ;  c std int
#include <fstream> // for file stream
#include <iostream>

using namespace std;

// you can modify those to get different sizes of image; no need to change anything other
const uint32_t mainImageWidth = 512;
const uint32_t mainImageHeight = 512;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    struct BmpHeader
    {
        /* 
            The first two bytes 'B' and 'M' are *magic numbers* unique to the bitmap file format.
            more here: https://en.wikipedia.org/wiki/List_of_file_signatures
        */
        char bitmapSignatureBytes[2] = {'B','M'}; 

        /* 
            The next four bytes contain total size of the bitmap file in bytes.

            As we are creating a 512 by 512 bitmap image, total size is the sum of:
            - size of meta data (14 + 40 = 54 bytes) 
            - size of pixels (512 * 512 * 3 = 7863432, each pixel is of 3 bytes in 24 bit bitmap file).
        */
        uint32_t sizeOfBitmapFile = 54 + (mainImageWidth * mainImageHeight *3);  

        //--
        uint32_t reservedBytes = 0; // ?
        //--

        /*
            The last field of bitmap file header contains the offset to the pixel data of the image from the start of the file. 
            In our case the offset is 54 bytes,
            as our pixel data is right after the bitmap file header and info header (14 + 40 = 54).
        */
        uint32_t pixelDataOffset = 54;

        void save_on_file(std::ofstream& fout) {
            fout.write(this->bitmapSignatureBytes, 2);
            fout.write((char*)&this->sizeOfBitmapFile, sizeof(uint32_t));
            fout.write((char*)&this->reservedBytes, sizeof(uint32_t));
            fout.write((char*)&this->pixelDataOffset, sizeof(uint32_t));
        }

    } bmpHeader;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*
        The bitmap file has various types of info header, but the most common one is the 40 byte Bitmap Info Header
    */
    struct BmpInfoHeader {
        uint32_t sizeOfThisHeader = 40;

        int32_t width = mainImageWidth; // in pixels
        int32_t height = mainImageHeight; // in pixels

        uint16_t numberOfColorPlanes = 1; // must be 1
        uint16_t colorDepth = 24;
        uint32_t compressionMethod = 0;
        uint32_t rawBitmapDataSize = 0; // generally ignored
        int32_t horizontalResolution = 3780; // in pixel per meter
        int32_t verticalResolution = 3780; // in pixel per meter
        uint32_t colorTableEntries = 0;
        uint32_t importantColors = 0;

        // below, function for creating part of the file
        void save_on_file(std::ofstream& fout) {
            fout.write((char*)&this->sizeOfThisHeader, sizeof(uint32_t));
            fout.write((char*)&this->width, sizeof(int32_t));
            fout.write((char*)&this->height, sizeof(int32_t));
            fout.write((char*)&this->numberOfColorPlanes, sizeof(uint16_t));
            fout.write((char*)&this->colorDepth, sizeof(uint16_t));
            fout.write((char*)&this->compressionMethod, sizeof(uint32_t));
            fout.write((char*)&this->rawBitmapDataSize, sizeof(uint32_t));
            fout.write((char*)&this->horizontalResolution, sizeof(int32_t));
            fout.write((char*)&this->verticalResolution, sizeof(int32_t));
            fout.write((char*)&this->colorTableEntries, sizeof(uint32_t));
            fout.write((char*)&this->importantColors, sizeof(uint32_t));
        }
    } bmpInfoHeader;

    /*
        The height of bitmap file can also be negative (you may have noticed the signed integers). 
        When height is negative the first pixel in file is drawn at top left of the image. 
        However the standard for bitmap files is to use positive height 
        and the first pixel in file is drawn at the bottom left of the image followed by other pixels.
    */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Pixel {
        //in bmp file we define in reverse so instead of *RGB* we have *BGR*
        uint8_t blue = 0;
        uint8_t green = 0;
        uint8_t red = 0;

        //function writing a single pixel into the image
        void save_on_file(std::ofstream& fout) {
            fout.write((char*)&this->blue, sizeof(uint8_t));
            fout.write((char*)&this->green, sizeof(uint8_t));
            fout.write((char*)&this->red, sizeof(uint8_t));
        }
    } pixel;

    

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ofstream fout("output.bmp", ios::binary);

    //fout.write((char *) &bmpHeader, 14);
    bmpHeader.save_on_file(fout);

    //fout.write((char *) &bmpInfoHeader, 40);
    bmpInfoHeader.save_on_file(fout);

    // writing pixel data
    size_t numberOfPixels = bmpInfoHeader.width * bmpInfoHeader.height;
    for (int i = 0; i < numberOfPixels; i++) {
        if(i<1000)
        {
            pixel.red = 255;
            pixel.green = 0;
            pixel.blue = 0;
        }
        else {
            pixel.red = 0;
            pixel.green = 0;
            pixel.blue = 0;
        }
        pixel.save_on_file(fout);
        //
    }
    fout.close();

    return 0;
}
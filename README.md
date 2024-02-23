# cpp-create-bmp-image
Program used for manually creating .bmp file. Program works on Linux, Ubuntu to be specific, 
as of other platforms I have no idea, might need slight modifications.

And to be honest, it is just an example that I can copy if i need this functionality 😅

# requires
1. `g++` compiler
2. `gnu make`
3. (optionaly) `convert` ( member of the `ImageMagick-ims6.q16` suite of tools, used for converting image types)

# commands
- `make` -> builds app
- `make bmp` -> same as above
- `make convert` -> converts .bmp to .png (using separately installed convert function)
- `make clean` -> clean the binary and the created images

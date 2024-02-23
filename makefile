bmp: clean_bmp
	g++ createbmp.cpp -o uint.exe

convert:
	-convert output.bmp output.png
	-rm output.bmp

clean_bmp:
	-rm output.bmp
	-rm output.png
	-rm uint.exe

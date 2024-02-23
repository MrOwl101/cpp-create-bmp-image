bmp: clean
	g++ createbmp.cpp -o uint.exe

convert:
	-convert output.bmp output.png

clean:
	-rm output.bmp
	-rm output.png
	-rm uint.exe

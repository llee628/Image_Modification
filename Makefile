all: project3.exe

project3.o: project3.cpp ColorImageClass.h annotateWithRectangle.h
	g++ -std=c++98 -Wall -c project3.cpp -o project3.o

ColorImageClass.o: ColorImageClass.cpp ColorClass.h RowColumnClass.h constants.h
	g++ -std=c++98 -Wall -c ColorImageClass.cpp -o ColorImageClass.o

RowColumnClass.o: RowColumnClass.cpp RowColumnClass.h constants.h
	g++ -std=c++98 -Wall -c RowColumnClass.cpp -o RowColumnClass.o

ColorClass.o: ColorClass.cpp ColorClass.h constants.h
	g++ -std=c++98 -Wall -c ColorClass.cpp -o ColorClass.o

handleInputFromKeyboard.o: handleInputFromKeyboard.cpp handleInputFromKeyboard.h constants.h
	g++ -std=c++98 -Wall -c handleInputFromKeyboard.cpp -o handleInputFromKeyboard.o

Rectangle.o: Rectangle.cpp Rectangle.h RowColumnClass.h ColorClass.h handleInputFromKeyboard.h
	g++ -std=c++98 -Wall -c Rectangle.cpp -o Rectangle.o

modifyImage.o: modifyImage.cpp modifyImage.h ColorImageClass.h Rectangle.h
	g++ -std=c++98 -Wall -c modifyImage.cpp -o modifyImage.o

annotateWithRectangle.o: annotateWithRectangle.cpp annotateWithRectangle.h ColorImageClass.h Rectangle.h modifyImage.h
	g++ -std=c++98 -Wall -c annotateWithRectangle.cpp -o annotateWithRectangle.o

project3.exe: project3.o ColorImageClass.o RowColumnClass.o ColorClass.o handleInputFromKeyboard.o Rectangle.o modifyImage.o annotateWithRectangle.o
	g++ -std=c++98 project3.o ColorImageClass.o RowColumnClass.o ColorClass.o handleInputFromKeyboard.o Rectangle.o modifyImage.o annotateWithRectangle.o -o project3.exe

clean:
	rm -f *.o *.exe
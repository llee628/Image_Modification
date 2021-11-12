all: proj3.exe

project3.o: project3.cpp ColorImageClass.h annotatePatternFromFile.h insertImage.h constants.h
	g++ -std=c++98 -Wall -c project3.cpp -o project3.o

ColorImageClass.o: ColorImageClass.cpp ColorImageClass.h ColorClass.h RowColumnClass.h constants.h isInputValid.h Rectangle.h
	g++ -std=c++98 -Wall -c ColorImageClass.cpp -o ColorImageClass.o

RowColumnClass.o: RowColumnClass.cpp RowColumnClass.h constants.h
	g++ -std=c++98 -Wall -c RowColumnClass.cpp -o RowColumnClass.o

ColorClass.o: ColorClass.cpp ColorClass.h constants.h isInputValid.h
	g++ -std=c++98 -Wall -c ColorClass.cpp -o ColorClass.o

handleInputFromKeyboard.o: handleInputFromKeyboard.cpp handleInputFromKeyboard.h constants.h
	g++ -std=c++98 -Wall -c handleInputFromKeyboard.cpp -o handleInputFromKeyboard.o

Rectangle.o: Rectangle.cpp Rectangle.h RowColumnClass.h ColorClass.h handleInputFromKeyboard.h constants.h
	g++ -std=c++98 -Wall -c Rectangle.cpp -o Rectangle.o

modifyImage.o: modifyImage.cpp modifyImage.h ColorImageClass.h Rectangle.h
	g++ -std=c++98 -Wall -c modifyImage.cpp -o modifyImage.o

annotatePatternFromFile.o: annotatePatternFromFile.cpp annotatePatternFromFile.h ColorImageClass.h Rectangle.h ColorClass.h modifyImage.h
	g++ -std=c++98 -Wall -c annotatePatternFromFile.cpp -o annotatePatternFromFile.o

insertImage.o: insertImage.cpp insertImage.h ColorImageClass.h ColorClass.h handleInputFromKeyboard.h modifyImage.h
	g++ -std=c++98 -Wall -c insertImage.cpp -o insertImage.o

isInputValid.o: isInputValid.cpp isInputValid.h constants.h
	g++ -std=c++98 -Wall -c isInputValid.cpp -o isInputValid.o

proj3.exe: project3.o ColorImageClass.o RowColumnClass.o ColorClass.o handleInputFromKeyboard.o Rectangle.o modifyImage.o annotatePatternFromFile.o insertImage.o isInputValid.o
	g++ -std=c++98 project3.o ColorImageClass.o RowColumnClass.o ColorClass.o handleInputFromKeyboard.o Rectangle.o modifyImage.o annotatePatternFromFile.o insertImage.o isInputValid.o -o proj3.exe

clean:
	rm -f *.o *.exe
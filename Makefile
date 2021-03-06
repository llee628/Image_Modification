all: proj3.exe

project3.o: project3.cpp ColorImageClass.h constants.h
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

isInputValid.o: isInputValid.cpp isInputValid.h constants.h
	g++ -std=c++98 -Wall -c isInputValid.cpp -o isInputValid.o

proj3.exe: project3.o ColorImageClass.o RowColumnClass.o ColorClass.o handleInputFromKeyboard.o Rectangle.o isInputValid.o
	g++ -std=c++98 project3.o ColorImageClass.o RowColumnClass.o ColorClass.o handleInputFromKeyboard.o Rectangle.o isInputValid.o -o proj3.exe

clean:
	rm -f *.o *.exe
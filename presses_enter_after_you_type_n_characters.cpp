//Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.

#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
int main()
{	//Automatic enter stuff.
	struct termios old_settings, new_settings;
	tcgetattr(STDIN_FILENO, &old_settings);
	new_settings = old_settings;
	
	//Makes keyboard input be accepted automatically, as if pressing enter.
	new_settings.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
	
	//Begins.
	for(;;)
	{	//Reads 5 characters.
		std::cout << "\nType 5 characters. \"Enter\" will be pressed automatically: ";
		std::string typed_characters;
		for(int a = 0; a < 5; a++)
		{	char c; if(std::cin.get(c)) {typed_characters += c; std::cout << c;}
		}
		std::cout << "\nCaptured string: " << typed_characters << "\n";
	}
	
	//Restores normal keyboard input mode.
	tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
}

//Technically, enter is pressed after each character input,
//and printing \n makes it look like enter was pressed after 5.
//And technically technically, that's a total lie. But this way,
//you can at least understand what the program is trying to do.

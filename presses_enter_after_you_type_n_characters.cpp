//Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.

#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
int main()
{	struct termios old_settings, new_settings;
	tcgetattr(STDIN_FILENO, &old_settings);
	new_settings = old_settings;
	std::string typed_characters;
	
	for(;;)
	{	//Reads 5 characters.
		std::cout << "\nType 5 characters. \"Enter\" will be pressed automatically: ";
		typed_characters = "";
		new_settings.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
		for(int a = 0; a < 5; a++)
		{	char c; if(std::cin.get(c)) {typed_characters += c; std::cout << c;}
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
		std::cout << "\nCaptured string: " << typed_characters << "\n";
	}
}

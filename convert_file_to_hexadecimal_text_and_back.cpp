//Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
int main()
{	std::ifstream in_stream;
	std::ofstream out_stream;
	
	std::cout << "\n(1) Bin to hex."
	          << "\n(2) Hex back to bin."
	          << "\n\nOption: ";
	std::string o; std::getline(std::cin, o); if((o != "1") && (o != "2")) {std::cout << "\nBad option.\n"; return 0;}
	
	//Gets path.
	std::cout << "\nDrop/enter file:\n";
	std::string path; std::getline(std::cin, path); if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();}
	if(!std::filesystem::exists(path)) {std::cout << "\nNo path " << path << "\n"; return 1;}
	
	//Bin to hex.
	if(o == "1")
	{	in_stream.open (path);  if( !in_stream) {std::cout << "\nCan't open file for reading. (Bin to hex).\n"; return 1;}
		out_stream.open("hex"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Bin to hex).\n"; return 1;}
		for(char file_byte; in_stream.get(file_byte);)
		{	static const char symbols[] = "0123456789abcdef";
			out_stream << symbols[(unsigned char)file_byte >> 4] << symbols[file_byte & 0xf];
		}
		in_stream.close();
		out_stream.close();
	}
	
	//Hex back to bin.
	if(o == "2")
	{	in_stream.open (path);  if( !in_stream) {std::cout << "\nCan't open file for reading. (Hex back to bin).\n"; return 1;}
		out_stream.open("bin"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Hex back to bin).\n"; return 1;}
		for(char file_byte; in_stream.get(file_byte);)
		{	if(file_byte < 58) {file_byte -= 48;} else {file_byte -= 87;}
			int raw_byte = file_byte << 4;
			in_stream.get(file_byte);
			if(file_byte < 58) {file_byte -= 48;} else {file_byte -= 87;}
			out_stream.put(raw_byte + file_byte);
		}
		in_stream.close();
		out_stream.close();
	}
}

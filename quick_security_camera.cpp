//YOUR CONTROLS:
int seconds_to_sleep_between_image_capture = 3;
int number_of_images_to_capture = 1000000;



/*Run it: "apt install g++ geany fswebcam". Open the .cpp in Geany. Hit F9 once. F5 to run.

Webcam auto-capture. Input can also be a smartphone via USB; use phone's
webcam option in "more USB options" when connecting phone to computer.*/

#include <chrono>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
int main()
{	//Detects webcams (priority: external).
	std::system("fswebcam -q -r 1920x1080 --no-banner                      on_board_webcam_test.jpg");
	std::system("fswebcam -q -r 1920x1080 --no-banner --device /dev/video2 external_webcam_test.jpg");
	
	if((!std::filesystem::exists("on_board_webcam_test.jpg"))
	&& (!std::filesystem::exists("external_webcam_test.jpg")))
	{	std::cout << "\nNo webcams detected. Try running this again.\n\n"
		          << "Do \"apt install fswebcam\"\n\n"
		          << "Try plugging in the webcam half way into the USB port.\n\n";
		return 0;
	}
	
	std::string prefix = "fswebcam -q -r 1920x1080 --no-banner ";
	if(std::filesystem::exists("external_webcam_test.jpg")) {prefix += " --device /dev/video2 ";}
	
	std::filesystem::remove_all("on_board_webcam_test.jpg");
	std::filesystem::remove_all("external_webcam_test.jpg");
	
	//Begins.
	std::cout << "\033[2J\033[3J\033[1;1H"; std::cout << "\n"; //Clears screen, erasing history.
	std::filesystem::create_directories("images");
	for(int a = 0; a < number_of_images_to_capture; a++)
	{	//Gets date & time.
		std::string date;
		auto now = std::chrono::system_clock::now();
		std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
		std::tm localTime; localtime_r(&currentTime, &localTime);
		std::ostringstream oss; oss << std::put_time(&localTime, "%Y_%m_%d_%H:%M:%S"); date = oss.str();
		
		//Takes a photo.
		std::string command = prefix; command += "images/"; command += date; command += ".jpg"; //fswebcam -q -r 1920x1080 --no-banner images/2026_11_06_02:13:46.jpg
		std::system(command.c_str());
		
		//Sleeps.
		std::cout << (a + 1) << " images captured...\n";
		for(int b = 0; b < seconds_to_sleep_between_image_capture; b++) {std::this_thread::sleep_for(std::chrono::milliseconds(1000));}
	}
}



/* Truly instant NAS: https://github.com/compromise-evident/what-not/blob/main/truly_instant_NAS



or you can even retrieve / delete images via local network.

* The machine running this should have the Gnome desktop environment,
  unfortunately. Go to Settings, Sharing. Enable sharing, then enable
  "File Sharing" without password. This creates the "Public"
  folder in /home/user/ if missing.
* Run this in a folder in /home/user/Public
* Now any machine on the network has full read / write access
  to that "Public" folder. Find it in your files browser
  in "Browse Network" / "Other Locations". */

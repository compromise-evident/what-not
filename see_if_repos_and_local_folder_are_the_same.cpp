//YOUR CONTROLS:
char github_username[] = "compromise-evident";



/*Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.

Even if you don't need this program,  you should have a folder named "github".
It should contain folders with names matching your github repo names. And those
folders should be structured just like your github repos. Edit your files locally,
then upload them to GitHub (overwrites those files online and shows you a diff).*/

#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
int main()
{	std::ifstream in_stream;
	
	//Gets path.
	std::cout << "\nDrop/enter your local folder."
	          << "\nIt should contain folders with names matching your github repo names."
	          << "\nAnd those folders should be structured just like your github repos:\n";
	std::string path; std::getline(std::cin, path); if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();}
	if(!std::filesystem::exists(path)) {std::cout << "\nNo path " << path << "\n"; return 1;}
	
	//Gets list of local repo names.
	std::vector <std::string> local_repo_names;
	for(const auto& entry : std::filesystem::directory_iterator(path))
	{	if(entry.is_directory()) {local_repo_names.push_back(entry.path().lexically_relative(path).string());} //Loads list of folders to RAM as relative paths.
	}
	std::sort(local_repo_names.begin(), local_repo_names.end()); //Sorts list of folders in RAM.
	
	//Compares local repos to github repos.
	std::cout << "\n";
	std::filesystem::remove_all("downloaded_repos");
	std::filesystem::create_directories("downloaded_repos");
	for(unsigned long long a = 0; a < local_repo_names.size(); a++)
	{	//Downloads a repo as main.zip.
		std::string wget = "wget -q https://github.com/"; wget += github_username; wget += "/"; wget += local_repo_names[a]; wget += "/archive/refs/heads/main.zip"; //wget -q https://github.com/username/repo_name/archive/refs/heads/main.zip
		std::system(wget.c_str());
		if(!std::filesystem::exists("main.zip")) {std::cout << "download failed: " << local_repo_names[a] << "\n"; continue;}
		
		//Unzips main.zip to folder "downloaded_repos". Looks like "my_repo-main".
		std::system("unzip -q main.zip -d downloaded_repos > /dev/null 2>&1");
		std::filesystem::remove_all("main.zip");
		
		//Renames downloaded repo (omits the "-main").
		std::string  bad_name = "downloaded_repos/" + local_repo_names[a]; bad_name += "-main";
		std::string good_name = "downloaded_repos/" + local_repo_names[a];
		std::filesystem::rename(bad_name, good_name);
		
		//Compares repos. (Creates file "sameness" containing the word "same" if the folders are the same, or containing the word "different" if the folders are not the same).
		std::string path_to_local_repo  = path + "/"; path_to_local_repo += local_repo_names[a];
		std::string path_to_online_repo = "downloaded_repos/" + local_repo_names[a];
		std::string diff = "diff -rq " + path_to_local_repo; diff += " "; diff += path_to_online_repo; diff += " >/dev/null && echo same > sameness || echo different > sameness"; //diff -rq folder_1 folder_2 >/dev/null && echo same > sameness || echo different > sameness
		std::system(diff.c_str());
		
		in_stream.open("sameness"); if(!in_stream) {std::cout << "\nCan't open file for reading. (Compares repos).\n"; return 1;}
		std::string file_line; std::getline(in_stream, file_line);
		in_stream.close();
		
		if(file_line == "same") {std::cout << "           same: " << local_repo_names[a] << "\n";}
		else                    {std::cout << "      different: " << local_repo_names[a] << "\n";}
		std::filesystem::remove_all("sameness");
	}
}

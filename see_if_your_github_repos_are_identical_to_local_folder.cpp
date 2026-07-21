//YOUR CONTROLS:                                                                Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
char user_name[] = "compromise-evident";



/*Even if you don't need this program,  you should have a folder named "github".
It should contain folders with names matching your repo names. And those folders
should be structured just like your repos.  Edit your files locally, then upload
them to GitHub, which will overwrite those files online  and show you a diff. */

//Download URLs: https://github.com/user_name/repo_name/archive/refs/heads/main.zip

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
int main()
{	char file_byte;
	std::ifstream in_stream;
	std::ofstream out_stream;
	
	std::string SHA_512_input;
	std::string SHA_512_output;
	
	//Gets path.
	std::cout << "\nDrop/enter your local folder."
	          << "\nIt should contain folders with names matching your repo names."
	          << "\nAnd those folders should be structured just like your repos:\n";
	std::string path; std::getline(std::cin, path); if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();}
	if(!std::filesystem::exists(path)) {std::cout << "\nNo path " << path << "\n"; return 1;}
	
	//Gets list of immediate folders from a folder.
	std::vector <std::string> repo_list;
	for(const auto& entry : std::filesystem::directory_iterator(path))
	{	if(entry.is_directory()) {repo_list.push_back(entry.path().lexically_relative(path).string());} //Loads list of folders to RAM as relative paths.
	}
	std::sort(repo_list.begin(), repo_list.end()); //Sorts list of folders in RAM.
	
	//Compares local repos to github repos.
	std::cout << "\033[2J\033[3J\033[1;1H"; //Clears screen, erasing history.
	for(unsigned long long loop = 0; loop < repo_list.size(); loop++)
	{	//Downloads the repo. "wget -q https://github.com/username/repo_name/archive/refs/heads/main.zip".
		std::string wget = "wget -q https://github.com/"; wget += user_name; wget += "/"; wget += repo_list[loop]; wget += "/archive/refs/heads/main.zip";
		system(wget.c_str());
		
		//Unzips the download.
		system("unzip -q main.zip > /dev/null 2>&1");
		std::filesystem::remove_all("main.zip");
		
		//Creates deterministic archive of the local repo.
		{	std::string path_to_repo = path + "/"; path_to_repo += repo_list[loop];
			
			//Gets list of ALL files & folders from a folder.
			std::vector <std::string>   file_list;
			std::vector <std::string> folder_list;
			for(const auto& entry : std::filesystem::recursive_directory_iterator(path_to_repo))
			{	     if(entry.is_regular_file()) {  file_list.push_back(entry.path().lexically_relative(path_to_repo).string());} //Loads list of   files to RAM as relative paths.
				else if(entry.is_directory   ()) {folder_list.push_back(entry.path().lexically_relative(path_to_repo).string());} //Loads list of folders to RAM as relative paths.
			}
			std::sort(  file_list.begin(),   file_list.end()); //Sorts list of   files in RAM.
			std::sort(folder_list.begin(), folder_list.end()); //Sorts list of folders in RAM.
			
			//Creates archive.
			out_stream.open("archive"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Creates archive).\n"; return 1;}
			for(unsigned long long a = 0; a < folder_list.size(); a++) {out_stream << folder_list[a];}
			for(unsigned long long a = 0; a < file_list.size(); a++)
			{	out_stream << file_list[a];
				std::string full_path = path_to_repo + "/"; full_path += file_list[a];
				in_stream.open(full_path); if(!in_stream) {std::cout << "\nCan't open file for reading. (Adds file content).\n"; return 1;}
				for(; in_stream.get(file_byte);) {out_stream.put(file_byte);}
				in_stream.close();
			}
			out_stream.close();
		}
		
		//Gets hash of the deterministic archive of the local repo.
		in_stream.open("archive"); if(!in_stream) {std::cout << "\nCan't open file for reading. (Gets hash of the deterministic archive of the local repo).\n"; return 1;}
		SHA_512_input = ""; for(; in_stream.get(file_byte);) {SHA_512_input.push_back(file_byte);}
		in_stream.close();
		
		{std::string msg = SHA_512_input; unsigned long long H[8] = {0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL, 0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL, 0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL, 0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL}; const unsigned long long K[80] = {0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL, 0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL, 0xd807aa98a3030242ULL, 0x12835b0145706fbeULL, 0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL, 0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL, 0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL, 0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL, 0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL, 0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL, 0x06ca6351e003826fULL, 0x142929670a0e6e70ULL, 0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL, 0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL, 0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL, 0xd192e819d6ef5218ULL, 0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL, 0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL, 0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL, 0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL, 0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL, 0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL, 0xca273eceea26619cULL, 0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL, 0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL, 0x113f9804bef90daeULL, 0x1b710b35131c471bULL, 0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL, 0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL}; unsigned long long orig_len_bits = msg.length() * 8ULL; msg.push_back((char)0x80); for(; (msg.length() % 128) != 112;) {msg.push_back((char)0x00);} msg.append(8, (char)0x00); for(int a = 0; a < 8; a++) {msg.push_back((char)((orig_len_bits >> (56 - a * 8)) & 0xFF));} for(unsigned long long offset = 0; offset < msg.length(); offset += 128) {unsigned long long W[80]; for(int i = 0; i < 16; i++) {unsigned long long p = offset + (i * 8); W[i] = ((unsigned long long)(unsigned char)msg[p + 0] << 56) | ((unsigned long long)(unsigned char)msg[p + 1] << 48) | ((unsigned long long)(unsigned char)msg[p + 2] << 40) | ((unsigned long long)(unsigned char)msg[p + 3] << 32) | ((unsigned long long)(unsigned char)msg[p + 4] << 24) | ((unsigned long long)(unsigned char)msg[p + 5] << 16) | ((unsigned long long)(unsigned char)msg[p + 6] <<  8) | ((unsigned long long)(unsigned char)msg[p + 7]);} for(int i = 16; i < 80; i++) {unsigned long long x0 = W[i - 15]; unsigned long long s0 = ((x0 >> 1) | (x0 << 63)) ^ ((x0 >> 8) | (x0 << 56)) ^ (x0 >> 7); unsigned long long x1 = W[i - 2]; unsigned long long s1 = ((x1 >> 19) | (x1 << 45)) ^ ((x1 >> 61) | (x1 << 3)) ^ (x1 >> 6); W[i] = s1 + W[i - 7] + s0 + W[i - 16];} unsigned long long a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7]; for(int i = 0; i < 80; i++) {unsigned long long bs1 = ((e >> 14) | (e << 50)) ^ ((e >> 18) | (e << 46)) ^ ((e >> 41) | (e << 23)); unsigned long long ch  = (e & f) ^ (~e & g); unsigned long long T1  = h + bs1 + ch + K[i] + W[i]; unsigned long long bs0 = ((a >> 28) | (a << 36)) ^ ((a >> 34) | (a << 30)) ^ ((a >> 39) | (a << 25)); unsigned long long maj = (a & b) ^ (a & c) ^ (b & c); unsigned long long T2  = bs0 + maj; h = g; g = f; f = e; e = d + T1; d = c; c = b; b = a; a = T1 + T2;} H[0] += a; H[1] += b; H[2] += c; H[3] += d; H[4] += e; H[5] += f; H[6] += g; H[7] += h;} SHA_512_output = ""; const char symbols[] = "0123456789abcdef"; for(int a = 0; a < 8; a++) {for(int b = 15; b >= 0; b--) {int nibble = (H[a] >> (b * 4)) & 0xF; SHA_512_output += symbols[nibble];}}}
		std::string hash_of_local_repo = SHA_512_output;
		
		std::filesystem::remove_all("archive");
		
		//Creates deterministic archive of the online repo.
		{	std::string path_to_repo = repo_list[loop] + "-main";
			
			//Gets list of ALL files & folders from a folder.
			std::vector <std::string>   file_list;
			std::vector <std::string> folder_list;
			for(const auto& entry : std::filesystem::recursive_directory_iterator(path_to_repo))
			{	     if(entry.is_regular_file()) {  file_list.push_back(entry.path().lexically_relative(path_to_repo).string());} //Loads list of   files to RAM as relative paths.
				else if(entry.is_directory   ()) {folder_list.push_back(entry.path().lexically_relative(path_to_repo).string());} //Loads list of folders to RAM as relative paths.
			}
			std::sort(  file_list.begin(),   file_list.end()); //Sorts list of   files in RAM.
			std::sort(folder_list.begin(), folder_list.end()); //Sorts list of folders in RAM.
			
			//Creates archive.
			out_stream.open("archive"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Creates archive).\n"; return 1;}
			for(unsigned long long a = 0; a < folder_list.size(); a++) {out_stream << folder_list[a];}
			for(unsigned long long a = 0; a < file_list.size(); a++)
			{	out_stream << file_list[a];
				std::string full_path = path_to_repo + "/"; full_path += file_list[a];
				in_stream.open(full_path); if(!in_stream) {std::cout << "\nCan't open file for reading. (Adds file content).\n"; return 1;}
				for(; in_stream.get(file_byte);) {out_stream.put(file_byte);}
				in_stream.close();
			}
			out_stream.close();
		}
		
		//Gets hash of the deterministic archive of the online repo.
		in_stream.open("archive"); if(!in_stream) {std::cout << "\nCan't open file for reading. (Gets hash of the deterministic archive of the online repo).\n"; return 1;}
		SHA_512_input = ""; for(; in_stream.get(file_byte);) {SHA_512_input.push_back(file_byte);}
		in_stream.close();
		
		{std::string msg = SHA_512_input; unsigned long long H[8] = {0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL, 0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL, 0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL, 0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL}; const unsigned long long K[80] = {0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL, 0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL, 0xd807aa98a3030242ULL, 0x12835b0145706fbeULL, 0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL, 0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL, 0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL, 0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL, 0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL, 0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL, 0x06ca6351e003826fULL, 0x142929670a0e6e70ULL, 0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL, 0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL, 0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL, 0xd192e819d6ef5218ULL, 0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL, 0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL, 0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL, 0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL, 0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL, 0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL, 0xca273eceea26619cULL, 0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL, 0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL, 0x113f9804bef90daeULL, 0x1b710b35131c471bULL, 0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL, 0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL}; unsigned long long orig_len_bits = msg.length() * 8ULL; msg.push_back((char)0x80); for(; (msg.length() % 128) != 112;) {msg.push_back((char)0x00);} msg.append(8, (char)0x00); for(int a = 0; a < 8; a++) {msg.push_back((char)((orig_len_bits >> (56 - a * 8)) & 0xFF));} for(unsigned long long offset = 0; offset < msg.length(); offset += 128) {unsigned long long W[80]; for(int i = 0; i < 16; i++) {unsigned long long p = offset + (i * 8); W[i] = ((unsigned long long)(unsigned char)msg[p + 0] << 56) | ((unsigned long long)(unsigned char)msg[p + 1] << 48) | ((unsigned long long)(unsigned char)msg[p + 2] << 40) | ((unsigned long long)(unsigned char)msg[p + 3] << 32) | ((unsigned long long)(unsigned char)msg[p + 4] << 24) | ((unsigned long long)(unsigned char)msg[p + 5] << 16) | ((unsigned long long)(unsigned char)msg[p + 6] <<  8) | ((unsigned long long)(unsigned char)msg[p + 7]);} for(int i = 16; i < 80; i++) {unsigned long long x0 = W[i - 15]; unsigned long long s0 = ((x0 >> 1) | (x0 << 63)) ^ ((x0 >> 8) | (x0 << 56)) ^ (x0 >> 7); unsigned long long x1 = W[i - 2]; unsigned long long s1 = ((x1 >> 19) | (x1 << 45)) ^ ((x1 >> 61) | (x1 << 3)) ^ (x1 >> 6); W[i] = s1 + W[i - 7] + s0 + W[i - 16];} unsigned long long a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7]; for(int i = 0; i < 80; i++) {unsigned long long bs1 = ((e >> 14) | (e << 50)) ^ ((e >> 18) | (e << 46)) ^ ((e >> 41) | (e << 23)); unsigned long long ch  = (e & f) ^ (~e & g); unsigned long long T1  = h + bs1 + ch + K[i] + W[i]; unsigned long long bs0 = ((a >> 28) | (a << 36)) ^ ((a >> 34) | (a << 30)) ^ ((a >> 39) | (a << 25)); unsigned long long maj = (a & b) ^ (a & c) ^ (b & c); unsigned long long T2  = bs0 + maj; h = g; g = f; f = e; e = d + T1; d = c; c = b; b = a; a = T1 + T2;} H[0] += a; H[1] += b; H[2] += c; H[3] += d; H[4] += e; H[5] += f; H[6] += g; H[7] += h;} SHA_512_output = ""; const char symbols[] = "0123456789abcdef"; for(int a = 0; a < 8; a++) {for(int b = 15; b >= 0; b--) {int nibble = (H[a] >> (b * 4)) & 0xF; SHA_512_output += symbols[nibble];}}}
		std::string hash_of_online_repo = SHA_512_output;
		
		std::filesystem::remove_all("archive");
		
		//Compares.
		if(hash_of_local_repo == hash_of_online_repo) {std::cout << "    IDENTICAL: " << repo_list[loop] << "\n";}
		else                                          {std::cout << "NOT IDENTICAL: " << repo_list[loop] << "\n";}
		
		//Removes the unzipped version of the download.
		std::string str = repo_list[loop] + "-main";
		std::filesystem::remove_all(str);
	}
}

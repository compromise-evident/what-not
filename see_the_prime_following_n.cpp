//YOUR CONTROLS:
char n[50001] = {"528037116243879373684169704087111038557573838"}; //Replace with a "2" to 50,000 digits



/*Run it: "apt install g++ geany libgmp-dev". Open the .cpp in Geany.
Go to Build >> Set Build Commands. Where it says "Compile" and "Build", append " -lgmp".
Hit F9 once. F5 to run. */

#include <gmp.h>
#include <iostream>
int main()
{	//Makes n prime.
	mpz_t in, out; mpz_init(in); mpz_init(out); mpz_set_str(in, n, 10); mpz_nextprime(out, in); mpz_get_str(n, 10, out);
	
	std::cout << n;
}

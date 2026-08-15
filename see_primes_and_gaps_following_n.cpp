//YOUR CONTROLS:
long long number_of_gaps = 10;
char n[50001] = {"528037116243879373684169704087111038557573838"}; //Replace with a "2" to 50,000 digits



/*Run it: "apt install g++ geany libgmp-dev". Open the .cpp in Geany.
Go to Build >> Set Build Commands. Where it says "Compile" and "Build", append " -lgmp".
Hit F9 once. F5 to run.

Near which private prime, will I find these public gaps? is
at least as statistically strong as semiprime factorization.*/

#include <gmp.h>
#include <iostream>
int main()
{	//Makes n prime.
	mpz_t in, out; mpz_init(in); mpz_init(out); mpz_set_str(in, n, 10); mpz_nextprime(out, in); mpz_get_str(n, 10, out);
	std::cout << "\nPrime gaps after prime:\n" << n << "\n\n";
	
	//Dedicates.
	mpz_t prime, two; mpz_init(prime); mpz_init(two); mpz_set_str(prime, n, 10); mpz_set_ui(two, 2);
	
	//Generates. (Copy-pastable & loopable; continues where it left off.)
	for(long long gap = 2, a = 0; a < number_of_gaps;)
	{	mpz_add(prime, prime, two);
		int primality = mpz_probab_prime_p(prime, 25);
		if(primality == false) {gap += 2;}
		else {std::cout << gap << "\n"; mpz_get_str(n, 10, prime); std::cout << n << "\n\n"; gap = 2; a++;}
	}
}

//YOUR CONTROLS:
int prime_and_composite_length = 20; //50k max
int quantity = 100000;



/*Run it: "apt install g++ geany libgmp-dev". Open the .cpp in Geany.
Go to Build >> Set Build Commands. Where it says "Compile" and "Build", append " -lgmp".
Hit F9 once. F5 to run.

Generates primes & composites
labeled 1 = prime, 0 = composite. */

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <gmp.h>
#include <iostream>
int main()
{	std::ofstream out_stream;
	
	std::srand(std::time(0));
	char p[50001] = {'\0'};
	char q[50001] = {'\0'};
	mpz_t randomness; mpz_init(randomness);
	mpz_t prime_p   ; mpz_init(prime_p   );
	
	out_stream.open("p"); if(!out_stream) {std::cout << "\nCan't open file for writing. (p).\n"; return 1;}
	for(int loops = 0; loops < quantity;)
	{	int which_one = (std::rand() % 2);
		if(which_one == 0)
		{	p[0] = ((std::rand() % 9) + 49); for(int a = 1; a < prime_and_composite_length; a++) {p[a] = ((std::rand() % 10) + 48);}     //Random p.
			mpz_set_str(randomness, p, 10); mpz_nextprime(prime_p, randomness); mpz_get_str(p, 10, prime_p);                             //p made prime.
			if(p[prime_and_composite_length] != '\0') {p[prime_and_composite_length] = '\0'; continue;}                                  //Restarts if p too long.
			
			//Saves to file: label, prime.
			//##############################
			out_stream << "1 " << p << "\n";
			//##############################
		}
		else
		{	for(int compositeness = 1; compositeness != 0;)
			{	q[0] = ((std::rand() % 9) + 49); for(int a = 1; a < prime_and_composite_length; a++) {q[a] = ((std::rand() % 10) + 48);} //Random q.
				mpz_set_str(randomness, q, 10); compositeness = mpz_probab_prime_p(randomness, 100);                                     //q used if composite.
			}
			mpz_get_str(q, 10, randomness);
			
			//Saves to file: label, composite.
			//##############################
			out_stream << "0 " << q << "\n";
			//##############################
		}
		
		loops++; std::cout << loops << " of " << quantity << "\n";                                                                       //Proceeds only if successful.
	}
	out_stream.close();
}

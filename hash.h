#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				HASH_INDEX_T hash = 0;
				unsigned long long w[5] = {0};
				int setTracker = 4, powTracker = 0, power = 36;

				for(int i = k.length() - 1; i >= 0; i--){
					if(powTracker == 6){
						setTracker--;
						powTracker = 0;
						power = 36;
					}

					char current;
					if(std::isdigit(k[i])){
						current = k[i];
					}

					else{
						current = std::tolower(k[i]);
					}

					HASH_INDEX_T value = letterDigitToNumber(current);

					if(value != static_cast<HASH_INDEX_T>(-1)){
							if(powTracker == 0){
								w[setTracker] += value;
							}

							else if (powTracker == 1){
								w[setTracker] += value * power;
							}

							else{
								power *= 36;
								w[setTracker] += value * power;
							}

							powTracker++;
					}
				}

				for(int i = 0; i < 5; i++){
					//std::cout << "w[" << i << "]: " << w[i] << std::endl;
					hash += rValues[i] * w[i];
				}

				return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				if(std::isdigit(letter)){
					return static_cast<HASH_INDEX_T>(letter - '0' + 26);
				}

				else if (std::isalpha(letter)){
					return static_cast<HASH_INDEX_T>(letter - 'a');
				}

				else{
					return static_cast<HASH_INDEX_T>(-1);
				}
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
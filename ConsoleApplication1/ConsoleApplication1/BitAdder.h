#pragma once

class BitAdder {
	public:
		//converts binary strings to integer
		unsigned long stringarr_tohex(std::array<std::string, 8> arr) {
			unsigned long i = 0;
			std::string bin_arr = "0x";
			int x = 0;
			while (x < 8) {
				int t = std::stoi(arr[x], nullptr, 2);
				bin_arr += Hexstr[t];

				x++;
			}

			std::stringstream iss(bin_arr);
			iss >> std::hex >> i;
			return i;
		}
		

		//converts array of hex to unsigned long
		unsigned long hexarr_toint(std::array<unsigned long long, 8> arr) {
			unsigned long i = 0;
			std::array<char, 8> hex_arr;
			std::string hexstr = "0x";
			int x = 0;
			int y = 0;
			for (int i = 0; i < 8; i++) {
			
				hex_arr[i] = Hexstr[arr[i]];


			}


			for (int i = 0; i < 8; i++) {
		
				hexstr += hex_arr[i];
			}

			std::istringstream iss(hexstr);
			iss >> std::hex >> i;
			return i;
		}

		//converts each element of an array of hex to hex string 2d array
		unsigned long HexConverter2d(std::array<unsigned long long, 8> set) {
			unsigned long i = 0;
			std::string hexconv = "0x";

			for (int i = 0; i < 8; i++) {
				//adds hex char from hexstr so the entire row of set is interpreted as one big hex string

				hexconv += Hexstr[set[i]];

			}

			//converts the hexconv to an integer
			std::istringstream iss(hexconv);
			iss >> std::hex >> i;
			return i;
		}


		//converts unsigned long to individual hex array.
		//basically creating a row nearly identical to a row from NSACONSTS
		//e.g int i[0] = {0x0, 0x6, 0xa....};
		std::string hex_str(unsigned long x) {
			std::stringstream Stream;
			Stream << std::hex << x;
			return Stream.str();
		}

		std::array<unsigned long long, 8> hexarr_toelems(unsigned long x) {

			
			std::array<unsigned long long, 8> vect;


			std::string hexstr = "0x";
			unsigned int out;
			//unsigned int y = 0;
			std::stringstream ss;
			 
			ss << std::hex << x;
	 
			for (int i = 0; i < ss.str().length(); i++)
			{
				 
				//adds hexstr + the hex string character to an element in the array of strings
				//converts the string to an hex

				std::stringstream oss(hexstr + ss.str()[i]);
				 

				oss >> std::hex >> out;

				vect[i] = out;

			}
			return vect;
		}
		
	private:
		std::string Hexstr = "0123456789abcdef";
		unsigned int HEXARR[16] = { 0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf };
};

#include "stdafx.h"
#include <algorithm>
#include <array>
#include <vector>
#include <bitset>
#include <iostream>
class BitHandler {

public:
	//Shift bits by rotNum of times
	std::array<std::string, 8> Bitshifter(int rotNum, std::vector<unsigned int> row)
	{
		std::string bin_arr;
		std::array<std::string, 8> retarr;
		 
		int x = 0;
		int i = 0;
		int y = 0;

		std::array<char, 32> cstr;
		 
		//adds the bitset to string
		for (; x < 8; x++) {
			std::bitset<4> barr(row[x]);
			i = 0;
			while (i < 4) {
				cstr[y] = barr.to_string()[i];
				y++;
				i++;
			}
		}

		/*Rotates the array by one at a time
		It is reversed because std::rotate only shifts one direction*/
		std::reverse(cstr.begin(), cstr.end());
		std::rotate(cstr.begin(), cstr.begin() + (rotNum % 32), cstr.end());



		//Now is reverse back to normal
		std::reverse(cstr.begin(), cstr.end());

		x = 0;
		//creates an array of 4bit strings to be easily converted back to decimal
		for (i = 0; i < row.size(); i++) {
			y = 0;
			while (y < 4) {
				retarr[i] += cstr[x];
				y++;
				x++;
				if (cstr.size() == 32) break;
			}
		}
		return retarr;
	}


	//XOR the bits of 3 arrays and returns the results as an array
	std::array<std::string, 8> Bitmod(std::array<std::string, 8> arr1, std::array<std::string, 8> arr2, std::array<std::string, 8> arr3) {
		std::array<std::string, 8> retarr;
		 
		int x = 0;
		std::string bitstr;



		std::bitset<4> zero(0);
		for (int i = 0; i < 8; i++) {
			bitstr = "";

			int no = std::stoi(arr1[i], nullptr, 2);
			int no2 = std::stoi(arr2[i], nullptr, 2);
			int no3 = std::stoi(arr3[i], nullptr, 2);
			//XOR's all bits
			std::bitset<4> set((no^no2^no3));

			//stores the string of 4bits to an array
			retarr[i] = set.to_string();
			//std::cout << retarr[i];
		}

		return retarr;
	}

	/*Choosing function! Specify the row in the CH param you want to start reading
	row2 and row3 are the rows where the the function will choose from*/
	std::array<std::string, 8> Choosing(std::vector<unsigned int> CHrow, std::vector<unsigned int> row2, std::vector<unsigned int> row3) {
		std::string bin_arr;
		int x = 0;
		std::array<std::string, 8> retarr;
		std::bitset<4> zero(0);
		for (int i = 0; i < 8; i++) {
			x = 0;
			//Converts each number to bitsets
			std::bitset<4> bitROW(CHrow[i % CHrow.size()]);
			std::bitset<4> bitF(row2[i]);
			std::bitset<4> bitG(row3[i]);
			bin_arr = "";
			while (x < 4) {
				//checks if the bit equals zero
				if (bitROW.to_string()[x] == zero.to_string()[x]) {
					bin_arr += bitG.to_string()[x];
				}
				else {
					bin_arr += bitF.to_string()[x];
				}
				x++;
			}
			retarr[i] = { bin_arr };
		}
		return retarr;
	}

	std::vector<unsigned int> AddNull(std::vector<unsigned int> arr) {
		
				
		while (arr.size() < 8) {
			arr.push_back(NULL);
		}
		
		return arr;
	}
	//Majority function! Checks for the majority of the bits in the first 3 rows of NSACONSTS
	std::array<std::string, 8> Majority(std::vector<unsigned int> A, std::vector<unsigned int> B, std::vector<unsigned int> C) {
		//arr2 only stores bits
		std::array<std::string, 8> arr2;
		
		
		//Start of increment
		int incre1 = 0;
		for (; incre1 < 8; incre1++) {
			//Adds A,B,C of the nsa constants to an integer
			//Every time it loops x,y,z will be a new integer from the row
			std::bitset<4> zero(0);
			//std::cout << " Maj: " << incre1 << std::endl;
			
			std::bitset<4> num1(A[incre1]);
			std::bitset<4> num2(B[incre1]);
			std::bitset<4> num3(C[incre1]);
			int no;
			int no2;
			int no3;
			int i = 0;
			do {
				(num1[i] == zero[0]) ? no = 0 : no = 1;
				(num2[i] == zero[0]) ? no2 = 0 : no2 = 1;
				(num3[i] == zero[0]) ? no3 = 0 : no3 = 1;
				int sum = no + no2 + no3;
				(sum > 1) ? arr2[incre1] += { '1' } : arr2[incre1] += { '0' };
				i++;
			} while (i < 4);
			std::reverse(arr2[incre1].begin(), arr2[incre1].end());
		}
		return arr2;
	}


};
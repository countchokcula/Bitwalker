// ConsoleApplication1.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "windows.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <sstream>
#include <tuple>
#include <array>
#include <memory>
#include <cmath>
#include <ctime>
#include <thread>
#include <future>
//#include "Opencl.cpp"
#include "Bithandler.h"
#include "BitAdder.h"
//With everything I do in this program, I do it for a reason!
class Dehasher : public BitHandler{


public:


	std::array<std::string, 8> shiftT1(std::array<unsigned long long, 8> a) {


		//A shifted
		std::array<std::string, 8>  Ashift2 = Bitshifter(2, a);
		std::array<std::string, 8>  Ashift13 = Bitshifter(13, a);
		std::array<std::string, 8>  Ashift22 = Bitshifter(22, a);
		//A summed
		std::array<std::string, 8> Asum = Bitmod(Ashift2, Ashift13, Ashift22);
		//p.set_value(Asum);
		return Asum;
	}
	std::array<std::string, 8> shiftT2(std::array<unsigned long long, 8> e) {
		//row E shifted
		//std::cout << "E shifting : ";
		std::array<std::string, 8>  Eshift6 = Bitshifter(6, e);
		//for (int i = 0; i < 8; i++) {
		//	std::cout << Eshift6[i];
		//}
		//std::cout << "\n 11: ";
		std::array<std::string, 8>  Eshift11 = Bitshifter(11, e);
		//for (int i = 0; i < 8; i++) {
			//std::cout << Eshift11[i];
		//}
		//std::cout << "\n 25: ";
		std::array<std::string, 8 >  Eshift25 = Bitshifter(25, e);
		//for (int i = 0; i < 8; i++) {
			//std::cout << Eshift25[i];
		//}
		//std::cout << std::endl;
		std::array<std::string, 8> Esum = Bitmod(Eshift6, Eshift11, Eshift25);
		 
		//p.set_value(Esum);
		return Esum;
	}
	void solver() {
		 
		int x = 0;
		nsa = {
			NSACONSTS[0],
			NSACONSTS[1],
			NSACONSTS[2],
			NSACONSTS[3],
			NSACONSTS[4],
			NSACONSTS[5],
			NSACONSTS[6],
			NSACONSTS[7] };


		//start
		//very first set of the default NSA consts
		//i've created a structure of pointers because they dynamically change


		std::array<std::string, 8> Asum;
		std::array<std::string, 8> Esum;

		while (x < 128) {
			//old values used to reassign vars
			//these are static and are reassigned on the next iteration

		
			nsa = newSTRUCT();
			
		 
			//holds 32 bits of 1d array. 
			 
			 
			std::array<std::string, 8> majority = Majority(nsa.a, nsa.b, nsa.c);
			 
			std::future<std::array<std::string, 8>> f1 = std::async(std::launch::async, &Dehasher::shiftT1, this, nsa.a);
 
			std::future<std::array<std::string, 8>> f2 = std::async(std::launch::async, &Dehasher::shiftT2, this, nsa.e);
 
			Asum = f1.get();
			Esum = f2.get();
			 
			//Choosing
			 
			std::array<std::string, 8> ch = Choosing(nsa.e, nsa.f, nsa.g);
 
			//chosen
			unsigned long CH = stringarr_tohex(ch);
		 
			//Majority to hex
			unsigned long maj = stringarr_tohex(majority);
 
			//E from Esum
			unsigned long E1 = stringarr_tohex(Esum);
		 
			//A from ASUM
			unsigned long A1 = stringarr_tohex(Asum);
 
			//row H from NSACONSTS



			unsigned long H1 = HexConverter2d(nsa.h);
 
			unsigned long oldsum = AddCH(CH, H1, E1);
		 
			unsigned long long newa = NewA(A1, maj, oldsum);

			int y = 0;
 
 
			


			
			 
			nsa.h = nsa.g;
			nsa.g = nsa.f;
			nsa.f = nsa.e;

			nsa.d = nsa.c;
			nsa.c = nsa.b;
			nsa.b = nsa.a;
	

		 
			nsa.a = hexarr_toelems(newa);
 
			 
			
			nsa.e = hexarr_toelems(oldsum + hexarr_toint(nsa.e));
		 
			x++;

		}
		 

	};
	
	void solver1() {
		int x = 0;

		//start
		//very first set of the default NSA consts
		//i've created a structure of pointers because they dynamically change

		nsa = {
			NSACONSTS[0],
			NSACONSTS[1],
			NSACONSTS[2],
			NSACONSTS[3],
			NSACONSTS[4],
			NSACONSTS[5],
			NSACONSTS[6],
			NSACONSTS[7] };
		while (x < 128) {
			//old values used to reassign vars

			nsa = newSTRUCT();

			//holds 32 bits of 1d array.
			std::array<std::string, 8> majority = Majority(nsa.a, nsa.b, nsa.c);

			//A shifted
			std::array<std::string, 8>  Ashift2 = Bitshifter(2, nsa.a);
			std::array<std::string, 8>  Ashift13 = Bitshifter(13, nsa.a);
			std::array<std::string, 8>  Ashift22 = Bitshifter(22, nsa.a);
			//A summed
			std::array<std::string, 8> Asum = Bitmod(Ashift2, Ashift13, Ashift22);

			//row E shifted
			std::array<std::string, 8>  Eshift6 = Bitshifter(6, nsa.e);
			std::array<std::string, 8>  Eshift11 = Bitshifter(11, nsa.e);
			std::array<std::string, 8>  Eshift25 = Bitshifter(25, nsa.e);

			//E summed
			std::array<std::string, 8> Esum = Bitmod(Eshift6, Eshift11, Eshift25);
			 
			//Choosing
			std::array<std::string, 8> ch = Choosing(nsa.e, nsa.f, nsa.g);
			//chosen
			unsigned long long CH = stringarr_tohex(ch);
			//Majority to hex
			unsigned long long maj = stringarr_tohex(majority);
			//E from Esum
			unsigned long long E1 = stringarr_tohex(Esum);
			//row H from NSACONSTS
			unsigned long long H1 = HexConverter2d(nsa.h);

			unsigned long long oldsum = AddCH( CH, H1, E1);

			unsigned long long newa = NewA(E1, maj, oldsum);

			
			nsa.h = nsa.g;
			nsa.g = nsa.f;
			nsa.f = nsa.e;

			nsa.d = nsa.c;
			nsa.c = nsa.b;
			nsa.b = nsa.a;
			 

			nsa.a = hexarr_toelems(newa);
			nsa.e = hexarr_toelems(oldsum + hexarr_toint(nsa.e));
			x++;
		}


	};

	void shiftP1(std::promise<std::array<std::string, 8>> *p, std::array<unsigned long long, 8> a) {


		//A shifted
		std::array<std::string, 8>  Ashift2 = Bitshifter(2, a);
		std::array<std::string, 8>  Ashift13 = Bitshifter(13, a);
		std::array<std::string, 8>  Ashift22 = Bitshifter(22, a);
		//A summed
		std::array<std::string, 8> Asum = Bitmod(Ashift2, Ashift13, Ashift22);
		p->set_value(Asum);

	}
	void shiftP2(std::promise<std::array<std::string, 8>> *p, std::array<unsigned long long, 8> e) {
		//row E shifted
		std::array<std::string, 8>  Eshift6 = Bitshifter(6, e);
		std::array<std::string, 8>  Eshift11 = Bitshifter(11, e);
		std::array<std::string, 8>  Eshift25 = Bitshifter(25, e);
		std::array<std::string, 8> Esum = Bitmod(Eshift6, Eshift11, Eshift25);

		p->set_value(Esum);

	}


	void solver3() {
		int x = 0;

		//start
		//very first set of the default NSA consts
		//i've created a structure of pointers because they dynamically change
		nsa = {
			NSACONSTS[0],
			NSACONSTS[1],
			NSACONSTS[2],
			NSACONSTS[3],
			NSACONSTS[4],
			NSACONSTS[5],
			NSACONSTS[6],
			NSACONSTS[7] };


		std::array<std::string, 8> Asum;
		std::array<std::string, 8> Esum;


		while (x < 128) {
			nsa = newSTRUCT();
			//holds 32 bits of 1d array.
			 
			std::array<std::string, 8> majority = Majority(nsa.a, nsa.b, nsa.c);

			 
			std::promise<std::array<std::string, 8>> prA;
			std::promise<std::array<std::string, 8>> prE;

			std::future<std::array<std::string, 8>> f1 = prA.get_future();
			std::future<std::array<std::string, 8>> f2 = prE.get_future();

			std::thread t1(&Dehasher::shiftP1, this, &prA, nsa.a);
			std::thread t2(&Dehasher::shiftP2, this, &prE, nsa.e);

			t1.join();
			t2.join();
			

			Asum = f1.get();
			Esum = f2.get();
			std::array<std::string, 8> ch = Choosing(nsa.e, nsa.f, nsa.g);
			//chosen
			unsigned long CH = stringarr_tohex(ch);

			//Majority to hex
			unsigned long maj = stringarr_tohex(majority);
			//E from Esum
			unsigned long E1 = stringarr_tohex(Esum);
			//A from ASUM
			unsigned long A1 = stringarr_tohex(Asum);
			//row H from NSACONSTS

			 

			unsigned long H1 = HexConverter2d(nsa.h);

			unsigned long oldsum = AddCH(CH, H1, E1);

			unsigned long newa = NewA(A1, maj, oldsum);

			
			 

			nsa.h = nsa.g;
			nsa.g = nsa.f;
			nsa.f = nsa.e;

			nsa.d = nsa.c;
			nsa.c = nsa.b;
			nsa.b = nsa.a;


			nsa.a = hexarr_toelems(newa);
			nsa.e = hexarr_toelems(oldsum + hexarr_toint(nsa.e));

			x++;
		}


	};
	void solverShow() {

		int x = 0;
		std::cout << " First the program sets the 8 constant values of the hash block e.g nsa.a = 0xc1b823a Or " << 0xc1b823a << "\n" << std::endl;
		
		for (int i = 0; i < 8; i++) {
			std::cout << NSACONSTS[0][i] << " ";
		}
		std::cout << " \n" << std::endl;
		std::cin.get();
		nsa = {
			NSACONSTS[0],
			NSACONSTS[1],
			NSACONSTS[2],
			NSACONSTS[3],
			NSACONSTS[4],
			NSACONSTS[5],
			NSACONSTS[6],
			NSACONSTS[7] };



		std::array<std::string, 8> Asum;
		std::array<std::string, 8> Esum;


 
	 

		//checks full any arrays less than zero
		nsa = newSTRUCT();


		//holds 32 bits of 1d array.
		std::cout << " Now it compares bit and puts them in a function names Majority, which checks betweens one and zeros\n Press enter so show the majority values of the first row!" << std::endl;
		std::cin.get();
		std::array<std::string, 8> majority = Majority(nsa.a, nsa.b, nsa.c);
		for (int i = 0; i < 8; i++) {
			std::cout << majority[i];
		}
		std::cout << std::endl << std::endl;
		//std::cout << "Async" << std::endl;
		Sleep(500);
		std::cout << "\n Now it executes two threads to get all of the bits of rows from a structure, and returns it as an array.  \n Press enter to execute a thread!" << std::endl;
		std::cin.get();
		std::cout << "\n Executing thread";
		Sleep(500);
		std::cout << ".";
		Sleep(500);
		std::cout << ".";
		Sleep(500);
		std::cout << ".\n" << std::endl;

		std::promise<std::array<std::string, 8>> prA;
		std::promise<std::array<std::string, 8>> prE;

		std::future<std::array<std::string, 8>> f1 = prA.get_future();
		std::future<std::array<std::string, 8>> f2 = prE.get_future();

		std::thread t1(&Dehasher::shiftP1, this, &prA, nsa.a);
		std::thread t2(&Dehasher::shiftP2, this, &prE, nsa.e);

		t1.join();
		t2.join();
		Asum = f1.get();
		Esum = f2.get();

		for (int i = 0; i < 8; i++) {
			std::cout << Asum[i];

		}
		Sleep(500);
		std::cout << std::endl;
		for (int i = 0; i < 8; i++) {
			std::cout << Esum[i];
		
		}
		std::cout << " \n" << std::endl;
		
		//Choosing
		//std::cout << "Ch" << std::endl
		std::cout << " Now it's at the choosing phase.\n\n Press enter to start choosing!" << std::endl;
		std::cin.get();
		std::array<std::string, 8> ch = Choosing(nsa.e, nsa.f, nsa.g);
		for (int i = 0; i < 8; i++) {
			std::cout << ch[i];

		}
		std::cout << "\n" << std::endl;
		//chosen
		std::cout << " Now it converts those arrays to hexadecimal integers\n\n  Press Enter to display integers" << std::endl;
		std::cin.get();
		unsigned long CH = stringarr_tohex(ch);

		//Majority to hex
		unsigned long maj = stringarr_tohex(majority);
		//E from Esum
		unsigned long E1 = stringarr_tohex(Esum);
		//A from ASUM
		unsigned long A1 = stringarr_tohex(Asum);
		//row H from NSACONSTS



		unsigned long H1 = HexConverter2d(nsa.h);
		std::cout << "Choosing: " << CH << " Majority: " << maj << " E: " << E1 << " A: " << A1 << std::endl;

		std::cout << " Now it adds! \n  Press enter to show the sums!" << std::endl;
		std::cin.get();
		unsigned long oldsum = AddCH(CH, H1, E1);

		unsigned long newa = NewA(A1, maj, oldsum);
		std::cout << " Oldsum adds the choosing value '" << CH << "'" << " H value '" << H1 << "'" << " and A '" << A1 << "'" << " which equals " << oldsum << std::endl;
		std::cout << "\n Newa adds the A1 values, the majority value and the oldsum value to get the new variable for row A\n\n  Press enter to continue!" << std::endl;
		std::cin.get();


		std::cout << " Now it reassigns old rows e.g nsa.b = nsa.a OR nsa.b = 0xc1b823a Or " << 0xc1b823a << std::endl;
		std::cin.get();
		nsa.h = nsa.g;
		nsa.g = nsa.f;
		nsa.f = nsa.e;

		nsa.d = nsa.c;
		nsa.c = nsa.b;
		nsa.b = nsa.a;


		nsa.a = hexarr_toelems(newa);
		nsa.e = hexarr_toelems(oldsum + hexarr_toint(nsa.e));

		char var;
		std::cout << "This does the SHA-256 algorithm. Now this process is completed after 128 times to mine an entire hash block![NOTE] THIS PROGRAM CANNOT MINE CERTAIN HASH BLOCKS! It's supposed to give you an idea of how fast your computer can mine a bitcoin hash" << std::endl;
		std::cout << "\n\n Would you like to see the video based off is this program? [y/n] \n" << std::endl;
		char mar;
		std::cin >> mar;
		if (mar == 'y') {
			ShellExecute(0, 0, L"https://www.youtube.com/watch?v=y3dqhixzGVo&feature=youtu.be", 0, 0, SW_SHOW);
		}
		std::cout << "\n Would you like to see it again? [y/n]";
			std::cin >> var;
			if (var == 'y') {
				solverShow();
			}
			else {
				std::cout << "\nGoodbye!\n" << std::endl;
			}
	};
	unsigned long long AddCH(unsigned long ch, unsigned long H, unsigned long E) {

		//version 2
		unsigned long W = 0x02000000;

		unsigned long sum = W + K + H + ch + E;

		return sum;
	}

	unsigned long long NewA(unsigned long asum, unsigned long maj, unsigned long oldsum) {
		 
		return asum + maj + oldsum;
	}

	
 
	
	struct nsaconstsN {
		//A [0]
		std::array<unsigned long long, 8> a;
		//B [1]
		std::array<unsigned long long, 8> b;
		//C [2]						  
		std::array<unsigned long long, 8> c;
		//D [3]						  
		std::array<unsigned long long, 8> d;
		//E [4]						  
		std::array<unsigned long long, 8> e;
		//F [5]						  
		std::array<unsigned long long, 8> f;
		//G [6]						  
		std::array<unsigned long long, 8> g;
		//H [7]						  
		std::array<unsigned long long, 8> h;
	} nsa;
	nsaconstsN newSTRUCT() {
		
		nsa.a = AddNull(nsa.a);
		nsa.b = AddNull(nsa.b);
		nsa.c = AddNull(nsa.c);
		nsa.d = AddNull(nsa.d);

		nsa.e = AddNull(nsa.e);
		nsa.f = AddNull(nsa.f);
		nsa.g = AddNull(nsa.g);
		nsa.h = AddNull(nsa.h);
		return nsa;
	}
 
private:
	int A = 0;
	int B = 1;
	int C = 2;
	int D = 3;
	int E = 4;
	int F = 5;
	int G = 6;
	int H = 7;
	//NSA constant values editable and dynamtically changes

	std::array<std::array<unsigned long long, 8>, 8> NSACONSTS = { {
		{ 0x6, 0xa, 0x0, 0x9, 0xe, 0x6, 0x6, 0x7 },
		{ 0xb, 0xb, 0x6, 0x7, 0xa, 0xe, 0x8, 0x5 },
		{ 0x3, 0xc, 0x6, 0xe, 0xf, 0x3, 0x7, 0x2 },
		{ 0xa, 0x5, 0x4, 0xf, 0xf, 0x5, 0x3, 0xa },
		{ 0x5, 0x1, 0x0, 0xe, 0x5, 0x2, 0x7, 0xf },
		{ 0x9, 0xb, 0x0, 0x5, 0x6, 0x8, 0x8, 0xc },
		{ 0x1, 0xf, 0x8, 0x3, 0xd, 0x9, 0xa, 0xb },
		{ 0x5, 0xb, 0xe, 0x0, 0xc, 0xd, 0x1, 0x9 }
	}
};

	//value K consts from NSA
	const unsigned long K = 0x428a2f98;


	/*Hexstr is used for a row from NSACONSTS to be interpreted as one big hex number later on
	if each hexadecimal number from the NSACONSTS array is interpreted literally it will interpret it LITERALLY that's why this string is needed

	eg  0xa = 10 so if you were to convert it into a string literal, the console will output 10 and NOT 0xa */
	std::string Hexstr = "0123456789abcdef";
	unsigned int HEXARR[16] = { 0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf };

	/*Some arrays are used as one big binary string, combining every element into one big string
	Instead of returning just one string, I've used arrays to keep track of numbers(every 4 bits) easily;
	They all store individual strings of ones and zeros and are later interpreted as numbers

	eg array[0] = {"0101"}*/


	/*holds 32 bits of 1d array.
	std::array<std::string, 8> majority = Majority();
	//row A shifted various times
	std::array<std::string, 8>  Ashift2 = Bitshifter(2, 0, NsaConsts);
	std::array<std::string, 8>  Ashift13 = Bitshifter(13, 0, NsaConsts);
	std::array<std::string, 8>  Ashift22 = Bitshifter(22, 0, NsaConsts);
	//A summed
	std::array<std::string, 8> Asum = Bitmod(Ashift2, Ashift13, Ashift22);

	//row E shifted
	std::array<std::string, 8>  Eshift6 = Bitshifter(6, 4, NsaConsts);
	std::array<std::string, 8>  Eshift11 = Bitshifter(11, 4, NsaConsts);
	std::array<std::string, 8>  Eshift25 = Bitshifter(25, 4, NsaConsts);
	//E summed
	std::array<std::string, 8> Esum = Bitmod(Eshift6, Eshift11, Eshift25);

	//Choosing
	std::array<std::string, 8> ch = Choosing(NsaConsts, 4, 5, 6);*/

};
	
int main()
{
	
	char i;
	std::cout << "Ready to start? [y/n] (psst type y or n)" << std::endl;
	std::cin >> i;
	if (i == 'p') {
		std::string arr[4] = { 
			{ "butt" },
			{ "ch!c" },
			{ "bur!" },
			{ "$ky!" }
			
		};
		srand(time(NULL));
		std::vector<char> a = { 'b','u','t','t' };
		std::vector<char> b = { 'c','h','!','c' };
		std::vector<char> c = { 'b','u','r','!' };
		std::vector<char> d = { '$','k','y', '!' };
		
		char aa[4];
		char bb[4];
		char cc[4];
		char dd[4];
		



		std::rotate(a.begin(), a.begin() + 2, a.end());
		std::rotate(b.begin(), b.begin() + 2, b.end());
		std::rotate(c.begin(), c.begin() + 2, c.end());
		std::rotate(d.begin(), d.begin() + 2, d.end());
		
		for (int i = 0; i < 4; i++) {
			aa[i] = a[i];
			bb[i] = b[i];
			cc[i] = c[i];
			dd[i] = d[i];
		}
		
		int num = rand() % 3 + 1;
		std::vector<char> f;
		f.reserve(sizeof(char) * 4);
		f.resize(4);
		std::string F;
		std::string out;
		std::cout << "\nIn this bash, cows have " << num << " leg(s)!" << " Enter any character to exit" << std::endl;
		
		
		std::cin >> F;
		for (int i = 0; i < 4; i++) {
			f[i] += F[i];
		}
		std::rotate(f.begin(), f.begin() + 2, f.end());
		
		for (int i = 0; i < 4; i++) {
			out += f[i];
		}

		if (out == arr[num]) {
			std::cout << "/n //////////You are the chosen one!" << std::endl;
		}

	}
	else if (i == 'y') {
		std::cout << "If you have a cpu greater than 1 core then you will benefit from this program, otherwise it will probably be slower\n\n" << std::endl;
		Sleep(1000);

		clock_t tStart = clock();


		//Opencl();
		Dehasher().solver();
		double t = (double)(clock() - tStart) / CLOCKS_PER_SEC;
		printf("Time taken with ASYNC: %.2fs\n", t);
		double hashesper5 = (5 * 60) / t;

		std::cout << "That's theoretically " << hashesper5 << "hashes every 5 minutes!" << std::endl;

		std::cout << std::endl;

		tStart = clock();

		Dehasher().solver1();

		t = (double)(clock() - tStart) / CLOCKS_PER_SEC;
		printf("Time taken without multithreading: %.2fs\n", t);
		hashesper5 = (5 * 60) / t;
		std::cout << "That's theoretically " << hashesper5 << "hashes every 5 minutes!" << std::endl;

		std::cout << std::endl;

		tStart = clock();

		Dehasher().solver3();

		t = (double)(clock() - tStart) / CLOCKS_PER_SEC;
		printf("Time taken with normal multithreading: %.2fs\n", t);
		hashesper5 = (5 * 60) / t;
		std::cout << "That's theoretically " << hashesper5 << "hashes every 5 minutes!" << std::endl;
		char var;
		std::cout << "\nwould you like to see a visual representation? [y/n]";
		std::cin >> var;
		if (var == 'y') {
			Dehasher().solverShow();
		}
		else {
			std::cout << "Goodbye!";
		}
	}
	else {
		std::cout << "Goodbye!\n" << std::endl;
	}

	return 0;
}



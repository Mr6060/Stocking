
#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <utility>
#include <algorithm>
#include <chrono>
#include <thread>

std::vector<std::string> desc;
int i;
std::vector<int> code;
std::vector<int> n;
bool flagFirstInsert;
std::ofstream writeToFlagFirstInsert, writeToCode, writeToDesc, writeToN;
std::ifstream readFromFlagFirstInsert, readFromCode, readFromDesc, readFromN;
std::string txtToWrite = " ";
std::string txtFromFile = " ";

template <typename Ty>
void cus_emplace(std::vector<Ty>& v, std::string&& str) {//This function  replaces a space to an underscore
	static_assert(std::is_same<Ty, std::string>(), "Error, not a string vector");
	for (auto& each : str)
		if (each == ' ')
			each = '_';
	v.push_back(std::forward<std::string>(str));
}

void cus_reemplace(std::vector<std::string>& v, std::string&& str) {//this function replaces an underscore to a space
	for (auto& each : str)
		if (each == '_')
			each = ' ';
	v.emplace_back(str);
}

void printDesc(const std::vector<std::string>& v) {
	if (v.empty())
		return (void)(std::cout << "[]");
	
	for (auto it = v.begin(); it != v.end(); ++it) {
		std::cout << "Code: " << code[std::distance(v.begin(), it)] << "\t\tDesctiption: ";
		
		std::string temp { it->begin(), it->end() };
		std::replace(temp.begin(), temp.end(), '_', ' ');
		if (it == v.end() - 1)
			std::cout << temp;
		else {
			std::cout << temp << " ";
		}
		
		temp.clear();   
		std::cout << "\t\tAmount: " << n[std::distance(v.begin(), it)] << "\t\t\n";
	}
	
	std::cout<<std::endl;
}


void firstInsert() {
	int temp, codeTemp;
	std::cout << "Welcome, this is the first insertion of the products, only alavailable once\n";
	std::cout << "Insert code = 0 to end\n";
	i = 0;
	writeToCode.open("code.txt", std::ios_base::out);
	do {
		static std::string emplaceString {};
		do {
			
			std::cout << "Insert code: ";
			std::cin >> temp;
			if (temp == 0)
				break;
		} while (std::find(code.begin(), code.end(), temp) != code.end());
		code.emplace_back(temp);
		if (temp == 0)
			break;
		std::cout << "Insert desctiption: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, emplaceString);
		cus_emplace(desc, std::move(emplaceString));
		std::cout << "Insert amount: ";
		std::cin >> n.emplace_back();
		i++;
		
		if (writeToCode.is_open()) {
			temp = code.back();
			writeToCode << temp << "\n";
		}

	} while (i > 0);
	writeToCode.close();
	flagFirstInsert = true;
	writeToFlagFirstInsert.open("flagFirstInsert.txt", std::ios_base::out | std::ios_base::trunc);
	if (writeToFlagFirstInsert.is_open()) {
		writeToFlagFirstInsert << 1;
	}
	
}

void loadFlagFirstInsert() {
	readFromFlagFirstInsert.open("flagFirstInsert.txt", std::ios_base::app);
	if (readFromFlagFirstInsert.is_open()) {
		readFromFlagFirstInsert >> flagFirstInsert;
	}
}

int main()
{
	int chooseOperation;
	//loadFlagFirstInsert();
	do {
		system("CLS");
		std::cout << "Welcome to this stock managing program!\n";
		std::cout << "Please, choose one of these operations:\n";
		if (flagFirstInsert == 0) {
			std::cout << "1.\tFirst Insertion (available only once)\n";
		} else {
			std::cout << "First Insertion Not Available\n";
		}
		std::cout << "2.\tDisplay all items in stock\n";
		std::cout << "10.\tEnd execution" << std::endl;
		std::cin >> chooseOperation;
		system("CLS");
		switch (chooseOperation) {
			case 1:
				if (flagFirstInsert == 0) {
					firstInsert();
					
				} else {
					std::cout << "This option isn't available." << std::endl;
					std::this_thread::sleep_for(std::chrono::seconds(3));
					
				}
				break;
			case 2:
				printDesc(desc);
				system("PAUSE");
				
				break;
		}
	} while (chooseOperation != 10);
	
	
	std::cout << std::endl;
	system("PAUSE");
	return 0;
}


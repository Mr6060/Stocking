
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
#include <conio.h>
using namespace std::literals::chrono_literals;

std::vector<std::string> desc;
int i;
std::vector<int> code;
std::vector<int> n;
bool flagFirstInsert;
std::ofstream writeToFlagFirstInsert, writeToCode, writeToDesc, writeToN;
std::ifstream readFromFlagFirstInsert, readFromCode, readFromDesc, readFromN;

template <typename Ty>
void cus_emplace(std::vector<Ty>& v, std::string&& str) {//This function  replaces a space to an underscore
	static_assert(std::is_same<Ty, std::string>(), "Error, not a string vector");
	for (auto& each : str)
		if (each == ' ')
			each = '_';
	v.push_back(std::forward<std::string>(str));
}

std::string emplace(std::string a) {
	for (auto& each : a)
		if (each == ' ')
			each = '_';
	return(a);
}

void unloadVectors();

void cus_reemplace(std::vector<std::string>& v, std::string&& str) {//this function replaces an underscore to a space
	for (auto& each : str)
		if (each == '_')
			each = ' ';
	v.emplace_back(str);
}

void printDesc(const std::vector<int>& v, const std::vector<std::string>& v2) {
	if (v.empty())
		return (void)(std::cout << "[]\n");
	for (auto it = v2.begin(); it != v2.end(); ++it) {
		std::cout << "Code: " << code[std::distance(v2.begin(), it)] << "\t\tDesctiption: ";
		
		std::string temp { it->begin(), it->end() };
		std::replace(temp.begin(), temp.end(), '_', ' ');
		if (it == v2.end() - 1)
			std::cout << temp;
		else {
			std::cout << temp << " ";
		}
		
		temp.clear();   
		std::cout << "\t\tAmount: " << n[std::distance(v2.begin(), it)] << "\t\t\n";
	}
	
	std::cout<<std::endl;
}


void firstInsert() {
	int temp, codeTemp;
	std::cout << "Welcome, this is the first insertion of the products, only alavailable once\n";
	std::cout << "Insert code = 0 to end\n";
	i = 0;
	do {
		static std::string emplaceString {};
		std::cout << "Insert code: ";
		std::cin >> temp;
		while (std::find(code.begin(), code.end(), temp) != code.end()) {
			std::cout << "code already present, please insert a new code: ";
			std::cin >> temp;
		}
		if (temp == 0)
			break;
		code.emplace_back(temp);
		std::cout << "Insert desctiption: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, emplaceString);
		cus_emplace(desc, std::move(emplaceString));
		std::cout << "Insert amount: ";
		std::cin >> n.emplace_back();
		i++;
	} while (i > 0);
	flagFirstInsert = true;
	writeToFlagFirstInsert.open("flagFirstInsert.txt", std::ios_base::out | std::ios_base::trunc);
	if (writeToFlagFirstInsert.is_open()) {
		writeToFlagFirstInsert << 1;
	}
	writeToFlagFirstInsert.close();
}

void loadVectors() {
	std::string tempCode, tempDesc, tempN;
	readFromCode.open("code.txt", std::ios_base::in);
	readFromDesc.open("desc.txt", std::ios_base::in);
	readFromN.open("amount.txt", std::ios_base::in);
	if (readFromCode.is_open()) {
		while (readFromCode.good()) {
			getline(readFromCode, tempCode);
			if(tempCode != "")
				code.emplace_back() = std::atoi(tempCode.c_str());
		}
	}
	if (readFromDesc.is_open()) {
		while (readFromDesc.good()) {
			getline(readFromDesc, tempDesc);
			if (tempDesc != "")
				desc.emplace_back() = tempDesc;
		}
	}
	if (readFromN.is_open()) {
		while (readFromN.good()) {
			getline(readFromN, tempN);
			if (tempN != "")
				n.emplace_back() = std::atoi(tempN.c_str());
		}
	}
	readFromCode.close();
	readFromDesc.close();
	readFromN.close();
}

/*void unloadVectors() {
	std::string a;
	writeToCode.open("code.txt", std::ios_base::out | std::ios_base::trunc);
	writeToDesc.open("desc.txt", std::ios_base::out | std::ios_base::trunc);
	writeToN.open("amount.txt", std::ios_base::out | std::ios_base::trunc);
	
	if (writeToCode.is_open()) {
		for (const auto& each : code) {
			writeToCode << each << "\n";
		}
		for (const auto& each : desc) {
			writeToDesc << each << "\n";
		}
		for (const auto& each : n) {
			writeToN << each << "\n";
		}

	}
	
	writeToCode.close();
	writeToCode.close();
	writeToN.close();
}*/

void loadFlagFirstInsert() {
	readFromFlagFirstInsert.open("flagFirstInsert.txt", std::ios_base::app);
	if (readFromFlagFirstInsert.is_open()) {
		readFromFlagFirstInsert >> flagFirstInsert;
	}
	readFromFlagFirstInsert.close();
}

void searchProduct() {  
	int tempCode, posCode;
	std::cout << "Insert code to search the product: ";
	std::cin >> tempCode;
	auto it = std::find(code.begin(), code.end(), tempCode);
	if (it == code.end()) {
		std::cout << "Codice non trovato\n";
		return;
	}
	posCode = std::distance(code.begin(), it);
	std::cout << "Code: " << tempCode << "\t\tDescription: " << desc[posCode] << "\t\t\tAmount: " << n[posCode] << std::endl;
}

void newProduct() {
	int temp, codeTemp, nTemp;
	std::cout << "Product insertion\nInsert code=0 to end\n";
	do {
		static std::string emplaceString {};
		std::cout << "Insert code: ";
		std::cin >> temp;
		while (std::find(code.begin(), code.end(), temp) != code.end()) {
			std::cout << "code already present, please insert a new code: ";
			std::cin >> temp;
		}
		if (temp == 0)
			break;
		code.emplace_back(temp);
		std::cout << "Insert desctiption: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, emplaceString);
		cus_emplace(desc, std::move(emplaceString));
		std::cout << "Insert amount: ";
		std::cin >> n.emplace_back();
		i++;
	} while (i > 0);
	printDesc(code, desc);
}

void modDesc() {
	int tempCode, posCode;
	std::string tempDesc, stringa;
	std::cout << "Insert code: ";
	std::cin >> tempCode;
	while (std::find(code.begin(), code.end(), tempCode) == code.end()) {
		std::cout << "Code not found, insert code: ";
		std::cin >> tempCode;
	}
	if (auto it = std::find(code.begin(), code.end(), tempCode); it != code.end()) {
		auto pos = std::distance(code.begin(), it);
		std::cout << "Insert the new description: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, tempDesc);
		desc[pos] = emplace(tempDesc);
	}

}

void modN() {
	int tempCode, newAmount;
	std::cout << "Insert code: ";
	std::cin >> tempCode;
	while (std::find(code.begin(), code.end(), tempCode) == code.end()) {
		std::cout << "Code not found, insert code: ";
		std::cin >> tempCode;
	}
	if (auto it = std::find(code.begin(), code.end(), tempCode); it != code.end()) {
		auto pos = std::distance(code.begin(), it);
		std::cout << "Insert the new amount: ";
		std::cin >> newAmount;
		n[pos] = newAmount;
	}
	
}

void modProduct() {
	int choose;
	do {
		system("CLS");
		std::cout << "In this section you can modify your products.\nPlease select the operation you would like to modify\n";
		std::cout << "1.\tModify description\n";
		std::cout << "2.\tModifiy amount\n";//later - use library to get user input key like '+' or '-' to increase or decrease amount
		std::cout << "10.\tReturn to main menu\n";
		std::cin >> choose;
		system("CLS");
		switch (choose) {
			case 1:
				modDesc();
				break;
			case 2:
				modN();
				break;
			case 3:
				break;
			case 10:
				unloadVectors();
				std::cout << "Saving changes\n";
				std::this_thread::sleep_for(2s);
				break;
		}
	

	} while (choose!=10);
}

void deleteProduct() {
	int tempCode = 0, posCode = 0;
	std::string tempDesc, stringa, yn;
	std::cout << "Insert code: ";
	std::cin >> tempCode;
	//while (std::find(code.begin(), code.end(), tempCode) == code.end()) {
		auto it = std::find(code.begin(), code.end(), tempCode);
		if (it == code.end()) {
			std::cout << "Codice non trovato\n";
			return;
		}
		posCode = std::distance(code.begin(), it);
		
	//}
	std::cout << "Are you sure you want to delete this product? Not reversible. (Y/n)\n";
	do {
		std::cin >> yn;
		if (yn == "y") {
			code.erase(code.begin() + posCode);
			desc.erase(desc.begin() + posCode);
			n.erase(n.begin() + posCode);
			
			std::cout << "Elimination succeded" << std::endl;
			std::this_thread::sleep_for(2s);
			break;
		} else
			if (yn == "n") {
				std::cout << "Elimination cancelled" << std::endl;
				break;
			} else {
				std::cout << "Please insert Yes (y) or Not (n)\n";
			}
	} while ((yn == "y") or (yn == "n"));
	unloadVectors();
}

void unloadVectors() {
	writeToCode.open("code.txt", std::ios_base::out | std::ios_base::trunc);
	writeToDesc.open("desc.txt", std::ios_base::out | std::ios_base::trunc);
	writeToN.open("amount.txt", std::ios_base::out | std::ios_base::trunc);


	for (int i = 0; i < code.size() -1 ; i++) {
		for (int j = i+1; j < code.size(); j++) {
			if (desc[i] > desc[j]) {
				std::swap(code[i], code[j]);
				std::swap(desc[i], desc[j]);
				std::swap(n[i], n[j]);
			}
		}
	}


	if (writeToCode.is_open()) {
		for (const auto& each : code) {
			writeToCode << each << "\n";
		}
		for (const auto& each : desc) {
			writeToDesc << each << "\n";
		}
		for (const auto& each : n) {
			writeToN << each << "\n";
		}

	}

	writeToCode.close();
	writeToCode.close();
	writeToN.close();
}

int main()
{
	int chooseOperation;
	loadFlagFirstInsert();
	loadVectors();
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
		std::cout << "3.\tSearch a product (by code)\n";
		std::cout << "4.\tInsert new product\n";
		std::cout << "5.\tModify products\n";
		std::cout << "6.\tDelete product\n";
		std::cout << "10.\tEnd execution" << std::endl;
		std::cin >> chooseOperation;
		system("CLS");
		switch (chooseOperation) {
			case 1:
				if (flagFirstInsert == 0) {
					firstInsert();
					
				} else {
					std::cout << "This option isn't available." << std::endl;
					std::this_thread::sleep_for(2s);
					
				}
				break;
			case 2:
				printDesc(code, desc);
				system("PAUSE");
				
				break;
			case 3:
				searchProduct();
				system("PAUSE");
				break;
			case 4:
				if (flagFirstInsert == 1){
					newProduct();
				}
				else
					std::cout << "Option is not available, you must do option #1 first." << std::endl;
				break;
			case 5:
				modProduct();
				break;
			case 6:
				deleteProduct();
				break;
			case 10:
				unloadVectors();
				std::cout << "Saving and exiting\n";
				std::this_thread::sleep_for(2s);
				break;
		}
	} while (chooseOperation != 10);
	std::cout << std::endl;
	system("PAUSE");
	return 0;
}


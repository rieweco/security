//fillUsers.cpp
//
//
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <openssl/md5.h>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <cmath>

#define SIZE 100
#define USERNAMESIZE 20
#define PASSWORDSIZE 3

using namespace std;

int main( int argc, char *argv[]) {
	
	//variables
	string lengthOfPassword = "";
	string numberOfUsers = "";
	int passwordLength = 0;
	int userLength = 0;
	
	srand((int)time(0));
	//create salt
	string salt;
	stringstream saltstream;
	for(int i = 0; i < 4; i++) {
		int newDigit = (rand() % 10);
		saltstream << newDigit;
	}
	salt = saltstream.str();	
	
	//populate password length and # of users from cmd line args
	if( argc != 3) 
		cout << "must enter length of pw followed by # of users! " << endl;
	else {
		lengthOfPassword = argv[1];
		numberOfUsers = argv[2];

		istringstream (lengthOfPassword) >> passwordLength;
		cout << passwordLength << endl;
		istringstream (numberOfUsers) >> userLength;
		cout << userLength << endl;

	}

	//set up usernames
	string base = "username";
	string userNameArray[userLength];
	string numberArray[userLength];

	for(int i = 0; i < userLength; i++) {
		stringstream ss;
		ss << setw(3) << setfill('0') << i;
		string number;
		ss >> number;
		numberArray[i] = number;
		cout << numberArray[i] << endl;	
	}

	for(int i = 0; i < userLength; i++) {
		userNameArray[i] = base + numberArray[i];
		cout << userNameArray[i] << endl;
	}

	//create passwords
	string password;
	string passwordArray[userLength];
	int temp = 10;	
	int degree = pow(10, passwordLength);
	for(int i = 0; i < userLength; i++) {
		stringstream ss;
		int newNumber = (rand() % degree);	
		ss << setw(passwordLength) << setfill('0') << newNumber;
		ss >> password;
		passwordArray[i] = password;
		cout << passwordArray[i] << endl;
	}
	

	//create md5 hash
	string md5PasswordArray[userLength];
	string md5PackageArray[userLength];
	unsigned char passwordMD5[USERNAMESIZE];
        char md5String[USERNAMESIZE];
	string password1;
	for( int x = 0; x < userLength; x++) {
		password1 = passwordArray[x];
        	strncpy(md5String, password1.c_str(), sizeof(md5String));
        	md5String[sizeof(md5String) - 1] = 0;

        	MD5((unsigned char*)&md5String, strlen(md5String), (unsigned char*)&passwordMD5);

        	char hashedMD5Password[32];
        	for( int j = 0; j < 16; j++) {
               		sprintf(&hashedMD5Password[j*2], "%02x", (unsigned int)passwordMD5[j]);
        	}
		md5PasswordArray[x] = hashedMD5Password;
       		printf("md5 password: %s\n", hashedMD5Password);	
	}
	
	//create SHA256 hash
	string shaPasswordArray[userLength];
	string shaPackageArray[userLength];
	unsigned char passwordSHA256[USERNAMESIZE];
	char hashedSHA256Password[64];
        char shaString[USERNAMESIZE];
        for( int k = 0; k < userLength; k++) {
		password1 = passwordArray[k];
		strncpy(shaString, password1.c_str(), sizeof(shaString));
        	SHA256((unsigned char*)&shaString, strlen(shaString), (unsigned char*)&passwordSHA256);

        	for( int z = 0; z < 32; z++) {
                	sprintf(&hashedSHA256Password[z*2], "%02x", (unsigned int)passwordSHA256[z]);
        	}
		shaPasswordArray[k] = hashedSHA256Password;
        	printf("sha256 password: %s\n", hashedSHA256Password);
	}

	//create SHA256 + salt hash
	string saltPasswordArray[userLength];
	string saltPackageArray[userLength];
	char saltString[4];
        strncpy(saltString, salt.c_str(), sizeof(saltString));
	cout << saltString << endl;
        char hashedSHAplusSalt[68];
	for( int y = 0; y < userLength; y++) {

	        strncpy(hashedSHAplusSalt, shaPasswordArray[y].c_str(), sizeof(hashedSHAplusSalt));
        	strncat(hashedSHAplusSalt, saltString, sizeof(hashedSHAplusSalt));	

        	unsigned char passwordSHA256salt[USERNAMESIZE];

        	SHA256((unsigned char*)&hashedSHAplusSalt, strlen(hashedSHAplusSalt), (unsigned char*)&passwordSHA256salt);
        	char hashedSHA256saltPassword[68];

        	for( int t = 0; t < 34; t++) {
                	sprintf(&hashedSHA256saltPassword[t*2], "%02x", (unsigned int)passwordSHA256salt[t]);
        	}
		saltPasswordArray[y] = hashedSHA256saltPassword;	
        	printf("sha256 + salt password: %s\n", hashedSHA256saltPassword);	
	}

	//create organized data for files
	string userNameAndPassword;
	string basicPackageArray[userLength];
		
	for(int i = 0; i < userLength; i++) {
		string tempName = userNameArray[i];
		stringstream ss;
		ss << tempName << " ";
		ss << passwordArray[i];
	        userNameAndPassword = ss.str();
		basicPackageArray[i] = userNameAndPassword;
	}
	
	
	for( int i = 0; i < userLength; i++) {
		string tempName = userNameArray[i];
		stringstream ss;
		ss << tempName << " ";
		ss << md5PasswordArray[i];
		userNameAndPassword = ss.str();
		md5PackageArray[i] = userNameAndPassword;
	}
	

	for(int i = 0; i < userLength; i++) {
		string tempName = userNameArray[i];
		stringstream ss;
		ss << tempName << " ";
		ss << shaPasswordArray[i];
		userNameAndPassword = ss.str();
		shaPackageArray[i] = userNameAndPassword;
	}


	for(int i = 0; i < userLength; i++) {
 		string tempName = userNameArray[i];
		stringstream ss;
		ss << tempName << " ";
		ss << saltPasswordArray[i];
		userNameAndPassword = ss.str();
		saltPackageArray[i] = userNameAndPassword;
	}

	//save into password files
	ofstream save;
	save.open("/accounts/students/c/carc35/SS2017/proj1/Security/passwdBasic", ios::app | ios::out);
	for( int i = 0; i < userLength; i++) {
                save << "\n" << basicPackageArray[i];
        }
	save.close();
       	cout << "Username and Password Saved to basic file!" << endl;

        save.open("/accounts/students/c/carc35/SS2017/proj1/Security/passwdmd5", ios::app | ios::out);
        for( int i = 0; i < userLength; i++) {
	        save << "\n" << md5PackageArray[i];	
        }        
	save.close();
        cout << "Username and Password Saved to md5 file!" << endl;

        save.open("/accounts/students/c/carc35/SS2017/proj1/Security/passwdSHA256", ios::app | ios::out);
        for( int i = 0; i < userLength; i++) {       
		save << "\n" << shaPackageArray[i];
	}
	save.close();
        cout << "Username and Password Saved to sha256 file!" << endl;

        save.open("/accounts/students/c/carc35/SS2017/proj1/Security/passwdSHA256salt", ios::app | ios::out);
        for( int i = 0; i < userLength; i++) {
		save << "\n" << saltPackageArray[i];
        }        
	save.close();
        cout << "Username and Password Saved to sha256salt file!" << endl;

	return 0;
}
	

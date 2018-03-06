//crackIt.cpp
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
#include <vector>

#define SIZE 100
#define USERNAMESIZE 20
#define PASSWORDSIZE 3

using namespace std;

//crack function for basic password file
void basicCrack(string array[], int lineNumber) {
	int attempts = 0;
	string guess;
	while(true) {
		for(int i = 0; i < 10; i++) {
			for( int j = 0; j < 10; j++) {
				for(int k = 0; k < 10; k++) {
					attempts++;
					stringstream ss;
					ss << i << j << k;
					ss >> guess;
					for(int a = 1; a < lineNumber; a++) {
							
						if(array[a].compare(guess) == 0) {
							cout << "found password!: " << guess << " at line: " << a << endl;
							cout << "it took " << attempts << " attempts!" << endl;
							ofstream readme;
							readme.open("/accounts/students/c/carc35/SS2017/proj1/README.txt", ios::app | ios::out);
							readme << "\n" << "crack on passwdBasic file";	
							readme << "\n" << "found password: " << guess << " at line: " << a;
							readme << "\n" << "it took: " << attempts << " attempts!";
							readme << "\n" << "----------------------------- ";
							readme.close();
							return;
						}
					}
				}
			}
		}
	}							
}

//crack function for md5 password file
void md5Crack(string array[], int lineNumber){
	int attempts = 0;
        string guess;
        while(true) {
                for(int i = 0; i < 10; i++) {
                        for( int j = 0; j < 10; j++) {
                                for(int k = 0; k < 10; k++) {
                                        attempts++;
                                        stringstream ss;
                                        ss << i << j << k;
                                        ss >> guess;
                                        for(int a = 1; a < lineNumber; a++) {
						attempts++;
						//copied md5 code from security.cpp
						unsigned char passwordMD5[USERNAMESIZE];
                				char md5String[USERNAMESIZE] ;
                				strncpy(md5String, guess.c_str(), sizeof(md5String));
                				md5String[sizeof(md5String) - 1] = 0;

                				MD5((unsigned char*)&md5String, strlen(md5String), (unsigned char*)&passwordMD5);

                				char hashedMD5Password[40];
                				for( int i = 0; i < 20; i++) {
                        				sprintf(&hashedMD5Password[i*2], "%02x", (unsigned int)passwordMD5[i]);
							if(array[a].compare(hashedMD5Password) == 0) {
                                                                cout << "found password!: " << hashedMD5Password << " at line: " << a << endl;
                                                                cout << "it took " << attempts << " attempts!" << endl;
								ofstream readme;
                                                        	readme.open("/accounts/students/c/carc35/SS2017/proj1/README.txt", ios::app | ios::out);
                                                        	readme << "\n" << "crack on passwdmd5 file";
                                                        	readme << "\n" << "found password: " << guess << " at line: " << a;
                                                        	readme << "\n" << "it took: " << attempts << " attempts!";
                                                        	readme << "\n" << "----------------------------- ";
                                                      	  	readme.close();
                                                                return;
                                                        }
						}
					}
				}
			}

                }
	}

}

//crack function for sha256 password file
void shaCrack(string array[], int lineNumber) {
	int attempts = 0;
	string guess;
	while(true) {
		for(int i = 0; i < 10; i++) {
                        for( int j = 0; j < 10; j++) {
                                for(int k = 0; k < 10; k++) {
                                        attempts++;
                                        stringstream ss;
                                        ss << i << j << k;
                                        ss >> guess;
                                        for(int a = 1; a < lineNumber; a++) {
						attempts++;
						//copied sha256 code from security.cpp
						unsigned char passwordSHA256[USERNAMESIZE];
               					char shaString[USERNAMESIZE];
                				strncpy(shaString, guess.c_str(), sizeof(shaString));
						cout << "sha string: " << shaString << endl;
                				SHA256((unsigned char*)&shaString, strlen(shaString), (unsigned char*)&passwordSHA256);
						
                				char hashedSHA256Password[64];
                				for( int i = 0; i < 32; i++) {
							attempts++;
                        				sprintf(&hashedSHA256Password[i*2], "%02x", (unsigned int)passwordSHA256[i]);
							
							if(array[a].compare(hashedSHA256Password) == 0) {
                                                		cout << "found password!: " << hashedSHA256Password << " at line: " << a << endl;
                                                		cout << "it took " << attempts << " attempts!" << endl;
								ofstream readme;
                                                        	readme.open("/accounts/students/c/carc35/SS2017/proj1/README.txt", ios::app | ios::out);
                                                        	readme << "\n" << "crack on passwdSHA256 file";
                                                        	readme << "\n" << "found password: " << guess << " at line: " << a;
                                                        	readme << "\n" << "it took: " << attempts << " attempts!";
                                                        	readme << "\n" << "----------------------------- ";
                                                        	readme.close();
                                                		return;
							}
                				} 
                                        }
                                }
                        }
                }
        }

}

//crack for sha256 + salt hash password file
void saltCrack(string array[], int lineNumber) {
        int attempts = 0;
        string guess;
	string saltString;
        while(true) {
                for(int i = 0; i < 10; i++) {
                        for( int j = 0; j < 10; j++) {
                                for(int k = 0; k < 10; k++) {
                                        attempts++;
					stringstream ss;
					ss << i << j << k;
                                        ss >> guess;
					cout << guess << endl;
                                        for(int a = 1; a < lineNumber; a++) {
						attempts++;
                                     		unsigned char passwordSHA256[USERNAMESIZE];
                                                char shaString[USERNAMESIZE];
                                                strncpy(shaString, guess.c_str(), sizeof(shaString));
						cout << "shaString: " << shaString << endl;

                                                SHA256((unsigned char*)&shaString, strlen(shaString), (unsigned char*)&passwordSHA256);
						
                                                char hashedSHA256Password[64];
                                                for( int i = 0; i < 32; i++) {
                                                        sprintf(&hashedSHA256Password[i*2], "%02x", (unsigned int)passwordSHA256[i]);
							
							for(int q = 0; q < 10; q++) {
                        					for( int w = 0; w < 10; w++) {
                                					for(int e = 0; e < 10; e++) {
										for(int r = 0; r < 10; r++) {
											attempts++;
											stringstream stream;
											stream << q << w << e << r;
											stream >> saltString;
											cout << saltString << endl;	

                									char hashedSHAplusSalt[68];
                									strncpy(hashedSHAplusSalt, hashedSHA256Password, sizeof(hashedSHAplusSalt));
                									strncat(hashedSHAplusSalt, saltString.c_str(), sizeof(hashedSHAplusSalt));                
                									unsigned char passwordSHA256salt[USERNAMESIZE];

                									SHA256((unsigned char*)&hashedSHAplusSalt, strlen(hashedSHAplusSalt), (unsigned char*)&passwordSHA256salt);
                									char hashedSHA256saltPassword[68];

                									for( int i = 0; i < 34; i++) {
                        									sprintf(&hashedSHA256saltPassword[i*2], "%02x", (unsigned int)passwordSHA256salt[i]);	
												if(array[a].compare(hashedSHA256saltPassword) == 0) {
                                                                					cout << "found password!: " << hashedSHA256saltPassword << " at line: " << a << endl;
                                                               	 					cout << "it took " << attempts << " attempts!" << endl;
													ofstream readme;
                                                        						readme.open("/accounts/students/c/carc35/SS2017/proj1/README.txt", ios::app | ios::out);
                                                        						readme << "\n" << "crack on passwdSHA256salt file";
                                                        						readme << "\n" << "found password: " << guess << " at line: " << a;
                                                        						readme << "\n" << "it took: " << attempts << " attempts!";
                                                        						readme << "\n" << "----------------------------- ";
                                                        						readme.close();
                                                                					return;
												}
											}
											
										}
									}
								}
							}
                				}
					}
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	
	//variables
	string lengthOfPassword = "";
	string passwordType = "";
	int passwordLength = 0;
	int basicCount = 0;
	int md5Count = 0;
	int shaCount = 0;
	int saltCount = 0;	

	if( argc !=3)
		cout << "must enter length of pw and password file name! " << endl;
	else {
		lengthOfPassword = argv[1];
		passwordType = argv[2];
		
		istringstream(lengthOfPassword) >> passwordLength;
		cout << "password length: " << passwordLength << endl;
		cout << "password type: " << passwordType << endl;
	}

	//open target file
	string fileArray[100];
	string line1 = "";
	string line2 = "";
	string username = "";
	string fileName = "";
	stringstream ss;
	ss << "/accounts/students/c/carc35/SS2017/proj1/Security/";
	ss << passwordType;
	fileName = ss.str();
	ifstream file;
	string fileLine;
	file.open(fileName.c_str(), ios::app | ios::out);
	
	int lineNumber = 0;
	
	//save passwords from file into array
	while(getline(file, fileLine)) {
		istringstream iss(fileLine);
		iss >> line1 >> line2;
		fileArray[lineNumber] = line2;
		lineNumber++;
	}
	
	file.close();	
 	
	int importedPasswordLength = fileArray[1].length();
	cout << "password length from imported file: " << importedPasswordLength << endl;


	
	//process cracking function to find password match
	if(passwordType == "passwdBasic") {
		basicCrack(fileArray, lineNumber);
	} else if(passwordType == "passwdSHA256") {
		shaCrack(fileArray, lineNumber);
	} else if(passwordType == "passwdmd5") { 
		md5Crack(fileArray, lineNumber);
	} else if(passwordType == "passwdSHA256salt") {
		saltCrack(fileArray, lineNumber);
	}


	return 0;
}


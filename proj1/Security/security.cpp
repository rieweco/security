//Cody Riewerts
//SS2017
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


#define SIZE 100
#define USERNAMESIZE 20
#define PASSWORDSIZE 3

using namespace std;

int main() {
	
	//variables
	int loginOption;
	bool validChoice = false;
	bool passwordsMatch = false;
	string userName = "";
	string password1 = "";
	string password2 = "";
	

	//create random seed and generate salt
	srand((int)time(0));
	string salt;
	stringstream stream;
	for(int i = 0; i < 4; i++) {
		int newDigit = (rand() % 10);
		stream << newDigit;
	}
	salt = stream.str();

	
	//introduction
	while (!validChoice) {
	
		cout << "Hello! Welcome to Cody's Security System!" << endl;
		cout << "What would you like to do?: " << endl;
		cout << "1) Create an account"<< endl;
		cout << "2) Authenticate my account" << endl;
	
		cin >> loginOption;
		
		if((loginOption == 1) |( loginOption == 2)) {
			validChoice = true;
		}
	}  
	

		
	
	//create user ( option 1)
	if(loginOption == 1) {
		cout << "you chose option 1!"<< endl;
		cout << "Create a username!" << endl; 
		cout << "username: " << endl;
		cin >> userName;
		
		cout << "Thank you " << userName << "!" << endl;
	
		//password creation
		while ( !passwordsMatch) {
		
			
			//test password for numbers only
			bool onlyNumbers = false;
			while ( !onlyNumbers) {
			
				cout << "Please create a password: ";
				cin >> password1;
				
				for(int i = 0; (i< password1.length() - 1); i++) {
					if( !isdigit(password1[i])) {
						cout << "Password can ONLY be numbers!" << endl;
						break;
					}
				onlyNumbers = true;
				}
			}	
		

			//test confirmation password for numbers only
			onlyNumbers = false;
			while( !onlyNumbers) {
				cout << "Confirm password: ";			
				cin >> password2;
				
				for( int i = 0; (i < password2.length() - 1); i++) {
					if( !isdigit(password2[i])) {
						cout << "Confirmation password can ONLY be numbers!" << endl;
						break;
					}
				onlyNumbers = true;
				}
			}	
			
	
			//compare passwords to make sure they match
			if(password1 == password2) {
				cout << "passwords match!"<< endl;;
				passwordsMatch = true;
				break;
			} else { 
				cout << "passwords are different" << endl;
			}
		}
		
		//create hd5 hash ** created based on askyb tutorial
		unsigned char passwordMD5[USERNAMESIZE];
                char md5String[USERNAMESIZE] ;
                strncpy(md5String, password1.c_str(), sizeof(md5String));
                md5String[sizeof(md5String) - 1] = 0;

                MD5((unsigned char*)&md5String, strlen(md5String), (unsigned char*)&passwordMD5);

                char hashedMD5Password[40];
                for( int i = 0; i < 20; i++) {
                        sprintf(&hashedMD5Password[i*2], "%02x", (unsigned int)passwordMD5[i]);
                }

                printf("md5 password: %s\n", hashedMD5Password);


		//create SHA256 hash ** created based on askyb tutorial
		unsigned char passwordSHA256[USERNAMESIZE];
		char shaString[USERNAMESIZE];
		strncpy(shaString, password1.c_str(), sizeof(shaString));
		
		SHA256((unsigned char*)&shaString, strlen(shaString), (unsigned char*)&passwordSHA256);
		
		char hashedSHA256Password[70];
		for( int i = 0; i < 35; i++) {
			sprintf(&hashedSHA256Password[i*2], "%02x", (unsigned int)passwordSHA256[i]);
		}
		
		printf("sha256 password: %s\n", hashedSHA256Password);
	
		
		//create SHA256 + salt hash
		char saltString[4];
		strncpy(saltString, salt.c_str(), sizeof(saltString));
		
		char hashedSHAplusSalt[74];
		strncpy(hashedSHAplusSalt, hashedSHA256Password, sizeof(hashedSHAplusSalt));
		strncat(hashedSHAplusSalt, saltString, sizeof(hashedSHAplusSalt));		        

		
		unsigned char passwordSHA256salt[USERNAMESIZE];
		
		SHA256((unsigned char*)&hashedSHAplusSalt, strlen(hashedSHAplusSalt), (unsigned char*)&passwordSHA256salt);
		char hashedSHA256saltPassword[74];	

		for( int i = 0; i < 50; i++) {
			sprintf(&hashedSHA256saltPassword[i*2], "%02x", (unsigned int)passwordSHA256salt[i]);
		}
		
		printf("sha256 + salt password: %s\n", hashedSHA256saltPassword);
		
		
		//save into password file
		ofstream save;
		save.open("passwdBasic", ios::app | ios::out);
		save << "\n" << userName << " " << password1;
		save.close();
		cout << "Username and Password Saved to basic file!" << endl;	

		save.open("passwdmd5", ios::app | ios::out);
                save << "\n" << userName << " " << hashedMD5Password;
                save.close();
                cout << "Username and Password Saved to md5 file!" << endl;
		
		save.open("passwdSHA256", ios::app | ios::out);
                save << "\n" << userName << " " << hashedSHA256Password;
                save.close();
                cout << "Username and Password Saved to sha256 file!" << endl;	
		
		save.open("passwdSHA256salt", ios::app | ios::out);
		save << "\n" << userName << "" << hashedSHA256saltPassword;
		save.close();
		cout << "Username and Password Saved to sha256salt file!" << endl;		



	//authenticate user (option 2)
	} 
	if(loginOption == 2) { 
		cout << "you chose option 2!" << endl;

		cout << "what is your username? :";
		cin >> userName;
		
		//read from passwd file
		string fileLine;
		ifstream file;
		
		file.open("passwdBasic");
		if(file.is_open()) {
			unsigned int lineNumber = 0;
			while( getline(file, fileLine)) {
				lineNumber++;
				if(fileLine.find(userName, 0) != string::npos) {
					password1 = fileLine.substr(userName.length() + 1);
					cout << "basic password: " << password1 << endl;
				}
			}	
			file.close();
	
		}
		else cout << "unable to open file" << endl;
		
		//read from md5 file
		file.open("passwdmd5");
	        if(file.is_open()) {
                    	unsigned int lineNumber = 0;
                       	while( getline(file, fileLine)) {
                            	lineNumber++;
                               	if(fileLine.find(userName, 0) != string::npos) { 
                                       	password1 = fileLine.substr(userName.length() + 1);
                                       	cout << "md5 password: " << password1 << endl;
                               	}
                        }
                       	file.close();
             
                }
		else cout << "unable to open file" << endl;
 
		//read from SHA256 file
		file.open("passwdSHA256");
               	if(file.is_open()) {
                       	unsigned int lineNumber = 0;
                       	while( getline(file, fileLine)) {
                               	lineNumber++;
                               	if(fileLine.find(userName, 0) != string::npos) {	
                      			password1 = fileLine.substr(userName.length() + 1); 
                                       	cout << "SHA256 password: " << password1 << endl;
                               	}
                       	}
                       	file.close();
              
                }
		else cout << "unable to open file" << endl;

		//read from SHA256salt
		file.open("passwdSHA256salt");
               	if(file.is_open()) {
                       	unsigned int lineNumber = 0;
                       	while( getline(file, fileLine)) {
                               	lineNumber++;
                               	if(fileLine.find(userName, 0) != string::npos) {
                                       	password1 = fileLine.substr(userName.length() + 1);
                                       	cout << "SHA256 + salt password: " << password1 << endl;
                               	}
                       	}	
                       	file.close();
               
                }


			
		else cout << "unable to open file" << endl;	
		
		
	}
	return 0;
}

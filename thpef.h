#pragma once
#include <cmath>
#include <cctype>
#include <string>
#include <iostream> 
#include <fstream>
#include <random>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

//Structure definitions
struct userData
{
    string firstName;
    string lastName;
    string street;
    string city;
    string state;
    string zip;

    double transaction;
    double balance;
};

//Write prototypes here

void writeLetter( userData user, string temp, string date );

string getDate();

bool openInput( ifstream &datafile, string input );

bool openOutput( ofstream &datafile, string output );

bool getClient( ifstream &input, userData &user );



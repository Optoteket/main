// Master Thesis Project, Spring of 2016 
// Claes Arvidson and Emelie Karlsson
// Applied Mathematics, Mathematical Institution, Linköpings Universitet 

// Main project file
// Created 2016-03-30 by Emelie Karlsson

#include <iostream>
#include <string>

#include "task.h" 

using namespace std;

time_t current_time = time(0);
tm* current_date = localtime(&current_time);

// File names
string log_file_name = "../target/logs/";

int main()
{
  try{
    TaskClass a; 
    return 0;
  } catch (const char* msg){ 
    cerr << msg << endl;
    //log_file << msg << endl;
  }
}

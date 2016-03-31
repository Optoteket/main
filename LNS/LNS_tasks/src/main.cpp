// Master Thesis Project, Spring of 2016 
// Claes Arvidson and Emelie Karlsson
// Applied Mathematics, Mathematical Institution, Linköpings Universitet 

// Main project file
// Created 2016-03-30 by Emelie Karlsson

#include <iostream>
#include <string>
#include <sstream>

#include "stdio.h"
#include "task.h" 

using namespace std;

time_t current_time = time(0);
tm* timedate = localtime(&current_time);
stringstream date;

// File names
string log_file_dir = "../target/logs/";
stringstream log_file_path;

int main()
{
  try{

    // 1. Create logfile
    date << "_" << timedate->tm_year + 1900 << "_" << timedate->tm_mon+1 << "_" << timedate->tm_mday << ":" << timedate->tm_hour << "-" << timedate->tm_min+1 << "-"<< timedate->tm_sec+1;
    log_file_path << log_file_dir << "logfile" << date.str() << ".dat"; 

    FILE* log_file = fopen(log_file_path.str().c_str(), "a");
    fprintf(log_file, date.str().c_str());

    // 2. Create resultfile

    // Create initial solution
    
    // LOOP: Calculate incremented costs
    // All weekends
    // All evening
    // All other tasks according to DEMAND (the highest demand is covered first)

    // Find most expensive tasks

    // Destroy most expensive tasks

    // Repair according to some principle 

    TaskClass a; 
    return 0;

    // Error handling 
  } catch (const char* msg){ 
    cerr << msg << endl;
    fprintf(log_file, msg);
  }
}

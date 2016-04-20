// Master Thesis Project, Spring of 2016 
// Claes Arvidson and Emelie Karlsson
// Applied Mathematics, Mathematical Institution, Linköpings Universitet 

// Main project file
// Created 2016-03-30 by Emelie Karlsson

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>  
#include <cstdlib>


#include "stdio.h"
#include "LibraryClass.h"
#include "Constants.h"

using namespace std;

time_t current_time = time(0);
tm* timedate = localtime(&current_time);
stringstream date;

//File locations
string log_file_dir = "../target/logs/";
string res_file_dir = "../target/results/";
stringstream log_file_path;
stringstream res_file_path;

int myrandom (int i) {return rand()%i;}

int main(int argc, char** argv)
{
  srand (unsigned (time(0)));
  //1. Create logfile
  date << timedate->tm_year + 1900 << "_" << timedate->tm_mon+1 << "_" << timedate->tm_mday << ":" << timedate->tm_hour << ":" << timedate->tm_min+1 << ":"<< timedate->tm_sec+1;
  log_file_path << log_file_dir << "logfile" << ".dat"; 

  ofstream log_file (log_file_path.str().c_str());
  if (log_file.is_open())
  {
    log_file << date.str().c_str() << endl;;
    log_file << "The logs are:" << endl;
    log_file.close();
  }
  else cout << "Unable to open file";

  freopen(log_file_path.str().c_str(), "a", stderr);

  //Create result file
  res_file_path << res_file_dir << "resfile" << ".dat"; 
  ofstream res_file (res_file_path.str().c_str());
  
  if(res_file.is_open())
  {
    res_file << date.str().c_str() << endl;
    res_file << "The results are:" << endl;
  }

  try{
    //2. Create library
    Library library {&res_file};
    
    //3. Create initial solution
    library.create_initial_solution();
    
    //Write results to resfile
    library.write_results();

    //4. Destroy and repair weekends
    /*****************************************/
    
    // library.fn_destroy_repair("weekend", 10);
    
    // library.fn_destroy_repair("tasks", 10);

    /*****************************************/

    //library.print_workers();

    // 2. Create resultfile
    // Open txt files. Read lines and put into classes/structs
    // Create initial solution
    
    // LOOP: Calculate incremented costs
    // All weekends
    // All evening
    // All other tasks according to DEMAND (the highest demand is covered first)

    // Find most expensive tasks

    // Destroy most expensive tasks

    // Repair according to some principle 

    return 0;

    // Error handling 
  } catch (const char* msg){ 
    cerr << msg << endl;
    //fprintf(log_file, msg);
  }
}

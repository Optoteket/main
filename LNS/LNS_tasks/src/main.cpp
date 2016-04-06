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


#include "stdio.h"
#include "task.h" 
#include "LibraryClass.h"
#include "WorkerClass.h"

using namespace std;

time_t current_time = time(0);
tm* timedate = localtime(&current_time);
stringstream date;

// File names
string log_file_dir = "../target/logs/";
stringstream log_file_path;


int main()
{
  //1. Create logfile
  date << "_" << timedate->tm_year + 1900 << "_" << timedate->tm_mon+1 << "_" << timedate->tm_mday << ":" << timedate->tm_hour << "-" << timedate->tm_min+1 << "-"<< timedate->tm_sec+1;
  log_file_path << log_file_dir << "logfile" << date.str() << ".dat"; 

  ofstream log_file (log_file_path.str().c_str());
  if (log_file.is_open())
  {
    log_file << date.str().c_str() << "\n";
    log_file << "This is another line.\n";
    log_file.close();
  }
  else cout << "Unable to open file";

  try{
    //2. Create library
    Library library;
    library.read_demand();
    library.print_demand();

    //3. Create workers
    ifstream worker_file ("../src/data/workers5W.txt");
    
    if (worker_file.fail())
    {
      cout << "Error: Could not read worker file" << endl;
    }

    vector<string> input_vector;
    string input;
    // int line_count = 0;
    // string worker_position;
    // int worker_ID;
    // string worker_name;
    // string worker_department;
    // string worker_weekend;
    // string worker_boss;
    // string worker_PL_type;
    // string worker_HB_type;
    // string worker_freeday;
    //int worker_avail_day;
    //int worker_avail

    while(getline(worker_file, input) && !input.empty()){

      // if(input_vector.size()== 152){
      // 	string blank_line = input_vector[151];
      // 	cout << "Blank line:" << endl;
      // 	cout << blank_line << endl;
      // 	cout << "End of blank line" << " Size:" << blank_line.size() << endl;

      // 	if (blank_line.empty()){
      // 	  cout << "Blank line empty" << endl;
      // 	}
      // 	else if (blank_line.compare("") != 0) cout << "2 spaces" << endl;
      // 	//else if (blank_line.c_str() == '\t') cout << "Tab" << endl;
      // }
      
      //Create a new worker when all data has been read 
      if(input.size()<2){
	for (int i=0; i < input_vector.size(); i++){
	  cout << input_vector[i] << endl; 
	}
	cout << "New person found!" << endl;
	string worker_position = input_vector[0];
	int worker_ID = atoi(input_vector[1].c_str());
	string worker_name = input_vector[2];
	string worker_department = input_vector[3];
	string worker_weekend = input_vector[4];
	string worker_boss = input_vector[5];
	string worker_PL_type = input_vector[6];
	string worker_HB_type = input_vector[7];
	string worker_freeday = input_vector[8];

	Worker worker {worker_position, worker_ID, worker_name, worker_department, worker_weekend, worker_boss, worker_PL_type, worker_HB_type, worker_freeday};

	break;
      }
      input_vector.push_back(input);  
    }



      // string worker_position = input;
      // int worker_ID = ;
      // string worker_name;
      // string worker_department;
      // string worker_weekend;
      // string worker_boss;
      // string worker_PL_type;
      // string worker_HB_type;
      // string worker_freeday;


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

    TaskClass a; 
    return 0;

    // Error handling 
  } catch (const char* msg){ 
    cerr << msg << endl;
    //fprintf(log_file, msg);
  }
}

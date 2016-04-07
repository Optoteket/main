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

//File names
string log_file_dir = "../target/logs/";
stringstream log_file_path;

//Function declarations
void create_workers(Library*);


int main()
{
  //1. Create logfile
  // date << "_" << timedate->tm_year + 1900 << "_" << timedate->tm_mon+1 << "_" << timedate->tm_mday << ":" << timedate->tm_hour << "-" << timedate->tm_min+1 << "-"<< timedate->tm_sec+1;
  // log_file_path << log_file_dir << "logfile" << date.str() << ".dat"; 

  // ofstream log_file (log_file_path.str().c_str());
  // if (log_file.is_open())
  // {
  //   log_file << date.str().c_str() << "\n";
  //   log_file << "This is another line.\n";
  //   log_file.close();
  // }
  // else cout << "Unable to open file";

  try{
    //2. Create library
    Library library;
    library.read_demand();
    library.print_demand();

    //3. Create workers
    library.create_workers();

    library.cost_avail_demand_diff();

    //4. Destroy and repair weekends
    /*****************************************/
    
    // library.fn_destroy_repair(weekend, 10);
    
    // library.fn_destroy_repair(tasks, 10);

    /*****************************************/

    //create_workers(&library);
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

    TaskClass a; 
    return 0;

    // Error handling 
  } catch (const char* msg){ 
    cerr << msg << endl;
    //fprintf(log_file, msg);
  }
}

// /************** Auxiliary function: create worker *************/
// void create_workers(Library* library){
//   ifstream worker_file ("../src/data/workers5W.txt");
    
//   if (worker_file.fail())
//     {
//       cout << "Error: Could not read worker file" << endl;
//     }

//   vector<string> input_vector;
//   vector<Worker> workers;
//   string input;

//   while(getline(worker_file, input)){

//     //Create a new worker when all data has been read 
//     if(input.size()<2){
//       // for (int i=0; i < input_vector.size(); i++){
//       // 	cout << input_vector[i] << endl; 
//       // }
//       //cout << "Read info about worker." << endl;
//        	string worker_position = input_vector[0];
//        	int worker_ID = atoi(input_vector[1].c_str());
//        	string worker_name = input_vector[2];
//        	string worker_department = input_vector[3];
//        	string worker_weekend = input_vector[4];
//        	string worker_boss = input_vector[5];
//        	string worker_PL_type = input_vector[6];
//        	string worker_HB_type = input_vector[7];
//        	string worker_freeday = input_vector[8];

//        	//Create worker
//        	Worker worker {worker_position, worker_ID, worker_name, worker_department, worker_weekend, worker_boss, worker_PL_type, worker_HB_type, worker_freeday};
// 	workers.push_back(worker);
//        	input_vector.erase (input_vector.begin(),input_vector.begin()+10);

//        	//Read availability, set in worker
//        	for (int i=0; i < input_vector.size(); i++){
//        	  vector<string> line_vector;
//        	  //Take current line
//        	  input = input_vector[i];
//        	  size_t pos = input.find(",");

//        	  //Write all words separated by space to input_vector
//        	  while (pos != string::npos){
//        	    line_vector.push_back(input.substr(0,pos));
//        	    input = input.substr(pos+1);
//        	    pos = input.find (",");
//        	  }

//        	  //Write task to input_vector
//        	  pos = input.find(" ");
//        	  line_vector.push_back(input.substr(0,pos));
//        	  input = input.substr(pos+1);

//        	  //Write 0 or 1 to input_vector
//        	  pos = input.find(" ");
//        	  line_vector.push_back(input.substr(pos+1));
//        	  input = input.substr(pos+1);

//       	  if (line_vector.size() == 4){
//        	    worker.set_avail(atoi(line_vector[0].c_str())-1, atoi(line_vector[1].c_str())-1, atoi(line_vector[2].c_str())-1,  atoi(line_vector[3].c_str()));
//        	  }
//        	  else cout << "Error: wrong number of arguments from avail file."<< endl;
//        	}
      
//        	worker.print_avail();
// 	library->add_worker(&worker);
// 	//Break after reading all lines of a worker 
// 	//break;
//       input_vector.clear();
//       }
      
//     else{
//       // Read all lines for a worker
//       input_vector.push_back(input); 
//     }
//   }

//   cout << "Library workers:" << endl;
//   for (int i=0; i < workers.size(); i++){
//     cout << workers[i].get_ID() << endl;
//   }

// }

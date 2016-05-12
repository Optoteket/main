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

/************* Function myrandom ***********/
int myrandom (int i) {return rand()%i;}

/************ Function find_position_req *******/
int find_position_req(int task_type){
  if (task_type <= PL)
    return Ass;
  else if (task_type <= HB)
    return Lib;
  else if (task_type == BokB)
    return BBlib;
  //TODO: add bokbussen
  else return no_position;
}

/************* Function collect AMPL statistics ***********/
void collect_AMPL_statistics(int* infeas, vector<int>& min_l, vector<int>& min_a){
  //string out_file_path = "../target/statistics/weekend_AMPL_data.csv";
  //ofstream out_file(out_file_path.c_str());
  string in_file_path = "../../../AMPLmodel/LNSweekendsAMPL/librarystaff10W_log.res";
  ifstream in_file(in_file_path.c_str());
  string input; 
  
  while(getline(in_file, input)){
    if(input.find("integer infeasible") !=string::npos){
      (*infeas)++;
      break;
    }
    else{
      if(input.find("min_lib = ") !=string::npos){
	size_t pos = input.find("= ");
	input = input.substr(pos+1,pos+2);
	min_l.push_back(atoi(input.c_str()));
      }
      if(input.find("min_ass = ") !=string::npos){
	size_t pos = input.find("= ");
	input = input.substr(pos+1,pos+2);
	min_a.push_back(atoi(input.c_str()));
      } 
    } 
  }
}


/***************** Main loop *****************/
int main(int argc, char** argv)
{
  //Timer start
  clock_t begin = clock();

  //Weekend statistics
  vector<int> min_ass;
  vector<int> min_lib;
  int infeasible_count = 0;
  string wend_AMPL_file_path = "../target/statistics/weekend_AMPL_data.csv";
  ofstream wend_AMPL_file(wend_AMPL_file_path.c_str());

  srand (unsigned (time(0)));
  //1. Create time and date stamp
  date << timedate->tm_year + 1900 << "_" 
       << timedate->tm_mon+1 << "_" << timedate->tm_mday << " " 
       << timedate->tm_hour << ":" << timedate->tm_min+1 << ":" 
       << timedate->tm_sec+1;
  log_file_path << log_file_dir << "logfile" << ".dat"; 

  ofstream log_file (log_file_path.str().c_str());
  if (log_file.is_open())
  {
    log_file << date.str().c_str() << endl;
    log_file << "The logs are:" << endl;
    log_file.close();
  }
  else cout << "Unable to open file";

  freopen(log_file_path.str().c_str(), "a", stderr);

  //Create result file
  res_file_path << res_file_dir << "resfile" << ".dat"; 
  ofstream res_file (res_file_path.str().c_str());
  //res_file.open(res_file_path.str().c_str());
  
  if(res_file.is_open())
    {
      res_file << date.str().c_str() << endl;
      res_file << "The results are:" << endl;
    }

  min_ass.clear();
  min_lib.clear();
  int max_loops = 1;
  double weights[3];


  for(int loop=0; loop < max_loops; loop++){
    if(loop < 80){
      weights[0]=10;
      weights[1]=10;
      weights[2]=weights[1]/10.0;
      double sum =  weights[0] +  weights[1] +  weights[2];
      weights[0]/=sum;
      weights[1]/=sum;
      weights[2]/=sum;
    }
    else if(loop < 80){
      weights[0]=10;
      weights[1]=40;
      weights[2]=0;
    }
    else if(loop < 120){
      weights[0]=10;
      weights[1]=10;
      weights[2]=0;
    }
    else if(loop < 160){
      weights[0]=10;
      weights[1]=5;
      weights[2]=5;
    }
   else if(loop < 200){
      weights[0]=10;
      weights[1]=0;
      weights[2]=2;
   }
    else if(loop < 240){
      weights[0]=10;
      weights[1]=0;
      weights[2]=5;
    }
    else if(loop < 280){
      weights[0]=10;
      weights[1]=0;
      weights[2]=10;
    }
    else if(loop < 320){
      weights[0]=10;
      weights[1]=10;
      weights[2]=10;
    }

    //2. Create library
    Library library {&res_file};

    //3. Create initial solution
    library.create_initial_solution();

    //4. Optimize weekends, input: num iterations, destroy percentage
    library.optimize_weekends(1, 20, weights);
    
    //Write results to resfile
    library.write_results();

    //Write weekends to AMPL format and run
    //library.write_weekend_AMPL_data();
    log_file.close();
    //system("../../../AMPLmodel/LNSweekendsAMPL/launchAMPL.sh");
    //collect_AMPL_statistics(&infeasible_count, min_lib, min_ass);

    if(loop == 39 || loop == 79 || loop == 119 || loop == 159 || loop == 199 || loop == 239 || loop == 279 || loop == 319){
      //Print costs to file
      double tot_cost = 0.0;
      wend_AMPL_file  << "With weights: " <<  weights[0] << ", "<<  weights[1] << ", "<<  weights[2] << endl;
      cout << "Number of infeasible solutions: " << infeasible_count << endl;
      wend_AMPL_file  << "Number of infeasible solutions:" << infeasible_count << endl;
      for(int i=0; i<(int) min_lib.size(); i++){
	cout << "Min num lib/ass: (" << i << ") "<< min_lib[i] << ", " << min_ass[i] << ". Cost: " << 2*min_lib[i] + min_ass[i] <<  endl;  
	wend_AMPL_file << "Min num lib/ass: (" << i << ") "<< min_lib[i] << ", " << min_ass[i] << ". Cost: " << 2*min_lib[i] + min_ass[i] << endl;  
	tot_cost += (2.0*min_lib[i] + 1.0*min_ass[i]);
      }
      cout << endl << "Average cost:" << tot_cost/(double)min_lib.size() << endl;
      wend_AMPL_file << endl << "Average cost:" << tot_cost/(double)min_lib.size() << endl << endl;
      
      //Clear variables
      infeasible_count = 0;
      min_ass.clear();
      min_lib.clear();
    }
  }



  //Timer end
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  //res_file << "Time of program: " << elapsed_secs << " s." << endl;
  //res_file.close();
  return 0;

}


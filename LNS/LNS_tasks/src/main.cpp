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


struct Ax_struct{
  int week;
  int day;
  int shift;
  string type;
  int number;
};

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
void collect_AMPL_statistics(int* infeas, vector<int>& min_l, vector<int>& min_a, vector<Ax_struct>& ax_vector){
  //string out_file_path = "../target/statistics/weekend_AMPL_data.csv";
  //ofstream out_file(out_file_path.c_str());
  string in_file_path = "../../../AMPLmodel/LNSweekendsAMPL/librarystaff10W_log.res";
  ifstream in_file(in_file_path.c_str());
  string input; 
  bool read_ax=false;
  bool found_ax = false;
  
  while(getline(in_file, input)){

    if(read_ax){
      if(input.find(";") !=string::npos){
	read_ax = false;
	found_ax = false;
      }
      else {
	if(!found_ax){
	  (*infeas)++;
	}
	found_ax=true;
	Ax_struct ax;
	//Find week
	size_t pos = input.find(" ");
	ax.week = atoi(input.substr(0,pos+1).c_str());
	input = input.substr(pos+1);
	//Find day
	pos = input.find(" ");
	ax.day = atoi(input.substr(0,pos+1).c_str());
	input = input.substr(pos+1);
	//Find shift
	pos = input.find(" ");
	ax.shift = atoi(input.substr(0,pos+1).c_str());
	input = input.substr(pos+1);
	//Find type
	pos = input.find(" ");
	ax.type = input.substr(0,pos+1);
	input = input.substr(pos+1);
	//Find value
	pos = input.length();
	ax.number = atoi(input.substr(0,pos+1).c_str());
	//Push back artificial worker
	ax_vector.push_back(ax);
      }
    }
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
    if(input.find("ax :=") !=string::npos){
      read_ax=true;
    } 
  }
}



/***************** Main loop *****************/
int main(int argc, char** argv)
{
  //Timer start
  clock_t begin = clock();

  //Weekend statistics variables and files
  vector<int> min_ass;
  vector<int> min_lib;
  vector<Ax_struct> ax_vector;
  vector<vector<Ax_struct>> ax_vector_vector;
  vector<double> library_costs;
  int infeasible_count = 0;
  string wend_AMPL_file_path = "../target/statistics/weekend_AMPL_data.csv";
  ofstream wend_AMPL_file(wend_AMPL_file_path.c_str());

  //Random seeding
  //srand (unsigned (time(0)));


  //Create time and date stamp for files
  date << timedate->tm_year + 1900 << "_" 
       << timedate->tm_mon+1 << "_" << timedate->tm_mday << " " 
       << timedate->tm_hour << ":" << timedate->tm_min+1 << ":" 
       << timedate->tm_sec+1;
  log_file_path << log_file_dir << "logfile" << ".dat"; 

  //Logfile header
  ofstream log_file (log_file_path.str().c_str());
  if (log_file.is_open())
  {
    log_file << date.str().c_str() << endl;
    log_file << "The logs are:" << endl;
    log_file.close();
  }
  else cout << "Unable to open file";

  //Std err to logfile
  //freopen(log_file_path.str().c_str(), "a", stderr);

  //Create result file
  res_file_path << res_file_dir << "resfile" << ".dat"; 
  ofstream res_file (res_file_path.str().c_str());
  
  if(res_file.is_open())
    {
      res_file << date.str().c_str() << endl;
      res_file << "The results are:" << endl;
    }
  min_ass.clear();
  min_lib.clear();
  library_costs.clear();

  int max_loops = 1;
  int num_tests = 1;
  double weights[3];
  int wend_iterations = 500;
  int wday_iterations = 20;

  //Create and instance of empty best library
  //Library best_library {&res_file};


  //AMPL loop
  for(int loop=0; loop < max_loops*num_tests; loop++){

    //1. Setting and normalizing weights for weekend objective function
    if(loop < max_loops){
      weights[0]=0.1; //Min number of full time avail workers/day
      weights[1]=0.1; //Min number of avail workers per shift
      weights[2]=10; //Min number of avail workers a day

      //Normalizing
      double sum =  weights[0] +  weights[1] +  weights[2];
      weights[0]/=sum;
      weights[1]/=sum;
      weights[2]/=sum;
    }
    else if(loop < max_loops*2){
      weights[0]=1; //Min number of full time avail workers/day
      weights[1]=1; //Min number of avail workers per shift
      weights[2]=10; //Min number of avail workers a day

      //Normalizing
      double sum =  weights[0] +  weights[1] +  weights[2];
      weights[0]/=sum;
      weights[1]/=sum;
      weights[2]/=sum;
    }
    else if(loop < max_loops*3){
      weights[0]=1; //Min number of full time avail workers/day
      weights[1]=1; //Min number of avail workers per shift
      weights[2]=100; //Min number of avail workers a day

      //Normalizing
      double sum =  weights[0] +  weights[1] +  weights[2];
      weights[0]/=sum;
      weights[1]/=sum;
      weights[2]/=sum;
    }
    else if(loop < max_loops*4){
      weights[0]=10; //Min number of full time avail workers/day
      weights[1]=10; //Min number of avail workers per shift
      weights[2]=10; //Min number of avail workers a day

      //Normalizing
      double sum =  weights[0] +  weights[1] +  weights[2];
      weights[0]/=sum;
      weights[1]/=sum;
      weights[2]/=sum;
    }
    else if(loop < max_loops*5){
      weights[0]=0; //Min number of full time avail workers/day
      weights[1]=0; //Min number of avail workers per shift
      weights[2]=0; //Min number of avail workers a day

      //Normalizing
      double sum =  weights[0] +  weights[1] +  weights[2] + 0.001;
      weights[0]/=sum;
      weights[1]/=sum;
      weights[2]/=sum;
    }
    else if(loop < max_loops*6){
      weights[0]=1; //Min number of full time avail workers/day
      weights[1]=10; //Min number of avail workers per shift
      weights[2]=1; //Min number of avail workers a day

      //Normalizing
      double sum =  weights[0] +  weights[1] +  weights[2];
      weights[0]/=sum;
      weights[1]/=sum;
      weights[2]/=sum;
    }
    else if(loop < max_loops*7){
      weights[0]=1; //Min number of full time avail workers/day
      weights[1]=1; //Min number of avail workers per shift
      weights[2]=10; //Min number of avail workers a day

      //Normalizing
      double sum =  weights[0] +  weights[1] +  weights[2];
      weights[0]/=sum;
      weights[1]/=sum;
      weights[2]/=sum;
    }
    else if(loop < max_loops*8){
      weights[0]=0; //Min number of full time avail workers/day
      weights[1]=0; //Min number of avail workers per shift
      weights[2]=0; //Min number of avail workers a day

      //Normalizing
      double sum =  weights[0] +  weights[1] +  weights[2]+0.001;
      weights[0]/=sum;
      weights[1]/=sum;
      weights[2]/=sum;
    }

    //2. Create library
    Library library {&res_file};

    //3. Create initial solution
    library.create_initial_solution();

    //4. Optimize weekends, input: num iterations, destroy percentage
    library.optimize_weekends(wend_iterations, 8, weights);
    
    //6. Optimize weekdays
    //library.optimize_weekday_tasks(wday_iterations);

    //5. Get objective function varibles
    double library_cost = library.get_library_cost();
    library_costs.push_back(library_cost);
    double cost_stand_in = library.get_stand_in_cost();
    library_costs.push_back(cost_stand_in);
    double cost_shift_avail = library.get_shift_avail_cost();
    library_costs.push_back(cost_shift_avail);
    double cost_day_avail = library.get_day_avail_cost();
    library_costs.push_back(cost_day_avail);
    double cost_stand_in_lib = library.get_stand_in_lib();
    library_costs.push_back(cost_stand_in_lib);
    double cost_stand_in_ass = library.get_stand_in_ass();
    library_costs.push_back(cost_stand_in_ass);

   //7. Check if library cost is better than max
    // if (library_cost > max_library_cost){
    //   best_library = library;
    // }

    //7. Write results to resfile
    library.write_results();

    //8. Write weekends to AMPL format and run
    library.write_weekend_AMPL_data();
    log_file.close();
    system("../../../AMPLmodel/LNSweekendsAMPL/launchAMPL.sh");
    collect_AMPL_statistics(&infeasible_count, min_lib, min_ass, ax_vector);
    ax_vector_vector.push_back(ax_vector);
    ax_vector.clear();
    usleep(1000);

    //9. Write AMPL statistics
    if(loop == max_loops-1 || loop == 2*max_loops-1 || loop == 3*max_loops-1 || loop == 4*max_loops-1 || loop == 5*max_loops-1 || loop == 6*max_loops-1 || loop == 7*max_loops-1  || loop == 8*max_loops-1){
      //Print costs to file
      double tot_cost = 0.0;
      int divisor = (int) min_lib.size() - infeasible_count;
      wend_AMPL_file  << date.str().c_str() << endl;
      wend_AMPL_file  << "With weights: " <<  weights[0] << ", "<<  weights[1] << ", "<<  weights[2] << endl;
      cout << "Number of infeasible solutions: " << infeasible_count << endl;
      wend_AMPL_file  << "Number of infeasible solutions:" << infeasible_count << endl;
      for(int i=0; i<(int) min_lib.size(); i++){
	cout << "Min num lib/ass: (" << i << ") "<< min_lib[i] << ", " << min_ass[i] << ". Cost: " << 2*min_lib[i] + min_ass[i];  
	cout << "    ObjFun value: " << library_costs[6*i] << endl;
	wend_AMPL_file << "Min num lib/ass: (" << i << ") "<< min_lib[i] << ", " << min_ass[i] << ". Cost: " << 2*min_lib[i] + min_ass[i];
	wend_AMPL_file << "    ObjFun value: " << library_costs[6*i] << ", Stand in cost: " << library_costs[6*i+1] << ", Shift avail: " << library_costs[6*i+2] << ", Day avail: " << library_costs[6*i+3] 
		       <<" Num stand ins (lib/ass): " << library_costs[6*i+4] <<"/" << library_costs[6*i+5] << endl;
	vector<Ax_struct>* ax_vec = &ax_vector_vector[i];
	if((int) ax_vec->size()>0){
	  wend_AMPL_file <<"Artificial workers placed at: " << endl;
	  cout << "Artificial workers placed at: " << endl;
	  for(int i=0; i<(int) ax_vec->size(); i++){
	    wend_AMPL_file << (*ax_vec)[i].week << ", "<< (*ax_vec)[i].day << ", " << (*ax_vec)[i].shift << ", "<< (*ax_vec)[i].type << ". Number: "<< (*ax_vec)[i].number << endl;
	    cout << (*ax_vec)[i].week << ", "<< (*ax_vec)[i].day << ", " << (*ax_vec)[i].shift << ", "<< (*ax_vec)[i].type << ". Number: "<< (*ax_vec)[i].number << endl;
	  }
	}
	else tot_cost += 2*min_lib[i] + min_ass[i];
      }
      cout << endl << "Average cost:" << tot_cost/divisor << endl;
      wend_AMPL_file << endl << "Average cost:" << tot_cost/divisor << endl << endl;
      
      //Clear variables
      infeasible_count = 0;
      min_ass.clear();
      min_lib.clear();
      library_costs.clear();
      ax_vector_vector.clear();
    }
  }

  

  //Timer end
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Time of program: " << elapsed_secs << " s." << endl;
  //res_file.close();
  return 0;

}


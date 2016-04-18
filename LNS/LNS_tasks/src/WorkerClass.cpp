// Worker class

#include "WorkerClass.h"
#include "Constants.h"

using namespace std;


/************ Worker constructor ***********/

Worker::Worker(string pos, int ID, string name, string department, string weekend, string boss, string PL_type, string HB_type, string freeday, int input_avail[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS]){

  identity.pos = pos; 
  identity.ID = ID;
  identity.name = name;
  identity.department = department;
  identity.weekend = weekend;
  identity.boss = boss;
  identity.PL_type = PL_type;
  identity.HB_type = HB_type;
  identity.freeday = freeday;

  //Weekend case
  if (identity.weekend.compare("weekend") != (int) identity.weekend.npos){
    current.weekend = 1;
    current.rotation = 1;
  }
  else { //No_weekend case
    current.weekend = 0;
    current.rotation = 1;
  }

  // Init all costs
  for (int i=0; i<NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      costs.num_tasks_day_cost[i][j] = 0;
      costs.stand_in_cost[i][j] = 0;
      for (int k=0; k<NUM_SHIFTS; k++){
	costs.total_cost[i][j][k] = 0;
      }
    }
  }

  //Set availability for all week rotations
  for (int h=0; h<NUM_ROTATIONS; h++){
    for (int i=0; i<NUM_WEEKS; i++){      
      for (int j=0; j<NUM_DAYS; j++){
	for (int k=0; k<NUM_SHIFTS; k++){
	  avail[h][i][j][k] = input_avail[((NUM_WEEKS + i-h) % NUM_WEEKS)][j][k];
	}
      }
    }    
  }

  //Find stand in avail days
  for (int h=0; h<NUM_ROTATIONS; h++){
    for (int i=0; i<NUM_WEEKS; i++){      
      for (int j=0; j<NUM_DAYS; j++){
	if (avail[h][i][j][0] > 0 && avail[h][i][j][1] > 0 &&  avail[h][i][j][2] > 0){
	  avail_day[h][i][j] = 1;
	}
	else {
	  avail_day[h][i][j] = 0;
	}
      }
    }
  }

  //Set no tasks as default, current avail and avail_day
  for (int i=0; i<NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
	tasks[i][j][k] = no_task;
	current.avail[i][j][k] = avail[current.rotation-1][i][j][k];
      }
      current.avail_day[i][j] = avail_day[current.rotation-1][i][j];
    }
  }  

}


void Worker::print_modulo(){
  for (int h=0; h<NUM_ROTATIONS; h++){
    for (int i=0; i< NUM_WEEKS; i++){
      cout << ((NUM_WEEKS + i-h) % NUM_WEEKS) +1;
    }
    cout << endl;
  }
}


/************ Worker copy constructor ***********/

Worker::Worker(const Worker &obj){
  
  //cout << "Worker copy constructor" << endl;

  identity.pos = obj.identity.pos; 
  identity.ID = obj.identity.ID;
  identity.name = obj.identity.name;
  identity.department = obj.identity.department;
  identity.weekend = obj.identity.weekend;
  identity.boss = obj.identity.boss;
  identity.PL_type = obj.identity.PL_type;
  identity.HB_type = obj.identity.HB_type;
  identity.freeday = obj.identity.freeday;

  current.weekend = obj.current.weekend;
  current.rotation = obj.current.rotation;  

  // Init all costs
  for (int i=0; i<NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      costs.num_tasks_day_cost[i][j] = obj.costs.num_tasks_day_cost[i][j];
      costs.stand_in_cost[i][j] = obj.costs.stand_in_cost[i][j];
      for (int k=0; k<NUM_SHIFTS; k++){
	costs.total_cost[i][j][k] = obj.costs.total_cost[i][j][k];
      }
    }
  }

  for (int h=0; h<NUM_ROTATIONS; h++){
    for (int i=0; i< NUM_WEEKS; i++){
      for (int j=0; j<NUM_DAYS; j++){
	avail_day[h][i][j]=obj.avail_day[h][i][j];
	for (int k=0; k<NUM_SHIFTS; k++){
	  avail[h][i][j][k] = obj.avail[h][i][j][k];	  
	}
      }
    }
  }

  for (int i=0; i<NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
  	tasks[i][j][k] = obj.tasks[i][j][k];
	current.avail[i][j][k] = obj.current.avail[i][j][k];
      }
      current.avail_day[i][j] = obj.current.avail_day[i][j];
    }
  }  
}

/***************** Worker cost functions ************/
int Worker::find_costs(int w, int d, int s){
  find_stand_in_cost(w,d);
  find_num_tasks_cost(w,d);

  costs.total_cost[w][d][s] =  
    costs.num_tasks_weight*costs.stand_in_cost[w][d] 
    + costs.stand_in_weight*costs.num_tasks_day_cost[w][d];
  
  return costs.total_cost[w][d][s];
}

void Worker::find_stand_in_cost(int w, int d){
  costs.stand_in_cost[w][d] = get_avail_day(w,d) - get_current_avail_day(w,d);
}

void Worker::find_num_tasks_cost(int w, int d){
  if (current.num_tasks_day[w][d] > MAX_TASKS_PER_DAY){
    costs.num_tasks_day_cost[w][d] = current.num_tasks_day[w][d] - MAX_TASKS_PER_DAY;
  }
}

/************** Worker functions: get **********/
int Worker::get_ID(){
  return identity.ID;
}

//string Worker::get_pos(){
//return identity.pos;
//}

int Worker::get_pos(){
  if (identity.pos.find("lib",0,3) == 0){
    return Lib;
  }
  else if (identity.pos.find("ass",0,3) == 0){
    return Ass;
  }
  else return no_worker;
}

string Worker::get_weekend(){
  return identity.weekend;
}

int Worker::get_rotation(){
  return current.rotation;
}

int Worker::get_current_weekend(){
  return current.weekend;
}

int Worker::get_avail(int week, int day, int shift){
  return avail[current.rotation-1][week][day][shift];
}

int Worker::get_current_avail(int week, int day, int shift){
  return current.avail[week][day][shift];
}

int Worker::get_avail_day(int week, int day){
  return avail_day[current.rotation-1][week][day];
}

int Worker::get_current_avail_day(int week, int day){
  return current.avail_day[week][day];
}

/************** Worker functions: set **********/

void Worker::set_weekend(int wend){
  if (current.weekend !=0){
    current.weekend = wend;
    set_rotation(wend);
  }
  else cout << "Error: cannot change weekend of non-weekend worker." << endl;
}

void Worker::set_rotation(int rot){
  current.rotation = rot;
  reset_current_avail();
}

void Worker::set_task(int w,int d,int s,int val){
  if(get_avail(w,d,s) != 0){
    tasks[w][d][s] = val;
    //Increment number of tasks that day
    current.num_tasks_day[w][d]++;
    //Set as unavailable for whole day
    set_current_avail_day("add_task",w,d);
    set_current_avail("add_task",w,d,s);
  }
  else cout << "Error: in set_task, worker not available." << endl;
}

void Worker::set_current_avail_day(string command, int w, int d){
  if (command == "add_task"){
    current.avail_day[w][d] = 0;
  }
}

void Worker::reset_current_avail(){
  for (int i=0; i<NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
	current.avail[i][j][k] = avail[current.rotation-1][i][j][k];
      }
    }
  }
}

void Worker::set_current_avail(string command, int w, int d, int s){
 if (command == "add_task"){
    //Remove availability from all rotations
      current.avail[w][d][s] = no_task;
  }
  else if (command == "del_task"){
      current.avail[w][d][s] = avail[current.rotation-1][w][d][s];
  }
}

void Worker::set_weekend_task(int task){
  //Saturday
  set_task(get_current_weekend()-1, 5, 0, task);
  set_current_avail("add_task", get_current_weekend()-1, 5, 0);

  //Sunday
  set_task(get_current_weekend()-1, 6, 0, task);
  set_current_avail("add_task", get_current_weekend()-1, 6, 0);

  //Friday
  if (task != HB){
    set_task(get_current_weekend()-1, 4, 3, task);
    set_current_avail("add_task", get_current_weekend()-1, 4, 3);
  }
}

/************* Worker functions: print ***********/

// void Worker::print_avail(){
//   cout << "Worker " << get_ID() << " availability:" << endl;
//   for (int i=0; i< NUM_WEEKS; i++){
//     for (int j=0; j< NUM_SHIFTS; j++){
//       for (int k=0; k< NUM_DAYS; k++){
// 	cout << avail[i][k][j] << " ";
//       }
//       cout << endl;
//     }
//     cout << endl << endl;
//   }
// }

void Worker::display_all_avail(){
  cout << "Current vailability vector for worker " << get_ID() << endl;
  for (int h=0; h<NUM_ROTATIONS; h++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for (int i=0; i< NUM_WEEKS; i++){
	for (int k=0; k< NUM_DAYS; k++){
	  cout << avail[h][i][k][j] << " ";
	}
	cout << "   ";
      }
      cout << endl;
    }
    cout << endl << endl;
  }
}

void Worker::display_all_current_avail(){
  cout << "Availability vector for worker " << get_ID() << endl;
    for (int j=0; j< NUM_SHIFTS; j++){
      for (int i=0; i< NUM_WEEKS; i++){
	for (int k=0; k< NUM_DAYS; k++){
	  cout << current.avail[i][k][j] << " ";
	}
	cout << "   ";
      }
      cout << endl;
  }
}

void Worker::display_avail(){
  cout << "Current availability for worker " << get_ID() << ", current rotation " << get_rotation() << endl;
  for (int j=0; j< NUM_SHIFTS; j++){
    for (int i=0; i< NUM_WEEKS; i++){
      for (int k=0; k< NUM_DAYS; k++){
	cout << avail[current.rotation-1][i][k][j] << " ";
      }
      cout << "   ";
    }
    cout << endl;
  }
}

void Worker::display_avail_day(){
  cout << "Avail day for worker: " << get_ID() << ", current rotation " << get_rotation() << endl;
  for (int i=0; i< NUM_WEEKS; i++){
    for (int k=0; k< NUM_DAYS; k++){
      cout << avail_day[current.rotation-1][i][k] << " ";
    }
    cout << "   ";
  }
  cout << endl;
}


 void Worker::display_tasks(){
  cout << "Current tasks for worker " << get_ID() << ", current rotation " << get_rotation() << endl;
  for (int j=0; j< NUM_SHIFTS; j++){
    for (int i=0; i< NUM_WEEKS; i++){
      for (int k=0; k< NUM_DAYS; k++){
	cout << tasks[i][k][j] << " ";
      }
      cout << "   ";
    }
    cout << endl;
  }
}

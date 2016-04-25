// Worker class

#include "WorkerClass.h"
#include "Constants.h"

using namespace std;

/************ Worker constructor ***********/

Worker::Worker(){

  identity.pos = "none"; 
  identity.ID = 0;
  identity.name = "none";
  identity.department = "none";
  identity.weekend = "none";
  identity.boss = "none";
  identity.PL_type = "none";
  identity.HB_type = "none";
  identity.freeday = "none";

  //Init current weekend and rotation
  current.weekend = 0;
  current.rotation = 1;


  // Init all costs  
  costs.weights[0] = 0; //Num_tasks_day weight
  costs.weights[1] = 0;
  costs.cost_sum = 0;

  for (int i=0; i<NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      costs.num_tasks_day_cost[i][j] = 0;
      costs.stand_in_cost[i][j] = 0;
      for (int k=0; k<NUM_SHIFTS; k++){
	costs.total_cost[i][j][k] = 0;
      }
    }
  }

  //Init all avail
  for (int h=0; h<NUM_ROTATIONS; h++){
    for (int i=0; i<NUM_WEEKS; i++){      
      for (int j=0; j<NUM_DAYS; j++){
	for (int k=0; k<NUM_SHIFTS; k++){
	  identity.avail[h][i][j][k] = 0;
	}
      }
    }    
  }

  //Find and init stand in avail days
  for (int h=0; h<NUM_ROTATIONS; h++){
    for (int i=0; i<NUM_WEEKS; i++){      
      for (int j=0; j<NUM_DAYS; j++){
	identity.avail_day[h][i][j] = 0;
      }
    }
  }
  

 //Init rest current
  for (int i=0; i<NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
	current.tasks[i][j][k] = no_task;
	current.avail[i][j][k] = 0;
      }
      current.avail_day[i][j] = 0;
      current.num_tasks_day[i][j] = no_task;
    }
  } 

}


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

  //Init current weekend and rotation
  if (identity.weekend.compare("weekend") != (int) identity.weekend.npos){
    current.weekend = 1;
    current.rotation = 1;
  }
  else { //No_weekend case
    current.weekend = 0;
    current.rotation = 1;
  }

  // Init all costs  
  costs.weights[0] = 5; //Num_tasks_day weight
  if (get_pos() == Lib)
    costs.weights[1] = 2; //Stand_in weight
  else costs.weights[1] = 1;
  costs.cost_sum = 0;

  for (int i=0; i<NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      costs.num_tasks_day_cost[i][j] = 0;
      costs.stand_in_cost[i][j] = 0;
      for (int k=0; k<NUM_SHIFTS; k++){
	costs.total_cost[i][j][k] = 0;
      }
    }
  }

  //Init all avail
  for (int h=0; h<NUM_ROTATIONS; h++){
    for (int i=0; i<NUM_WEEKS; i++){      
      for (int j=0; j<NUM_DAYS; j++){
	for (int k=0; k<NUM_SHIFTS; k++){
	  identity.avail[h][i][j][k] = input_avail[((NUM_WEEKS + i-h) % NUM_WEEKS)][j][k];
	}
      }
    }    
  }

  //Find and init stand in avail days
  for (int h=0; h<NUM_ROTATIONS; h++){
    for (int i=0; i<NUM_WEEKS; i++){      
      for (int j=0; j<NUM_DAYS; j++){
	if (identity.avail[h][i][j][0] > 0 && identity.avail[h][i][j][1] > 0 &&  identity.avail[h][i][j][2] > 0){
	 identity.avail_day[h][i][j] = 1;
	}
	else {
	  identity.avail_day[h][i][j] = 0;
	}
      }
    }
  } 

 //Init rest current
  for (int i=0; i<NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
	current.tasks[i][j][k] = no_task;
	current.avail[i][j][k] = identity.avail[current.rotation-1][i][j][k];
      }
      current.avail_day[i][j] = identity.avail_day[current.rotation-1][i][j];
      current.num_tasks_day[i][j] = no_task;
    }
  } 

}


// void Worker::print_modulo(){
//   for (int h=0; h<NUM_ROTATIONS; h++){
//     for (int i=0; i< NUM_WEEKS; i++){
//       cout << ((NUM_WEEKS + i-h) % NUM_WEEKS) +1;
//     }
//     cout << endl;
//   }
// }


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
  costs.weights[0] = obj.costs.weights[0];
  costs.weights[1] = obj.costs.weights[1];
  costs.cost_sum = obj.costs.cost_sum;

  for (int i=0; i<NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      costs.num_tasks_day_cost[i][j] = obj.costs.num_tasks_day_cost[i][j];
      costs.stand_in_cost[i][j] = obj.costs.stand_in_cost[i][j];
      for (int k=0; k<NUM_SHIFTS; k++){
	costs.total_cost[i][j][k] = obj.costs.total_cost[i][j][k];
      }
    }
  }

 //Init all avail
  for (int h=0; h<NUM_ROTATIONS; h++){
    for (int i=0; i<NUM_WEEKS; i++){      
      for (int j=0; j<NUM_DAYS; j++){
	for (int k=0; k<NUM_SHIFTS; k++){
	  identity.avail[h][i][j][k] = obj.identity.avail[h][i][j][k];	  
	}
	identity.avail_day[h][i][j] =  obj.identity.avail_day[h][i][j];
      }
    }    
  }


 //Init rest current
  for (int i=0; i<NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
	current.tasks[i][j][k] = obj.current.tasks[i][j][k];
	current.avail[i][j][k] = obj.current.avail[i][j][k];
      }
      current.avail_day[i][j] = obj.current.avail_day[i][j];
      current.num_tasks_day[i][j] = obj.current.num_tasks_day[i][j];
    }
  } 

}

/***************** Worker cost functions ************/
int Worker::find_costs(int w, int d, int s){
  int cost1 = find_stand_in_cost(w,d);
  int cost2 = find_num_tasks_cost(w,d);

  int cost=
    //costs.total_cost[w][d][s] =  
    costs.weights[0]*cost1
    //costs.num_tasks_day_cost[w][d]
    + costs.weights[1]*cost2;
    //*costs.stand_in_cost[w][d];

  //return costs.total_cost[w][d][s];
  return cost;
}

int Worker::find_stand_in_cost(int w, int d){
  return get_avail_day(w,d) - get_current_avail_day(w,d);
  //costs.stand_in_cost[w][d] = get_avail_day(w,d) - get_current_avail_day(w,d);
}

int Worker::find_num_tasks_cost(int w, int d){
  int cost;
  if (current.num_tasks_day[w][d] > MAX_TASKS_PER_DAY){
    cost = current.num_tasks_day[w][d] - MAX_TASKS_PER_DAY;
    //costs.num_tasks_day_cost[w][d] = current.num_tasks_day[w][d] - MAX_TASKS_PER_DAY;
  }
  //else costs.num_tasks_day_cost[w][d] = 0;
  else cost = 0;
  return cost;
}

/************** Worker functions: get **********/
int Worker::get_ID(){
  return identity.ID;
}

int Worker::get_pos(){
  if (identity.pos.find("lib",0,3) == 0){
    return Lib;
  }
  else if (identity.pos.find("ass",0,3) == 0){
    return Ass;
  }
  else return no_position;
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
  return identity.avail[current.rotation-1][week][day][shift];
}

int Worker::get_current_avail(int week, int day, int shift){
  return current.avail[week][day][shift];
}

int Worker::get_current_task(int week, int day, int shift){
  return current.tasks[week][day][shift];
}

int Worker::get_weekend_task(){
  //if (current.weekend != 0)
    return current.tasks[current.weekend-1][5][0];
  //else cerr << "Error: In get weekend task, worker has no weekend." << endl;
}

int Worker::get_avail_day(int week, int day){
  return identity.avail_day[current.rotation-1][week][day];
}

int Worker::get_current_avail_day(int week, int day){
  return current.avail_day[week][day];
}

int Worker::get_cost_sum() const{
  return costs.cost_sum;
}

/************** Worker functions: set **********/

void Worker::set_stand_in_cost(int w, int d){
  costs.stand_in_cost[w][d] = get_avail_day(w,d) - get_current_avail_day(w,d);
}

void Worker::set_num_tasks_cost(int w, int d){
   if (current.num_tasks_day[w][d] > MAX_TASKS_PER_DAY){
    costs.num_tasks_day_cost[w][d] = current.num_tasks_day[w][d] - MAX_TASKS_PER_DAY;
  }
  else costs.num_tasks_day_cost[w][d] = 0;
}

void Worker::set_total_cost(int w, int d, int s){
  set_stand_in_cost(w,d);
  set_num_tasks_cost(w,d);

  costs.total_cost[w][d][s] =  
    costs.weights[0]*costs.num_tasks_day_cost[w][d]
    + costs.weights[1]*costs.stand_in_cost[w][d];
}


void Worker::set_cost_sum(){
  //Reset cost sum
  costs.cost_sum=0;

  //Find cost sum
  for (int i=0; i<NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
	costs.cost_sum += costs.total_cost[i][j][k];
      }
    }
  }
}

void Worker::set_current_weekend(int wend){
  if (identity.weekend.find("no_weekend",0,10) == 0){
    cerr << "Error: cannot change weekend of non-weekend worker." << endl;
  }
  //If weekend is removed, set avail with no weekend rest
  else if (wend == 0){
    remove_week_rest();
    current.weekend = wend;
  }
  //If weekend is added, set avail with current rotation
  else {
    current.weekend = wend;
    set_rotation(wend);

    //TODO: take tasks into consideration
    reset_current_avail();
    reset_current_avail_day();
  }
}

void Worker::set_current_weekend(int wend, int task){
  if (identity.weekend.find("no_weekend",0,10) == 0){
    cerr << "Error: cannot change weekend of non-weekend worker." << endl;
  }
  //If weekend is removed, set avail with no weekend rest
  else if (wend == 0){
    cerr << "Error: use remove_weekend_task() instead" << endl;
    remove_week_rest();
    current.weekend = wend;
  }
  //If weekend is added, set avail with current rotation
  else {
    //Set weekend and rotation variables
    current.weekend = wend;
    set_rotation(wend);

    //Set weekend task
    set_weekend_task(task);

    //Reset avail varaibles
    reset_current_avail();
    reset_current_avail_day();
  }
}



void Worker::set_rotation(int rot){
  current.rotation = rot;
}

void Worker::set_task(int w,int d,int s,int task){
  //if(get_current_task(w,d,s) != task){

    //Adjust number of tasks that day
    if(task != no_task && get_current_task(w,d,s) == no_task){
      current.num_tasks_day[w][d]++;
    }
    else if (task == no_task && get_current_task(w,d,s) != no_task) 
      current.num_tasks_day[w][d]--;

    //Add task
    current.tasks[w][d][s] = task;
    
    //Set as unavailable
    set_current_avail_day(w,d,task);
    set_current_avail(w,d,s,task);

    //Set task costs
    set_total_cost(w,d,s);
    set_cost_sum();
    
    // }
    //else cerr << "Error: in set_task, week: "<< w << " day: " << d
    //	    << " shift: " << s << ". Worker " << get_ID() << " already at task." << endl;
}



void Worker::set_current_avail(int w, int d, int s, int added_task){
 if (added_task == no_task){
    current.avail[w][d][s] = identity.avail[current.rotation-1][w][d][s];
  }
 else {
      current.avail[w][d][s] = no_task;
  }
}

void Worker::reset_current_avail(){
  int count=0;
  for (int i=0; i<NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
	//current.avail[i][j][k] = identity.avail[current.rotation-1][i][j][k];
	if(get_current_task(i,j,k) == no_task)
	  current.avail[i][j][k] = identity.avail[current.rotation-1][i][j][k];
	//set_current_avail(i,j,k,no_task);
	//If there is a task but there is no availability, remove task
	else if (get_current_task(i,j,k) != no_task && identity.avail[current.rotation-1][i][j][k] == no_task){
	  //removed_tasks.push_back(SingleTask(get_current_task(i,j,k),i ,j ,k, 1, 0, get_current_task(i,j,k), get_pos(), )
	  count++;
	  //current.avail[i][j][k] = no_task;

	  //Remove task
	  set_task(i,j,k, no_task);
	}
      }
    }
  }
  cout << "Num of tasks removed at ID " << get_ID() << ": " << count << endl; 
}

// void Worker::redistribute_tasks(){
  
// }

void Worker::remove_weekrest_tasks(){
  //int count=0;
  for (int i=current.weekend-1; i<=current.weekend % NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
	//If there is a task placed but there is no availability, remove task
	//if (get_current_task(i,j,k) != no_task && identity.avail[current.rotation-1][i][j][k] == no_task){
	  set_task(i,j,k,no_task);
	  //count++;
	 //}
      }
    }
  }
  //cout << "Num of tasks removed at ID " << get_ID() << ": " << count << endl; 
}

void Worker::set_current_avail_day(int w, int d, int added_task){
  if (added_task == no_task){
    current.avail_day[w][d] = identity.avail_day[current.rotation-1][w][d];
  }
  else current.avail_day[w][d] = no_task;
}

void Worker::reset_current_avail_day(){
  for (int i=0; i<NUM_WEEKS; i++){      
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
	if(get_current_task(i,j,0) == no_task && get_current_task(i,j,1) == no_task 
	   && get_current_task(i,j,2) == no_task && get_current_task(i,j,3) == no_task)
	  current.avail_day[i][j] = identity.avail_day[current.rotation-1][i][j];
	//set_current_avail_day(i,j,no_task);
      }
    }
  }
}

void Worker::set_weekend_task(int task){

  //Saturday
  set_task(get_current_weekend()-1, 5, 0, task);

  //Sunday
  set_task(get_current_weekend()-1, 6, 0, task);

  //Friday
  if (task != HB || !no_friday_when_HB){
    set_task(get_current_weekend()-1, 4, 3, task);
  }

  // if (task == no_task){
  //   //
  //   set_current_weekend(no_task);
  // }
}

void Worker::remove_weekend_task(){
  set_weekend_task(no_task);
  //set_current_weekend(no_task);
  remove_week_rest();
  current.weekend = 0;
}

void Worker::remove_week_rest(){
  //Set a person avail as if there is no weekend rest
  //TODO: 10 weeks, current.weekend + 2 % NUM_WEEKS
  int first_week = 0;
  int second_week = 0;

  //For even weekends 2 and 4
  if(current.weekend % 2){
    first_week = 3;
    second_week = 2;
  }
  //For odd weekends 1,3 and 5
  else {
    first_week = 2;
    second_week = 3;
  }

  for (int j=0; j<NUM_DAYS; j++){
    for (int k=0; k<NUM_SHIFTS; k++){
      //Set weekend week
      if(get_current_task(current.weekend-1,j,k) == no_task)
	current.avail[current.weekend-1][j][k] = identity.avail[0][first_week][j][k];
      //Set weekrest week
      if(get_current_task(current.weekend % NUM_WEEKS,j,k) == no_task)
	current.avail[current.weekend % NUM_WEEKS][j][k] = identity.avail[0][second_week][j][k];
    }
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
	  cout << identity.avail[h][i][k][j] << " ";
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
	cout << identity.avail[current.rotation-1][i][k][j] << " ";
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
      cout << identity.avail_day[current.rotation-1][i][k] << " ";
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
	cout << current.tasks[i][k][j] << " ";
      }
      cout << "   ";
    }
    cout << endl;
  }
}

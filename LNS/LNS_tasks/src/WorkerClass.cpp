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


  //Init num_PL_week
  for (int w=0; w <NUM_WEEKS; w++){
    current.num_PL_week[w] = 0;
  }
  current.num_PL = 0;

  // Init all costs  
  costs.weights[0] = 0; //Num_tasks_day weight
  costs.weights[1] = 0;
  costs.weights[2] = 0;
  costs.weights[3] = 0;
  costs.weights[4] = 0;
  costs.weights[5] = 0;
  costs.cost_sum = 0;
  costs.PL_cost = 0;


  for (int w=0; w<NUM_WEEKS; w++){      
    for (int d=0; d<NUM_DAYS; d++){
      costs.num_tasks_day_cost[w][d] = 0;
      costs.stand_in_cost[w][d] = 0;
      for (int s=0; s<NUM_SHIFTS; s++){
	costs.total_cost[w][d][s] = 0;
	costs.num_same_shifts_week_cost[w][s] = 0;
      }
    }
    costs.PL_week_cost[w] = 0;
    costs.num_tasks_week_cost[w] = 0;
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
	current.num_same_shifts_week[i][k] = 0;
      }
      current.avail_day[i][j] = 0;
      current.num_tasks_day[i][j] = no_task;
    }
    current.num_tasks_week[i] = 0; 
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

  //Init current num_PL_week
  for (int w=0; w <NUM_WEEKS; w++){
    current.num_PL_week[w] = 0;
  }
  current.num_PL = 0;

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
  //High prio weight
  costs.weights[0] = 100; //Num_tasks_day weight

  //Stand in librarians cost more
  if (get_pos() == Lib)
    costs.weights[1] = 2; //Stand_in weight
  else costs.weights[1] = 1;

  //Mid prio weights
  costs.weights[2] = 5;//PL per week cost
  costs.weights[3] = 5;//Num_PL cost
  costs.weights[4] = 10;//Num_tasks_week cost
  costs.weights[5] = 4;//Same task shift cost

  costs.PL_cost = 0;
  costs.cost_sum = 0;

  for (int w=0; w<NUM_WEEKS; w++){      
    for (int d=0; d<NUM_DAYS; d++){
      costs.num_tasks_day_cost[w][d] = 0;
      costs.stand_in_cost[w][d] = 0;
      for (int s=0; s<NUM_SHIFTS; s++){
	costs.total_cost[w][d][s] = 0;
	costs.num_same_shifts_week_cost[w][s] = 0;
      }
    }
    costs.PL_week_cost[w] = 0;
    costs.num_tasks_week_cost[w] = 0;
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
	if (identity.avail[h][i][j][0] > 0 && identity.avail[h][i][j][1] > 0 && identity.avail[h][i][j][2] > 0){
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
	current.num_same_shifts_week[i][k] = 0;
      }
      current.avail_day[i][j] = identity.avail_day[current.rotation-1][i][j];
      current.num_tasks_day[i][j] = no_task;
    }
    current.num_tasks_week[i] = 0; 
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

  //Init num_PL_week
  for (int w=0; w <NUM_WEEKS; w++){
    current.num_PL_week[w] = obj.current.num_PL_week[w];
  }
  current.num_PL = obj.current.num_PL;
  

  // Init all costs
  costs.weights[0] = obj.costs.weights[0];
  costs.weights[1] = obj.costs.weights[1];
  costs.weights[2] = obj.costs.weights[2];
  costs.weights[3] = obj.costs.weights[3];
  costs.weights[4] = obj.costs.weights[4];
  costs.weights[5] = obj.costs.weights[5];
  costs.cost_sum = obj.costs.cost_sum;
  costs.PL_cost = obj.costs.PL_cost;

  for (int w=0; w<NUM_WEEKS; w++){      
    for (int d=0; d<NUM_DAYS; d++){
      costs.num_tasks_day_cost[w][d] = obj.costs.num_tasks_day_cost[w][d];
      costs.stand_in_cost[w][d] = obj.costs.stand_in_cost[w][d];
      for (int s=0; s<NUM_SHIFTS; s++){
	costs.total_cost[w][d][s] = obj.costs.total_cost[w][d][s];
	costs.num_same_shifts_week_cost[w][s] = obj.costs.num_same_shifts_week_cost[w][s];
      }
    }
    costs.PL_week_cost[w] = obj.costs.PL_week_cost[w];
    costs.num_tasks_week_cost[w] = obj.costs.num_tasks_week_cost[w];
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
  for (int w=0; w<NUM_WEEKS; w++){      
    for (int d=0; d<NUM_DAYS; d++){
      for (int s=0; s<NUM_SHIFTS; s++){
	current.tasks[w][d][s] = obj.current.tasks[w][d][s];
	current.avail[w][d][s] = obj.current.avail[w][d][s];
	current.num_same_shifts_week[w][s] = obj.current.num_same_shifts_week[w][s];
      }
      current.avail_day[w][d] = obj.current.avail_day[w][d];
      current.num_tasks_day[w][d] = obj.current.num_tasks_day[w][d];
    }
    current.num_tasks_week[w] = obj.current.num_tasks_week[w]; 
  } 

}

// /***************** Worker cost functions ************/
// int Worker::find_temp_costs(int w, int d, int s){
//   int cost1 = find_num_tasks_cost(w,d);
//   int cost2 = find_stand_in_cost(w,d);
//   int cost =  costs.weights[0]*cost1 + costs.weights[1]*cost2;

//   return cost;
// }

// int Worker::find_stand_in_cost(int w, int d){
//   return get_avail_day(w,d) - get_current_avail_day(w,d);
// }

// int Worker::find_num_tasks_cost(int w, int d){
//   int cost;
//   if (current.num_tasks_day[w][d] > MAX_TASKS_PER_DAY){
//     cost = current.num_tasks_day[w][d] - MAX_TASKS_PER_DAY;
//   }
//   else cost = 0;
//   return cost;
// }

/************** Worker functions: get **********/
int Worker::get_cost_sum(){
  return costs.cost_sum;
}

int Worker::get_HB_type(){
  if (identity.HB_type.find("standard_HB",0,11) == 0){
    return standard_HB;
  }
  else if (identity.HB_type.find("only_HB",0,7) == 0){
    return only_HB;
  }
  else if (identity.HB_type.find("no_HB",0,5) == 0){
    return no_HB;
  }
  else {
    cerr << "Error: in get_HB_type. No valid HB type found " << identity.HB_type << endl;
    return no_HB_type;
  }
}

int Worker::get_PL_type(){
  if (identity.PL_type.find("standard_PL",0,11) == 0){
    return standard_PL;
  }
  else if (identity.PL_type.find("many_PL",0,7) == 0){
    return many_PL;
  }
  else if (identity.PL_type.find("no_PL",0,5) == 0){
    return no_PL;
  }
  else {
    cerr << "Error: in get_PL_type. No valid PL type found " << identity.PL_type << endl;
    return no_PL_type;
  }
}

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
  else {
    cerr << "Error: in get_pos. No valid pos found" << endl;
    return no_position;
  }
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

int Worker::get_weekend_task_type(){
  return current.tasks[current.weekend-1][sat][0];
}

int Worker::get_cost_sum_no_stand_in(){
  int cost_sum=costs.cost_sum;
  for (int w=0; w<NUM_WEEKS; w++){ 
    for (int d=0; d<NUM_DAYS; d++){
      cost_sum -= costs.weights[1]*costs.stand_in_cost[w][d];
    }
  }
  return cost_sum;
}

int Worker::get_num_excess_tasks_week(){
  int excess_tasks=0;
  for (int w=0; w<NUM_WEEKS; w++){  
    excess_tasks += costs.num_tasks_week_cost[w];
  }
  return excess_tasks;
}

int Worker::get_num_excess_tasks_day(){
  int excess_tasks=0;
  for (int w=0; w<NUM_WEEKS; w++){  
    for (int d=0; d<NUM_DAYS; d++){
      excess_tasks += costs.num_tasks_day_cost[w][d];
    }
  }
  return excess_tasks;
}

int Worker::get_num_excess_PL(){
  return costs.PL_cost;
}

int Worker::get_num_excess_PL_week(){
  int excess_tasks=0;
  for (int w=0; w<NUM_WEEKS; w++){  
    excess_tasks += costs.PL_week_cost[w];
  }
  return excess_tasks;
}

int Worker::get_num_excess_same_shifts_week(){
  int excess_tasks=0;
  for (int w=0; w<NUM_WEEKS; w++){  
    for (int s=0; s<NUM_SHIFTS; s++){
      excess_tasks += costs.num_tasks_day_cost[w][s];
    }
  }
  return excess_tasks;
}

int Worker::get_worst_week(){
  //Reset cost sum
  int cost_sum[NUM_WEEKS]={0,0,0,0,0};
  int worst_week = 0;
  int worst_week_cost=0;

  //Find cost sum
  for (int w=0; w<NUM_WEEKS; w++){      
    for (int d=0; d<NUM_DAYS; d++){
      for (int s=0; s<NUM_SHIFTS; s++){
	cost_sum[w] += costs.total_cost[w][d][s];
	if(cost_sum[w] > worst_week_cost){
	  worst_week_cost = cost_sum[w];
	  worst_week = w;
	}
      }
    }
  }
  return worst_week;
}

/************** Worker functions: set **********/
void Worker::set_PL_costs(int w){
  //Set PL cost per week
  if(current.num_PL_week[w] > MAX_PL_PER_WEEK)
    costs.PL_week_cost[w] = current.num_PL_week[w]- MAX_PL_PER_WEEK;
  else costs.PL_week_cost[w] = 0;

  //Set total PL cost
  if(get_PL_type() == no_PL){
     costs.PL_cost = current.num_PL;
  }
  else if (get_PL_type() == standard_PL){
    if(current.num_PL > 1 + (MAX_PL_10W_STANDARD-1)/2)
      costs.PL_cost = current.num_PL - MAX_PL_10W_STANDARD;
    else costs.PL_cost = 0;
  }
  else if (get_PL_type() == many_PL){
    if(current.num_PL > 1 + (MAX_PL_10W_MANY-1)/2)
      costs.PL_cost = current.num_PL - MAX_PL_10W_MANY;
    else costs.PL_cost = 0;
  } 
}

void Worker::set_stand_in_cost(int w, int d){ 
  costs.stand_in_cost[w][d] = get_avail_day(w,d) - get_current_avail_day(w,d);
}

void Worker::set_num_tasks_costs(int w, int d){
  //Set num tasks costs per day
  if((d == fri && current.tasks[w][d][0] == BokB && current.tasks[w][d][3] != no_task)
     ||(current.tasks[w][d][0] == BokB && current.tasks[w][d][3] == BokB)){
    //Can have one extra task at friday evening if BokB in the morning
    if (current.num_tasks_day[w][d] > (MAX_TASKS_PER_DAY+1)){
      costs.num_tasks_day_cost[w][d] = current.num_tasks_day[w][d] - (MAX_TASKS_PER_DAY+1);
    }
    else costs.num_tasks_week_cost[w] = 0;
  }
  else if (current.num_tasks_day[w][d] > MAX_TASKS_PER_DAY ){
    costs.num_tasks_day_cost[w][d] = current.num_tasks_day[w][d] - MAX_TASKS_PER_DAY;
  }
  else costs.num_tasks_day_cost[w][d] = 0;

  //Set num tasks costs per week
  if (current.num_tasks_week[w] > MAX_TASKS_PER_WEEK  &&  get_ID() != 36){
    costs.num_tasks_week_cost[w] = current.num_tasks_week[w] - MAX_TASKS_PER_WEEK;
  }
  else costs.num_tasks_week_cost[w] = 0;
}

void Worker::set_num_same_shift_cost(int w, int s){
  //Set num same shift costs
  if(get_ID() == 36){
    costs.num_same_shifts_week_cost[w][s] = 0;
  }
  else if (current.num_same_shifts_week[w][s] > MAX_TASKS_SAME_SHIFT){
    costs.num_same_shifts_week_cost[w][s] = current.num_same_shifts_week[w][s] - MAX_TASKS_SAME_SHIFT;
  }
  else costs.num_same_shifts_week_cost[w][s] = 0;
}


void Worker::set_total_cost(int w, int d, int s){
  set_stand_in_cost(w,d);
  set_num_tasks_costs(w,d);
  set_PL_costs(w);
  set_num_same_shift_cost(w,s);

  costs.total_cost[w][d][s] =  
    //Hight prio
    costs.weights[0]*costs.num_tasks_day_cost[w][d]

    //Stand in (soft constraint)
    + costs.weights[1]*costs.stand_in_cost[w][d]

    //Mid prio
    + costs.weights[2]*costs.PL_week_cost[w]
    + costs.weights[3]*costs.PL_cost
    + costs.weights[4]*costs.num_tasks_week_cost[w]
    + costs.weights[5]*costs.num_same_shifts_week_cost[w][s]
    ;
}


void Worker::set_cost_sum(){
  //Reset cost sum
  costs.cost_sum=0;

  //Find cost sum
  for (int w=0; w<NUM_WEEKS; w++){      
    for (int d=0; d<NUM_DAYS; d++){
      for (int s=0; s<NUM_SHIFTS; s++){
	costs.cost_sum += costs.total_cost[w][d][s];
      }
    }
  }
}

//  void Worker::set_current_weekend(int wend){
//   if (identity.weekend.find("no_weekend",0,10) == 0){
//     cerr << "Error: cannot change weekend of non-weekend worker." << endl;
//   }
//   //If weekend is removed, set avail with no weekend rest
//   else if (wend == 0){
//     current.weekend = wend;
//   }
//   //If weekend is added, set avail with current rotation
//   else {
//     current.weekend = wend;
//     current.rotation = wend;

//     set_weekend_task(no_task);

//     //TODO: take tasks into consideration
//     reset_current_avail();
//     reset_current_avail_day();
//   }
// }

void Worker::set_current_weekend(int wend, int task){
  if (identity.weekend.find("no_weekend",0,10) == 0){
    cerr << "Error: cannot change weekend of non-weekend worker." << endl;
  }
  else {
    //Set weekend and rotation variables
    current.weekend = wend+1;
    current.rotation = wend+1;

    //Rotate avail - OBS: used when no tasks are distributed
    rotate_current_avail();
    rotate_current_avail_day();

    //Set weekend task
    set_weekend_task(task);
  }
}



void Worker::set_rotation(int rot){
  current.rotation = rot;
}

void Worker::set_task(int w,int d,int s,int task){
  //Add task, if not a task is already present
  if(get_current_task(w,d,s) == no_task){
    //Adjust number of tasks that day
    current.num_tasks_day[w][d]++;

    //Adjust number of weekday tasks that week
    if(d <= fri){
      current.num_tasks_week[w]++;
    }

    //Adjust number of PL that week
    if(task == PL){
      current.num_PL_week[w]++;
      current.num_PL++;
    }
    //Adjust number of tasks placed at the same shift a week
    if(d <= fri){
      current.num_same_shifts_week[w][s]++;
    }

    //1. Add task - before updating avail and cost!
    current.tasks[w][d][s] = task;

    //2. Set as unavailable
    set_current_avail(w,d,s);
    set_current_avail_day(w,d);

    //3. Set task costs
    set_total_cost(w,d,s);
    set_cost_sum();
  }
  else cerr << "Error: in set_task, week: "<< w << " day: " << d
  	    << " shift: " << s << ". Worker " << get_ID() << " already has a task." << endl;

}

void Worker::remove_task(int w, int d, int s){
  //Get task to be removed
  int task = current.tasks[w][d][s];

  //Remove task if task exists
  if(task != no_task){
    //Adjust num tasks that day
    current.num_tasks_day[w][d]--;

    //Adjust number of weekday tasks that week
    if(d <= fri){
      current.num_tasks_week[w]--;
    }

    //Adjust number of PL that week
    if(task == PL){
      current.num_PL_week[w]--;
      current.num_PL--;
    }

    //Adjust number of tasks placed at the same shift a week
    if(d <= fri){
      current.num_same_shifts_week[w][s]--;
    }

    //1. Remove task - before updating avail and cost!
    current.tasks[w][d][s] = no_task;

    //2. Set as available
    set_current_avail(w,d,s);
    set_current_avail_day(w,d);

    //3. Set task costs
    set_total_cost(w,d,s);
    set_cost_sum();
  }
}



void Worker::set_current_avail(int w, int d, int s){
  if (get_current_task(w,d,s) == no_task){
    current.avail[w][d][s] = identity.avail[current.rotation-1][w][d][s];
  }
 else {
      current.avail[w][d][s] = no_task;
  }
}

void Worker::rotate_current_avail(){
  for (int w=0; w<NUM_WEEKS; w++){      
    for (int d=0; d<NUM_DAYS; d++){
      for (int s=0; s<NUM_SHIFTS; s++){
	//Set current avail to new rotation of avail
	current.avail[w][d][s] = identity.avail[current.rotation-1][w][d][s];
      }
    }
  }
}


// void Worker::redistribute_tasks(){
  
// }

// void Worker::remove_weekrest_tasks(){
//   //int count=0;
//   for (int i=current.weekend-1; i<=current.weekend % NUM_WEEKS; i++){      
//     for (int j=0; j<NUM_DAYS; j++){
//       for (int k=0; k<NUM_SHIFTS; k++){
// 	//If there is a task placed but there is no availability, remove task
// 	//if (get_current_task(i,j,k) != no_task && identity.avail[current.rotation-1][i][j][k] == no_task){
// 	  set_task(i,j,k,no_task);
// 	  //count++;
// 	 //}
//       }
//     }
//   }
//   //cout << "Num of tasks removed at ID " << get_ID() << ": " << count << endl; 
// }

void Worker::set_current_avail_day(int w, int d){
  if(get_current_task(w,d,0) == no_task && get_current_task(w,d,1) == no_task 
     && get_current_task(w,d,2) == no_task && get_current_task(w,d,3) == no_task
     && get_avail_day(w, d) == 1){
    current.avail_day[w][d] = 1;
  }
  else current.avail_day[w][d] = 0;
}

void Worker::rotate_current_avail_day(){
  for (int w=0; w<NUM_WEEKS; w++){      
    for (int d=0; d<NUM_DAYS; d++){
      //Set current avail day to rotaion of avail day
      current.avail_day[w][d] = identity.avail_day[current.rotation-1][w][d];
    }
  }
}

void Worker::set_weekend_task(int task){

  //Saturday
  set_task(current.weekend-1, sat, 0, task);

  //Sunday
  set_task(current.weekend-1, sun, 0, task);

  //Friday
  if (task != HB || !no_friday_when_HB){
    set_task(current.weekend-1, fri, 3, task);
  }
}

void Worker::remove_weekend(){
  int task = current.tasks[current.weekend-1][sat][0];

  //Saturday
  remove_task(current.weekend-1, sat, 0);

  //Sunday
  remove_task(current.weekend-1, sun, 0);

  //Friday
  if (task != HB || !no_friday_when_HB){
    remove_task(current.weekend-1, fri, 3);
  }
}

void Worker::remove_week(int w){   
  for (int d=0; d<NUM_DAYS; d++){
    for (int s=0; s< NUM_SHIFTS; s++){
      remove_task(w,d,s);
    }
  }
}

bool Worker::has_weekend_task(){
  return (current.tasks[current.weekend-1][sat][0] != 0);
}

// void Worker::remove_week_rest(){
//   //Set a person avail as if there is no weekend rest
//   //TODO: 10 weeks, current.weekend + 2 % NUM_WEEKS
//   int first_week = 0;
//   int second_week = 0;

//   //For even weekends 2 and 4
//   if(current.weekend % 2){
//     first_week = 3;
//     second_week = 2;
//   }
//   //For odd weekends 1,3 and 5
//   else {
//     first_week = 2;
//     second_week = 3;
//   }

//   for (int j=0; j<NUM_DAYS; j++){
//     for (int k=0; k<NUM_SHIFTS; k++){
//       //Set weekend week
//       if(get_current_task(current.weekend-1,j,k) == no_task)
// 	current.avail[current.weekend-1][j][k] = identity.avail[0][first_week][j][k];
//       //Set weekrest week
//       if(get_current_task(current.weekend % NUM_WEEKS,j,k) == no_task)
// 	current.avail[current.weekend % NUM_WEEKS][j][k] = identity.avail[0][second_week][j][k];
//     }
//   }
// }


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

// Worker class

#include "WorkerClass.h"
#include "Constants.h"

using namespace std;


/************ Worker constructor ***********/

Worker::Worker(string pos, int ID, string name, string department, string weekend, string boss, string PL_type, string HB_type, string freeday, int worker_avail[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS]){

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

  //Set availability for all week rotations
  for (int h=0; h<NUM_ROTATIONS; h++){
    for (int i=0; i<NUM_WEEKS; i++){      
      for (int j=0; j<NUM_DAYS; j++){
	for (int k=0; k<NUM_SHIFTS; k++){
	  avail[h][i][j][k] = worker_avail[((NUM_WEEKS + i-h) % NUM_WEEKS)][j][k];
	}
      }
    }    
  }

    for (int i=0; i<NUM_WEEKS; i++){      
      for (int j=0; j<NUM_DAYS; j++){
    	for (int k=0; k<NUM_SHIFTS; k++){
    	  tasks[i][j][k] = 0;
    	}
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
  
  cout << "Worker copy constructor" << endl;

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

  for (int h=0; h<NUM_ROTATIONS; h++){
    for (int i=0; i< NUM_WEEKS; i++){
      for (int j=0; j<NUM_DAYS; j++){
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
      }
    }
  } 
  
}


/************** Worker functions: get **********/
int Worker::get_ID(){
  return identity.ID;
}

string Worker::get_pos(){
  return identity.pos;
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
}

void Worker::set_task(int w,int d,int s,int val){
  tasks[w][d][s] = val;
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
  cout << "Availability vector for worker " << get_ID() << endl;
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

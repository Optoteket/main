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

  if (identity.weekend.compare("weekend") != identity.weekend.npos){
    current.weekend = 1;
  }
  else current.weekend = 0;

  //Set availability
  int temp_avail[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
	avail[i][j][k] = worker_avail[i][j][k];
	temp_avail[i][j][k] = avail[i][j][k];
      }
    }
  }

  //avail_vector.push_back(temp_avail);

  // Set all other possible week rotations
  for(int h=0; h<NUM_ROTATIONS-1; h++){
    for (int i=0; i<NUM_WEEKS; i++){
      for (int j=0; j<NUM_DAYS; j++){
	for (int k=0; k<NUM_SHIFTS; k++){
	  temp_avail[((i+1) % NUM_WEEKS) + 1][j][k] = temp_avail[i][j][k];
	}
      }
    }
    //avail_vector.push_back(temp_avail);
  }

  display_avail_vector();

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

  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
	avail[i][j][k] = obj.avail[i][j][k];
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

int Worker::get_current_weekend(){
  return current.weekend;
}

int Worker::get_avail(int week, int day, int shift){
  return avail[week][day][shift];
}


/************** Worker functions: set **********/

void Worker::set_weekend(int wend){
  current.weekend = wend;
}

void Worker::set_avail(int week, int day, int shift, int value){
  avail[week][day][shift] = value;
}

/************* Worker function: shift avail ************/

/************* Worker functions: print ***********/

void Worker::print_avail(){
  cout << "Worker " << get_ID() << " availability:" << endl;
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for (int k=0; k< NUM_DAYS; k++){
	cout << avail[i][k][j] << " ";
      }
      cout << endl;
    }
    cout << endl << endl;
  }
}

void Worker::display_avail_vector(){
  cout << "Availability vector for worker" << get_ID() << endl;
  for (int l=0; l< NUM_ROTATIONS; l++){
    for (int i=0; i< NUM_WEEKS; i++){
      for (int j=0; j< NUM_SHIFTS; j++){
	for (int k=0; k< NUM_DAYS; k++){
	  cout << avail_vector[l][k][j][l] << " ";
	}
	cout << "   ";
      }
      cout << endl;
    }
    cout << endl << endl;
  }
}


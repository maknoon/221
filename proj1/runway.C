#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream> //for logging fxns
#include <unistd.h> //for sleep
#include "LQueue.h"
using namespace std;

/*** global objs ***/
ofstream outf("runway.log");

/*** macros ***/
//#define VIP 3

/*** in-suite functions ***/
// TODO should make this variadic lol
/*
 * @function: log
 * @usage: logging function; prints to outfile runway.log & cout
 * @params: string input, bool fromCL: if the string came from the commandline,
 *          bool lf: include a line feed at the end of the log
 * @returns: none
 */
void log(string input, bool lf=false, bool fromCL=false)
{
  if (fromCL) { outf << input << endl; return; }
  if (lf) { outf << input << endl; cout << input << endl; }
  else { outf << input; cout << input; }
}

/*
 * @function: int_to_string
 * @usage: converts inputted number into string format
 * @params: double input number
 * @returns: string format of input
 * notes: referenced http://stackoverflow.com/questions/5590381/
 */
string int_to_string(double input)
{
  stringstream ss;
  ss << input;
  return ss.str();
}

/*** main program starts here ***/
int main(void)
{
  // === VARIABLES === 
  // variable declarations for user inputs.
  // t = time, r = rate
  int t_land, t_takeOff, r_land, r_takeOff, t_total;
  int random1, random2;
  int c_land, c_takeOff; // c = counters
  int vip_value;
  
  // variable declarations for queue-related operations.
  Queue takeoff, landing, overflow;
  bool runway, priority_landing, priority_takeoff;
  
  // variable declarations for stats.
  // m = max num planes, tw = total wait time, total = total planes
  int m_takeoff = 0, m_landing = 0, m_priority = 0;
  double total_takeoff = 0.0, total_landing = 0.0;
  double tw_takeoff = 0.0, tw_landing = 0.0;
  double avg_takeoff = 0.0, avg_landing = 0.0;
  
  // seed random function w/ time
  srand(time(NULL));
      
  // === GET USER-INPUT ===
  log("Enter: ", true);
  log("   Time for a plane to land (in minutes): ");
  cin >> t_land; log(int_to_string(t_land), true, true);
  c_land = t_land + 1;
  log("   Time for a plane to takeOff (in minutes): ");
  cin >> t_takeOff; log(int_to_string(t_takeOff), true, true);
  c_takeOff = t_takeOff + 1;
  log("   Landing rate (planes per hour): ");
  cin >> r_land; log(int_to_string(r_land), true, true);
  log("   Takeoff rate (planes per hour): ");
  cin >> r_takeOff; log(int_to_string(r_takeOff), true, true);
  log("   How long to run the simulation (in minutes): ");
  cin >> t_total; log(int_to_string(t_total), true, true);
  log("   Set a VIP value (recommended < 3): ");
  cin >> vip_value; log(int_to_string(vip_value), true, true);
  log(" ", true); //endl
  
  // === START THE SIMULATION ===
  // (use giant for loop)
  for (int i = 1; i <= t_total; i++) {
    log("Time = "); log(int_to_string(i), true); //print time
    
    //--- (1) generate the two random plane numbers
    
    random1 = rand() % 60;
    random2 = rand() % 60;
    
    //--- check VIP status of the plane
    priority_landing = (random1 <= vip_value);
    priority_takeoff = (random2 <= vip_value);

    //--- (2) place planes in appropriate queues
    
    // populate landing queue
    if (random1 < r_land) {
      log("Plane "); log(int_to_string(696900+i));
      log(" wants to land; added to landing queue; ");
      landing.enqueue(i);
      
      // update all-time max queue size & print current queue size
      if (landing.size() > m_landing) m_landing = landing.size();
      log(int_to_string(landing.size())); log(" in queue", true);
      
      // give plane VIP status if it's special uw u
      if (priority_landing) {
	landing.move_to_front(i);
	log("Plane "); log(int_to_string(696900+i));
	log(" is a VIP plane and has been moved to the front!", true);
	m_priority++;
	priority_landing = !priority_landing;
      } else ;
      
      total_landing += 1.0; //inc all-time count of planes in queue
    }
    
    // populate takeoff queue
    if (random2 < r_takeOff) {
      log("Plane "); log(int_to_string(696900-i));
      if (takeoff.size() > 3) {
        log(" wants to takeoff but queue is packed; dispatching to overflow; ");
	overflow.enqueue(i);
      } else {
        log(" wants to takeoff; added to takeoff queue; ");
        takeoff.enqueue(i);
      }

      // update all-time max queue size & print current queue size
      if (takeoff.size() > m_takeoff) m_takeoff = takeoff.size();
      log(int_to_string(takeoff.size())); log(" in queue; ");
      log(int_to_string(overflow.size())); log(" in overflow queue", true);
      
      // give plane VIP status if it's special uw u
      if (priority_takeoff) {
        log("Plane "); log(int_to_string(696900-i));
	log(" is a VIP plane and has been moved to the front!", true);
	if (overflow.empty()) {
	  takeoff.move_to_front(i);
        } else {
	  overflow.move_to_front(i);
	  overflow.dequeue();
	  takeoff.enqueue(i);
	  takeoff.move_to_front(i);
	}
	m_priority++;
	priority_takeoff = !priority_takeoff;
      } else ;
      
      total_takeoff += 1.0; //inc all-time count of planes in queue
    }
    
    //--- (3) RUNWAY LOGIC
    
    // runway is only free if no planes need to land or takeoff
    // i.e. if any of the counts are not decremented to 1, the runway is busy
    runway = (c_land == 1 && c_takeOff == 1);
    
    //--- (4) check if runway has traffic
    
    if (!runway) {
      // prioritize the landing queue & dispatch landing plane
      // ensure that there isn't a plane already taking off
      if (!landing.empty() && c_takeOff == t_takeOff + 1) {
        if (c_land == t_land + 1) {
          log("Landing: Plane ");
	  log(int_to_string(696900+landing.front()), true);
        }
        c_land--;
      }
      // otherwise, dispatch plane to takeoff
      else if (!takeoff.empty()) {
	if (c_takeOff == t_takeOff + 1) { 
          log("Landing: Plane ");
	  log(int_to_string(696900-takeoff.front()), true);
        }
        c_takeOff--;
      }
    }
    
    // add to total wait time by checking size of queue-1
    if (!landing.empty()) {
      if (c_land == t_land + 1) tw_landing += (double)landing.size();
      else tw_landing += (double)(landing.size() - 1);
    }
    if (!takeoff.empty()) {
      if (c_takeOff == t_takeOff + 1) tw_takeoff += (double)(takeoff.size() + overflow.size());
      else tw_takeoff += (double)(takeoff.size() + overflow.size() - 1);
    }
    
    // if plane has completed its landing, dequeue it
    if (c_land == 1) {
      landing.dequeue();
      log("Landing complete; "); 
      log(int_to_string(landing.size())); log(" in queue", true);
      c_land = t_land + 1; //reset the count
    }
    // if plane has completed its takeoff, dequeue it
    if (c_takeOff == 1) {
      takeoff.dequeue();
      log("Takeoff complete; ");
      log(int_to_string(takeoff.size())); log(" in queue; ");
      log(int_to_string(overflow.size())); log(" in overflow queue", true);
      c_takeOff = t_takeOff + 1; //reset the count
    }
    
    // if there is room in takeoff, merge the overflow queue in
    if (takeoff.size() <= 3 && !overflow.empty()) {
      takeoff.merge_two_queues(overflow);
      log("Takeoff traffic subsiding; merging overflow into the takeoff queue", true);
      while (!overflow.empty()) overflow.dequeue();
    }

    // wait a second; make it easier to read
    sleep(1);
  }
  
  // === CLEAN UP ===
  while (!takeoff.empty()) takeoff.dequeue();
  while (!landing.empty()) landing.dequeue();
  
  // === PRINT SUMMARY ===
  // calculate avg time waiting from (total wait time / total planes in queue)
  avg_landing = (total_landing != 0.0) ? (tw_landing / total_landing) : 0;
  avg_takeoff = (total_takeoff != 0.0) ? (tw_takeoff / total_takeoff) : 0;

  log(" ", true); log("STATISTICS", true); log(" ", true);
  log("Maximum number of planes in landing queue was: "); 
  log(int_to_string(m_landing), true);
  log("Average minutes spent waiting to land: ");
  log(int_to_string(avg_landing), true);
  log("Maximum number of planes in takeoff queue was: ");
  log(int_to_string(m_takeoff), true);
  log("Average minutes spent waiting to takeoff: "); 
  log(int_to_string(avg_takeoff), true);
  log("Total number of planes given priority was: ");
  log(int_to_string(m_priority), true);
  cout << endl;

  return 0;
}

#include <stdio.h>
#include <sys/types.h>

typedef struct {

  pid_t id; // Process id to represent it in /proc filesystem 
  char *cmdline; // cmdline from which process is executed
  uid_t uid;   // this helps in restart with the same user
  int isRunning;   // is process running check it in proc directory
  


}PROCESS_INFO;

typedef struct {
  
  PROCESS_INFO* info;
  PROCESS_INFO *next;

}PROCESS_QUEUE; 


/* Get process info by supplying process id */

PROCESS_INFO* getProcessInfobyPid ( pid_t pid );

/* Manage a queue for Processes to manage */

void add_to_queue(PROCESS_INFO*, PROCESS_QUEUE*);


/* Monitor queue every 5 seconds and this is the function
 * that will run as daemon on the server */

void monitor_queue( PROCESS_QUEUE* queue );

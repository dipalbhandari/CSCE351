#include <semaphore.h>
#define monitor_h



typedef struct
{
  int numThreadBlocked;
  sem_t threadBlocked;

}cond;

extern void monitor();
extern int count(cond cv);
extern void wait(cond cv);
extern void signal(cond cv);
extern void mon_checkCustomer();
extern int mon_checkStylist();
extern void mon_debugPrint ();


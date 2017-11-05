#include "Problem.hpp"
#include "Schedule.hpp"

#include "test/testProblem.hpp"
#include "test/testSchedule.hpp"

int main(int argc, char** argv){
  if (argc==1) return 1;
  else {
    Problem test(argv[1]);
    printProblem(test);
    Schedule sch(test);    
    printSchedule(sch);
    Schedule::mutationRange=1.8;
    Schedule::localPoolSize=1000;
    for (int gen=0; gen<10; gen++) {
      sch.mutate();
      printSchedule(sch);
    }
  }
}

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
  }
}

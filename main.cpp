#include "Problem.hpp"


#include "test/testProblem.hpp"

int main(int argc, char** argv){
  if (argc==1) return 1;
  else {
    Problem test(argv[1]);
    printProblem(test);
  }
}

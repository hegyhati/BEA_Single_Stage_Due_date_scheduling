#include "../Problem.hpp"

#include <iostream>
#include <iomanip>
using namespace std;

void printProblem (const Problem& problem){
  cout<<setw(4)<<"Job";
  cout<<"|";
  cout<<setw(9)<<"Deadline";
  cout<<"|";  
  for (int u=0; u<problem.getUnitCount(); u++)
    cout<<setw(6)<<u<<"|";
  for (int j=0; j<problem.getJobCount(); j++) {
    cout<<"\n----+---------+";
    for (int u=0; u<problem.getUnitCount(); u++)
      cout<<"------+";
    cout<<"\n";
    cout<<setw(4)<<j;
    cout<<"|";
    cout<<setw(9)<<problem.getDeadline(j);
    cout<<"|";  
    for (int u=0; u<problem.getUnitCount(); u++)
      cout<<setw(6)<<problem.getProcTime(j,u)<<"|";
  }
  cout<<"\n";
}

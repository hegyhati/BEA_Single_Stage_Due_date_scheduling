#include "Problem.hpp"

#include <fstream>

Problem::Problem(std::string filename){
  std::ifstream inputfile (filename.c_str());
  if (inputfile.is_open()) {
    inputfile>>nJobs;
    inputfile>>nUnits;
    
    deadline = new double[nJobs];
    procTime = new double*[nJobs];
    
    for (int j=0; j<nJobs; j++){
      inputfile>>deadline[j];
      procTime[j]=new double[nUnits];
      for (int u=0; u<nUnits; u++)
        inputfile>>procTime[j][u];
    }
  } else {
    nJobs=nUnits=0;
    deadline=NULL;
    procTime=NULL;
  }
}

Problem::~Problem(){
  if (nJobs){
    delete [] deadline;
    for (int j=0; j<nJobs; j++)
      delete [] procTime[j];
    delete [] procTime;
  }
}

int Problem::getJobCount() const {return nJobs;}
int Problem::getUnitCount() const {return nUnits;}
double Problem::getProcTime(int job, int unit) const {return procTime[job%nJobs][unit%nUnits];}
double Problem::getDeadline(int job) const {return deadline[job%nJobs];}

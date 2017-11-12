#include "Problem.hpp"

#include <fstream>
#include <limits>

Problem::Problem(std::string filename, ObjectiveFunction obj): objFunct(obj){
  std::ifstream inputfile (filename.c_str());
  if (inputfile.is_open()) {
    inputfile>>nJobs;
    inputfile>>nUnits;
    
    deadline = new double[nJobs];
    procTime = new double*[nJobs];
    setupTime = new double*[nJobs];
    
    for (unsigned int j=0; j<nJobs; j++){
      inputfile>>deadline[j];
      procTime[j]=new double[nUnits];
      for (unsigned int u=0; u<nUnits; u++)
        inputfile>>procTime[j][u];
    }
    for (unsigned int j=0; j<nJobs; j++){
      setupTime[j]=new double[nJobs];
      for (unsigned int k=0; k<nJobs; k++){
        double setup;
        inputfile>>setup;
        if(setup<0) setupTime[j][k]=std::numeric_limits<double>::infinity();
        else setupTime[j][k]=setup;
      }
    }
  } else {
    nJobs=nUnits=0;
    deadline=NULL;
    procTime=NULL;
    setupTime=NULL;
  }
}

Problem::~Problem(){
  if (nJobs){
    delete [] deadline;
    for (unsigned int j=0; j<nJobs; j++)
      delete [] procTime[j];
    delete [] procTime;
  }
}

unsigned int Problem::getJobCount() const {return nJobs;}
unsigned int Problem::getUnitCount() const {return nUnits;}
double Problem::getProcTime(int job, int unit) const {return procTime[job%nJobs][unit%nUnits];}

double Problem::getSetupTime(int job1, int job2) const {return setupTime[job1%nJobs][job2%nJobs];}
double Problem::getDeadline(int job) const {return deadline[job%nJobs];}

Problem::ObjectiveFunction Problem::getObjective() const {return objFunct;}

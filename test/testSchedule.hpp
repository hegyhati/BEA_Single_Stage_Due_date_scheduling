#ifndef TEST_SCHEDULE_HPP
  #define TEST_SCHEDULE_HPP

  #include "../Schedule.hpp"

  #include <iostream>
  #include <map>
  using namespace std;

  void printSchedule(const Schedule& schedule){  
    map <int,map<double,int>> prodlist;
    for(int j=0;j<schedule.problem->getJobCount(); j++)
      prodlist[(int) schedule.getPriority(j)][schedule.getPriority(j)] = j;
    for(const auto& itu : prodlist){
      cout<<"U"<<itu.first<<":";
      for (const auto& itj : prodlist[itu.first])
        cout<<" "<<itj.second<<"("<<itj.first<<")";
      cout<<"\n";
    }
    cout<<"Lateness: "<<schedule.getTotalLateness()<<"\n";
  }

#endif

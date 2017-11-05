#include "BEA.hpp"

#include <random>


int BEA::populationSize=100;
int BEA::bestKeepCount=40;
int BEA::crossoverCount=15;
int BEA::newCount=20;

BEA::BEA(const Problem& problem, int size) : problem(problem){
  populationSize=size;
  std::list<Schedule> tmp;
  for(int p=0; p<size; p++) tmp.push_back(Schedule(problem));
  for(auto it: tmp) {
    it.mutate();
    population.insert( std::pair<double,Schedule>(it.getTotalLateness(),it));
  }  
}

std::list<double> BEA::getCurrentValues() const {
  std::list<double> toReturn;
  for(auto it: population) toReturn.push_back(it.first);
  return toReturn;
}

double BEA::getCurrentBestValue() const {return population.begin()->first;}
Schedule BEA::getCurrentBestSolution() const {return population.begin()->second;}


double BEA::evolve(){
  double oldbest=getCurrentBestValue();
  std::map<double,Schedule> next_population;
  
  // Mutate old ones
  for(auto it: population) {
    it.second.mutate();
    next_population.insert(std::pair<double,Schedule>(it.second.getTotalLateness(),it.second));
  }
  
  // Insert new random ones mutated
  std::list<Schedule> tmp_new;
  for(int p=0; p<newCount; p++) tmp_new.push_back(Schedule(problem));
  for(auto it: tmp_new) {
    it.mutate();
    next_population.insert( std::pair<double,Schedule>(it.getTotalLateness(),it));
  }  
  
  // Do some crossovers
  std::list<Schedule> tmp_crossover;
  int parent1,parent2;
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_int_distribution<int> uniform_dist(0,next_population.size()-1);
  std::map<double,Schedule>::iterator it1,it2;
  
  for(int p=0; p<crossoverCount; p++) {
    for(it1=next_population.begin(),parent1=uniform_dist(e);parent1;parent1--) it1++;
    for(it2=next_population.begin(),parent2=uniform_dist(e);parent2;parent2--) it2++;
    tmp_crossover.push_back((it1->second)&&(it2->second));
  }
  
  for(auto it: tmp_crossover) {
    it.mutate();
    next_population.insert( std::pair<double,Schedule>(it.getTotalLateness(),it));
  }  
  
  
  //Elitism  
  population.clear();  
  int toSelect=populationSize;
  int remaining=next_population.size(); 
  double multiplier = (double) (populationSize-bestKeepCount) / (populationSize+newCount+crossoverCount-bestKeepCount);
  std::uniform_int_distribution<int> uniform_dist_2(0,remaining);
  for(auto it=next_population.begin();toSelect;it++,remaining--){
    if (toSelect>=populationSize-bestKeepCount || toSelect==remaining 
      || uniform_dist_2(e) < toSelect * multiplier) {     
      population.insert(std::pair<double,Schedule>(it->first,it->second));
      toSelect--;      
    }
  }  
  return getCurrentBestValue()-oldbest;
}

//////////////////////////////////////
//FuzzyDT implementation 
//////////////////////////////////////

#ifndef FUZZY_DT_H
#define FUZZY_DT_H

#include "image.h"
#include <queue>
#include "mex.h"
#include <vector>
#include <math.h>
using namespace std;

class Qelem{
 public:
  double value;
  long index;

  Qelem(long i, double v){value=v; index=i;}
};

class ElemComparison{
 public:
   bool operator() (const Qelem& lhs, const Qelem&rhs) const{
    return lhs.value>rhs.value;
  } 
};

typedef priority_queue<Qelem, vector<Qelem>, ElemComparison> Pq;

void FuzzyDT(imagetype seeds, imagetype labels, imagetype cost, double* dt, double *segmentation){

  int nelem = seeds.getNelem();

  bool* inQ=new bool[nelem];

  Pq Q;

  for(int i=0; i< nelem; i++ ){
    dt[i]=10000000; //INF
    inQ[i]=false;
    segmentation[i]=labels[i];

    if(seeds[i]>0){
      dt[i]=0;
      Q.push(Qelem(i,0));
      inQ[i]=true;
    }
  }

  int ni;
  double fval;

  vector<int> neighbors;

  while(!Q.empty()){
    Qelem e =Q.top();
    Q.pop();
    
    if(inQ[e.index]){
      inQ[e.index]=false;
     
      seeds.get_6_neighbors(e.index, neighbors);
      
      for(int i=0; i<neighbors.size(); i++){
	ni=neighbors[i];
	
	fval= fval=dt[e.index]+0.5*abs(double(cost[ni])+double(cost[e.index]));
	 
	if(fval<dt[ni] || (fval==dt[ni] && segmentation[e.index]<segmentation[ni])){
	  dt[ni]=fval;
	  segmentation[ni]=segmentation[e.index];
	  Q.push(Qelem(ni,fval));
	  inQ[ni]=true;
	  
	}
      }
    }
  }
  delete[] inQ;
}

#endif

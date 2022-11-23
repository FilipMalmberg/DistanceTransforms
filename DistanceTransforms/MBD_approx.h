//////////////////////////////////////
//Approximate MBD implementation 
//////////////////////////////////////

#ifndef MBD_APPROX_H
#define MBD_APPROX_H

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

void MBD_approx(imagetype seeds, imagetype labels, imagetype cost, double* dt, double *segmentation){

  int nelem = seeds.getNelem();

  bool* inQ=new bool[nelem];
  uint8* dtmin=new uint8[nelem];
  uint8* dtmax=new uint8[nelem];

  Pq Q;

  for(int i=0; i< nelem; i++ ){
    dt[i]=255; //INF
    dtmin[i]=cost[i];
    dtmax[i]=cost[i];
    inQ[i]=false;
    segmentation[i]=labels[i];

    if(seeds[i]>0){
      dt[i]=0;
      Q.push(Qelem(i,0));
      inQ[i]=true;
    }
  }

  int ni;
  double fval,minVal,maxVal;

  vector<int> neighbors;

  while(!Q.empty()){
    Qelem e =Q.top();
    Q.pop();
    
    if(inQ[e.index]){
      inQ[e.index]=false;
     
      seeds.get_6_neighbors(e.index, neighbors);
      
      for(int i=0; i<neighbors.size(); i++){
	ni=neighbors[i];
	
	minVal=min(dtmin[e.index],cost[ni]);
	maxVal=max(dtmax[e.index],cost[ni]);
	fval=(maxVal-minVal);
	 
	if(fval<dt[ni] || (fval==dt[ni] && segmentation[e.index]<segmentation[ni]) ){
	  dt[ni]=fval;
	  dtmin[ni]=minVal;
	  dtmax[ni]=maxVal;
	  segmentation[ni]=segmentation[e.index];
	  Q.push(Qelem(ni,fval));
	  inQ[ni]=true;
	  
	}
      }
    }
  }
  delete[] inQ;
  delete[] dtmin;
  delete[] dtmax;
}

#endif

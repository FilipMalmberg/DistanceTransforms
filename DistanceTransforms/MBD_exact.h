//////////////////////////////////////
//Exact MBD implementation 
//////////////////////////////////////

#ifndef MBD_EXACT_H
#define MBD_EXACT_H

#include "image.h"
#include <queue>
#include "mex.h"
#include <vector>
#include <math.h>
using namespace std;

class Qelem{
 public:
  double maxvalue;
  double minvalue;
  long index;

  Qelem(long i, double min, double max){maxvalue=max; minvalue=min; index=i;}
};

class ElemComparison{
 public:
   bool operator() (const Qelem& lhs, const Qelem&rhs) const{
     if(lhs.maxvalue==rhs.maxvalue){
       return lhs.minvalue<rhs.minvalue;
     }
     return lhs.maxvalue>rhs.maxvalue;
  } 
};

typedef priority_queue<Qelem, vector<Qelem>, ElemComparison> Pq;

void MBD_exact(imagetype seeds, imagetype labels, imagetype cost, double* dt, double *segmentation){

  int nelem = seeds.getNelem();

  bool* inQ=new bool[nelem];
  int* dtmin=new int[nelem];
  int* dtmax=new int[nelem];
  double* minseg=new double[nelem];

  Pq Q;

  for(int i=0; i< nelem; i++ ){
    dt[i]=256; //INF
    dtmin[i]=-1;
    dtmax[i]=256;
    inQ[i]=false;
    segmentation[i]=labels[i];
    minseg[i]=labels[i];
    if(seeds[i]>0){
      dt[i]=0;
      dtmin[i]=cost[i];
      dtmax[i]=cost[i];
      Q.push(Qelem(i,cost[i],cost[i]));
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
	
	minVal=min(dtmin[e.index],int(cost[ni]));
	maxVal=max(dtmax[e.index],int(cost[ni]));
	 
	if(minVal>dtmin[ni] || (minVal==dtmin[ni] && minseg[e.index]<minseg[ni]) ){
	  dtmin[ni]=minVal;
	  dtmax[ni]=maxVal;
	  minseg[ni]=minseg[e.index];

	  if(maxVal-minVal <dt[ni] || ( maxVal-minVal == dt[ni] && minseg[e.index]< minseg[ni] ) ){
	    dt[ni]=maxVal-minVal;
	    segmentation[ni]=minseg[ni]; 
	  }

	  Q.push(Qelem(ni,minVal,maxVal));
	  inQ[ni]=true;
	  
	}
      }
    }
  }
  delete[] inQ;
  delete[] dtmin;
  delete[] dtmax;
  delete[] minseg;
}

#endif

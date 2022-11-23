////////////////////////////////////////////////////////////
//Image:
//  A wrapper class for easier handling of 2D and 3D image data 
//  represented as a 1D array. (with MATLAB-style indexing).
////////////////////////////////////////////////////////////


#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
using namespace std;

template <class T> 
class image{
 private:
  T *data; 
  int x_size;
  int y_size;
  int z_size;
  int nelem;
  
  
  
 public:
  image(T* d,int x, int y, int z=1){
    data = d;
    z_size=z;
    x_size=x;
    y_size=y;
    nelem=x*y*z;
  }

  image<T> getCopy(){
    int x=this->x_size;
    int y=this->y_size;
    int z=this->z_size;
    T *d=new T[this->nelem];
    for(int j=0; j<this->nelem; j++){
     d[j]=this->data[j];
    }
    return image(d,x,y,z);
  }

  int getNelem() const{
    return nelem;
  }
  
  int getXsize() const{
    return x_size;
  }

  int getYsize() const{
    return y_size;
  }

  int getZsize() const{
    return z_size;
  }
  
  int xyz2index(int x, int y, int z){
     return(x_size*y_size*z + y_size*x + y);
  }
  
  int index2x(int i){
    return (i%(x_size*y_size))/y_size; 
  }

  int index2y(int i){
    return (i%(x_size*y_size))%y_size;  
  }

  int index2z(int i){
    return i/(x_size*y_size); 
  }

  int xy2index(int x, int y){
    return(xyz2index(x,y,0)); 
  }
  
  bool valid(int i){
    return(i>=0 && i<nelem);
  }
  
  bool valid(int x, int y, int z=0){
    return(x>=0 && x<x_size && y>=0 && y<y_size && z>=0 && z<z_size);
  }
  
  T& operator()(int x, int y, int z=0){
    return data[xyz2index(x,y,z)];
  }
  
  T& operator[](int i){
    return data[i];
  }

   vector<int> get_4_neighbors(int x, int y){
    vector<int> result;
    if(valid(x+1,y)){
      result.push_back(xy2index(x+1,y));
    }
    if(valid(x-1,y)){
      result.push_back(xy2index(x-1,y));
    }
    if(valid(x,y+1)){
      result.push_back(xy2index(x,y+1));
    }
    if(valid(x,y-1)){
      result.push_back(xy2index(x,y-1));
    }
    return result;
  }

  vector<int> get_4_neighbors(int i){
    return get_4_neighbors(index2x(i), index2y(i));
  }

    vector<int> get_8_neighbors(int x, int y){
    vector<int> result;
    if(valid(x+1,y)){
      result.push_back(xy2index(x+1,y));
    }
    if(valid(x-1,y)){
      result.push_back(xy2index(x-1,y));
    }
    if(valid(x,y+1)){
      result.push_back(xy2index(x,y+1));
    }
    if(valid(x,y-1)){
      result.push_back(xy2index(x,y-1));
    }
    if(valid(x-1,y-1)){
      result.push_back(xy2index(x-1,y-1));
    }
    if(valid(x-1,y+1)){
      result.push_back(xy2index(x-1,y+1));
    }
    if(valid(x+1,y+1)){
      result.push_back(xy2index(x+1,y+1));
    }
    if(valid(x+1,y-1)){
      result.push_back(xy2index(x+1,y-1));
    }

    return result;
  }

  vector<int> get_8_neighbors(int i){
    return get_8_neighbors(index2x(i), index2y(i));
  }

  
  void get_6_neighbors(int x, int y, int z, vector<int>& n){
    n.clear();
    if(valid(x+1,y,z)){
      n.push_back(xyz2index(x+1,y,z));
    }
    if(valid(x-1,y,z)){
      n.push_back(xyz2index(x-1,y,z));
    }
    if(valid(x,y+1,z)){
      n.push_back(xyz2index(x,y+1,z));
    }
    if(valid(x,y-1,z)){
      n.push_back(xyz2index(x,y-1,z));
    }
    if(valid(x,y,z-1)){
      n.push_back(xyz2index(x,y,z-1));
    }
    if(valid(x,y,z+1)){
      n.push_back(xyz2index(x,y,z+1));
    }
  }

  void get_6_neighbors(int i, vector<int>& n){
    get_6_neighbors(index2x(i), index2y(i), index2z(i),n);
  }


  vector<int> get_18_neighbors(int x, int y, int z){
    vector<int> result;
    if(valid(x+1,y,z)){
      result.push_back(xyz2index(x+1,y,z));
    }    
    if(valid(x-1,y,z)){
      result.push_back(xyz2index(x-1,y,z));
    }
    if(valid(x,y+1,z)){
      result.push_back(xyz2index(x,y+1,z));
    }
    if(valid(x,y-1,z)){
      result.push_back(xyz2index(x,y-1,z));
    }
    if(valid(x,y,z-1)){
      result.push_back(xyz2index(x,y,z-1));
    }
    if(valid(x,y,z+1)){
      result.push_back(xyz2index(x,y,z+1));
    }
    if(valid(x+1,y+1,z)){
      result.push_back(xyz2index(x+1,y+1,z));
    }
    if(valid(x+1,y-1,z)){
      result.push_back(xyz2index(x+1,y-1,z));
    }
    if(valid(x+1,y,z+1)){
      result.push_back(xyz2index(x+1,y,z+1));
    }
    if(valid(x+1,y,z-1)){
      result.push_back(xyz2index(x+1,y,z-1));
    }
    if(valid(x-1,y+1,z)){
      result.push_back(xyz2index(x-1,y+1,z));
    }
    if(valid(x-1,y-1,z)){
      result.push_back(xyz2index(x-1,y-1,z));
    }
    if(valid(x-1,y,z+1)){
      result.push_back(xyz2index(x-1,y,z+1));
    }
    if(valid(x-1,y,z-1)){
      result.push_back(xyz2index(x-1,y,z-1));
    }
    if(valid(x,y+1,z+1)){
      result.push_back(xyz2index(x,y+1,z+1));
    }
    if(valid(x,y+1,z-1)){
      result.push_back(xyz2index(x,y+1,z-1));
    }
    if(valid(x,y-1,z+1)){
      result.push_back(xyz2index(x,y-1,z+1));
    }
    if(valid(x,y-1,z-1)){
      result.push_back(xyz2index(x,y-1,z-1));
    }
    return result;
  }
  
  vector<int> get_18_neighbors(int i){
    return get_18_neighbors(index2x(i), index2y(i), index2z(i));
  }

  vector<int> get_26_neighbors(int x, int y, int z){
    vector<int> result;
    for(int i=-1; i<2; i++){
      for(int j=-1; j<2; j++){
	for(int k=-1; k<2; k++){
	  if(valid(x+i,y+j,z+k) && !(i==0 && j==0 && k==0)){
	    result.push_back(xyz2index(x+i,y+j,z+k));
	  }
	}
      }
    }
    return result;
  }

  vector<int> get_26_neighbors(int i){
    return get_26_neighbors(index2x(i), index2y(i), index2z(i));
  }

  vector<int> getRneighbors(int x, int y, int z, int r){
    vector<int> result;
    for(int i=-1; i<r; i++){
      for(int j=-1; j<r; j++){
	for(int k=-1; k<r; k++){
	  if(valid(x+i,y+j,z+k) && !(i==0 && j==0 && k==0)){
	    result.push_back(xyz2index(x+i,y+j,z+k));
	  }
	}
      }
    }
    return result;
  }

  vector<int> getRneighbors(int i, int r){
    return getRneighbors(index2x(i), index2y(i), index2z(i),r);
  }


  
};

#endif

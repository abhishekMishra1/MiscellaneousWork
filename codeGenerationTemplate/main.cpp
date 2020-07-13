#include"generator.hpp"
#include<iostream>
using namespace std;

int main(int argc, char *argv[]){
  if(argc>1){
    const string flnm = argv[1];
    Generator gen(flnm);
    gen.parseFileName();
    gen.startPrinting();
  }
  else
    cout<<"Please provide file name also\n";
  return 0;
}
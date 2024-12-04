#include "concat_files.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> readlines(const string& fname) {

  vector<string> lines;
  //ifstream inFS;
  //inFS.open(fname);
  ifstream inFS(fname); //both do the same thing.



  if(!inFS.is_open()){
    cout<< "Could not open file: " << fname << endl;

    return lines;

  }

  string line; //creating a temporary variable to store each line in
  
  while (getline(inFS, line)){ //
    lines.push_back(line);
  }
  
  inFS.close();

  return lines;
}



void concatFiles(const string& in_fname, const string& out_fname) {
  // TODO student
  //Use a range based for loop here 

  vector<string> fileNames = readlines(in_fname); //Understand this line

  ofstream outFS(out_fname);
  
  if(!outFS.is_open()){
    cout << "Error: could not open output file " << out_fname << endl;
    return ;
  }

  //This is the range based for loop 

  for(const string& fileName /*for each element*/ : fileNames){

    ifstream inFS(fileName);
    
    if(!inFS.is_open()){
      cout << "Error: could not open this file: " << fileName << endl;
      continue; //skip this file and continue with the rest
    }

    string line;
    while(getline(inFS, line)){
      outFS << line << endl;
    }

    inFS.close();

  }

  outFS.close();


}

int main() {
  // TODO student: Add manual testing code, if desired
  return 0;
}

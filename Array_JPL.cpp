#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {

//user input
  string boarding;
  string destination;
  cout<<"Enter boarding point"<<endl;
  cin>>boarding;
  cout<<"Enter destination"<<endl;
  cin>>destination;

 

//Reading input from file and storing it in array
  ifstream inputfile("database.csv"); 
  string stop;
  string line;
  int row=0,col=0,r=1;

  while (inputfile.peek() != EOF) {
    getline(inputfile, line, '\n');
    row=0;
    stringstream s(line);
    while (getline(s, stop, ',')) {
      row++;
      if(r<row){
        r=row;
      }
    }
    col++;
 }
  
  //cout << r << endl <<col;
  string arr[r][col];
  row=0;
  col=0;
  //cout << "array created";

  inputfile.close();

  //Reopen file to print array
  ifstream in("database.csv");
  
  while (in.peek() != EOF) {
    getline(in, line, '\n');
    row=0;
    stringstream s(line);
    while (getline(s, stop, ',')) {
      arr[row][col]=stop;
      cout << arr[row][col]<<" ";
      row++;
    
    }
    cout << endl;
    col++;
 }
  cout<<"\n"<<r<<col<<row;
  // remember r= columns, col= rows
  return 0;
}
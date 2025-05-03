// Chanco, Malubag, Villanueva
// 3 BS Computer Engineering

// ENGG 151.01
// Project 3: Linear Time-Invariant System Simulator

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

#include "Chanco-Malubag-Villanueva_Project-3_Function.h"

using namespace std;

int main(int argc, char *argv[])
{
  //append mode
  fstream in;
  in.open("ltisim-log.txt", ios::app);
  if(!in)
    in.open("ltisim-log.txt");
  else
  {
    in << "String_fstream";
    cout << "Data appended successfully\n";
    in.close();
    string word;
    in.open("ltisim-log.txt");
    while(in >> word)
      cout << word << " ";
    in.close();
  }
}
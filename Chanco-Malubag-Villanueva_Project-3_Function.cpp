// Chanco, Malubag, Villanueva
// 3 BS Computer Engineering

// ENGG 151.01
// Project 3: Linear Time-Invariant System Simulator

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>

#include "Chanco-Malubag-Villanueva_Project-3_Function.h"

using namespace std;

void compute_outputs(double * acoef, double * bcoef, 
                     double * inputs, double * outputs, int sizea, int sizeb,
                     double * input_samples, int nSamples,
                     double ** output_samples)
{
  
}

double * extractSystem (string filename, int &duration)
{
  ifstream f(filename);

  if(f.good() && f.is_open())
  {
    string line;
    stringstream s;

    vector<double> v;

    double number;
    double * system;

    bool firstLine = true;
    bool secondLine = false;

    duration = 0;
    int nNonRecursiveCoefs = 0;
    int nRecursiveCoefs = 0;

    cout << "\n" << filename << " accessed!\n";

    while(getline(f,line))
    {
      s << line;

      if(firstLine)
      {
        s >> nNonRecursiveCoefs;
        cout << nNonRecursiveCoefs << endl;

        int M = nNonRecursiveCoefs - 1;

        secondLine = true;
      }
      if(secondLine)
      {
        firstLine = false;
        
        s >> nRecursiveCoefs;
        cout << nRecursiveCoefs << endl; 

        int N = nRecursiveCoefs;
      }
      else
      {
        duration++;

        while(s >> number)
        {
          cout << number << endl;

          v.push_back(number);
        }

        s.clear();
      }

      //reset all
      s.clear();
      number = 0;
      line.clear();
      secondLine = false;
    }

    //putting into array
    if(v.size() !=0)
    {
      int j = 0;

      system = new double [duration];

      for(int i=0; i<duration; i++)
      {
        system[i] = v[j];
        j++;
      }

      return system;
    }
    else
    {
      cout << "\n" << filename << " is empty" << endl;
      return NULL;
    }
  }
  else
  {
    cout << "\nERROR: File \"" << filename << "\" cannot be accessed.\n";
    return NULL;
  }
}
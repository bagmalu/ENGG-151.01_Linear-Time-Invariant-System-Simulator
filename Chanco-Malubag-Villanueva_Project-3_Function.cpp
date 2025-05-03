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

double * extractSystem(string filename)
{
  ifstream f(filename);

  if(f.good() && f.is_open())
  {
    string line;
    stringstream s;
    vector<double> v;
    double num;
    int duration;
    int nNonRecursiveCoefs = 0;
    int nRecursiveCoefs = 0;

    while(getline(f,line))
    {
      s << line;

      s >> nNonRecursiveCoefs;
      s >> nRecursiveCoefs;

      while(s >> num) v.push_back(num);

      s.clear();
      num = 0.0;
      line.clear();
    }

    double * acoef = new double[nNonRecursiveCoefs];
    double * bcoef = new double[nRecursiveCoefs];

    if(v.size() !=0)
    {
      int j = 0;

      double * inputs = new double[duration];

      for(int i=0; i<duration; i++)
      {
        inputs[i] = v[j];
        j++;
      }

      return inputs;
    }
    else
    {
      cout << "\nERROR: File \"" << filename << "\" is empty.\n";
      return NULL;
    }
  }
  else
  {
    cout << "\nERROR: File \"" << filename << "\" cannot be accessed.\n";
    return NULL;
  }
}
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

double * extractSystem (string filename, int &nNonRecursiveCoefs, int &nRecursiveCoefs, double * &acoef, double * &bcoef)
{
  ifstream f(filename);

  if(f.good() && f.is_open())
  {
    string line;
    stringstream s;

    vector<double> v;

    double coef;

    nNonRecursiveCoefs = 0;
    nRecursiveCoefs = 0;

    //first line
    if(getline(f,line))
    {
      stringstream s(line);
      s >> nNonRecursiveCoefs;
    }

    //second line
    if(getline(f,line))
    {
      stringstream s(line);
      s >> nRecursiveCoefs;
    }

    while(getline(f,line))
    {
      stringstream s(line);
      while(s >> coef)
        v.push_back(coef);
    }

    //putting into array
    if(v.size() != 0)
    {
      acoef = new double[nRecursiveCoefs];
      bcoef = new double[nNonRecursiveCoefs];

      for(int i=0; i<nNonRecursiveCoefs; i++)
        bcoef[i] = v[i];

      for(int i=0; i<nRecursiveCoefs; i++)
        acoef[i] = v[nNonRecursiveCoefs+i];
      
      return NULL;;
    }
    else
    {
      cout << "\nERROR: \"" << filename << "\" is empty\n";
      return NULL;
    }
  }
  else
  {
    cout << "\nERROR: \"" << filename << "\" cannot be accessed.\n";
    return NULL;
  }
}
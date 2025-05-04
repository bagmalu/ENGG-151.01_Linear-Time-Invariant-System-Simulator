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
                     double * output_samples)
{
  //general input-output relationship for LTI systems formula
  for(int n=0; n<nSamples; n++)
  {
    double yn = 0.0;

    for(int i=0; i<sizeb; i++)
    {
      if(n-i >= 0)
        yn += bcoef[i] * input_samples[n-i];
    }


    for(int j=1; j<=sizea; j++)
    {
      if(n-j >= 0)
        yn -= acoef[j-1] * output_samples[n-j];
    }

    output_samples[n] = yn;
  }
}

double * extractSystem (string filename, int &nNonRecursiveCoefs, int &nRecursiveCoefs, double * &acoef, double * &bcoef)
{
  ifstream f(filename);

  if(f.good() && f.is_open())
  {
    string line;
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

      return NULL;
    }
    else
    {
      cout << "\nERROR: \"" << filename << "\" is empty\n";
      return nullptr;
    }
  }
  else
  {
    cout << "\nERROR: \"" << filename << "\" cannot be accessed.\n";
    return nullptr;
  }
}

double * extractSignal (string filename, int &n, int &nSamples, double * &input_samples)
{
  ifstream f(filename);

  if(f.good())
  {
    string line;
    vector<double> v;
    double number;

    nSamples = 0;
    n = 0;

    if(getline(f,line))
    {
      stringstream s(line); 

      if(!(s >> n))
      {
        s.clear();
        s.str(line);

        while(s >> number)
        {
          v.push_back(number); 
          nSamples++;
        }
      }
      else 
      {
        while(s >> number)
        {
          v.push_back(number); 
          nSamples++;
        }
      }
    }

    while(getline(f,line))
    {
      stringstream s(line); 

      while(s >> number)
      {
        v.push_back(number); 
        nSamples++; 
      }
    }

    //putting into array
    if(v.size() !=0)
    {
      input_samples = new double [nSamples];

      for(int i=0; i<nSamples; i++)
        input_samples[i] = v[i];
      
      return NULL;
    }
    else
    {
      cout << "\nERROR: \"" << filename << "\" is empty" << endl;
      return nullptr;
    }
  }
  cout << "\nERROR: \"" << filename << "\" not accessible" << endl;
  return nullptr;
}
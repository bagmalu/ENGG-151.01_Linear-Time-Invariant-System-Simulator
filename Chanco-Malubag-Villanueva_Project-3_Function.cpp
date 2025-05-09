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

void compute_outputs(double* acoef, double* bcoef, double* inputs, double* outputs,
                     int nRecursiveCoefs, int nNonRecursiveCoefs,
                     double* input_samples, int nSamples, double* output_samples)
{
    // Initialize inputs and outputs to zero
    for (int i = 0; i < nNonRecursiveCoefs; i++) {
        inputs[i] = 0.0;
    }
    for (int i = 0; i < nRecursiveCoefs; i++) {
        outputs[i] = 0.0;
    }
    // Compute outputs for each sample
    for (int n = 0; n < nSamples; n++) {
        // Shift inputs
        for (int i = nNonRecursiveCoefs - 1; i > 0; i--) {
            inputs[i] = inputs[i - 1];
        }
        inputs[0] = input_samples[n];

        // Compute current output
        output_samples[n] = 0.0;
        for (int i = 0; i < nNonRecursiveCoefs; i++) {
            output_samples[n] += bcoef[i] * inputs[i];
        }
        for (int i = 0; i < nRecursiveCoefs; i++) {
            output_samples[n] -= acoef[i] * outputs[i];
        }

        // Shift outputs
        for (int i = nRecursiveCoefs - 1; i > 0; i--) {
            outputs[i] = outputs[i - 1];
        }
        outputs[0] = output_samples[n];
    }
}

double *extractSystem(string filename, int &nNonRecursiveCoefs, int &nRecursiveCoefs, double *&acoef, double *&bcoef)
{
  ifstream f(filename);

  if (f.good() && f.is_open())
  {
    string line;
    vector<double> v;
    double coef;

    nNonRecursiveCoefs = 0;
    nRecursiveCoefs = 0;

    if (getline(f, line))
    {
      stringstream s(line);
      s >> nNonRecursiveCoefs;
    }

    if (getline(f, line))
    {
      stringstream s(line);
      s >> nRecursiveCoefs;
    }

    while (getline(f, line))
    {
      stringstream s(line);
      while (s >> coef)
        v.push_back(coef);
    }

    if (v.size() != 0)
    {
      acoef = new double[nRecursiveCoefs];
      bcoef = new double[nNonRecursiveCoefs];

      for (int i = 0; i < nNonRecursiveCoefs; i++)
        bcoef[i] = v[i];

      for (int i = 0; i < nRecursiveCoefs; i++)
        acoef[i] = v[nNonRecursiveCoefs + i];

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

double *extractSignal(string filename, int &n, int &nSamples, double *&input_samples)
{
  ifstream f(filename);

  if (f.good())
  {
    string line;
    vector<double> v;
    double number;

    nSamples = 0;
    n = 0;

    if (getline(f, line))
    {
      stringstream s(line);

      if (!(s >> n))
      {
        s.clear();
        s.str(line);

        while (s >> number)
        {
          v.push_back(number);
          nSamples++;
        }
      }
      else
      {
        while (s >> number)
        {
          v.push_back(number);
          nSamples++;
        }
      }
    }

    while (getline(f, line))
    {
      stringstream s(line);

      while (s >> number)
      {
        v.push_back(number);
        nSamples++;
      }
    }

    if (v.size() != 0)
    {
      input_samples = new double[nSamples];

      for (int i = 0; i < nSamples; i++)
        input_samples[i] = v[i];

      return input_samples;
    }
    else
    {
      cout << "\nERROR: \"" << filename << "\" is empty" << endl;
      return NULL;
    }
  }

  cout << "\nERROR: \"" << filename << "\" not accessible" << endl;
  return NULL;
}

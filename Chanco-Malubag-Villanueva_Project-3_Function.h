// Chanco, Malubag, Villanueva
// 3 BS Computer Engineering

// ENGG 151.01
// Project 3: Linear Time-Invariant System Simulator

#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void compute_outputs(double * acoef, double * bcoef,
                     double * inputs, double * outputs, int sizea, int sizeb,
                     double * input_samples, int nSamples,
                     double * output_samples);

double * extractSystem (string filename, int &nNonRecursiveCoefs,
         int &nRecursiveCoefs, double * &acoef, double * &bcoef);

double * extractSignal (string filename, int &n, int &nSamples,
                        double * &input_samples);

#endif // FUNCTION_H

// Chanco, Malubag, Villanueva
// 3 BS Computer Engineering

// ENGG 151.01
// Project 3: Linear Time-Invariant System Simulator

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

#include "Chanco-Malubag-Villanueva_Project-3_Function.h"

using namespace std;

int main(int argc, char *argv[])
{
  cout << "\nLinear Time-Invariant System Simulator"
  << "\nType \"help\" for more information." << endl;

  ofstream logFile("ltisim-log.txt", ios::app);
  if (!logFile.is_open())
  {
    cout << "\nERROR: Unable to open log file \"ltisim-log.txt\" for logging.\n";
  }

  string userInput, command, filename;
  double next_input;

  int nNonRecursiveCoefs = 0, nRecursiveCoefs = 0;
  double *acoef = NULL;
  double *bcoef = NULL;

  int n = 0, nSamples = 0;
  double *inputs = NULL;
  double *outputs = NULL;

  double *input_samples = NULL;
  double *output_samples = NULL;

  while (true)
  {
    cout << "\nltisim> ";
    getline(cin, userInput);
    transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);

    stringstream ss(userInput);

    if (userInput.empty())
    {
      cout << "\nERROR: No command has been specified.\n";
    }
    else if (ss >> next_input)
    {
      if (ss.eof())
      {
        if (acoef == NULL || bcoef == NULL)
        {
          cout << "\nERROR: No LTI system has been defined yet.\n";
        }
        else
        {
          double temp_input[1] = {next_input};
          double temp_output[1];

          compute_outputs(acoef, bcoef, inputs, outputs,
                        nRecursiveCoefs, nNonRecursiveCoefs,
                        temp_input, 1, temp_output);

          cout << " \t" << temp_output[0] << endl;

          if (logFile.is_open())
          {
            logFile << next_input << "\t" << temp_output[0] << endl;
          }
        }
      }
        else
        {
          cout << "\nERROR: Floating point number contains extra characters.\n";
        }
        }
    else
    {
      ss.clear();
      ss.str(userInput);

      if (ss >> command)
      {
        if (command == "help")
        {
        cout << "\nCommands:\n"
        << "  help               - displays this message\n"
        << "  system <filename>  - extracts input coefficients from a file \n"
        << "  <number>           - inputs number to the system\n"
        << "  signal <filename>  - extracts an input signal from a file\n"
        << "  clear              - clears all memory and restarts simulation\n"
        << "  exit               - terminates the program\n";
        }
        else if (command == "system")
        {
          if (!(ss >> filename))
          cout << "\nERROR: No filename has been specified.\n";
          else
          {
            if (extractSystem(filename, nNonRecursiveCoefs,
            nRecursiveCoefs, acoef, bcoef) == NULL)
            {
              cout << "\nSystem obtained from \"" << filename << "\"."
              << " recursive coefs: " << nRecursiveCoefs << ","
              << " nonrecursive coefs: " << nNonRecursiveCoefs << endl;

              if (logFile.is_open())
              {
                logFile << "\nnew system\n";
                logFile << nNonRecursiveCoefs << endl;
                logFile << nRecursiveCoefs << endl;
                for (int i = 0; i < nNonRecursiveCoefs; i++) {
                  logFile << bcoef[i] << endl;
                }
                for (int i = 0; i < nRecursiveCoefs; i++) {
                  logFile << acoef[i] << endl;
                }
                logFile << "ready\n\n";
              }

              delete[] inputs;
              delete[] outputs;
              delete[] input_samples;
              delete[] output_samples;
              inputs = new double[nNonRecursiveCoefs]();
              outputs = new double[nRecursiveCoefs]();
             }
          }
        }
        else if (command == "signal")
        {
          if (!(ss >> filename))
          cout << "\nERROR: No filename has been specified.\n";
          else if (acoef == NULL || bcoef == NULL)
          cout << "\nERROR: No LTI system has been defined yet.\n";
          else if (extractSignal(filename, n, nSamples, input_samples) != NULL)
          {
            cout << "\nSignal obtained from \"" << filename << "\"."
            << " start index: " << n << ","
            << " duration: " << nSamples << endl;

            if (output_samples != NULL) delete[] output_samples;
              output_samples = new double[nSamples];
              compute_outputs(acoef, bcoef, inputs, outputs,
              nRecursiveCoefs, nNonRecursiveCoefs,
              input_samples, nSamples, output_samples);

            if (logFile.is_open())
            {
              for (int i = 0; i < nSamples; i++)
              {
                logFile << input_samples[i] << "\t" << output_samples[i] << endl;
              }
            }

            if (nSamples < 10)
              for (int i = 0; i < nSamples; i++)
              cout << input_samples[i] << "\t" << output_samples[i] << endl;
          }
        }
        else if (command == "clear")
        {
          delete[] acoef;
          delete[] bcoef;
          delete[] inputs;
          delete[] outputs;
          delete[] input_samples;
          delete[] output_samples;

          next_input = 0.0;
          nNonRecursiveCoefs = 0;
          nRecursiveCoefs = 0;
          n = 0;
          nSamples = 0;

          cout << "\nAll memory has been cleared.\n";
        }
        else if (command == "exit")
        {
          cout << "\nProgram has been terminated.\n";
          logFile.close();
          return 0;
        }
        else
        {
          cout << "\nERROR: Command \"" << command << "\" does not exist.\n";
        }
      }
    }
  }
}

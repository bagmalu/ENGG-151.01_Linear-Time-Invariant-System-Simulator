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

  //log file, append mode
  ofstream logfile;
  logfile.open("ltisim-log.txt", ios::app);

  if(!logfile) //file does not exist
    logfile.open("ltisim-log.txt");
    
  if(!logfile.is_open()) //file cannot be opened
    cout << "ERROR: Unable to open ltisim-log.txt for appending." << endl;

  //if need to append smtg, use: logfile << entry << endl; (parang cout lang)

  //program loop
  string userInput, command, filename;
  double next_input;

  int nNonRecursiveCoefs, nRecursiveCoefs;
  double * acoef = NULL;
  double * bcoef = NULL;

  int n = 0;
  int nSamples = 0;
  double * inputs = NULL;
  double * outputs = NULL;
  
  // double * input_samples;
  // double ** output_samples;

  while(1)
  {
    //prompt for user inputs
    cout << "\nltisim> ";
    getline(cin, userInput);

    //converts all userInput characters to lowercase
    transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
    
    stringstream ss(userInput);

    //if input is empty
    if(userInput.empty())
      cout << "\nERROR: No command has been specified.\n";

    //if input is any floating point number
    else if(ss >> next_input) 
    {
      if(ss.eof())
      {
        if(acoef == NULL || bcoef == NULL)
        {
          cout << "\nERROR: No LTI system has been defined yet.\n";
        }
        else
        {
          //number is treated as next input to the system
          
          //insert compute_outputs() here

          // cout << inputs[i] << "\t" << outputs[i] << endl;
          // logfile << inputs[i] << "\t" << outputs[i] << endl;
        }
      }
      else
        cout << "\nERROR: Floating point number contains extra characters.\n";
    }

    //if input is any string
    else
    {
      ss.clear();
      ss.str(userInput);

      if(ss >> command) 
      {
        if(command == "help")
        {
          cout << "\nCommands:\n"
               << "  help               - displays this message\n"
               << "  system <filename>  - extracts input coefficients from a file \n"
               << "  <number>           - inputs number to the system\n"
               << "  signal <filename>  - extracts an input signal from a file\n"
               << "  clear              - clears all memory and restarts simulation\n"  
               << "  exit               - terminates the program\n";
        }
        else if(command == "system")
        {
          if(!(ss >> filename)) 
            cout << "\nERROR: No filename has been specified.\n"; 
          else
          {
            if(extractSystem (filename, nNonRecursiveCoefs, nRecursiveCoefs, acoef, bcoef) == NULL)
            {
              logfile << "\nnew system\n" << endl;
              for(int i=0; i<nNonRecursiveCoefs; i++)
                logfile << "b(" << i << ") = " << bcoef[i] << endl;
              for(int i=0; i<nRecursiveCoefs; i++)
                logfile << "a(" << i+1 << ") = " << acoef[i] << endl;
              logfile << "\nready\n";

              cout << "\nSystem obtained from \"" << filename << "\"."
                   << " recursive coefs: " << nRecursiveCoefs << ","
                   << " nonrecursive coefs: " << nNonRecursiveCoefs << endl;

              //clear initial conditions to 0.0
            }
          }
        }
        else if(command == "signal")
        {
          if(!(ss >> filename)) 
            cout << "\nERROR: No filename has been specified.\n"; 
          else
          {
            if(acoef == NULL || bcoef == NULL)
            {
              cout << "\nERROR: No LTI system has been defined yet.\n";
            }
            else if(extractSignal (filename, n, nSamples, inputs) != NULL)
            {
              cout << "\nSignal obtained from \"" << filename << "\"."
                   << " start index: " << n << ","
                   << " duration: " << nSamples << endl;

              //inputted signal serves as input to LTI system, one sample at a time
              //starting index is ignored

              compute_outputs(acoef, bcoef, inputs, outputs, nNonRecursiveCoefs, nRecursiveCoefs, inputs, nSamples, outputs);

              if(nSamples > 10)
              {
                for(int i=0; i<nSamples; i++)
                {
                  cout << inputs[i] << "\t" << outputs[i] << endl;
                  logfile << inputs[i] << "\t" << outputs[i] << endl;
                }
              }
              //else cout & logfile << summary of the number of inputs simulated << endl;
            }
          }
        }
        else if(command == "clear")
        {
          //clears all inputs and outputs to 0
          //restarts simulation
          //does NOT clear the screen

          delete[] acoef;
          delete[] bcoef;
          delete[] inputs;
          delete[] outputs;

          next_input = 0.0;
          nNonRecursiveCoefs = 0;
          nRecursiveCoefs = 0;
          n = 0;
          nSamples = 0;

          logfile << "\ncleared\n";
          cout << "\nAll memory has been cleared.\n";
        }
        else if(command == "exit")
        {
          cout << "\nProgram has been terminated.\n";
          return(0);
        }
        else cout << "\nERROR: Command \"" << command << "\" does not exist.\n";
      }
    }
  }
}
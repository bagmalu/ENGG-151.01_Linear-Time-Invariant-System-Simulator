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

  //just made these based on void in function.cpp
  // int sizea, sizeb, nSamples;
  // double * acoef = new double[sizea];
  // double * bcoef = new double[sizeb];
  // double * inputs = new double[nSamples];
  // double * outputs = new double[nSamples];
  // double * input_samples = new double[nSamples];
  // double * output_samples = new double[nSamples];

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
        //number is treated as next input to the system
        //next output is computed

        cout << "output" << endl;
        logfile << "input \toutput" << endl;

        //cout << "ERROR: No LTI system has been defined yet." << endl;
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
          //extract coefficients from filename
          
          if(!(ss >> filename)) 
            cout << "\nERROR: No filename has been specified.\n"; 
          else
          {
            ifstream systemFile;
            systemFile.open(filename);

            if(!systemFile.is_open() || !systemFile.good()) 
              cout << "\nERROR: File \"" << filename << "\" cannot be accessed.\n";
          }

          //if new lti system is valid
          logfile << "new system" << endl;

          //for each component: logfile << components << endl;
          //logfile << "ready" << endl;
          //clear initial conditions to 0.0
        }
        else if(command == "signal")
        {
          cout << "\n*extract signal from filename*\n";
          //inputted signal serves as input to LTI system, one sample at a time
          //starting index is ignored
          //logfile << "input \toutput" << endl;
          //if(duration < 10) cout << "input \toutput" << endl;
          //else cout << summary of the number of inputs simulated << endl;
          
          if(!(ss >> filename)) 
            cout << "\nERROR: No filename has been specified.\n"; 
          else
          {
            ifstream signalFile;
            signalFile.open(filename);

            if(!signalFile.is_open() || !signalFile.good()) 
              cout << "\nERROR: File \"" << filename << "\" cannot be accessed.\n";
          }
        }
        else if(command == "clear")
        {
          //clears all inputs and outputs to 0
          //restarts simulation
          //does NOT clear the screen

          //idk if this syntax is allowed
          // delete[] acoef;
          // delete[] bcoef;
          // delete[] inputs;
          // delete[] outputs;
          // delete[] input_samples;
          // delete[] output_samples;
          // sizea = sizeb = nSamples = 0;

          logfile << "cleared" << endl;
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
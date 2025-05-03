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

  while(1)
  {
    cout << "\nltisim> ";
    getline(cin, userInput);
    
    stringstream ss(userInput);

    //FIX: input validation (it accepts 123.45asdf67 as 123.45)
    if(ss >> next_input) //if input is any floating point number
    {
      cout << "\nNumber is treated as next input to the system\n";
      //next output is computed
      //cout << output << endl;
      //logfile << "next_input \toutput" << endl;
      //cout << "ERROR: No LTI system has been defined yet." << endl;
    } 

    else
    {
      ss.clear();
      ss.str(userInput);

      if(ss >> command) //if input is any string
      {
        if(command == "help")
        {
          cout << "\nProgram instructions\n";
        }

        else if(command == "system")
        {
          cout << "\nExtract coefficients from filename\n";
          //extract function
          //logfile << "new system" << endl;
          //for each component: logfile << components << endl;
          //logfile << "ready" << endl;
          //clear initial conditions to 0.0

          ss >> filename; 
          cout << filename << endl;

          ifstream systemFile;
          systemFile.open(filename);

          if(!systemFile.is_open() || !systemFile.good()) cout << "\nERROR: File \"" << filename << "\" cannot be accessed.\n";
        }

        else if(command == "signal")
        {
          cout << "\nExtract signal from filename\n";
          //inputted signal serves as input to LTI system, one sample at a time
          //starting index is ignored
          //logfile << "input \toutput" << endl;
          //if(duration < 10) cout << "input \toutput" << endl;
          //else cout << summary of the number of inputs simulated << endl;
          
          ss >> filename; 
          cout << filename << endl;

          ifstream signalFile;
          signalFile.open(filename);

          if(!signalFile.is_open() || !signalFile.good()) cout << "\nERROR: File \"" << filename << "\" cannot be accessed.\n";
        }
        
        else if(command == "exit")
        {
          cout << "\nProgram is terminated.\n";
          return(0);
        }

        else cout << "\nCommand \"" << command << "\" does not exist.\n";
      }
    }
  }
}
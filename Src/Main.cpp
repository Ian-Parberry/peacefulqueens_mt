/// \file Main.cpp
/// \brief Code for the function main().

// MIT License
//
// Copyright (c) 2022 Ian Parberry
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <cinttypes>
#include <iostream>
#include <fstream>

#include "Timer.h"
#include "Backtrack.h"

/// \brief Main.
///
/// Main.
/// \return 0 (What could possibly go wrong?)

int main(){
  std::ofstream output("Output.txt");
  output << "<center>" << std::endl;
  output << "<table>" << std::endl;
  output << "<tr>" << "<th>n</th>"  << "<th>Solutions</th>" <<
    "<th>CPU Time</th>" << "<th>Elapsed Time</th>" << std::endl;

  CTimer* pTimer = new CTimer; //timer for elapsed and CPU time
  
  for(size_t n=2; n<=4; n++){
    CBacktrack* pBacktracker = new CBacktrack(n); //backtracker
    std::cout << "Board size " << n << std::endl;

    pTimer->Start(); //start timing CPU and elapsed time
    std::cout << "Starting at " << pTimer->GetTimeAndDate() << std::endl;

    const uint64_t nCount = pBacktracker->Backtrack(); //backtrack
    const std::string strCount(CommaSeparatedString(nCount));
  
    std::cout << "Finishing at " << pTimer->GetTimeAndDate() << std::endl;
    std::cout << "Elapsed time " << pTimer->GetElapsedTime() << std::endl;
    std::cout << "CPU time " << pTimer->GetCPUTime() << std::endl;
  
    std::cout << pBacktracker->GetNumTasks() << " tasks processed by " <<
      pBacktracker->GetNumThreads() << " threads" << std::endl;
    std::cout << "Number of solutions " << strCount << std::endl;
    std::cout << std::endl;

    output << "<tr>";
    output << "<td>" << n << "</td><td>" << strCount << "</td><td>" <<
      pTimer->GetCPUTime() << "</td><td>" << pTimer->GetElapsedTime() <<
      "</td>" << std::endl;
  
    delete pBacktracker;
  } //for
  
  output << "</table>" << std::endl;
  output << "</center>" << std::endl;

  //clean up and exit

  delete pTimer;
  return 0;
} //main

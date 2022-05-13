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

#include "Timer.h"
#include "Backtrack.h"

/// \brief Main.
///
/// Main.
/// \return 0 (What could possibly go wrong?)

int main(){
  const size_t n = 14; //width and height of the chessboard

  CBacktrack* pBacktracker = new CBacktrack(n); //backtracker
  CTimer* pTimer = new CTimer; //timer for elapsed and CPU time

  pTimer->Start(); //start timing CPU and elapsed time
  std::cout << "Starting at " << pTimer->GetCurrentDateAndTime() << std::endl;

  uint64_t nCount = pBacktracker->Backtrack(); //backtrack
  
  std::cout << "Finishing at " << pTimer->GetCurrentDateAndTime() << std::endl;
  std::cout << "Elapsed time " << pTimer->GetElapsedTime() << std::endl;
  std::cout << "CPU time " << pTimer->GetCPUTime() << std::endl;
  
  std::cout << pBacktracker->GetNumTasks() << " tasks processed" << std::endl;
  std::cout << "Board size " << n << std::endl;
  std::cout << "Number of solutions " << nCount << std::endl;
  
  //clean up and exit
  
  delete pTimer;
  delete pBacktracker;

  return 0;
} //main

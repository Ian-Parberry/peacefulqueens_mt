/// \file CMain.cpp
/// \brief Code for the class CMain.

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

#include "Backtrack.h"

#include "Task.h"

/// The constructor. Reserve space for the permutation, diagonal,
/// and back-diagonal arrays. Initialize the permutation array to the identity
/// permutation. Initialize the diagonal and back-diagonal arrays to all
/// `true`, indicating that all diagonals and back-diagonals are initially
/// not occupied by a queen. Create a thread manager.
/// \param n Size (width and height) of chessboard.

CBacktrack::CBacktrack(const size_t n):
  m_nSize(n),
  m_nDiagonalSize(2*n - 1)
{
  m_nPerm = new size_t[m_nSize];
  m_bBackDiagonal = new bool[m_nDiagonalSize]; 
  m_bDiagonal = new bool[m_nDiagonalSize]; 
  
  for(size_t i=0; i<m_nSize; i++)
    m_nPerm[i] = i;
  
  for(size_t i=0; i<m_nDiagonalSize; i++)
    m_bBackDiagonal[i] = m_bDiagonal[i] = true;

  m_pThreadManager = new CThreadManager;
} //constructor

/// Destructor. Delete arrays and objects created by constructor.

CBacktrack::~CBacktrack(){
  delete m_pThreadManager;

  delete [] m_bDiagonal;
  delete [] m_bBackDiagonal;
  delete [] m_nPerm;
} //destructor

/// Create and assign a task to finish off a partial solution.
/// \param m Start index in permutation.

void CBacktrack::CreateTask(const size_t m){
  CTask* pTask = new CTask(m_nSize);
  
  pTask->SetPerm(m_nPerm); 
  pTask->SetDiagonal(m_bDiagonal); 
  pTask->SetBackDiagonal(m_bBackDiagonal); 
  pTask->SetStartIndex(m); 

  m_pThreadManager->Insert(pTask);
  m_nNumTasks++;
} //CreateTask

/// Backtrack over the tail of the permutation.
/// \param m The last index filled in.
/// \param nTail The size of the tail to be filled in here.

void CBacktrack::Backtrack(const size_t m, const size_t nTail){
  if(m == nTail) //base of recursion, meaning that the tail has been filled in
    CreateTask(m); //create a task for the threads to perform

  else{ 
    for(int i=0; i<m; i++){
      const size_t j = m - 1; //largest index to swap
      const size_t k = j - i; //smallest index to swap
      const size_t dx = m_nPerm[k] + j; //diagonal index
      const size_t bx = m_nPerm[k] - m + m_nSize; //back-diagonal index

      if(m_bBackDiagonal[bx] && m_bDiagonal[dx]){ //diagonal & back-diagonal unused      
        if((m != m_nSize && (!(m_nSize & 1) || m != m_nSize - 1 || 
          m_nPerm[m] != m_nSize/2)) || m_nPerm[k] >= m_nSize/2)
        {
           std::swap(m_nPerm[j], m_nPerm[k]); //permute

           m_bBackDiagonal[bx] = m_bDiagonal[dx] = false; //mark back-diagonal and diagonal used
           Backtrack(j, nTail); //recurse on smaller array
           m_bBackDiagonal[bx] = m_bDiagonal[dx] = true; //mark back-diagonal and diagonal unused

           std::swap(m_nPerm[j], m_nPerm[k]); //unpermute
        } //if
      } //if
    } //for
  } //else
} //Backtrack

/// Backtrack for Peaceful Queens solutions. Create initial configurations,
/// spawn threads, wait until all threads have terminated, then process the
/// resulting Peaceful Queens solutions.
/// \return The number of Peaceful Queens solutions found.

uint64_t CBacktrack::Backtrack(){
  if(m_nSize < 4)return 0; //bail and fail

  const size_t nTail = 2; //number of entries in suffix
  const size_t n = (m_nSize < nTail)? m_nSize: m_nSize - nTail;

  Backtrack(m_nSize, n);
  
  m_pThreadManager->Spawn(); //spawn threads
  m_pThreadManager->Wait(); //wait for threads to finish
  m_pThreadManager->Process(); //process the results

  return m_pThreadManager->GetCount(); //get the result and return it
} //Backtrack

/// Reader function for the number of tasks completed.
/// \return Number of tasks completed.

const size_t CBacktrack::GetNumTasks() const{
  return m_nNumTasks;
} //GetNumTasks

/// Reader function for the number of threads used by this application.
/// Assumes that the thread manager has been created and initialized. 
/// \return Number of threads used.

const size_t CBacktrack::GetNumThreads() const{
  return m_pThreadManager->GetNumThreads();
} //GetNumThreads
/// \file Task.cpp
/// \brief Code for the class CTask.

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

#include <algorithm>

#include "Task.h"

/// The constructor. Reserve space for the permutation, diagonal,
/// and back-diagonal arrays. Initialize the permutation array to the identity
/// permutation. Initialize the diagonal and back-diagonal arrays to all
/// `true`, indicating that all diagonals and back-diagonals are initially
/// not occupied by a queen.
/// \param n Size (width and height) of chessboard.

CTask::CTask(const size_t n):
  m_nSize(n), m_nDiagonalSize(2*n - 1), CBaseTask()
{
  m_nPerm = new size_t[m_nSize];
  m_bBackDiagonal = new bool[m_nDiagonalSize]; 
  m_bDiagonal = new bool[m_nDiagonalSize]; 
  
  for(size_t i=0; i<m_nSize; i++)
    m_nPerm[i] = i;
  
  for(size_t i=0; i<m_nDiagonalSize; i++)
    m_bBackDiagonal[i] = m_bDiagonal[i] = true;
} //constructor

/// Destructor. Delete memory created by constructor.

CTask::~CTask(){
  delete [] m_bDiagonal;
  delete [] m_bBackDiagonal;
  delete [] m_nPerm;
} //destructor

/// Perform this task, that is, start backtracking.

void CTask::Perform(){ 
  Backtrack(m_nStartIndex);
} //Perform

/// Recursively backtrack for the Peaceful Queens problem. Exhaustively search
/// through permutations to avoid row and column conflicts, pruning using a
/// pair of arrays to detect diagonal and back-diagonal conflicts. Keep track
/// of the number of solutions found. 
/// \param m Previous array element.

void CTask::Backtrack(const size_t m){
  if(m == 0)m_nCount++; else{ 
    for(size_t i=0; i<m; i++){
      const size_t j = m - 1; //first element to swap in permutation
      const size_t k = j - i; //second element to swap in permutation
      const size_t dx = m_nPerm[k] + j; //diagonal index
      const size_t bx = m_nPerm[k] - m + m_nSize; //back-diagonal index

      if(m_bBackDiagonal[bx] && m_bDiagonal[dx]){ //diagonal & back-diagonal unused
        std::swap(m_nPerm[j], m_nPerm[k]); //permute

        m_bBackDiagonal[bx] = m_bDiagonal[dx] = false; //mark back-diagonal and diagonal used
        Backtrack(j); //recurse on smaller array
        m_bBackDiagonal[bx] = m_bDiagonal[dx] = true; //mark back-diagonal and diagonal unused

        std::swap(m_nPerm[j], m_nPerm[k]); //unpermute
      } //if
    } //for
  } //else
} //Backtrack

/// Reader function for the count member variable.
/// \return m_nCount.

const uint64_t CTask::GetCount() const{
  return m_nCount;
} //GetCount

/// Set permutation. Assumes that the permutation array has been created and
/// has size `m_nSize`.
/// \param p New permutation.

void CTask::SetPerm(size_t* p){
  for(size_t i=0; i<m_nSize; i++)
    m_nPerm[i] = p[i];
} //SetPerm

/// Set diagonal array. Assumes that the diagonal array has been created and
/// has size `m_nDiagonalSize`.
/// \param p New diagonal array values.

void CTask::SetDiagonal(bool* p){
  for(size_t i=0; i<m_nDiagonalSize; i++)
    m_bDiagonal[i] = p[i];
} //SetDiagonal

/// Set back-diagonal. Assumes that the back-diagonal array has been created
/// and has size `m_nDiagonalSize`.
/// \param p New back-diagonal array values.

void CTask::SetBackDiagonal(bool* p){
  for(size_t i=0; i<m_nDiagonalSize; i++)
    m_bBackDiagonal[i] = p[i];
} //SetBackDiagonal

/// Set start index.
/// \param n New start index.

void CTask::SetStartIndex(const size_t n){
  m_nStartIndex = n;
} //SetStartIndex
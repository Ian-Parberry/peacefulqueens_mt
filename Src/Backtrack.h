/// \file Backtrack.h
/// \brief Header for the class CMain.

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

#ifndef __Backtrack_h_
#define __Backtrack_h_

#include <cinttypes>

#include "ThreadManager.h"

class CBacktrack{
  private:
    CThreadManager* m_pThreadManager = nullptr; ///< Pointer to thread manager.

    size_t* m_nPerm = nullptr; ///< Permutation.
    bool* m_bDiagonal = nullptr; ///< Diagonal unoccupied.
    bool* m_bBackDiagonal = nullptr; ///< Back-diagonal unoccupied.

    size_t m_nSize = 0; ///< Size (width and height) of chessboard.
    size_t m_nDiagonalSize = 0; ///< Number of diagonals and back-diagonals.
    size_t m_nNumTasks = 0; ///< Number of threaded tasks.

    void CreateTask(const size_t);
    void Backtrack(const size_t, const size_t);
    void Backtrack(const size_t);

  public:
    CBacktrack(const size_t); ///< Constructor.
    ~CBacktrack(); ///< Destructor.
    
    uint64_t Backtrack();
    const size_t GetNumTasks() const;
}; //CBacktrack

#endif //__Backtrack_h_

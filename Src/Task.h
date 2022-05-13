/// \file Task.h
/// \brief Header for the class CTask.

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

#ifndef __Task_h_
#define __Task_h_

#include <cinttypes>

#include "BaseTask.h"

/// \brief Task.
///
/// Describes a  task.

class CTask: public CBaseTask{
  private:
    size_t* m_nPerm = nullptr; ///< Permutation.
    bool* m_bDiagonal = nullptr; ///< Diagonal unoccupied.
    bool* m_bBackDiagonal = nullptr; ///< Back-diagonal unoccupied.

    size_t m_nSize = 0; ///< Size (width and height) of chessboard.
    size_t m_nDiagonalSize = 0; ///< Number of diagonals and back-diagonals.
    size_t m_nStartIndex = 0; ///<Starting index into permutation.

    uint64_t m_nCount = 0; ///< Number of solutions found.

    void Backtrack(const size_t); ///< Backtrack.

  public:
    CTask(const size_t); ///< Constructor.
    ~CTask(); ///< Destructor.
    
    void SetPerm(size_t*); ///< Set permutation.
    void SetDiagonal(bool*); ///< Set diagonal.
    void SetBackDiagonal(bool*); ///< Set back-diagonal.
    void SetStartIndex(const size_t); ///< Set start index.

    virtual void Perform(); ///< Perform the task.
    const uint64_t GetCount() const; ///< Get the count.
}; //CTask

#endif //__Task_h_

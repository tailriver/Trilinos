// @HEADER
// ************************************************************************
//
//               Rapid Optimization Library (ROL) Package
//                 Copyright (2014) Sandia Corporation
//
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact lead developers:
//              Drew Kouri   (dpkouri@sandia.gov) and
//              Denis Ridzal (dridzal@sandia.gov)
//
// ************************************************************************
// @HEADER

#ifndef HS_PROBLEM_019_HPP
#define HS_PROBLEM_019_HPP

#include "ROL_NonlinearProgram.hpp"

namespace HS {

namespace HS_019 {
template<class Real>
class Obj {
public:
  template<class ScalarT> 
  ScalarT value( const std::vector<ScalarT> &x, Real &tol ) {
     ScalarT a = x[0]-10;
     ScalarT b = x[1]-20;
 
    return a*a*a + b*b*b;
  }
};

template<class Real> 
class InCon {
public:
  template<class ScalarT> 
  void value( std::vector<ScalarT> &c,
              const std::vector<ScalarT> &x,
              Real &tol ) {
    ScalarT a = x[0]-5;
    ScalarT b = x[1]-5;
    ScalarT d = x[0]-6;

    c[0] =  a*a + b*b - 100;
    c[1] = -b*b - d*d + 82.81;
  }
};
}


template<class Real> 
class Problem_019 : public ROL::NonlinearProgram<Real> {

  template<typename T> using RCP = Teuchos::RCP<T>;
  
  typedef ROL::Vector<Real>               V;
  typedef ROL::Objective<Real>            OBJ;
  typedef ROL::InequalityConstraint<Real> INCON;
  typedef ROL::NonlinearProgram<Real>     NP;

public:

  Problem_019() : NP( dimension_x() ) {
    NP::setLower(0,13.0);
    NP::setUpper(0,100.0);
    NP::setLower(1,0.0);
    NP::setUpper(1,100.0);
  }  

  int dimension_x()  { return 2; }
  int dimension_ci() { return 2; }

  const RCP<OBJ> getObjective() { 
    return Teuchos::rcp( new ROL::Sacado_StdObjective<Real,HS_019::Obj> );
  }

  const RCP<INCON> getInequalityConstraint() {
    return Teuchos::rcp( 
      new ROL::Sacado_StdInequalityConstraint<Real,HS_019::InCon> );
  }

  const RCP<const V> getInitialGuess() {
    Real x[] = {20.1,5.84};
    return NP::createOptVector(x);
  };
   
  bool initialGuessIsFeasible() { return false; }
  
  Real getInitialObjectiveValue() { 
    return Real(-1808.858296);
  }
 
  Real getSolutionObjectiveValue() {
    return -6961.81381;
  }

  RCP<const V> getSolutionSet() {
    Real x[] = {14.095,0.84296079};
    return ROL::CreatePartitionedVector(NP::createOptVector(x));
  }
 
};

} // namespace HS

#endif // HS_PROBLEM_019_HPP

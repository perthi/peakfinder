/**************************************************************************
 * This file is property of and copyright by the Experimental Nuclear     *
 * Physics Group, Dep. of Physics                                         *
 * University of Oslo, Norway, 2007                                       *
 *                                                                        *
 * Author: Per Thomas Hille <perthi@fys.uio.no> for the ALICE HLT Project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to perthi@fys.uio.no                                *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/
#include "PeakFinderMatrixGenerator.h"
#include "DataTypes.h"

PeakFinderMatrixGenerator::PeakFinderMatrixGenerator() : fPFMatrix(0)
{

}


PeakFinderMatrixGenerator::~PeakFinderMatrixGenerator()
{

}


TMatrixD*  
PeakFinderMatrixGenerator::GenerateMatrix(const NSamples_t &nSamples,  const TMin_t &tmin  , const  TMax_t &tmax , const NDivisions_t  &ndiv, const Tau_t  &tau)
{
  fPFMatrix  = new TMatrixD( ndiv.GetValue() ,  nSamples.GetValue());
  //  const double interval =  t0max - t0min;
  const double epsilon =  (tmax - tmin)/ndiv.GetValue();
 
  for(int i=0; i   <   ndiv.GetValue() ; ++i )
    {
      
    }

}






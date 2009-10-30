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


// void GeneratePulse( vector<T> &pfAmplitudes, const NSamples_t &N, const Tau_t &tau, const T0_t  &t0)  


TMatrixD*  
PeakFinderMatrixGenerator::GenerateMatrix(const NSamples_t &nSamples,  const TMin_t &tmin  , const  TMax_t &tmax , const NDivisions_t  &ndiv, const Tau_t  &tau)
{
  PulseGenerator *p = new PulseGenerator();

  fPFMatrix  = new TMatrixD( ndiv.GetValue() ,  nSamples.GetValue());
  //  const double interval =  t0max - t0min;
  // const double epsilon =  (tmax - tmin)/ndiv.GetValue();
  double array[nSamples.GetValue()][ndiv.GetValue()];

  // const double t0 =  tmin;
  const double epsilon =  (tmax - tmin)/ndiv;
  

  vector<double> amplitudes;
  
  //  static double tmpdoublearray[(const int)(nSamples*ndiv)];
  double tmpdoublearray[(const int)(nSamples*ndiv)];


  for(int t=0; t < ndiv; t++ )
    {
      p->GeneratePulse(amplitudes, nSamples, tau,  T0_t (tmin + epsilon*t ) );
      
      for(int i=0; i < nSamples; i++ )
	{
	  tmpdoublearray[ (int)(t*nSamples + i)] =  amplitudes.at(i);
	}
    }
  
  fPFMatrix->SetMatrixArray( tmpdoublearray );
  
}



//h.SetMatrixArray(data);




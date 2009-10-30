#ifndef PULSEGENERATOR_H
#define PULSEGENERATOR_H

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

#include <vector>
#include <iostream>
#include "math.h"
#include "TH1D.h"
#include "DataTypes.h"

using namespace std;

class  PulseGenerator
{
 public:
  PulseGenerator();
  virtual ~PulseGenerator();
  
  template<class T>
    void GeneratePulse( vector<T> &pfAmplitudes, const NSamples_t &N, const Tau_t &tau, const T0_t  &t0)   
    {
      pfAmplitudes.clear();
      
      for(int i=0;  i < N;  i++ )
	{
	  T tmp = 0;
	  double t=SampleIndex2us(i); 
	  double t0tmp = SampleIndex2us( t0.GetValue() );
	  
	  
	  if( (t-t0tmp) > 0 )
	    {
	      tmp = exp(2)*pow ( (t-t0tmp)/tau ,  2  ) * exp(-2*(t-t0tmp)/tau); 
	    }
	  else
	    { 
	      pfAmplitudes.push_back(0);
	    }
	  
	  if( tmp > fVerySmallNumber )
	    {
	      pfAmplitudes.push_back(tmp);
	    }
	  else
	    { 
	      if( i>  (5 + t0))
		{
		  break;
		}
	    }
	} 
    }
  
  template<class T>
    void Print(const vector<T> &array)
    {
      cout <<   array.size() << endl;
      for(int i=0; i < array.size(); i++)
	{
	  cout << array.at(i) << "\t" << endl;
	}
    }

  inline double SampleIndex2us(const double sampleindex)
  {
    return  sampleindex*(fTs/1000);
  }
  
  template <class T>
    void  Plot( vector<T> &pfAmplitudes )
    {
      
      TH1D *h = new  TH1D("tmp", "tmp", pfAmplitudes.size(), 0,   pfAmplitudes.size());
      
      for(int i=0; i < pfAmplitudes.size(); i++ )
	{
	  h->SetBinContent(i,pfAmplitudes.at(i));
	}
      h->Draw();
    }


 private:
  // PulseGenerator();
  double fFs; //sampling rate in MHz
  double fTs; //sampling intervall (1/fFs) in ns
  double fVerySmallNumber;

 //  double tau;
  
};

#endif

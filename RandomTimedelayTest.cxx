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
#include "RandomTimedelayTest.h"
#include "PulseGenerator.h"
#include "TRandom3.h"
#include "TH1D.h"

#include "DataTypes.h"


//RandomTimedelayTest::RandomTimedelayTest( int argc, const char** argv )


RandomTimedelayTest::RandomTimedelayTest()
{
  //  PulseGenerator *p= new  PulseGenerator(argc, argv); 
  //  PulseGenerator *p= new  PulseGenerator( ); 
  //  vector <double> tmp;
  //  p->GeneratePulse( tmp, 100000 ,  0.2, 7.3);
  // p->Print(tmp);
  //  p->Plot(tmp);
  TestRandom();  
}


RandomTimedelayTest::~RandomTimedelayTest()
{

}


void 
RandomTimedelayTest::TestRandom()
{
  Int_t n=5000;
  //  Int_t n=10; 
  double tw = 45.321;
  TRandom3 *t = new TRandom3();
  t->SetSeed();
  Double_t  rndArray[n];
  t->RndmArray(n, rndArray);
  TH1D *h = new TH1D("test2", "test2", 30000, -90, 90);
  PulseGenerator *p= new  PulseGenerator(); 

  for(int i=0; i < n ; i++)
    {
      vector<double> tmpAmp;
      
      //  p->GeneratePulse(tmpAmp, NSamples_t(100),  Tau_t(0.2),   T0_t( tw*rndArray[i]) );
      p->GeneratePulse(tmpAmp, NSamples_t(100),  Tau_t(0.2) ,   T0_t( tw*rndArray[i]) );
   
    double tmmpdiff = MakeInitialTOFGuess(tmpAmp) - tw*rndArray[i]; 
      h->Fill(tmmpdiff);
      
      if(i==2)
	{
	  //	  p->Plot(tmpAmp);
	}
    }

  h->Draw();
}

// RndmArray(Int_t n, Double_t *array) 

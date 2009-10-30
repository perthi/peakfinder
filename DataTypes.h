#ifndef DATATYPES_H
#define DATATYPES_H

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

#include <iostream>
#include <string>
#include <execinfo.h>

using namespace std;

//static double cnt =0 ;

//////////Tau
template <class T>
class Val_t
{
 public:
  explicit Val_t(const T &t, const T min, const T max, const string name, const string subscript) :  
  fVal(t),
    fMinValue(min), 
    fMaxValue(max), 
    fName(name),
    fSubscript(subscript) 
    {
    
      //  cnt ++;

      //   cout << __FILE__<<":"<<__LINE__ <<": Is called a total of "<< cnt << "  times" << endl;

      if(t > max || t < min)
	{
	  void *array[10];
	  size_t size;
	  char **strings;
	  size_t i;
	  
	  size = backtrace (array, 10);
	  strings = backtrace_symbols (array, size);
	  
	  printf ("Obtained %zd stack frames.\n", size);
	  
	  for (i = 0; i < size; i++)
	    {
	      printf ("%s\n", strings[i]);
	    }

	  free (strings);


	  cout <<__FILE__<<":"<<__FUNCTION__<<": line "<<__LINE__  <<": ERROR::The allowed range for paramter "<< \
	    name <<" is  [min, max] = "<< "["<< min<<", "<< max <<"]  " << subscript << endl;
	  
	  exit(-1);
	}
    } ; 
 
  const T GetValue() const { return  fVal;};  
 private:
  Val_t();
  const T  fVal;
  const double fMinValue;
  const double fMaxValue;

 public:
  const string fName;
  
 private:
  const string fSubscript;
  //  static double cnt;
};


//static double Val_t<double>::cnt =0 ;
//static double Val_t<int>::cnt =0 ;


class  Tau_t : public Val_t <const double> 
{
 public:
 explicit Tau_t( const double &t) : Val_t<const double>:: Val_t( t, 0.2, 4, "Tau_t", " us" ) 
    {
      //   cnt ++;
      //   cout <<__FILE__<<__LINE__<< ": The construcor of " << fName << " was called a totsl of "<< cnt <<  " Times"  << endl;
    };
 private:
  Tau_t();
};


class  Amplitude_t : public Val_t<const double>
{
 public:
  explicit Amplitude_t( const double t = 1) : Val_t<const double>::Val_t( t,  0.1, 1023, "Amplitude_t", " ADC counts"    ) {} ;
 private:
  Amplitude_t();
};



class  NSamples_t : public Val_t<const int>
{
 public:
  explicit   NSamples_t( const int t) : Val_t<const int>::Val_t(t, 1 , 1023, "NSamples_t", " N") {};
 private:
  NSamples_t();
};


class T0_t : public Val_t<const double>
{
 public:
  explicit T0_t( const double t)  : Val_t<const double>::Val_t(t, -100, 1023, "T0_t", " Sample indexes") {};
 private:
  T0_t();
};


class TMax_t : public Val_t<const double>
{
 public:
  explicit TMax_t( const double t) : Val_t<const double>::Val_t(t, -100, 1023, "TMax_t",  " Sample indexes" ) {} ;
 private:
  TMax_t();
};


class TMin_t : public Val_t<const double>
{
 public:
  explicit  TMin_t( const double t) :Val_t<const double>::Val_t( t , -100, 1023, "TMix_t", " Sample indexes"  ) {} ;
 private:
  TMin_t();
};


class NDivisions_t : public Val_t<const int>
{
 public:
  explicit NDivisions_t( const int t) : Val_t<const int>::Val_t(t,  100, 10000, "NDivision_t", " Divisions"   ) {} ;
 private:
  NDivisions_t();
};


//PeakFinderMatrixGenerator::GenerateMatrix( const NSamples_t &nSamples,  const TMin_t &tmin  , const  TMax_t &tmax , const NDivisions_t  &ndiv, const Tau_t  &tau  )

/*
class PFMatrixParameters
{
 public:
 PFMatrixParameters(const NSamples_t &nSamples,  const TMin_t &tmin  , const  TMax_t &tmax , const NDivisions_t  &ndiv, const Tau_t  &tau):
  
 private:
  PFMatrixParameters();
  const NSamples_t fNSamples;
  const TMin_t
}
*/

template <class T, class T2>  
  inline  double  operator / ( const T  &lhs, const  Val_t<T2> &rhs ) 
{
  return  lhs/(rhs.GetValue());
};



template <class T, class T2>  
inline double operator  + (  const T &lhs,   const Val_t<T2> &rhs )
{
  return  (double)lhs +  (double)rhs.GetValue();
}


template <class T>  
inline double operator  + (  const Val_t<T> &lhs,   const double &rhs )
{
  return  (double)lhs.GetValue() +  (double)rhs;
}


template <class T, class T2>  
bool  operator <  ( const T &lhs, const  Val_t<T2> & rhs) 
{
  if( lhs < rhs.GetValue() )
    {
      return true;
    }
  else
    {
      return false;
    }
};


template <class T, class T2>  
  inline double operator -  ( const T &lhs, const Val_t<T2> & rhs) 
{
  return (double)lhs - (double)rhs.GetValue();
};


template <class T, class T2>  
  inline double operator *  ( const Val_t<T> &lhs, const Val_t<T2> & rhs) 
{
  return (double)lhs.GetValue()*(double)rhs.GetValue();
};


template <class T>  
inline double operator *  (int lhs, const Val_t<T> & rhs) 
{
  return (double)lhs*(double)rhs.GetValue();
};


  
inline double operator -  ( const TMax_t &lhs, const TMin_t &rhs) 
{
  return lhs.GetValue() - rhs.GetValue();
};


#endif



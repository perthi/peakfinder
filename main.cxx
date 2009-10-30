#include <iostream>
#include "stdio.h"
#include <iostream>
#include "DataTypes.h"
#include "RandomTimedelayTest.h"

#ifndef __CINT__
# include <stdexcept>
# include <TSystem.h>
# include <TApplication.h>
#endif
using namespace std;


int
main( int argc, const char** argv)
{
  try {
    TApplication app("app", 0, 0);
    //RandomTimedelayTest *r = new RandomTimedelayTest ( argc,  argv );
    RandomTimedelayTest *r = new RandomTimedelayTest(   );
    

   app.Run();
  }
  catch (std::exception& e) 
    {
      std::cerr << e.what() << std::endl;
      return 1;
    }
  return 0;
}


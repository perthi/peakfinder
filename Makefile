
GCC_FLAGS        = g++ 	-ggdb    -fPIC -ffunction-sections


ROOTLIBS         =  `root-config --libs` -lVMC -lGeom -lEG -lMinuit -lProof -lProofPlayer -lNet
#ALIROOTLIBS      = -L$(ALICE_ROOT)/lib/tgt_linux   -lCDB -lRAWDatabase -lRAWDatarec -lRAWDatasim \
#				-lEMCALbase -lEMCALrec   -lEMCALsim -lSTRUCT  -lSTEER  -lSTEERBase \
#			        -lESD

LIBS		 = $(ROOTLIBS)

ROOTINCLUDE      = -I$(ROOTSYS)/include
ALIROOTINCLUDE   = -I$(ALICE_ROOT)/include  -I$(ALICE_ROOT)/RAW  -I$(ALICE_ROOT)/EMCAL  -I$(ALICE_ROOT)/EMCAL/SMcalib/
INCLUDES	 =  $(ROOTINCLUDE) $(ALIROOTINCLUDE) 

HeadSuf=h
SrcSuf=cxx
ObjSuf=o


PROGRAM 	 = peakfindertest


SRC=	main.cxx \
	PulseGenerator.cxx \
	RandomTimedelayTest.cxx \
	PeakFinderMatrixGenerator.cxx \
	DataTypes.cxx \
	PeakFinderVectorsGenerator.cxx


OBJS=$(subst .cxx,.o, $(SRC))


$(PROGRAM):$(OBJS)
	@echo HELLO WORLD0 $(OBJS)
	$(GCC_FLAGS) $(OBJS)  $(LIBS) $(ESDLIB) -o $(PROGRAM)

$(OBJS):%.o: %.cxx
	$(GCC_FLAGS) $(INCLUDES) -c $< -o $@		

include $(subst .cxx,.d, $(SRC))

%.d: %.cxx
	gcc -M $(INCLUDES) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean:
		@rm -f  *.o  *~  *.d $(PROGRAM)




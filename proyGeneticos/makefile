# -*- Mode: makefile -*-
# Copyright (c) 1999 Matthew Wall, all rights reserved
# -----------------------------------------------------------------------------
#   To make all of the examples, do 'make'.  You can compile any one of
# the examples by typing 'make exN' where N is the number of the example you
# want to compile.  See the README for a description of what each example does.
# -----------------------------------------------------------------------------

include galib247/makevars

# Set these paths to the location of the GA library and headers.
#GA_INC_DIR= /usr/local/include
#GA_LIB_DIR= /usr/local/lib
GA_INC_DIR= galib247/
GA_LIB_DIR= galib247/ga

INC_DIRS= -I$(GA_INC_DIR)
LIB_DIRS= -L$(GA_LIB_DIR)

EXS=randtest\
 proy proy2 proy3 proy4 proy5

.SUFFIXES: .cpp
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -c $<

all: $(EXS)

# Use this for non-gnu make
#$(EXS): $$@.o
#	$(CXX) $@.o -o $@ $(LIB_DIRS) -lga -lm $(CXX_LIBS)

# Use this for gnu make
$(EXS): %: %.o
	$(CXX) $@.o -o $@ $(LIB_DIRS) -lga -lm $(CXX_LIBS)

clean:
	$(RM) $(EXS)
	$(RM) *.o *~ *.bak *.pixie core
	$(RM) test_results.txt test_stats.txt
	$(RM) *.dat
	$(RM) *.out *.exe vc* *.pdb

test: $(EXS)
	$(RM) test_results.txt test_stats.txt
	@echo "running tests.  this could take up to 1/2 hour, depending on"
	@echo "the speed of your computer.  monitor test_results.txt and"
	@echo "test_stats.txt to see what is happening."
	@echo ""
	@rm -f test_results.txt
	@echo `uname -a` > test_stats.txt
	@echo "" >> test_stats.txt
	for x in $(EXS); do \
          echo "$$x... "; \
          echo "$$x" >> test_stats.txt; \
          echo "start:  " `date` >> test_stats.txt; \
          ./$$x seed 555 >> test_results.txt; \
          echo "finish: " `date` >> test_stats.txt; \
          echo "" >> test_stats.txt; \
        done

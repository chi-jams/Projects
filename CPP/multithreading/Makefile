
###########################
# Variables and Constants #
###########################

# The name of your compiled project
PROGNAME = multithreading 

# All the dependencies of the final program
OBJS = main.o 

# The compiler being used
CC = g++

# Flags
# -Wall is to display warnings
# -c is to compile cpp files to .o files
# -g is (I think) debug info
CFLAGS = -Wall -c -g -std=c++11
LFLAGS = -Wall -g


#######################
# Including Libraries #
#######################

# Add your include and library directories here

#INCPATH += -I./include
#LIBPATH += -L./lib

# Add every single library being used

# Ex
# LIBS += -llibrary

############################
# Compilation Instructions #
############################

#all: $(PROGNAME)

# The compilation instruction for the final program
$(PROGNAME): $(OBJS) 
	$(CC) $(LFLAGS) $(INCPATH) -o $@ $^ $(LIBPATH) $(LIBS)

# Compilation instructions for all .cpp files
# EXAMPLE FORMAT:
# test.o: test.cpp test.h
# 	$(CC) $(CFLAGS) test.cpp

# ... or we just use stuff that does this automatically
.c.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -o $@ $<

.cc.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -o $@ $<

.cpp.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -o $@ $<

# Deletes all of the compiled files in the folder
clean:
	rm -r *.o *~ $(PROGNAME).exe

# Same as above, but for windows because windows is dumb
cleanWin:
	del /S *.o *~ $(PROGNAME).exe

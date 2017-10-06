
# The name of your compiled project
PROGNAME = png_scale

# All the dependencies of the final program
OBJS = main.o

# The compiler being used
CC = g++

# Flags
# REFER TO man gcc/g++ for details on this
# -Wall is to display warnings
# -c is to compile cpp files to .o files
# -g is (I think) debug info
# -o is outfile
# -std=c++11 is to use c++11 mode
CFLAGS = -Wall -c -g

# Linker Flags
LFLAGS = -Wall

INCPATH = -I./include

LIBS += -lpng

# The compilation instruction for the final program
$(PROGNAME): $(OBJS) 
	$(CC) $(LFLAGS) $(OBJS) -o $(PROGNAME) $(LIBPATH) $(LIBS)

# PUT NEW CPP COMPILATION INSTRUCTIONS BELOW HERE
# Compilation instructions for all cpp files
# Technically we could wild card this, 
# but that kind of defeats the purpose of makefiles

# EXAMPLE FORMAT:
# test.o: test.cpp test.h
# 	$(CC) $(CFLAGS) test.cpp

# ... or we just use stuff that does this automatically
.c.o: 	
	$(CC) $(CFLAGS) $(INCPATH) -o $@ $<

.cpp.o: 	
	$(CC) $(CFLAGS) $(INCPATH) -o $@ $<

# Deletes all of the compiled files in the folder
clean:
	rm *.o *~ $(PROGNAME)

# Same as above, but for windows because windows is dumb
cleanWin:
	del *.o *~ $(PROGNAME).exe

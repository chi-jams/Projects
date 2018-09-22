
# The name of your compiled project
PROGNAME = 

SRCDIR = src
OBJDIR = obj

# All the dependencies of the final program
CPPS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(addprefix $(OBJDIR)/,$(notdir $(CPPS:.cpp=.o)))

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

INCPATH += -I./inc

# The linking instruction for the final program
$(PROGNAME): $(OBJS)
	$(CC) $(LFLAGS) -o $(PROGNAME) $^ $(LIBPATH) $(LIBS)

# PUT NEW CPP COMPILATION INSTRUCTIONS BELOW HERE
# Compilation instructions for all cpp files
# Technically we could wild card this, 
# but that kind of defeats the purpose of makefiles

# EXAMPLE FORMAT:
# test.o: test.cpp test.h
# 	$(CC) $(CFLAGS) test.cpp

# ... or we just use stuff that does this automatically
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCPATH) -o $@ $<

# Deletes all of the compiled files in the folder
clean:
	rm -r *.o *~ $(PROGNAME)

# Same as above, but for windows because windows is dumb
cleanWin:
	del /S *.o *~ $(PROGNAME).exe


###########################
# Variables and Constants #
###########################

# The name of your compiled project
PROGNAME = djameson_A3 

# All the dependencies of the final program
OBJS = main.o Camera.o modelBasic.o modelLoader.o tessModel.o texModel.o perlin.o src/shaderUtils.o src/ShaderProgram.o src/OpenGLUtils.o

# The compiler being used
CC = g++

# Flags
# -Wall is to display warnings
# -c is to compile cpp files to .o files
# -g is (I think) debug info
# -std=c++11 is to use c++11 mode
CFLAGS = -Wall -c -g
LFLAGS = -Wall -g

#######################
# Including Libraries #
#######################

INCPATH += -I./include
LIBPATH += -L./lib

# Include GLEW
LIBS += -lglew32

# Inlucde GLFW
LIBS += -lglfw3 -lgdi32

# Include SOIL
LIBS += -lSOIL

####################
# OpenGL directory #
####################
INCPATH += -IC:/Strawberry/c/include
LIBPATH += -LC:/Strawberry/c/lib
LIBS += -lopengl32 -lglu32

############################
# Compilation Instructions #
############################

#all: $(PROGNAME)

# The compilation instruction for the final program
$(PROGNAME): $(OBJS) 
	$(CC) $(LFLAGS) $(INCPATH) -o $(PROGNAME) $^ $(LIBPATH) $(LIBS)

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

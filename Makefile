###############################################################################
#
# Makefile
#
# Created May 2010 by J M Brisson Lopes, IST
#
###############################################################################

LIBINCDIR   = cglib/include
LIBINCDIRCG = $(LIBINCDIR)/cg
LIBSRCDIR   = cglib/src
LIBDIR      = cglib/lib

LIBSOURCES = $(wildcard $(LIBSRCDIR)/*.cpp)
LIBOBJS    = $(LIBSOURCES:$(LIBSRCDIR)%.cpp=$(LIBDIR)%.o)
LIBNAME    = cglib.a
LIB        = $(LIBDIR)/lib$(LIBNAME).a

PROGRAM    = test
PRGSRCDIR  = template
PRGSRC     = $(wildcard $(PRGSRCDIR)/*.cpp)
PRGOBJDIR  = template/obj
PRGOBJS    = $(PRGSRC:$(PRGSRCDIR)%.cpp=$(PRGOBJDIR)%.o)
PRGINCDIR  = template

###############################################################################

ifdef DEBUG
OPTFLAGS = -g
else
OPTFLAGS = -O3
endif

CC      = g++
#CFLAGS  = -Wall $(OPTFLAGS)
CFLAGS  = $(OPTFLAGS)
LDFLAGS =  -L $(LIBDIR) -l $(LIBNAME) -lGL -lglu -lglut
INCFLAGS = -I $(LIBINCDIR) -I $(LIBINCDIRCG)

UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)  # Mac OS X
# OpenGL and GLUT are frameworks, override LDFLAGS above
LDFLAGS = -L$(LIBDIR) -l$(LIBNAME) -framework OpenGL -framework GLUT
# Universal binary support
CFLAGS  += -arch ppc -arch i386
endif
ifeq ($(UNAME), CYGWIN_NT-5.1)  # Cygwin
# OpenGL and GLUT libs are named differently, override LDFLAGS above
LDFLAGS =  -L $(LIBDIR) -l $(LIBNAME) -lopengl32 -lglu32 -lglut32
EXE = .exe
endif

###############################################################################

all: $(PRGOBJDIR) $(PROGRAM)

$(PROGRAM): $(PRGSRC) $(PRGOBJS) $(PRGOBJDIR) $(LIB)
	$(CC) $(CFLAGS) $(PRGOBJS)  -I $(PRGINCDIR) $(INCFLAGS) $(LDFLAGS) -o $@

$(LIB): $(LIBDIR) $(LIBSOURCES) $(LIBINCDIRCG)/*.h $(LIBOBJS)
	rm -f $(LIB)
	ar -cq $(LIB) $(LIBOBJS)
	ranlib $(LIB)

$(LIBDIR) $(PRGOBJDIR):
	@ test -d $@ || mkdir -p $@
	
clean:
	rm -f $(PROGRAM)
	rm -rf $(PRGOBJDIR)
	rm -rf $(LIBDIR)
	rm -f log.txt

.PHONY: all clean

###############################################################################

$(LIBDIR)/%.o: $(LIBSRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $^ -o $@ $(INCFLAGS)

$(PRGOBJDIR)/%.o: $(PRGSRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $^ -o $@ $(INCFLAGS)

###############################################################################

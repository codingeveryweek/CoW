ROOT = $(CURDIR)/
OBJPATH = $(ROOT)obj/
BINPATH = $(ROOT)bin/

all : inPlaceListExample hello

inPlaceListExample : $(OBJPATH) $(OBJPATH)inPlaceListExample.o
	g++ -o $(BINPATH)inPlaceListExample $(OBJPATH)inPlaceListExample.o 

hello : $(OBJPATH) $(OBJPATH)hello.o 
	g++ -o $(BINPATH)hello $(OBJPATH)hello.o

$(OBJPATH)hello.o : $(BINPATH) $(ROOT)hello/hello.cc
	g++ -c $(ROOT)hello/hello.cc -o $(OBJPATH)hello.o

$(OBJPATH)inPlaceListExample.o : $(ROOT)examples/inPlaceListExample.cc
	g++ -c $(ROOT)examples/inPlaceListExample.cc -o $(OBJPATH)inPlaceListExample.o

$(OBJPATH) : 
	mkdir $(OBJPATH)

$(BINPATH) :
	mkdir $(BINPATH)
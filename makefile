ROOT = $(CURDIR)/
OBJPATH = $(ROOT)obj/
BINPATH = $(ROOT)bin/

hello : $(OBJPATH) $(OBJPATH)hello.o 
	g++ -o $(BINPATH)hello $(OBJPATH)hello.o

$(OBJPATH)hello.o : $(BINPATH) $(ROOT)hello/hello.cc
	g++ -c $(ROOT)hello/hello.cc -o $(OBJPATH)hello.o

$(OBJPATH) : 
	mkdir $(OBJPATH)

$(BINPATH) :
	mkdir $(BINPATH)
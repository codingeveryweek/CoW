ROOT = $(CURDIR)/
OBJPATH = $(ROOT)obj/
BINPATH = $(ROOT)bin/

#Requires manully run "git clone https://github.com/google/googletest.git" from directory ~/repos
GOOGLETEST = ~/repos/googletest/

all : inPlaceListExample hello

inPlaceListExample : $(OBJPATH) $(OBJPATH)inPlaceListExample.o
	g++ -o $(BINPATH)inPlaceListExample $(OBJPATH)inPlaceListExample.o 

inPlaceListTest : $(OBJPATH) $(OBJPATH)inPlaceListTest.o $(OBJPATH)gtest.o $(OBJPATH)gtest_main.o
	g++ $(OBJPATH)inPlaceListTest.o $(OBJPATH)gtest.o $(OBJPATH)gtest_main.o -lpthread -o $(BINPATH)inPlaceListTest

hello : $(OBJPATH) $(OBJPATH)hello.o 
	g++ -o $(BINPATH)hello $(OBJPATH)hello.o

$(OBJPATH)hello.o : $(BINPATH) $(ROOT)hello/hello.cc
	g++ -c $(ROOT)hello/hello.cc -o $(OBJPATH)hello.o

$(OBJPATH)inPlaceListExample.o : $(ROOT)examples/inPlaceListExample.cc
	g++ -c $(ROOT)examples/inPlaceListExample.cc -o $(OBJPATH)inPlaceListExample.o

$(OBJPATH)inPlaceListTest.o : $(ROOT)commontest/inPlaceListTest.cc
	g++ -I ${GOOGLETEST}googletest/include -I ${ROOT} -c ${ROOT}/commontest/inPlaceListTest.cc -o $(OBJPATH)inPlaceListTest.o

$(OBJPATH)gtest.o : $(GOOGLETEST)googletest/src/gtest-all.cc
	g++ -I ${GOOGLETEST}googletest/include -I ${GOOGLETEST}googletest -c $(GOOGLETEST)googletest/src/gtest-all.cc -o $(OBJPATH)gtest.o

$(OBJPATH)gtest_main.o : $(GOOGLETEST)googletest/src/gtest_main.cc
	g++ -I ${GOOGLETEST}googletest/include -c $(GOOGLETEST)googletest/src/gtest_main.cc -o $(OBJPATH)gtest_main.o

$(OBJPATH) : 
	mkdir $(OBJPATH)

$(BINPATH) :
	mkdir $(BINPATH)

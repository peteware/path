CXX		= $(CROSS)g++
AR		= $(CROSS)ar
RANLIB		= $(CROSS)ranlib

LIBRARY		= path
TEST_PROG	= test_path
LIB_PATH	= -L../../src -l$(LIBRARY)
LIBNAME		= ../../src/lib$(LIBRARY).a

TEST_SRCS	= \
		CanonicalUnit.cpp \
		ExpandUnit.cpp \
		GlobUnit.cpp \
		NodeUnit.cpp \
		PathLookupUnit.cpp \
		RulesBaseUnit.cpp \
		PathUnit.cpp \
		RefcountUnit.cpp \
		SysBaseUnit.cpp \
		RulesUnixUnit.cpp \
		RulesWin32Unit.cpp \
		main.cpp
TEST_OBJS	=  \
		GlobUnit.o \
		CanonicalUnit.o \
		ExpandUnit.o \
		NodeUnit.o \
		PathLookupUnit.o \
		RulesBaseUnit.o \
		PathUnit.o \
		RefcountUnit.o \
		SysBaseUnit.o \
		RulesUnixUnit.o \
		RulesWin32Unit.o \
		main.o

O		= -g -Wall
CPPFLAGS	= $O -I. -I../../include -I$(HOME)/usr/include 
LIBCPPUNIT      = -lcppunit

all:		$(TEST_PROG) runtest

$(TEST_PROG):	$(TEST_OBJS) $(LIBNAME)
		$(LINK.cc) $(TEST_OBJS) $(LIB_PATH) $(LIBCPPUNIT) -o $(TEST_PROG)

clean:
		$(RM) -f *.o $(TEST_PROG)

runtest:	$(TEST_PROG)
		./$(TEST_PROG)

depend:
		$(COMPILE.cc) -MM $(TEST_SRCS) > .depends

-include .depends

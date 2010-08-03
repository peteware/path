LIBRARY		= path
TEST_PROG	= test_path
LIB_PATH	= -L../../src -l$(LIBRARY)
LIBNAME		= ../../src/lib$(FASTLINK_LIBRARY).a

TEST_SRCS	= \
		CanonicalUnit.cpp \
		ExpandUnit.cpp \
		NodeUnit.cpp \
		PathLookupUnit.cpp \
		PathRulesUnit.cpp \
		PathUnit.cpp \
		RefcountUnit.cpp \
		SysCallsUnit.cpp \
		UnixRulesUnit.cpp \
		Win32RulesUnit.cpp \
		main.cpp
TEST_OBJS	=  \
		CanonicalUnit.o \
		ExpandUnit.o \
		NodeUnit.o \
		PathLookupUnit.o \
		PathRulesUnit.o \
		PathUnit.o \
		RefcountUnit.o \
		SysCallsUnit.o \
		UnixRulesUnit.o \
		Win32RulesUnit.o \
		main.o

O		= -g -Wall
CPPFLAGS	= $O -I. -I../../include -I$(HOME)/usr/include 
LIBCPPUNIT      = -R$(HOME)/usr/lib -L$(HOME)/usr/lib -lcppunit

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

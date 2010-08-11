CXX		= $(CROSS)g++
AR		= $(CROSS)ar
RANLIB		= $(CROSS)ranlib

LIBRARY		= path
LIBNAME		= lib$(LIBRARY).a

LIB_PATH	= -L. -l$(LIBRARY)

LIB_SRCS	= \
		BadPath.cpp \
		Canonical.cpp \
		Exception.cpp \
		FileStream.cpp \
		Glob.cpp \
		Node.cpp \
		NodeInfo.cpp \
		Path.cpp \
		PathException.cpp \
		PathExtra.cpp \
		PathIter.cpp \
		PathLookup.cpp \
		PathRules.cpp \
		Permission.cpp \
		Strings.cpp \
		SysCalls.cpp \
		SysUnixBase.cpp \
		Unimplemented.cpp \
		UnixRules.cpp \
		UriRules.cpp \
		Win32Rules.cpp
LIB_OBJS	= \
		BadPath.o \
		Canonical.o \
		Exception.o \
		FileStream.o \
		Glob.o \
		Node.o \
		NodeInfo.o \
		Path.o \
		PathException.o \
		PathExtra.o \
		PathIter.o \
		PathLookup.o \
		PathRules.o \
		Permission.o \
		Strings.o \
		SysCalls.o \
		SysUnixBase.o \
		Unimplemented.o \
		UnixRules.o \
		UriRules.o \
		Win32Rules.o

O		= -g -Wall
CPPFLAGS	= $O -I. -I../include -I/opt/local/include
ARFLAGS		= cr

all:		$(LIBNAME)

$(LIBNAME):	$(LIB_OBJS)
		$(AR) $(ARFLAGS) $(LIBNAME) $(LIB_OBJS)
		$(RANLIB) $(LIBNAME)

clean:
		$(RM) -f *.o $(LIBNAME) $(FASTLINK_PROG)

depend:
		$(COMPILE.cc) -MM $(LIB_SRCS) > .depends

-include .depends

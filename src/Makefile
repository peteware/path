CXX		= $(CROSS)g++
AR		= $(CROSS)ar
RANLIB		= $(CROSS)ranlib

LIBRARY		= path
LIBNAME		= lib$(LIBRARY).a

LIB_PATH	= -L. -l$(LIBRARY)

LIB_SRCS	= \
		BadPathException.cpp \
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
		RulesBase.cpp \
		PathPermissionException.cpp \
		Strings.cpp \
		SysBase.cpp \
		SysUnixBase.cpp \
		SysWin32.cpp \
		Unimplemented.cpp \
		RulesUnix.cpp \
		RulesUri.cpp \
		RulesWin32.cpp
LIB_OBJS	= \
		BadPathException.o \
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
		RulesBase.o \
		PathPermissionException.o \
		Strings.o \
		SysBase.o \
		SysUnixBase.o \
		SysWin32.o \
		Unimplemented.o \
		RulesUnix.o \
		RulesUri.o \
		RulesWin32.o

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

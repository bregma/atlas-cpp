
INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES = libAtlasCodecs-0.6.la

libAtlasCodecs_0_6_la_LDFLAGS = $(INTERFACE_VERSION)

libAtlasCodecs_0_6_la_LIBADD = $(top_builddir)/Atlas/libAtlas-0.6.la

libAtlasCodecs_0_6_la_SOURCES = \
	Utility.cpp XML.cpp Packed.cpp Bach.cpp

libAtlasCodecsincludedir = $(includedir)/Atlas-C++-0.6/Atlas/Codecs

libAtlasCodecsinclude_HEADERS = Utility.h XML.h Packed.h Bach.h

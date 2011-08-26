VERSION = .02
CC = gcc
CFLAGS = -Wall -DVERSION=\"$(VERSION)\"
MFLIB = mflib.o mflib_lua.o
OBJS = main.o $(MFLIB)
INC = mflib.h
INCLUDES = -I../src
LIBS = -L/usr/local/lib -L../src
LDFLAGS = -llua -lm -ldl
RM = rm -f
INSTALLDIR = /usr/local/bin
TESTS = get_css_path \
	string_from_file \
	get_script_as_string \
	splice_tag \
	get_tag \
	get_indentation \
	table_to_attr \
	walk_lua_global \
	chomp \
	underscore_to_dash\
	cache

moonfall: $(OBJS)
	gcc $(CFLAGS) -o moonfall $(OBJS) $(LIBS) $(INCLUDES) $(LDFLAGS)

main.o: main.c $(INC)
	gcc $(CFLAGS) -o main.o -c main.c $(LIBS) $(INCLUDES)

mflib.o: mflib.c $(INC)
	gcc $(CFLAGS) -o mflib.o -c mflib.c $(LIBS) $(INCLUDES)

mflib_lua.o: mflib_lua.c mflib_lua_to_source $(INC)
	gcc $(CFLAGS) -o mflib_lua.o -c mflib_lua.c $(LIBS) $(INCLUDES)

mflib_lua.c: mflib.lua mflib_lua_to_source
	./mflib_lua_to_source

mflib_lua_to_source: mflib_lua_to_source.c
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS) $(INCLUDES)

install: moonfall
	install -d $(INSTALLDIR)
	install -b moonfall $(INSTALLDIR)
	ln -sf $(INSTALLDIR)/moonfall /usr/bin/moonfall 

DOWNLOADS = ../moonfall_site/downloads

dist:
	make clean
	tar cvfz $(DOWNLOADS)/moonfall_source$(VERSION).tar.gz ../moonfall_source
	cd $(DOWNLOADS); ln -sf moonfall_source$(VERSION).tar.gz latest_moonfall.tar.gz;
	cd $(DOWNLOADS); chmod 644 moonfall_source$(VERSION).tar.gz

clean:
	$(RM) moonfall
	$(RM) $(OBJS)
	$(RM) $(TESTS)
	$(RM) mflib_lua_to_source
	$(RM) mflib_lua.c

lua:
	cd ../src; make a

tests: $(TESTS)

get_css_path: get_css_path.c $(MFLIB)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS) $(INCLUDES)

string_from_file: string_from_file.c $(MFLIB)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS) $(INCLUDES)

get_script_as_string: get_script_as_string.c $(MFLIB)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS) $(INCLUDES)

splice_tag: splice_tag.c $(MFLIB)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS) $(INCLUDES)

get_tag: get_tag.c $(MFLIB)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS) $(INCLUDES)

get_indentation: get_indentation.c $(MFLIB)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS) $(INCLUDES)

table_to_attr: table_to_attr.c $(MFLIB)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS) $(INCLUDES)

walk_lua_global: walk_lua_global.c $(MFLIB)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS) $(INCLUDES)

chomp: chomp.c $(MFLIB)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS) $(INCLUDES)

underscore_to_dash: underscore_to_dash.c $(MFLIB)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS) $(INCLUDES)

cache: cache.c $(MFLIB)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS) $(INCLUDES)
/* Copyright 2007 Kevin Swope, All Rights Reserved */

/* This file is part of Moonfall. */

/* Moonfall is free software; you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation; either version 3 of the License, or */
/* (at your option) any later version. */
  
/* Moonfall is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/* GNU General Public License for more details. */

/* You should have received a copy of the GNU General Public License */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */


#ifndef mflib_h
#define mflib_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#define OPEN_TAG '['
#define CLOSE_TAG ']'

void* _malloc(int);
void* _calloc(int);
void* _realloc(char*, int);
void* _mystrdup(const char*);

void process_switches(int, char**);

void chomp(char *str);

void underscore_to_dash(char*);

void warn(char*, ...);

#define CSS_PATH_BUFF_SIZE 1000
char* get_css_path(char*);

char* string_from_file(char*);

void string_to_file(char*, char*);

char* get_script_as_string(char*);

char* splice_tag(char*, char*, char*, char *);

#define MAX_TAG_LEN 100
char* get_tag(char*);

lua_State* get_lua(char*);

char* num_to_px(lua_State*, size_t);

char* get_indentation(char*, char*);

char* stack_index_as_css(lua_State*, size_t, char*, 
			 char*, char*);

char* table_as_attr(lua_State*, size_t, char*,
		    char*, char*);

void walk_lua_global(lua_State*, const char*);

void output(char**, char*);


char *maybe_return_cache(char*);

void maybe_write_cache(char*, char*);

#endif

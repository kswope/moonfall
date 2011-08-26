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

// Test driver for table_to_attr()

#include "mflib.h"

int global_first_row; 

int main(int argc, char *argv[]) {

  if (argc < 2) {
    puts("*** call like this: ./get_css_path ./script.mfl");
    exit(1);
  }

  // set up embedded lua interpreter and run on script
  lua_State *L = get_lua(argv[1]);

  //// get css file as string
  char *csspath = get_css_path(argv[1]);
  char *css_str = string_from_file(csspath);
  free(csspath);

  char *key = "scheme";

  char *tag = calloc(strlen(key), 1);
  strcat(tag, "[");
  strcat(tag, key);
  strcat(tag, "]");

  char *tag_begin = strstr(css_str, tag);

  if ( ! tag_begin ) {
    warn("couldn't find tag %s", tag);
    exit(1);
  }

  lua_getglobal(L, key);
  
  if( ! lua_istable(L, -1) ) {
    warn("%s is not a table", key);
    exit(1);
  }

  char *attrs = table_as_attr(L, -1, key, css_str, tag_begin);
  printf("%s\n", attrs);

  return(0);

}


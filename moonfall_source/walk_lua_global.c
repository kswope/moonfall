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

// Test driver for travel_dots()

#include "mflib.h"


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

  char *key = "test.one";

  char *tag = calloc(strlen(key), 1);
  strcat(tag, "[");
  strcat(tag, key);
  strcat(tag, "]");

  char *cursor = strstr(css_str, tag);
  if( ! cursor ) {
    warn("[%s] not found", key);
    exit(1);
  }

  walk_lua_global(L, key);

  // attrs will be garbage is nothing found
  char *attrs = stack_index_as_css(L, -1, key, css_str, cursor);

  puts(attrs);

  return(0);

}

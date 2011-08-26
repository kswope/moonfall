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


#include "mflib.h"

// My hackpologies, we start off the code with a global variable, this
// is to tell the recursish table_as_attr()/stack_index_as_css() combo
// functions to not indent the first column of table in css.
extern int global_first_row; 

int main(int argc, char *argv[]) {

  char *css_str = NULL; // what we're here for

  process_switches(argc, argv); // process -h and -v, can exit()

  char *csspath = get_css_path(argv[1]);

  if ( (css_str = maybe_return_cache(csspath)) ) {
    output(argv, css_str);    
    exit(0);
  } 

  // set up embedded lua interpreter and run on script
  lua_State *L = get_lua(argv[1]);

  //// get css file as string
  css_str = string_from_file(csspath);
  free(csspath);

  char *tag_begin = NULL;
  int advance = 0; // optimization, start search this far in
  while ( (tag_begin = strchr(css_str + advance, OPEN_TAG)) != NULL ) {

    advance = (tag_begin - css_str) + 1; // advance 1 past tag found

    char *tag_name = get_tag(tag_begin);

    walk_lua_global(L, tag_name);

    if ( lua_type(L, -1) != LUA_TNIL ) { // if walk_lua_global stacked anything

      global_first_row = 1;

      char *css_frag = stack_index_as_css(L, 
					  -1, 
					  tag_name, 
					  css_str, 
					  tag_begin);

      chomp(css_frag); // remove any trailing whitespace from new css fragment

      css_str = splice_tag(css_str,
			   tag_begin,
			   strchr(tag_begin, CLOSE_TAG),
			   css_frag);

      free(css_frag);

    } else { // found a tag in the css but no corresponding lua global
      warn("unknown tag, %s", tag_name);
    }

    free(tag_name);

  }


  maybe_write_cache(css_str, css_str);

  output(argv, css_str);

  return(0);

}


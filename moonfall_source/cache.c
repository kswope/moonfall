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

// Test driver for maybe_return_cache() and maybe_write_cache()

#include "mflib.h"


int main(int argc, char *argv[]) {

  if (argc < 2) {
    warn("call like this: ./get_css_path ./script.mfl");
    exit(1);
  }

  setenv("cache", "/tmp/moonfall.cache", 1);

  //// get css file as string
  char *css_path = get_css_path(argv[1]);

  char *cache = maybe_return_cache(css_path);
  if ( cache ) {
    warn("returned cache, exiting");
    //puts(cache);
    exit(0);
  } else {
    warn("didn't return cache");
  }

  char *css_str = string_from_file(css_path);
  maybe_write_cache(css_path, css_str);

  return(0);

}


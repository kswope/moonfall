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

// Test driver for get_script_as_string()

#include "mflib.h"

int main(int argc, char *argv[]) {

  if (argc < 2) {
    warn("call like this: ./string_from_file script.mfl");
    exit(1);
  }

  char *string = get_script_as_string(argv[1]);

  printf("%s\n", string);

  return(0);

}


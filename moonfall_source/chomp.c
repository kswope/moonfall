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

// Test driver for chomp()

#include "mflib.h"


int main(int argc, char *argv[]) {

  char *str = _calloc(10000);

  strcat(str, "Lorem ipsum     \n\n     \n");

  chomp(str);

  printf(">%s<\n", str);

  return(0);

}


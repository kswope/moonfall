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

// Test driver for splice_tag()

#include "mflib.h"

int main(int argc, char *argv[]) {

  char *str = _calloc(1000);

  strcat(str, "|Lorem >[ipsum]< dolor sit amet|\n");
  strcat(str, "|Lorem >[ipsum]< dolor sit amet|\n");
  strcat(str, "|Lorem >[ipsum]< dolor sit amet|\n");
  strcat(str, "|Lorem >[ipsum]< dolor sit amet|");

  puts(str);

  char *begin = NULL;
  char *end = NULL;
  while ( (begin = strchr(str, OPEN_TAG)) != NULL ) {

    char *tag = get_tag(begin);
    free(tag);

    end = strchr(begin, CLOSE_TAG);

    str = splice_tag(str, begin, end, "x");

  }

  printf(str);
  free(str);

  return(0);

}

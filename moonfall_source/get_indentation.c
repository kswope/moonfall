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

// Test driver for get_indentation()

#include "mflib.h"

int main(int argc, char *argv[]) {


  char *str = _calloc(10000);

  strcat(str, "Lorem\n");
  strcat(str, "\tipsum\n");
  strcat(str, "\t\tdolor\n");
  strcat(str, "\t\t\tsit\n");
  strcat(str, "\t\t\t\tamet\n");
  strcat(str, "\t\t\t\t\tconsectetuer\n");
  strcat(str, "\t\t\t\t\t\tadipiscing\n");
  strcat(str, "\t\t\t\t\t\t\telit.\n");

  char *cursor =  strstr(str, "sit");
  char *indent = get_indentation(str, cursor);

  printf("%s", str);

  if ( indent ) {
    printf("%s%s", indent, cursor);
  }
  else {
    printf("%s", cursor);
  }

  free(indent);

  return(0);

}


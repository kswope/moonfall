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

// Test driver for get_tag()

#include "mflib.h"

int main(int argc, char *argv[]) {

  char *str = _calloc(10000);

  strcat(str, "Lorem [ipsum] dolor sit amet, consectetuer adipiscing elit.");
  strcat(str, "Praesent dignissim nibh. Nam et pede congue ante blandit");
  strcat(str, "aliquam. Donec viverra. Duis eget turpis. Nunc pellentesque");
  strcat(str, "dui nec nulla. Aenean dapibus. Sed in eros. Proin iaculis");
  strcat(str, "consequat ante. Pellentesque id elit eget turpis aliquet");
  strcat(str, "vehicula. Mauris dictum. Nam consectetuer. Pellentesque non");
  strcat(str, "[leo vitae orci ullamcorper bibendum. Sed eu diam ac nibh");
  strcat(str, "auctor pharetra. Duis molestie vestibulum turpis. Nulla");
  strcat(str, "facilisi. Proin risus. Integer congue, augue non dignissim");
  strcat(str, "pellentesque, libero ligula ullamcorper dolor, eget");
  strcat(str, "scelerisque elit elit id enim. Nunc eu nulla sed urna");
  strcat(str, "vehicula vehicula.");

  char *begin = NULL;
  char *str_cursor = str;
  while ( (begin = strchr(str_cursor, OPEN_TAG)) != NULL ) {

    str_cursor = begin + 1; // move past found tag

    char *tag = get_tag(begin);

    puts(tag);

    free(tag);

  }

  return(0);

}


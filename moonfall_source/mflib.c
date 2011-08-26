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

int global_first_row = 0;

//----------------------------------------------------------------------------
// malloc that exits with error message
//----------------------------------------------------------------------------
void* _malloc(int size) {

  char *buffer = malloc(size);
  if (buffer == NULL) {
    warn("_malloc error");
    exit(1);
  }

  return buffer;

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// calloc that exits with error message
//----------------------------------------------------------------------------
void* _calloc(int size) {

  char *buffer = calloc(size, 1);
  if (buffer == NULL) {
    warn("_calloc error");
    exit(1);
  }

  return buffer;

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// realloc that exits with error message
//----------------------------------------------------------------------------
void* _realloc(char *buffer, int size) {

  char *buffer2 = realloc(buffer, size);
  if (buffer == NULL) {
    warn("_realloc error");
    exit(1);
  }

  return buffer2;

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// strdup that exits with error message
//----------------------------------------------------------------------------
void* _mystrdup(const char *buffer) {

  char *buffer2 = strdup(buffer);
  if (buffer == NULL) {
    warn("_mystrdup error");
    exit(1);
  }

  return buffer2;

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void process_switches(int argc, char *argv[]) {

  if ( argc == 1 ) {
    printf("-h for help\n");
    printf("-v for version\n");
    exit(0);
  } 

  if ( argv[1] ) {

    if ( ! strcmp("-v", argv[1]) || ! strcmp("--version", argv[1]) ) {
      printf("version %s Copyright 2007 Kevin Swope\n", VERSION);
      exit(0);
    }

    if ( ! strcmp("-h", argv[1]) || ! strcmp("--help", argv[1]) ) {
      printf("./script -http will suppress headers\n");
      printf("./script -css will supress headers and css (for print() debugging)\n");
      exit(0);
    }

  } 

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Remove all trailing whitespace from string.  Leaves wasted space at end.
//----------------------------------------------------------------------------
void chomp(char *str) {

  int len = strlen(str);

  char *cursor = (str + len - 1);
  while ( cursor >= str ) {

    if ( *cursor == ' ' || *cursor == '\n' ) {
      *cursor = '\0';
    } else {
      break;
    }

    cursor--;

  }

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void underscore_to_dash(char *str) {

  char *cursor = str;

  while ( *cursor != '\0' ) {

    if ( *cursor == '_' ) {
      *cursor = '-';
    }

    cursor++;
  }

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void warn(char *fmt, ...) {

  va_list argp;
  fprintf(stderr, "*** moonfall, ");
  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
  fprintf(stderr, "\n");

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Figure out path to css source file using path to script.
// Since moonfall is run from a hashbang, second argument is script
//----------------------------------------------------------------------------
char* get_css_path(char *argv1){

  //// get current working directory
  char *cwd = _malloc(CSS_PATH_BUFF_SIZE);
  
  if (getcwd(cwd, CSS_PATH_BUFF_SIZE) == NULL) {
    warn("getcwd() error");
    return NULL;
  }
  
  char *script_path = _calloc(CSS_PATH_BUFF_SIZE);

  //// figure out path to script directory to find css path
  // starts with '.', use cwd and script path to find script dir 
  // starts with '/', done, but remove script name
  // else, assume script name has no path, we're in script dir (prob debugging)

  // relative path, (argv1) begins with a '.'
  if ( *argv1 == '.' ) {

    // prepend with cwd
    strcat(script_path, cwd);
    strcat(script_path, argv1 + 1); // also remove '.'

    // cut off script name from path, leaving /
    *(strrchr(script_path, '/') + 1) = '\0';


  }
  else if ( *argv1 == '/' ) {

    // script must begin with '/', we have an absolute path, and we are done
    strcat(script_path, argv1);

    // cut off script name from path, leaving /
    *(strrchr(script_path, '/') + 1) = '\0';

  }

  if ( getenv("css") ) {
    strcat(script_path, getenv("css"));
  } else { // go with default
    strcat(script_path, "moonfall.css");
  }

  free(cwd);
  return script_path;

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Reads file into buffer, don't forget to free returned pointer
// Warning: I got this code off the web, which is not a bad thing,
// but I'm unsure why the returned string doesn't need to be terminated.
// Is it because, fseek(fp, 0 SEEK_END) includes the EOF, which in
// turn is malloc'd room in the buffer, and then fread reads in this
// EOF which becomes the strings terminator?  If not, danger may be here.
// Ok seems this does need to be terminated, hard to track down bug,
// thx web!
//----------------------------------------------------------------------------
char* string_from_file(char *filename) {

  FILE *fp = fopen(filename , "r");
  if ( fp == NULL ) {
    warn("couldn't open %s for reading", filename); 
    exit(1);
  }

  // obtain file size:
  fseek(fp, 0, SEEK_END);
  long lSize = ftell(fp);
  rewind(fp);

  // allocate memory to contain the whole file:
  char *buffer = _malloc(lSize + 1);

  // copy the file into the buffer:
  size_t result = fread(buffer, 1, lSize, fp);
  if ( result != lSize ) {
    warn("error reading from %s", filename);
    exit (1);
  }

  fclose (fp);

  *(buffer + lSize) = '\0';

  return buffer;
  
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//  Writes out a string to a file
//----------------------------------------------------------------------------
void string_to_file(char *filename, char *str) {

  FILE *fp = fopen(filename , "w");
  if ( fp == NULL ) {
    warn("couldn't open %s for writing", filename); 
    exit(1);
  }

  fwrite (str , 1, strlen(str), fp);
  fclose (fp);

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Like string_from_file(), but removes first line,
//----------------------------------------------------------------------------
char* get_script_as_string(char *filename) {

  char *file_string = string_from_file(filename);

  char *newstr = _calloc(strlen(file_string));

  // find address past first '\n'
  char *second_line = strchr(file_string, '\n') + 1;

  strcat(newstr, second_line);

  // free the original string
  free(file_string);

  return newstr;

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Replace substring with another string.  
// This will adjust to remove marker tags:
// Example string: "replace this [var] here"  
// In this example 'begin' and 'end' are strchr() of OPEN_TAG and CLOSE_TAG
// WARNING: This will free the original string, so make sure its malloc'd
//----------------------------------------------------------------------------
char* splice_tag(char *orig_str, 
                 char *begin, 
                 char *end, 
                 char *replace) {

  // figure out lengths for new buffer
  int head_len = begin - orig_str;
  char *end_cursor = end + 1; // skip closing tag
  int tail_len = strlen(end_cursor);
  int rep_len  = strlen(replace);
  int new_len = (head_len + tail_len + rep_len);

  char *new_string = _malloc(new_len + 1);
  char *new_cursor = new_string;

  int i;

  // slurp up original sting for head_len into new
  char *orig_str_cursor = orig_str;
  for ( i = 0; i < head_len; i++ ) {
    *new_cursor++ = *orig_str_cursor++;
  }

  // slurp up replacement string
  for ( i = 0; i < rep_len; i++ ) {
    *new_cursor++ = *replace++;
  }

  // slurp up tail
  for ( i = 0; i < tail_len; i++ ) {
    *new_cursor++ = *end_cursor++;
  }

  *new_cursor = '\0';

  free(orig_str);

  return new_string;

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Gets a tag, [this_is_a_tag], from a string, beginning at passed pointer.
// Don't forget to free() returned value when you are done.
// Has a built in limit: MAX_TAG_LEN from header
//----------------------------------------------------------------------------
char* get_tag(char *begin) {

  begin++; // skip the opening OPEN_TAG

  char *end = strchr(begin, CLOSE_TAG);

  size_t tag_length = end - begin;

  // limit tag length
  tag_length = (tag_length < MAX_TAG_LEN) ? tag_length : MAX_TAG_LEN;

  char *text = _calloc(tag_length + 1);

  strncpy(text, begin, tag_length);
    
  return text;

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Reads in script
// Starts up lua interpreter
// Feeds script to lua interpreter
// Returns pointer to lua interpreter instance
//----------------------------------------------------------------------------
lua_State* get_lua(char *argv1) {

  extern char *mflib_lua; // lua source with are including with script

  // get this script as a string
  char *script_string = get_script_as_string(argv1);
  char *spacer = "\n";

  // prepend script with lua library
  char *total_script = _calloc(strlen(script_string) + 
                               strlen(mflib_lua) 
                               + 1 + strlen(spacer));
  
  strcat(total_script, mflib_lua);
  strcat(total_script, spacer);
  strcat(total_script, script_string);
  free(script_string);

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  int error = luaL_loadbuffer(L,
			      total_script,
			      strlen(total_script),
			      "lua script") || lua_pcall(L, 0, 0, 0);
  if (error) {
    warn("%s", lua_tostring(L, -1));
    lua_pop(L, 1); // pop error message from stack
  }

  free(total_script);

  return L;

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Get number from lua stack as string, append with "px", 
// return as string, don't forget to free
//----------------------------------------------------------------------------
char* num_to_px(lua_State *L, size_t lua_index) {

  // len of number as string, only way I know how
  size_t len = 0;
  lua_tolstring(L, lua_index, &len); // query length

  char *num = _calloc(len + 3); // len + "px" + '\0'

  // assemble string
  strcat(num, lua_tostring(L, lua_index)); 
  strcat(num, "px");

  return num;
  
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Figure out if cursor position is indented, if so, return whitespace
// identical to indentation level, if not, return null.
//----------------------------------------------------------------------------
char* get_indentation(char *string, char *cursor) {
 
  cursor--; // take one step back
 
  char *indent = _calloc(1); // save up transversed chars
  while ( (cursor >= string) && ((*cursor == ' ') || (*cursor == '\t')) ) {
    int bufflen = strlen(indent) + 1;
    indent = _realloc(indent, bufflen + 1); // room for one more and NULL
    *(indent + bufflen -1) = *cursor;
    *(indent + bufflen) = '\0';
    cursor--;
  }
 
  if ( *cursor == '\n' ) { // we have indentation
    return indent;
  }
  else { // not indented, hit something else before a '\n'
    return NULL;
  }
 
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Convert index on lua stack to a css attribute value.
// Strings aren't touched
// Number are appended with "px"
// Tables are turned into formatted string of css attributes.
// Anything returned needs to be free'd.
// Given "css_string" and "cursor" to figure out if table needs indentation.
//----------------------------------------------------------------------------
char* stack_index_as_css(lua_State *L, 
			 size_t lua_index, 
			 char *tag_name, // for error message
			 char *css_string, // for table_as_attr
			 char *cursor) { // for table_as_attr

  switch ( lua_type(L, -1) ) {  // figure out which type we are dealing with

  case LUA_TSTRING: {

    // get len of string in stack
    size_t len = 0;
    lua_tolstring(L, -1, &len);
    
    // copy str into buffer and return
    char *str = malloc(len + 1);
    strcpy(str, lua_tostring(L, -1));

    return(str);
    break;

  }

  case LUA_TNUMBER: { //// numbers are appended with "px"
	  	  
    char *num = num_to_px(L, -1); // get num from lua, appended with "px"
    return(num);
    break;

  }

  case LUA_TTABLE: {

    // convert table to css
    char *attr = table_as_attr(L, -1, tag_name, css_string, cursor); 
    return(attr);
    break;

  }

  case LUA_TBOOLEAN: {

    if ( lua_isboolean(L, -1) ) {
      char *str = _calloc(strlen("true") + 1);
      strcpy(str, "true");
      return str;
    }
    else {
      char *str = _calloc(strlen("false") + 1);
      strcpy(str, "false");
      return str;
    }

    break;

  }

  default: {
    warn("unhandled tag in stack_index_as_css: \"%s\", type %s",
	 tag_name,
	 lua_typename(L, lua_type(L, -1)));
    return _calloc(1); // give caller something to free
    break;

  }

  }

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Convert lua table to attributes in css
// Don't forget to free the string returned.
//----------------------------------------------------------------------------
char* table_as_attr(lua_State *L, 
		    size_t lua_index, 
		    char *tag_name,
		    char *css_string,
		    char *cursor) {

  if( ! lua_istable(L, -1) ) {
    warn("not a table passsed to table_as_attr");
    exit(1);
  }

  // figure out if these attributes need indentation in css output
  char *indent = get_indentation(css_string, cursor);

  char *css = _calloc(1); // start with empty string

  lua_pushnil(L); // first key

  while (lua_next(L, -2) != 0) { // looping over lua table

    // make a copy of key because we need to modify it
    char *key = _mystrdup(lua_tostring(L, -2));
    underscore_to_dash(key);

    // convert 10 to 10px, bools to something, and tables will recurse back here
    char *value = stack_index_as_css(L, -1, tag_name, css_string, cursor);

    if ( lua_type(L, -1) == LUA_TTABLE ) {  // value is table

      // already formatted by recursive call, just realloc and concat
      int linelen = strlen(value);
      int cssbufflen = strlen(css) + 1;
      css = _realloc(css, cssbufflen + linelen);
      *(css + cssbufflen) = '\0'; // where to start concats
      strcat(css, value);

    } else { // value is not table, turn into css line

      char *colon = NULL;
      char *end = NULL;
      if ( indent ) { // do we have indent to work with?
	colon = ": ";
	end = ";\n";
      } else { // single line
	colon = ":";
	end = "; ";
      }

      size_t linelen =
	strlen(key) +
	strlen(colon) +
	strlen(value) +
	strlen(end);

      if ( indent && ! global_first_row ) { // increase size for indent
	linelen = linelen + strlen(indent);
      }

      int cssbufflen = strlen(css) + 1;
      css = _realloc(css, cssbufflen + linelen);
      *(css + cssbufflen) = '\0'; // where to start concats
      
      if ( indent && ! global_first_row ) {
	strcat(css, indent);
      }

      strcat(css, key);
      strcat(css, colon);
      strcat(css, value);
      strcat(css, end);

    }

    lua_pop(L, 1);

    free(key);
    free(value);

    global_first_row = 0; // global hack, we're no long on first table row

  }

  free(indent);

  return css;

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// This is a replacement for lua_getglobal().
// If lua global contains dots we travel down them until we put
// final value into top of stack.  Otherwise just call lua_getglobal.
// The deal is, that lua_getglobal just sees "table2.table2.table3" as
// a one variable with 2 dots in it, it doesn't transverse, so we do that.
//----------------------------------------------------------------------------
void walk_lua_global(lua_State *L, const char *tag_name) {

  if ( ! strchr(tag_name, '.') ) {
    lua_getglobal(L, tag_name);
    return;
  }

  char *tag_name_dup = _mystrdup(tag_name);

  // count seperators in string
  int count = 0;
  char *cursor = tag_name_dup;
  while ( (cursor = strchr(cursor, '.')) ) {
    cursor++; // advance past match
    count++;
  }
	
  char *tok = NULL;
  tok = strtok(tag_name_dup, "."); // make copy, its const

  lua_getglobal(L, tok);

  if ( lua_type(L, -1) != LUA_TTABLE ) {
    // we were misled, var has dots, but this is not a table we can index
    return;
  }

  int i = 0;
  for ( i = 0; i < (count); i++ ) {
    tok = strtok(NULL, ".");
    lua_pushstring(L, tok);
    lua_gettable(L, -2);
  }

  free(tag_name_dup);

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Types of output depending on switches
//----------------------------------------------------------------------------
void output(char *argv[], char *css_str) {

  if ( argv[2] && !strcmp(argv[2], "-http") ) { // no header

    printf(css_str);
    printf("\n"); // last line doesnt show on terminal without this, why?

  } else if (argv[2] && !strcmp(argv[2], "-css")) { // no css or header

    // don't print out string, used if you want nothing but lua output

  } else { // both header and css

    printf("Content-Type: text/css\n\n");
    printf(css_str);
    printf("\n"); // last line doesnt show on terminal without this, why?

  }

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Checks if cache env variable is set, if so, checks for updated cache.  
// If cache is too old returns null, else returns cache as string.
//----------------------------------------------------------------------------
char *maybe_return_cache(char *css_path) {

  char *cache_path = getenv("cache");

  if ( ! cache_path ) {
    return NULL; // not asked to check for cache
  }

  // check is cache exists
  if ( access(cache_path, F_OK) ) { // returns -1 if file doesnt exist
    return NULL; // nope, no cache
  }

  //// check if cache is newer than css file, return if so.

  // get stat of cache file
  struct stat cache_stat;
  stat(cache_path, &cache_stat);

  // get stat of source css file
  struct stat css_stat;
  stat(css_path, &css_stat);

  if ( difftime(css_stat.st_mtime, cache_stat.st_mtime) > 0 ) {
    return NULL;
  } else {
    return string_from_file(cache_path);
  }

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Checks if cache env variable is set, if so, writes cache.  
//----------------------------------------------------------------------------
void maybe_write_cache(char *css_path, char *css_str) {

  char *cache_path = getenv("cache");

  if ( ! cache_path ) {
    return; // not asked to write cache
  }

  string_to_file(cache_path, css_str);

}
//----------------------------------------------------------------------------

/*
 * This file contains functions that helps save and load username
 */
#ifndef _FILE_SYSTEM_USERNAME_CACHE_H_
#define _FILE_SYSTEM_USERNAME_CACHE_H_

/*
 * Function: Save_Username
 * Usage: Just give the string to it
 * ---------------------------------
 */
void Save_Username(char *username);

/*
 * Function: Load_Last_Username
 * Usage: Call it and it will return the last username
 * ---------------------------------------------------
 * By default the name is 'DEFAULT'
 */
char *Load_Last_Username();

#endif //_FILE_SYSTEM_USERNAME_CACHE_H_

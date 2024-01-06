/******************************************************************
*
*   file:     cmds.c
*   author:   betty o'neil
*   date:     Oct. 9th 2022
*
*   semantic actions for commands called by tutor (cs341, mp1)
*
*   revisions:
*      9/90  eb   cleanup, convert function declarations to ansi
*      9/91  eb   changes so that this can be used for hw1
*      9/02  re   minor changes to quit command
*/
/* the Makefile arranges that #include <..> searches in the right
   places for these headers-- 200920*/

#include <stdio.h>
#include "slex.h"

/*===================================================================*
*
*   Command table for tutor program -- an array of structures of type
*   cmd -- for each command provide the token, the function to call when
*   that token is found, and the help message.
*
*   slex.h contains the typdef for struct cmd, and declares the
*   cmds array as extern to all the other parts of the program.
*   Code in slex.c parses user input command line and calls the
*   requested semantic action, passing a pointer to the cmd struct
*   and any arguments the user may have entered.
*
*===================================================================*/

/* Create Prototype for all commands (stop, md, ms, help) */
PROTOTYPE int stop(Cmd *cp, char *arguments);
PROTOTYPE int mem_display(Cmd *cp, char *arguments);
PROTOTYPE int mem_set(Cmd *cp, char *arguments);
PROTOTYPE int help(Cmd *cp, char *arguments);

/* command table */
/* Adding stop, md, ms, and help into command table */
Cmd cmds[] = {{"md",  mem_display, "Memory display: MD <addr>"},
	      {"ms", mem_set, "Memory set: MS <addr> <value>"},
	      {"h", help, "Help: H <command>"},
              {"s",   stop,        "Stop" },
              {NULL,  NULL,        NULL}};  /* null cmd to flag end of table */

char xyz = 6;  /* test global variable  */
char *pxyz = &xyz;  /* test pointer to xyz */
/*===================================================================*
*		command			routines
*
*   Each command routine is called with 2 args, the remaining
*   part of the line to parse and a pointer to the struct cmd for this
*   command. Each returns 0 for continue or 1 for all-done.
*
*===================================================================*/

/* Stop function which just returns 1 */
int stop(Cmd *cp, char *arguments)
{
  return 1;			/* all done flag */
}

/*===================================================================*
*
*   mem_display: display contents of 16 bytes in hex
*
*/

/* Memory Display function which displays contents of 16 bytes in hex */
int mem_display(Cmd *cp, char *arguments)
{ 	
  /* Creating variables int a and unsigned char pointer c */
  int a = 0;
  unsigned char *c;

  /* Using sscanf to store input in variable a */
  /* Then initialize variable c with a */
  sscanf(arguments, "%x", &a);
  c = (unsigned char *)&a; 

  /* Printing the value of variable a */
  printf("%02x ", a); 

  /* Creating a variable int i = 0 */
  /* Using a while-loop to iterate while i <= 16, because 16 pairs of hex characters */
  int i = 0;
  while(i <= 16) {
	  printf("%02x ", *(c + i));
	  i++;
  }

  /* Creating a variable int j = 0 */
  /* Using a while-loop to iterate while j <= 16, because 16 characters interpreting each byte */
  /* Using if-else statements to condition for each byte to be represented as ASCII codes from 0x20 to 0x7e or "," */
  int j = 0;
  while(j <= 16) {
          if(*(c + j) <= 0x7e && *(c + j) >= 0x20) {
		  printf("%c", *(c + j));
	  } else {
		  printf(".");
          }
	  j++;
  }

  /* Print statements to print the values and message */
  printf("\n");
  printf("Reached mem_display, passed argument string: |%s|\n", arguments);
  printf("        help message: %s\n", cp->help);
  return 0;
}

/* Memory Set funtion which stores byte values at specified address */
int mem_set(Cmd *cp, char *arguments)
{
  /* Creating variables int a, int b, and unsigned char pointer c */
  int a = 0, b = 0;
  unsigned char *c;

  /* Using sscanf to store inputs in variables a and b */
  sscanf(arguments, "%x %x", &a, &b);

  /* Then initialize variable c with a and pointer c with b */
  c = (unsigned char *)&a;
  *c = b;

  /* Simply return 0 at end of function */
  return 0;
}

/* Help function which helps on the specified command, or all commands if no argument */
int help(Cmd *cp, char *arguments)
{
  /* Creating variables char x, int n, int m, and int l which is (n/m) */
  char x[2];
  int n = sizeof(cmds);
  int m = sizeof(Cmd);
  int l = (n/m);

  /* Using sscanf to store input in variable x */
  sscanf(arguments, "%s", x);

  /* Creating a variable int i = 0 */
  /* Using a for-loop to iterate starting from i = 0 and for i < l */
  /* Using if statements in for-loop to create conition if (strcmp(cmds[i].cmdtoken, x) = 0),
   * where cmd token records the list of arguments and environment variables that are associated with a command */
  /* Using "strcmp" to compare two strings for if statement */
  int i = 0;
  for(i = 0; i < l; i++) {
	  if(strcmp(cmds[i].cmdtoken, x) == 0) {
		  printf("%s\n", cmds[i].help);
          }
  }

  /* Simply return 0 at end of function */
  return 0;
}


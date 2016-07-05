/**
 * Troulakis Giorgos Rafail
 * CSD
 * AM 2716
 * Assignment 1
 * HY345
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>



static clock_t st_time;
static clock_t en_time;
static struct tms st_cpu;
static struct tms en_cpu;

struct tms {
clock_t tms_utime; /* user time */
clock_t tms_stime; /* system time */
clock_t tms_cutime; /* user time of children */
clock_t tms_cstime; /* system time of children */
};



char cwd[1024];
char *array[15],*arraytmp[15],*arraytmp0[15],*array1[15],*outputfile[0],*arrayenv[15],*arraypipes[15],*inouput[1],*arraywithoutTime[15];
char *instr;
int pip,kout=0;
int GLOBAL_i=0;

/*
 * if it is 1 the char will be '<',else if it is 2 the char will be '>'
 */
int type_redirection=0,we_have_envs=0,execution=0,PrevChildpid,status;

/*
 * commands
 */

char *command;
char *command_path;
char *def_bin_path;

/*
 * arguments
 */
char *p,*pi;
char buffer[100],inbuffer[100];
char tmpbuffer[100];

/**
 *prints the login with dir
 */
void login_etc_print();

/**
 *read and parse in tokens the whole line which user gives
 */
void read_and_parse();

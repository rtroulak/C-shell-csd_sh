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
#include "Cshell.h"
#include <sys/time.h>
#include <time.h>
#include <stdint.h>







void start_clock(){
  st_time = times(&st_cpu);
}

void end_clock(char *msg){
  en_time = times(&en_cpu);
  fputs(msg,stdout);
  
  printf("\nen_time: %d\n",(int)en_time);
  printf("st_time: %d\n",(int)st_time);
  
  printf("en_cpu.tms_utime: %d\n",(int)en_cpu.tms_utime);
  printf("et_cpu.tms_stime: %d\n",(int)en_cpu.tms_stime);
  printf("st_cpu.tms_utime: %d\n",(int)st_cpu.tms_utime);
  printf("st_cpu.tms_stime: %d\n",(int)st_cpu.tms_stime);
  printf("Real Time: %d, User Time %d, System Time %d\n",(int)(en_time - st_time),(int)(en_cpu.tms_utime - st_cpu.tms_utime),(int)(en_cpu.tms_stime - st_cpu.tms_stime));
}






/**
 *prints the login with dir
 */
void login_etc_print(){
    printf("%s@csd_sh:~",getlogin());
 
    if (getcwd(cwd, sizeof(cwd)) != NULL)
       fprintf(stdout, "%s", cwd);
    printf("/$  ");
  }

 
 void initarray(){
   int i=0;
   for(i=0;i<=15;i++){
     
     array[i]=NULL;
     array1[i]=NULL;
     
  }

   
   
}
  
/**
 *read and parse in tokens the whole line which user gives
 */
void read_and_parse(){
    GLOBAL_i=0;
    initarray();
    int i=0,j=0,o=0,o1=0,lt=0,mt=0,mmt=0,it=0,ex=0,exe=0;
    
    pip=0;
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strlen(buffer)-1] = '\0';
    
   
    
    strcpy(tmpbuffer, buffer);
 
    
    
    
    
    
    for(i=0;i<strlen(tmpbuffer);i++){
    /**
 * STRTOK FOR '|'
 */
    
    //printf("%c",buffer[i]);
    if(buffer[i]=='|'){
    pi = strtok (tmpbuffer,"|"); 
    while (pi != NULL)
    {
     // printf("%s,",p);
      arraypipes[pip++] = pi;
       printf("%s,",arraypipes[pip-1]);
      pi = strtok (NULL, "|");
      
    }
 
    if(pip>1){
      
      type_redirection=5;
    }
    }
    
    if(i+1==strlen(tmpbuffer)){
      
      if(buffer[i]=='&'){
	printf("\t\t\t\t\t\n\nteleutaio=%c\n\n",buffer[i]);
	buffer[i]=' ';
	GLOBAL_i=1;
      }
    }
    if(buffer[i]=='>'){
       kout=1;
    }
    }  
    
/**
 * STRTOK FOR '<'
 */
    p = strtok (buffer,"<");  
    while (p != NULL)
    {
      array1[lt++] = p;
      p = strtok (NULL, "<");
      
    }
    
    if(lt>1){
      
      type_redirection=1;
    }
    
 

/**
 * STRTOK FOR '>'
 */
    for(i=0;i<strlen(buffer);i++){
      
      if(buffer[i]=='>' && mmt==1){
	type_redirection=3;
	mmt=0;
      }
      else if(buffer[i]=='>' && mmt==0){
	
	mmt=1;
      }
      
    }

     p = strtok (buffer,">"); 
    while (p != NULL)
    {
      array1[mt++] = p;
      p = strtok (NULL, ">");
      
    }
    
    if(mt>1){
     
      if(mmt==1)
	type_redirection=2;
    }
    

    
 
   
 /**
 * STRTOK FOR ' '
 */
  p = strtok (array1[0], " ");
   while (p != NULL)
    {
      if(j==0)
	command=p;
      array[j++] = p;
      p = strtok (NULL, " ");
    }

 
 
 /*check for enviroments*/
 for(i=0;i<j;i++){
   
    if(strcmp(array[i],"=")==0){
      
      we_have_envs=1;
      
    }
   
  
   
  }
  
 /**
 * STRTOK FOR '='
 */
   p = strtok (buffer,"="); 
    while (p != NULL)
    {
      arrayenv[it++] = p;
      p = strtok (NULL, "=");
      
    }
    
    if(it>1){
	we_have_envs=1;
    }
    
 /**
 * STRTOK FOR './'
 */

    if(array[0][0]=='.'){
      if(array[0][1]=='/'){
      printf("teleia kai backslash!\n");
      ex=1;
      }
    }
    
    if(ex==1){
      ex=0;
      execution=2;
    }
    
//     int last=0;
//    while(array[j][last+1]!=NULL){
//       
//       
//       last++;
//     }
//  printf("\n\t\t\t\tteleutaio=%c\n",array[j][last-1]);
 
 
 
 
 

 }
 


 

 
void main(int argc, char *argv[]){
  
    pid_t child;
    pid_t c;
    
   
    
    while(1){
    
    type_redirection=0; 
    login_etc_print();
    read_and_parse();
    
   
    int i=0,j=0,flag_io=0;
    /*
    while(arrayenv[j]!=NULL) {
      printf("a!rray%d: %s\n",j, arrayenv[j]);
      j++;
    }
    */
      
 
    
    j=0;
      if(strcmp(array[0],"exit")==0 ){
      
      exit(666);
      }
      
      
      if(strcmp(array[0],"setenv")==0){
	
	we_have_envs=1;
	arrayenv[0]=array[1];
	arrayenv[1]=array[2];
	printf("VAR=%s and VAL=%s\n",arrayenv[0],arrayenv[1]);
	
      }
      
      if(strcmp(array[0],"unsetenv")==0){
	
	we_have_envs=2;
	arrayenv[0]=array[1];
	printf("VAR=%s to delete\n",arrayenv[0]);
	
      }
      
      
      if(we_have_envs==1){
	
	printf("we have enviroments\n");
	setenv(arrayenv[0],arrayenv[1],0);
	we_have_envs=0;
	
	
      }else if(we_have_envs==2){
	
	printf("we have enviroments to del\n");
	unsetenv(arrayenv[0]);
	we_have_envs=0;
      }
      
      
       
  
    if(strcmp(array[0],"cd")==0){
	
	
	
	PrevChildpid=getpid();
	printf("Child: PID of Child = %ld\n", (long) getpid());
	
	char *new_pth;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	  asprintf(&new_pth,"%s%s%s",cwd,"/",array[1]);
	  
	chdir(new_pth);
	  
	
      }else{
 

	
	
	
	
	
	
  //PIPES PARSING
   
   if(pip>0){
      
      
      int y=0;
      printf("noPipes=%d\n",pip);
     
      while(arraypipes[y]!=NULL){
	printf(" pipes: %s\n",arraypipes[y]);
	y++;
      }
    
    
      /**
      * STRTOK FOR ' '
      */
      p = strtok (arraypipes[0], " ");
      while (p != NULL)
      {
	if(j==0)
	  command=p;
	arraytmp0[j++] = p;
	p = strtok (NULL, " ");
      }
    
    
    
	j=0;
      
      p = strtok (arraypipes[1], " ");
      while (p != NULL)
      {
	if(j==0)
	  command=p;
	arraytmp[j++] = p;
	p = strtok (NULL, " ");
      }
      
      
    }/*
    i=0;
    printf("ARRAY:");
    while(arraytmp0[i]!=NULL){
    printf("%s ",arraytmp0[i]);
    
      i++;
    }
    printf("\n");
    i=0;
    printf("ARRAYtmp:");
    while(arraytmp[i]!=NULL){
    printf("%s ",arraytmp[i]);
    
      i++;
    }
    printf("\n");
    
    */
    
    
  // END OF PIPES
  
  
  
  
  
  
    
    
    
        
       if(pip>0){
	
	 
	int     fd[2];
	pid_t   childpid;
	char    readbuffer[80];
	pipe(fd);
	//printf("HERE WE HAVE PIPES\n");
	
	
	command_path="/bin/";
	char *new_str1;
	asprintf(&new_str1,"%s%s",command_path,arraytmp[0]);
	
	
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        } 
        if(childpid == 0)
        {
	  
	  //printf("!pid=%d\n",childpid);
	  
	  //printf("i'm the child used for %s \n",arraytmp0[0]);
	  dup2(fd[1], STDOUT_FILENO);
	  close(fd[1]);
	  execvp(arraytmp0[0],arraytmp0);
	}    /*parent process*/
	else
        {	
	  
	  childpid=fork();

        if(childpid==0)
        {
            //printf("i'm in the second child, which will be used to run %s\n",arraytmp[0]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
	    if(strcmp(arraytmp[0],"sort")==0){
		execv(new_str1, arraytmp);
	      
	    }
	    else
	      execvp(arraytmp[0],arraytmp);
        }
	  
	}
	
	
	
	wait();
	
    
       }else{ 
	 
	 
	 child = fork();
	 
	 if (child == 0) { /* Child process. */
   
      
      printf("Child Process\n");
   
      
      
      if(execution==2){
 	
 
 	execution=0;
	execvp(array[0], array);
	
 	
	
      }
      
      int xi=1,yi=0;
      while(array[xi]!=NULL){
      arraywithoutTime[yi]=array[xi];
      
      xi++;
      yi++;
      }
      
      if(strcmp(array[0],"csdTime")==0){
	
	printf("execution with timers\n");
	struct tms cpu_time;
	clock_t start,end,elapsed;
	start=times(&cpu_time);
	execvp(arraywithoutTime[1], arraywithoutTime);
	execution=0;
	end=times(&cpu_time);
	elapsed=end-start;    //elapsed real time
	printf("user: %jd,   sys: %jd real %jd\n",(intmax_t) cpu_time.tms_utime, (intmax_t) cpu_time.tms_stime,(intmax_t)elapsed);
	
      }
      
      
      
      
      
      
      
      command_path="/bin/";
      char *new_str;
      asprintf(&new_str,"%s%s",command_path,command);
      if(strcmp(array[0],"cd")==1){
	
      
      printf("Child: PID of Child = %ld\n", (long) getpid());
      
      if(type_redirection==0){
      execv(new_str, array); /* array[0] has the command name. */
      
      
      
      /* If the child process reaches this point, then */
      /* execv must have failed. */
      fprintf(stderr, "Child process could not do execv.We will try execvp....\n");
      /*we try with execvp*/
      execvp(array[0], array);
      exit(1);
      }else  if(type_redirection==3){
	
	printf("output mode3...\n");
	
	FILE* file= fopen (array1[1], "a+");
	dup2(fileno(file), fileno(stdout));
	fclose(file);
	type_redirection=0;
	
	execv(new_str, array); 
	exit(1);
	fprintf(stderr, "Child process could not do execv.We will try execvp2....\n");
        execvp(array[0], array);
	exit(1);
	
	
      }
      else  if(type_redirection==2){
	
	printf("output mode2...\n");
	
	FILE* file= fopen (array1[1], "w+");
	dup2(fileno(file), fileno(stdout));
	fclose(file);
	type_redirection=0;
	
	execv(new_str, array); 
	exit(1);
	fprintf(stderr, "Child process could not do execv.We will try execvp2....\n");
        execvp(array[0], array);
	exit(1);
	
	
      }
      else  if(type_redirection==1){
	  printf("input mode!...\n");
	  int yolo=0;
	    strcpy(inbuffer,buffer);
	   
	    
	  int c1;
	  FILE* in_file1= fopen (array1[1],"r");
	  
	  while ((c1 = getc(in_file1)) != EOF)
	  putchar(c1);
	
	  dup2(fileno(in_file1), 1);
	  fclose(in_file1);
	  type_redirection=0;
	  execv(new_str, array); 
	  exit(1);
	  fprintf(stderr, "Child process could not do execv.We will try execvp2....\n");
	  execvp(array[0], array);
	  
	 
	  
	  exit(1);
	
      }
      
      
      
      
      
      fprintf(stderr, "Child process could not do execvp.We will try another?....\n");
      //exit(1);
      
      }
      
      if(strcmp(array[0],"cat")==0){
	
	//printf("111input mode1...%s\ntype=%d\n",array1[1],type_redirection);
	int yolo=0;
	
	
	
	
	if(kout>0){
	  
	    
	     kout=0;
	     p = strtok (array1[1],">"); 
	    while (p != NULL)
	    {
	    inouput[yolo++] = p;
	    p = strtok (NULL, ">");
      
	    }
	    yolo=0;
	 /*   
	  int c3;
	  FILE* in_file3= fopen (inouput[1],"r");
	  
	  while ((c3 = getc(in_file3)) != EOF)
	  putchar(c3);
	
	  */
	   /* 
	  dup2(fileno(in_file3), 1);
	  fclose(in_file3);
	  */
	   
	   
	  FILE* file3= fopen (inouput[1], "w+");
	  dup2(fileno(file3), fileno(stdout));
	  
	
	  fclose(file3);
	 
	  
	  type_redirection=0;
	
	  execv(new_str, array); 
	  exit(1);
	  fprintf(stderr, "Child process could not do execv.We will try execvp2....\n");
	  execvp(array[0], array);
	  exit(1);
	    
	    
	   
	  }
	
	
	
	
	
	
	
	
	int c;
	FILE* in_file;
	if(type_redirection==1){
	  //printf("array1[1]=%s\n",array1[1]);
	  in_file= fopen (array1[1],"r");
	}
	else{
	  in_file= fopen (array[1],"r");
	  //printf("array[1]=%s",array[1]);
	}
	
	
	while ((c = getc(in_file)) != EOF)
	  putchar(c);
	
	//dup2(fileno(in_file), 1);
	fclose(in_file);
	type_redirection=0;
	
	}
      
      
    }
    /*parent process*/
    else if(child>1){
      printf("Parent process \n");
      if(GLOBAL_i==0)
	wait();
      else{
	wait(child, &status, WNOHANG);
	printf("Child will running in backround is %d\n", child);
	
      }
      
    }
    
      }

    }
    
    
    
    }
   
    
}

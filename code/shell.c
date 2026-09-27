/* fork_exec.c — compile: gcc -o fork_exec fork_exec.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// DONE DARFT 1 display cs4023-shell> and read a complete command line
// from stand input using fgets() or getline(). 
//Strip the trailing newline
int main(int argc, string argv[]) { //get input
    char input[100];  //character array
    
    printf("<CS4023-shell>\n"); //print start of command line
    if (fgets(input, sizeof(input), stdin) == NULL)
    { //fgets()  reads a line & stores into string stored by str
        printf("Fail to read the input stream");
    } //fgets() reads the trailing newline character & retunrs data string followed by '\n'                                              
    else
    {       //solution strcspn() function                                   
         input[strcspn(input, "\n")] = '\0';    //we have given "\n" as a second-string so we will get the length of the string before the "\n", now put the "\0"in the place of "\n"        
    }
    printf("Entered data = , %s\n", input);//CHECK DO I NEED TO PRINT THIS
    return 0; //might need to move 

//DONE DRAFT 1tokenise? the command line into an argument vector? 
//(argv[]) terminated by NULL? when how ?, seperating the program
//name? what is the program name? from its arguments using spaces an tabs? manually just like printing spaces where for what?

//explanaitons:tokenization is the process of breaking a string into smaller parts , called tokens, using delimiters like spaces, commas or other characters
//strtok() to simplify tokenization  parsing strings 
//./myprogram is the program name arg1 arg2 are the arguments, so we need to split them from eachother
//we need to store each token somewhere
//an argument vector is an array of strings char *argv[] so each token becomes an element
//after stroing all tokens, the very last element needs to be NULL, so other functions know when the argument list ends
//like the \0 at the end of the string , but here its the end of an array of strings
    char delimiter[] = " "; //to split up
    char *token; //empty string to store token
    token = strtok(input, delimiter); //get the first token
    char *argv[100]; //create array for strings
    int countOfTokens = 0;
    while (token) //while loop to get the rest of token 
    {
        printf("%s\n", token); //only need for testing print out seperation i think
        argv[countOfTokens] = token; //trying to store token in an array
        countOfTokens++;
        token = strtok(NULL, delimiter);
    }
    argv[countOfTokens] = NULL; //tryign to make the poisiton after the last input NULL
    return 0;

//DONE DRAFT 1 for each non-built in command call fork()
//to create a child process then call execvp() in the child
//parent calls waitpid() to collect child's exit status
//print a message if exit status is non-zero
    pid_t pid = fork();
    int status;
    if (pid < 0)  
    {
        perror("error: ");
        continue; //continue, report problem and carry on 
    }
    if (pid == 0) 
    { /* I am the child  */
    execvp(argv[0], argv); //argv[0] slot holding command name 
    exit(-1); //if execvp fails (returns) not sure if this belongs here
    }
    else          
    { 
    /* I am the parent, pid = child's PID */ 
    waitpid(pid, &status, 0); //& for pointing to address
    
    }
    if (WIFEXITED(status) && WEXITSTATUS(status))//the child exited normally and its exit code is non zero
    { 
        printf("%d: my child exited with a non-zero status %d\n", getpid(), WEXITSTATUS(status));
    }



//handle cmd1 or cmd2  by calling pipe() to create a kernel pipe
//forking 2 children , redirecting child 1s stdout to the pipe write end
//and child twos stdin to the pipe read end via dup2(), closing all surplus file descriptors
//in both parent and child and waiting for both children
//pipe() fills an array of two file descriptors, index read and write, FIFO
    char inbuf[input];
    int fileDesc[2]; //new array for file descriptors, 0 is read, 1 is write
    if (pipe(fileDesc) < 0)
    {
        exit(1);
    }
//fork() decide which branch of code runs in which process
    for (int i = 0; i < 2; i++) //child block pid == 0 pick command by i -> dup2 close pipe ends then execvp
    {
        pid = fork();
        if (pid == 0 )
        {
            getpid(); //not sure where dup2() fits in or STDIN.. STDOUT, not sure code wise how to redirect child stdoutput to write end
        if (i == 0)
        {
            dup2(fileDesc[0], STDOUT_FILENO);
            close();
            waitpid();
            execvp(args[0],args);
        }
        else if (i == 1)
        {
            dup2(fileDesc[1], STDIN_FILENO);
            close();
            waitpid();
            execvp(args[1],args);
        }
    } //parent after loop closes both ends -> waitpid for both children
    }
//dup2(), argument order important which descriptor gets duplicated onto which, STDIN_FILENO and STDOUT_FILENO
//after a child has redirected with dup2() does it still need the original pipe descriptor open
//execvp() to actually run cmd1 and cmd2 , exec family of functions
//waitpid() and wait() , to reap both children in the parent 
    return 0;
}

//handle cmd > file (truncate and wrie) , cmd < file (file from file)
//and cmd >> file(Append) by opening a file with the apporpriate open() flags 
//and calling dup2() to redirect the relevant standard stream

//handle cmd & fork and execute the command without calling wait()
//immediatly, the shell prints [PID] <pid> and immediatly returns to the prompt 

//implement exit cd [dir] and pwd

// install a SIGNT handler using sigaction() so that CTRL+C
//kills the current foreground child process but does not terminate
// the shell itself, the shel m,ust not exit on SIGINT it must redisplay the prompt 


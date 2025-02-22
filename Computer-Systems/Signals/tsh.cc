// 
// tsh - A tiny shell program with job control
// 
// <Put your name and login ID here>
//

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string>

#include "globals.h" //excluded
#include "jobs.h" //excluded
#include "helper-routines.h" //excluded

//
// Needed global variable definitions
//

static char prompt[] = "tsh> ";
int verbose = 0;

//
// You need to implement the functions eval, builtin_cmd, do_bgfg,
// waitfg, sigchld_handler, sigstp_handler, sigint_handler
//
// The code below provides the "prototypes" for those functions
// so that earlier code can refer to them. You need to fill in the
// function bodies below.
// 

void eval(char *cmdline);
int builtin_cmd(char **argv);
void do_bgfg(char **argv);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

//
// main - The shell's main routine 
//
int main(int argc, char **argv) 
{
  int emit_prompt = 1; // emit prompt (default)

  //
  // Redirect stderr to stdout (so that driver will get all output
  // on the pipe connected to stdout)
  //
  dup2(1, 2);

  /* Parse the command line */
  char c;
  while ((c = getopt(argc, argv, "hvp")) != EOF) {
    switch (c) {
    case 'h':             // print help message
      usage();
      break;
    case 'v':             // emit additional diagnostic info
      verbose = 1;
      break;
    case 'p':             // don't print a prompt
      emit_prompt = 0;  // handy for automatic testing
      break;
    default:
      usage();
    }
  }

  //
  // Install the signal handlers
  //

  //
  // These are the ones you will need to implement
  //
  Signal(SIGINT,  sigint_handler);   // ctrl-c
  Signal(SIGTSTP, sigtstp_handler);  // ctrl-z
  Signal(SIGCHLD, sigchld_handler);  // Terminated or stopped child

  //
  // This one provides a clean way to kill the shell
  //
  Signal(SIGQUIT, sigquit_handler); 

  //
  // Initialize the job list
  //
  initjobs(jobs);

  //
  // Execute the shell's read/eval loop
  //
  for(;;) {
    //
    // Read command line
    //
    if (emit_prompt) {
      printf("%s", prompt);
      fflush(stdout);
    }

    char cmdline[MAXLINE];

    if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
      app_error("fgets error");
    }
    //
    // End of file? (did user type ctrl-d?)
    //
    if (feof(stdin)) {
      fflush(stdout);
      exit(0);
    }

    //
    // Evaluate command line
    //
    eval(cmdline);
    fflush(stdout);
    fflush(stdout);
  } 

  exit(0); //control never reaches here
}
  
/////////////////////////////////////////////////////////////////////////////
//
// eval - Evaluate the command line that the user has just typed in
// 
// If the user has requested a built-in command (quit, jobs, bg or fg)
// then execute it immediately. Otherwise, fork a child process and
// run the job in the context of the child. If the job is running in
// the foreground, wait for it to terminate and then return.  Note:
// each child process must have a unique process group ID so that our
// background children don't receive SIGINT (SIGTSTP) from the kernel
// when we type ctrl-c (ctrl-z) at the keyboard.
//
void eval(char *cmdline) 
{
  char* argv[MAXARGS]; /* holds cmd line args */
  int bg = parseline(cmdline, argv); /* parses line cmd line into argv and keeps track if process is bg or not */
  pid_t pid; /* process id */

  // Setting up signal blocker mask
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    // mask will now block SIGCHLD signals from being sent during eval execution
  // ---

  if (argv[0] == NULL)  return;   /* ignore empty lines */
  if (!builtin_cmd(argv)) { /* is the command not a builtin command? */
    sigprocmask(SIG_BLOCK, &mask, 0); // start SIGCHLD blocking
    if ((pid = fork()) == 0) { /* If we're in the child process */
      setpgid(0, 0);
      if (execve(argv[0], argv, environ) < 0) { /* Checks if exec is successful */
        printf("%s: Command not found\n", argv[0]);
        exit(0); /* exits child process */
      }

    } else {
      if (bg == 1) { /* is the process a bg process? */
        addjob(jobs, pid, BG, cmdline); /* add it to jobs list */
        sigprocmask(SIG_UNBLOCK, &mask, NULL); // resume taking SIGCHLD
        printf("[%d] (%d) %s", pid2jid(pid), pid, cmdline);
      } else { /* then the process must be a fg process */
        addjob(jobs, pid, FG, cmdline); /* add it to the jobs list */
        sigprocmask(SIG_UNBLOCK, &mask, NULL); // resume taking SIGCHLD
        waitfg(pid); /* waits until fg child process finishes to reap it */
      }
    }
  }
  return;
}


/////////////////////////////////////////////////////////////////////////////
//
// builtin_cmd - If the user has typed a built-in command then execute
// it immediately. The command name would be in argv[0] and
// is a C string. We've cast this to a C++ string type to simplify
// string comparisons; however, the do_bgfg routine will need 
// to use the argv array as well to look for a job number.
//
int builtin_cmd(char **argv) 
{
  if (!strcmp(argv[0], "quit")) { 
      /* test for quit command */
    //raise(SIGQUIT);
    exit(0);
  } else if (!strcmp(argv[0], "fg") || !strcmp(argv[0], "bg")) {
      /* test for bg/fg process command */
    do_bgfg(argv);
    return 1;
  } else if (!strcmp(argv[0], "jobs")) {
      /* test of jobs list command */
    listjobs(jobs);
    return 1;
  } else if (!strcmp(argv[0], "&")) {
    return 1;
  }
  return 0;     /* not a builtin command */
}

/////////////////////////////////////////////////////////////////////////////
//
// do_bgfg - Execute the builtin bg and fg commands
//
void do_bgfg(char **argv) 
{
  ////// BEGIN PROVIDED CODE
  struct job_t *jobp=NULL;
  int jid;
  pid_t pid;  
  /* Ignore command if no argument */
  if (!argv[1]) {
    printf("%s command requires PID or %%jobid argument\n", argv[0]);
    return;
  }
  /* Parse the required PID or %JID arg */
  if (isdigit(argv[1][0])) {
    pid = atoi(argv[1]);
    if (!(jobp = getjobpid(jobs, pid))) {
      printf("(%d): No such process\n", pid);
      return;
    }
  }
  else if (argv[1][0] == '%') {
    jid = atoi(&argv[1][1]);
    if (!(jobp = getjobjid(jobs, jid))) {
      printf("%s: No such job\n", argv[1]);
      return;
    }
  }	    
  else {
    printf("%s: argument must be a PID or %%jobid\n", argv[0]);
    return;
  }
  ////// END PROVIDED CODE



  pid = jobp->pid;
  if (!strcmp(argv[0], "fg")) { 
      // is it a fg process?
    jobp->state = FG; /* adjust state accordingly */
    kill(-pid, SIGCONT); /* send cont signal */
    waitfg(jobp->pid); /* wait for child process to execute */
  } else if (!strcmp(argv[0], "bg")) { 
      // is is a bg process?
    jobp->state = BG; /* adjust state accordingly */
    kill(-pid, SIGCONT); /* send cont signal */
    printf("[%d] (%d) %s", jobp->jid, jobp->pid, jobp->cmdline);
  }
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// waitfg - Block until process pid is no longer the foreground process
//
void waitfg(pid_t pid)
{
  while (fgpid(jobs) == pid) sleep(1);
    // while the current pid is a gf process
    // cycle through infinite loop, checking status every second
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// Signal handlers
//


/////////////////////////////////////////////////////////////////////////////
//
// sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
//     a child job terminates (becomes a zombie), or stops because it
//     received a SIGSTOP or SIGTSTP signal. The handler reaps all
//     available zombie children, but doesn't wait for any other
//     currently running children to terminate.  
//
void sigchld_handler(int sig) 
{
  pid_t pid;
  int status;
  
  // Setting up signal blocking mask
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, 0);
  // --- 

    // WNOHANG: allow waiting
    // WUNTRACED: is child stopped status flag
  while ((pid = waitpid(WAIT_ANY, &status, WNOHANG | WUNTRACED)) > 0) {
      // If either flags are active, loop through the following:
  
    if (WIFSIGNALED(status)) { /* upon signal recieved */
      printf("Job [%d] (%d) terminated by signal %d\n", pid2jid(pid), pid, WTERMSIG(status));
      deletejob(jobs, pid); // removes the job from job list
    } 
    
    else if (WIFSTOPPED(status)) { /* upon child stopped */
      printf("Job [%d] (%d) stopped by signal %d\n", pid2jid(pid), pid, WSTOPSIG(status));
      getjobpid(jobs, pid)->state = ST; /* change state to STopped */
    }

    else if (WIFEXITED(status)) {
      deletejob(jobs, pid); // remove exited processes from job list
    }
  }
  sigprocmask(SIG_UNBLOCK, &mask, 0); // resume taking signals
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// sigint_handler - The kernel sends a SIGINT to the shell whenver the
//    user types ctrl-c at the keyboard.  Catch it and send it along
//    to the foreground job.  
//
void sigint_handler(int sig) 
{
  pid_t pid = fgpid(jobs); // get current fg pid of job
  if (pid > 0) kill(-pid, sig); // if the non-child pid exists, send sig (SIGSTP) to all jobs of pid
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
//     the user types ctrl-z at the keyboard. Catch it and suspend the
//     foreground job by sending it a SIGTSTP.  
//
void sigtstp_handler(int sig) 
{
  pid_t pid = fgpid(jobs); // get current fg pid of job
  if (pid > 0) kill(-pid, sig); // if the non-child pid exists, send sig (SIGSTP) to all jobs of pid
  return;
}

/*********************
 * End signal handlers
 *********************/




/*
//// Execute command: ////
// killall myspin myint myfork tsh
// make clean
// make
// ./shellAutograder.py
*/
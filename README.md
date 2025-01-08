# PipeFlow
---
## Project Overview
---
<mark>**What is a Pipe in Linux?**</mark>

![image](assets/pipe.jpg)

**The Pipe** is a command in Linux that lets you use two or more commands such that output of one command serves as input to the next. In short, the output of each process directly as input to the next one like a pipeline. The symbol ‘|’ denotes a pipe.

Pipes help you mash-up two or more commands at the same time and run them consecutively. You can use powerful commands which can perform complex tasks in a jiffy.

Let us understand this with an example.

When you use ‘cat’ command to view a file which spans multiple pages, the prompt quickly jumps to the last page of the file, and you do not see the content in the middle.

To avoid this, you can pipe the output of the ‘cat’ command to ‘less’ which will show you only one scroll length of content at a time.

```bash
$ cat filename | less 
```
**therefor** 
in this project we choud do the same thing that pipe do.

![image](assets/pipe2.jpg)

## Sources
---
**in this project we are allowed to use the following functions:**

* [**access**](http://manpagesfr.free.fr/man/man2/access.2.html)
* [**open**](http://manpagesfr.free.fr/man/man2/open.2.html)
* [**unlink**](http://manpagesfr.free.fr/man/man2/unlink.2.html)
* [**close**](http://manpagesfr.free.fr/man/man2/close.2.html)
* [**read**](http://manpagesfr.free.fr/man/man2/read.2.html)
* [**write**](http://manpagesfr.free.fr/man/man2/write.2.html)
* [**malloc**](http://manpagesfr.free.fr/man/man3/malloc.3.html)
* [**waitpid**](https://linux.die.net/man/3/waitpid)
* [**wait**](http://manpagesfr.free.fr/man/man2/wait.2.html)
* [**free**](http://manpagesfr.free.fr/man/man3/malloc.3.html)
* [**pipe**](http://manpagesfr.free.fr/man/man2/pipe.2.html)
* [**dup**](http://manpagesfr.free.fr/man/man2/dup.2.html)
* [**dup2**](http://manpagesfr.free.fr/man/man2/dup.2.html)
* [**execve**](https://man7.org/linux/man-pages/man2/execve.2.html)
* [**fork**](http://manpagesfr.free.fr/man/man2/fork.2.html)
* [**perror**](http://manpagesfr.free.fr/man/man3/perror.3.html)
* [**strerror**](http://manpagesfr.free.fr/man/man3/strerror.3.html)
* [**exit**](http://manpagesfr.free.fr/man/man3/exit.3.html)

**others sources should help you :**

* [**Unix Processes in C**](https://www.youtube.com/watch?v=PErrlOx3LYE&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=22) a good youtube playlist to inderstanding  how processing works in c .
* [**Pipex Cookbook**](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901)

## About functions
---
* <span an style="color: red;">**access** :</span>


The **access()** function is used to determine whether the user has permission to access a file (or whether a file is stored
 
in).

**Format** :

```
#include <unistd.h>

int access(const char *pathname, int how);
```
When checking to see if a process has appropriate permissions, access() looks at the real user ID (UID) and group ID (GID), not the effective IDs.

pathname is the name of the file whose accessibility you want to test. The how argument indicates the access modes you want to test. The following symbols are defined in the unistd.h header file for use in the how argument :

F_OK
Tests whether the file exists.

R_OK
Tests whether the file can be accessed for reading.

W_OK
Tests whether the file can be accessed for writing.

X_OK
Tests whether the file can be accessed for execution.

**Returned value** :

If the specified access is permitted, access() returns 0.

If the given file cannot be accessed in the specified way, access() returns -1 and sets errno to one of the following values:

**Example** :

```
#include <stdio.h>
#include <unistd.h>

main() {
  char path[]="⁄";

  if (access(path, F_OK) != 0)
    printf("'%s' does not exist!\n", path);
  else {
    if (access(path, R_OK) == 0)
      printf("You have read access to '%s'\n", path);
    if (access(path, W_OK) == 0)
      printf("You have write access to '%s'\n", path);
    if (access(path, X_OK) == 0)
      printf("You have search access to '%s'\n", path);
  }
}
```
* <span an style="color: red;">**open** :</span>

The **open()** function creates and returns a new file descriptor for the file named by filename. Initially, the file position indicator for the file is at the beginning of the file. The argument mode (see Permission Bits) is used only when a file is created, but it doesn’t hurt to supply the argument in any case.

**Function Definition** :

```
int open(const char *path, int oflags);
int open(const char *path, int oflags, mode_t mode);
```

| Field         | Description          |
| ------------- |:-------------:|
| const char *path      | The relative or absolute path to the file that is to be opened. |
| int oflags      | A bitwise 'or' separated list of values that determine the method in which the file is to be opened (whether it should be read only, read/write, whether it should be cleared when opened, etc). See a list of legal values for this field at the end.     |
| mode_t mode | A bitwise 'or' separated list of values that determine the permissions of the file if it is created. See a list of legal values at the end.      |
|return value | Returns the file descriptor for the new file. The file descriptor returned is always the smallest integer greater than zero that is still available. If a negative value is returned, then there was an error opening the file.|

**Example** :

```
#include <unistd.h>
#include <fcntl.h>
 
int main()
{
    int filedesc = open("testfile.txt", O_WRONLY | O_APPEND);
    if(filedesc < 0)
        return 1;
 
    if(write(filedesc,"This will be output to testfile.txt\n", 36) != 36)
    {
        write(2,"There was an error writing to testfile.txt\n");
        return 1;
    }
 
    return 0;
}
```
**Available Values for oflag** :

Value	    |   Meaning     |
|-----------|:-------------:|
O_RDONLY    |   Open the file so that it is read only.
O_WRONLY	| Open the file so that it is write only.
O_RDWR	    | Open the file so that it can be read from and written to.
O_APPEND	| Append new information to the end of the file.
O_TRUNC	    | Initially clear all data from the file.
O_CREAT	    | If the file does not exist, create it. If the O_CREAT option is used, then you must include the third parameter.
O_EXCL	    | Combined with the O_CREAT option, it ensures that the caller must create the file. If the file already exists, the call will fail.

* <span style="color: red;">**fork** :</span>

**Fork()** system call is used for creating a new process, which is called child process, which runs concurrently with the process that makes the fork() call (parent process). After a new child process is created, both processes will execute the next instruction following the fork() system call. A child process uses the same pc(program counter), same CPU registers, same open files which use in the parent process.

It takes no parameters and returns an integer value. Below are different values returned by fork().

**Negative Value :** creation of a child process was unsuccessful.

**Zero :** Returned to the newly created child process.
**Positive value :** Returned to parent or caller. The value contains process ID of newly created child process.

**Example** :

```
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{

	// make two process which run same
	// program after this instruction
	fork();

	printf("Hello world!\n");
	return 0;
}
```
Output:

```
Hello world!
Hello world!
```

* <span style="color: red;">**wait and waitpid** :</span>

All of these system calls are used to wait for state changes in a
child of the calling process, and obtain information about the
child whose state has changed.  A state change is considered to
be: the child terminated; the child was stopped by a signal; or
the child was resumed by a signal.  In the case of a terminated
child, performing a wait allows the system to release the
resources associated with the child; if a wait is not performed,
then the terminated child remains in a "zombie" state .

The **wait()** system call suspends execution of the current process until one of its children terminates. The call wait(&status) is equivalent to:
```
waitpid(-1, &status, 0);
```

The **waitpid()** system call suspends execution of the current process until a child specified by pid argument has changed state. By default, **waitpid()** waits only for terminated children, but this behaviour is modifiable via the options argument, as described below.

**The value of pid can be:**

|Tag	|	Description|
|-------|:-------------:|
|<-1	| meaning wait for any child process whose process group ID is equal to the absolute value of pid.|
|-1	| meaning wait for any child process.|
|0	| meaning wait for any child process whose process group ID is equal to that of the calling process.|
|> 0	|meaning wait for the child whose process ID is equal to the value of pid.|

**Example** :

```
//Create two children
pid_t child1;
pid_t child2;
child1 = fork();

//wait for child1 to finish, then kill child2
waitpid() ... child1 {
kill(child2) }
```

* <span style="color: red;">**pipe** :</span>

**pipe()** is a Linux system function. The **pipe()** system function is used to open file descriptors, which are used to communicate between different Linux processes. In short, the **pipe()** function is used for inter-process communication in Linux. 

**Function Definition** :

```
int pipe(int pipefd[2]);
```

The first element of the pipefd array, pipefd[0] is used for reading data from the pipe.

The second element of the pipefd array, pipefd[1] is used for writing data to the pipe.

On success, the pipe() function returns 0. If an error occurs during pipe initialization, then the pipe() function returns -1.

The pipe() function is defined in the header unistd.h. In order to use the pipe() function in your C program, you must include the header unistd.h

**Exemple** :

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(void) {
  int pipefds[2];
 
  if(pipe(pipefds) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
 
  printf("Read File Descriptor Value: %d\n", pipefds[0]);
  printf("Write File Descriptor Value: %d\n", pipefds[1]);
 
  return EXIT_SUCCESS;
}
```

* <span style="color: red;">**dup and dup2** :</span>

The **dup()** system call creates a copy of a file descriptor.

The **dup2()** system call performs the same task as **dup()**, but instead of using the lowest-numbered unused file descriptor, it uses the file descriptor number specified in newfd.  In other words, the file descriptor newfd is adjusted so that it now refers to the same open file description as oldfd.

On success, the **dup2()** function returns the new file descriptor. If an error occurs, **dup2()** returns -1.

The **dup()** and **dup2()** function is defined in the header file unistd.h.

In Linux, there are 3 standard file descriptors. They are:

**stdin:** This is the standard input file descriptor. It is used to take input from the terminal by default.
The stdin file descriptor is also represented by the number 0.



**stdout:** This is the standard output file descriptor. It is used to print something to the console/terminal by default.The stdout file descriptor is also represented by the number 1.

**stderr:** This is the standard error file descriptor. It does the same thing as the stdout file descriptor. The stderr file descriptor is used to print error messages on the console/terminal.The stderr file descriptor is also represented by the number 2.

**Exemples** :

redirect Standard Output to a file

The following example closes standard output for running processes, reassigns standard output to go to the file referenced by pfd , and closes the original file descriptor to clean up.

```
#include <unistd.h>

int pfd;

close(1);
dup(pfd);
close(pfd);
```

the following example redirects messages from stderr to stdout.

```
#include <unistd.h>

dup2(2, 1); // 2-stderr; 1-stdout
```

* <span style="color: red;">**execve** :</span>

**Execve()** function is used for the execution of the program that is referred to by pathname. The exec family is used mainly in the C programming language and has many functions. These functions execute a system command in a separate process from the main program and print the output. In this article, we will discuss some of the main functions of the exec family and mainly execve functions with some elementary examples.

When execve() is successfully processed, it does not return value. The successful exec replaces the current process and cannot return anything to the program through which the call is made. These processes also have an exit status, but the parent process collects the value. If the execve is returning something to the prom that has been called, it means an error has occurred, and the returning value is -1. And errno includes the values like E2BIG, ENOMEM, EACCES. These errors occur when the list of arguments is above the system limit. There is insufficient memory available that executes the new process, or the relevant file has violated the rules of sharing and locking.

**Syntaxe** :

```
int execve(const char *path, char *const argv[], char *const envp[]);
```
**Paramètres** :

|Nom	|Description|
|------|:-----------:|
|path	|Ce paramètre permet d'indiquer le nom du fichier à exécuter.|
|argv[]	|Ce paramètre permet d'indiquer le tableau de paramètres.|
|envp[]	|Ce paramètre permet d'indiquer un tableau de variable d'environnement.|

**Exemples** :

```
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

main() {
execve("hello",NULL,NULL);
printf("Error");
}
```
In the above program we are calling an executable "hello" and passig no arguments to it. We said that the execve never returns to the calling function if there is no error, to confirm this we have added a print statement after execve which should not get printed if the call is successful.

execve can also be used to run scripts that start with the line #! pointing to an interpreter.

For example :

script.sh

```
#!/bin/bash

echo $0 
echo $1 $2
```
save the script as script.sh and give it execute permissions.
```
chmod 777 script.sh
```

```
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

main() {
char *temp[] = {NULL,"hello","world",NULL};
temp[0]="script.sh";
execve("script.sh",temp,NULL);
printf("world");
}
```

Compile and execute the program execve.c and we should see the output

```
script.sh
hello world
```

## Compiling and running
---

* **for mandatory part** :

Run <mark>make</mark>.

![image](assets/pipex_manda.png)

```bash
$ make
$ ./pipex file1 cmd1 cmd2 file2
```

* **for bonus part** :

Run <mark>make bonus</mark>.

![image](assets/pipex_bonus.png)

```bash
$ make bonus
$  ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

Support « and » when the first parameter is "here_doc".

you can ran it like this.

```bash
$ make bonus
$  ./pipex here_doc LIMITER cmd cmd1 file2
```
Should behave like:

```bash
$  cmd << LIMITER | cmd1 >> file
```

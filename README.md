# SS -simple shell-

Anthony Armour and Adam Taylor's submission for project 0x16. C - Simple Shell

## General info

SS (short for simple shell) is a replica of the shell within a Linux based operating system's terminal.

## Usability

Our simple shell has currently all of the following concepts implemented:

  * Beautiful code that passes all Betty checks
  * A Unix command line interpreter
  * Handling command lines with arguments
  * Handling the `PATH`
  * The `EXIT` built-in command
  * The `env` built-in command
  * The use of our own hand-written `getline` function
  * The use of our own hand-written `strtok` function
  * Handling arguments for the built-in `exit`
  * Handling `Crtl+C`
  * The `setenv` and `unsetenv` built-in commands
  * The `cd` built-in command
  * The command separator `;`
  * The 'alias' built-in command
  * Handling comments (#)
  * Handling a file as input

## Usage

Compile the program using:
```
gcc -o SS *.c
```
Then you are free to use any of the above useable commands/built-ins as shown below:

```
./SS [COMMAND] [ARGUMENTS]
```
  * [COMMAND] = The command you would like the simple shell to execute
  * [ARGUMENTS] = Whichever arguments you would like to pass with your command

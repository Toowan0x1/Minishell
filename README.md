#  Minishell

The existence of shells is linked to the very existence of IT. At the time, all coders agreed
that communicating with a computer using aligned 1/0 switches was seriously
irritating. It was only logical that they came up with the idea to communicate with
a computer using interactive lines of commands in a language somewhat close
to english.The objective of this project is to create a simple shell using c.

![Alt Text](https://cdn.outdoorhub.com/wp-content/uploads/sites/2/2015/12/outdoorhub--2015-12-02_00-01-38.jpg)

Minishell is a project developed as part of the 42 curriculum. It aims to create a simplified shell that can interpret and execute basic commands, handle environment variables, and implement some built-in functionalities.

Installation
To install and run the Minishell project, follow these steps:

Clone the repository:
'git clone https://github.com/your-username/minishell.git'

Navigate to the project directory:
'cd minishell'

Compile the source code:
'make'

Run Minishell:
'./minishell'

Usage
Once you have started Minishell, you can enter commands and execute them. The shell supports various features and built-in commands, including but not limited to:

Running external commands by specifying the command's name.
Handling environment variables using the syntax $VAR_NAME.
Redirecting input/output using the < and > symbols.
Implementing pipes using the | symbol.
Managing the exit status of previously executed commands with the $? variable.
Implementing built-in commands like echo, cd, env, export, unset, exit, etc.
Here's an example of using Minishell:

shell
Copy code
$ ./minishell
minishell$ echo Hello, World!
Hello, World!
minishell$ ls -l
total 8
-rwxr-xr-x  1 user  staff  16376 May 20 12:00 minishell
minishell$ cd ..
minishell$ pwd
/Users/user
minishell$ exit
$
Contributing
Contributions to the Minishell project are welcome. If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.

<br>

##  The Project consist of two parts :
**Parsing**

        1. readline
        2. pipes
        3. Command and arguments
        4. Protections
        5. The <,>, >> redirects
        6. Environment variables
        7. The separations
        8. history
**The execution**

        1. Redirects
        2. Env, export, unset
        3. Exit and $?
        4. Pipes / signals / process links 

## Contributing 

[Omar El Houmadi](https://github.com/toowan0x1)
<br/>
&emsp;42intra profile : [oel-houm](https://profile.intra.42.fr/users/oel-houm)
<br/>
[Walid Bouwachma](https://github.com/bwalid)<br/>
&emsp;42intra profile : [wbouwach](https://profile.intra.42.fr/users/wbouwach) <br/>
<br/>

#  Minishell

Minishell is a project developed as part of the 42 curriculum. It aims to create a simplified shell that can interpret and execute basic commands, handle environment variables, and implement some built-in functionalities.

Installation
To install and run the Minishell project, follow these steps:

Clone the repository:
'git clone https://github.com/0xtoowan/minishell.git'

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

**Executor:**<br/>
<img src="[path/to/image.jpg](https://cdn.intra.42.fr/users/e1135c041804efcda5fe167ee06f8e27/wbouwach.JPG)" alt="oel-houm Text" width="300" height="auto" style="max-width: 100%;">
[Omar El Houmadi](https://github.com/toowan0x1)
<br/>
&emsp;42 intra profile : [oel-houm](https://profile.intra.42.fr/users/oel-houm)
<br/>
**Parser:**<br/>
<img src="[path/to/image.jpg](https://cdn.intra.42.fr/users/e1135c041804efcda5fe167ee06f8e27/wbouwach.JPG)" alt="oel-houm Text" width="300" height="auto" style="max-width: 100%;">
[Walid Bouwachma](https://github.com/bwalidd)<br/>
&emsp;42 intra profile : [wbouwach](https://profile.intra.42.fr/users/wbouwach) <br/>
<br/>

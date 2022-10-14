# test.vim  
![image](https://user-images.githubusercontent.com/83845332/195946377-5dfb5f20-532f-4e06-af46-177e3c107b25.png)  
A test executor for vim.  
This plugin works as a virtual judge, it is given test cases so that it reviews which are correct and which are not.
# Install  
- **vim-plug**
```
Plug 'Cris-lml007/test.vim'
```
Execute `:call TestViCompiler()` for compiler the judge.  
# Usage  
For use the judge your must have an file `NameProgram.test` with next syntax:  
```
1 2
3 -2
5 5
~~ All of the above are inputs for the program to test, the symbols ~~ means end of inputs.
3
~# All of the above are outputs expected by the program, the symbols ~# means end of #{1,2,3..n} outputs.
1
~# Each of these represent a test case, for n input lines there must be n expected outputs (~#).
11
```
![image](https://user-images.githubusercontent.com/83845332/195950056-a3d9072e-65b8-4c57-881c-2c14eba0a400.png)  
# Support
Support all languages compiled or that can executed with `./program`.  

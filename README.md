# 🧪test.vim  
<div align="center">
  <center>
  	 <img src="https://user-images.githubusercontent.com/83845332/195946377-5dfb5f20-532f-4e06-af46-177e3c107b25.png" /><br>
     <img alt="Linux" src="https://img.shields.io/badge/Linux-%23.svg?style=flat-square&logo=linux&color=FCC624&logoColor=black" />
     <img alt="macOS" src="https://img.shields.io/badge/macOS-%23.svg?style=flat-square&logo=apple&color=000000&logoColor=white" />
     <img src="https://img.shields.io/badge/Neovim-0.7.2-blueviolet.svg?style=flat-square&logo=Neovim&logoColor=green" alt="Neovim minimum version"/>
  </center>
</div> 

A test executor for vim.  
This plugin works as a virtual judge, it is given test cases so that it reviews which are correct and which are not.
# ⚒️ Install  
**This plugin has better integration with [dotfile nvim](https://github.com/Cris-lml007/dotfile-nvim/).**
- **vim-plug**
```
Plug 'Cris-lml007/test.vim'
```
Execute `:call TestViCompiler()` for compiler the judge.  
# ⚙️Usage  
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
Execute `:TestVi` for tesing cases.  
![image](https://user-images.githubusercontent.com/83845332/195950056-a3d9072e-65b8-4c57-881c-2c14eba0a400.png)  
# 💻Support
|*LANGUAGE*|*SUPPORT*|
|--|-|
|java|yes|
|javascript|yes|
|C++|yes|
|pascal|yes|
|python|yes|
|bashscript|yes|
|dotnet|beta|  

Support all languages compiled or that can executed with `./program` and receive an input by `echo 'inputs' | ./program`.

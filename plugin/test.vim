function! TestViCompiler()
	execute '!g++ -o'.expand(stdpath('data'). '/plugged/test.vim/src/test ').expand(stdpath('data'). '/plugged/test.vim/src/test.cpp')
	echo "compiling..."
endfunction

function! TestVi()
	execute 'sp term://'.expand(stdpath('data'). '/plugged/test.vim/src/test ').expand('%')
endfunction

command! TestVi call TestVi()

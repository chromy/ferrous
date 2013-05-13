ferrous
=======

Yet another home made C compiler.

Intro
-----
To force me to do this properly I'm writing this up as tutorial as I go along,
beneath are the steps I went through as I did them.
Each step has an associated git tag (Step 1 has the tag step1) so to jump to
the code as it was for the nth step you can do:
```bash
$ git checkout stepN
```

Step -1
-------
In addition to generic things that you should already have 
(namely a C compiler) we're going to need:

* [Flex](http://en.wikipedia.org/wiki/Flex_lexical_analyser) and 
* [Bison](http://en.wikipedia.org/wiki/GNU_bison).

Unfortunately if you are on OSX the version of Bison that ships with XCode is 
quite old and you will need to build/force your package manager to install
a newer version (2.7 works).

> The documentation for flex/bison (and their forebears lex/yacc) 
> is famously awful. Generally you 
> have suffer through the initial setup by reading examples
> (like this one!) but after that it stops hurting so much, honest.

If you have everything you should be able to do the following:
```bash
$ flex -V && bison -V && cc -v
```
and get output that looks something like this (except maybe with more junk):
```bash
flex 2.5.35 Apple(flex-31)
bison (GNU Bison) 2.7
Apple clang version 4.1 (tags/Apple/clang-421.11.66) (based on LLVM 3.1svn)
```

Step 0
------
I'm going to start with the reentrant parser [example](http://en.wikipedia.org/wiki/GNU_bison) 
from Bison's Wikipedia page, this means we don't have to spend ages 
working out which flags we need to set to get Bison and Flex to play nice.

We get five files:

*   lexer.l
    The Flex input file.
*   parser.y
    The Bison input file.
*   expression.h and expression.c
    The file which encodes the AST and an how to evaulate 

By default Bison creates a non-reentrant parser, one which uses global 
variables to keep state which means you can't have two parsers around at once.
In our case this wouldn't actually be so bad (we're unlikely to need to compile
two files simultaneously) but it's still nice because it keeps everything more 
contained.

* explain files
* makefile

```bash
$ make
flex lexer.l
bison parser.y
cc -c -o lexer.o lexer.c
cc -c -o parser.o parser.c
cc -c -o expression.o expression.c
cc ferrous.c lexer.o parser.o expression.o -o fe
$ ./fe
Result of ' 4 + 2*10 + 3*( 5 + 1 )' is 42
```

Step 1
------

Removed read from string.

Built in echo seems to do weird things.
```bash
$ /bin/echo '1+2*3' | ./fe
Result is 7
```


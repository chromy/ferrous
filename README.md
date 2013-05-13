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



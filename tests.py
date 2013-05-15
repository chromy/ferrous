#! /usr/bin/env python
import os
from cmdtest import Program

abspath = os.path.abspath
fe_path = abspath('./fe')
fe = Program(fe_path)

@fe.test
def should_evaluate_constants():
    fe(_in='1')
    p = Program('./a.out')
    assert '1' in p().out

@fe.test
def should_evaluate_sums():
    fe(_in='1+2')
    p = Program('./a.out')
    assert '3' in p().out

if __name__ == '__main__':
    fe.run()


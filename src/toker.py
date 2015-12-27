#!/usr/bin/python
# -*- coding: utf-8 -*-

import itertools
import sys
from argparse import ArgumentParser

__author__ = "Nicholas Carlini <npc@berkeley.edu> and Mathias Payer <mathias.payer@nebelwelt.net>"
__description__ = "Script to tokenize a BF script into a printf interpreter."
__version__ = filter(str.isdigit, "$Revision: 1 $")

parser = ArgumentParser(description=__description__)
parser.add_argument('-v', '--version', action='version', version='%(prog)s {:s}'.format(__version__))
parser.add_argument('-t', '--template', type=str, metavar='template filename', help='Filename for the template to use.', required=False, default='bf_pre.c')
parser.add_argument('-bf', '--brainfuck', type=str, metavar='bf file', help='BF program', required=True)
parser.add_argument('-i', '--input', type=str, metavar='input to bf', help='BF input', required=False, default='')
args = parser.parse_args()
                    
prog = open(args.brainfuck).read()
prog = "".join([x for x in prog if x in "<>+-.,[]"])
prog = prog.replace("[-]", "Z")

remap = {'<':[1],
         '>':[2],
         '+':[3],
         '-':[4],
         '.':[5,6],
         ',':[7,8],
         '[':[9,10,11],
         ']':[12],
         'Z':[13],
         'F':[14],
         'B':[15],#,16,17],
         'A':[18],
         }

newprog = []
progiter = iter(prog)
while len(prog):
    e = prog[0]
    if e in '<>+-':
        res = itertools.takewhile(lambda x: x == e, prog)
        count = len(list(res))
        if e == '>':
            newprog.append(('F',count))
        elif e == '<':
            assert count < 256
            newprog.append(('B',65536-count))
        elif e == '+':
            newprog.append(('A',count))
        elif e == '-':
            newprog.append(('A',256-count))
        prog = prog[count:]
    else:
        newprog.append(e)
        prog = prog[1:]

stack = []
index = 2

txt = open(args.template).read()
txt = txt.replace('###INPUT###', args.input)
print txt[0:txt.find('###TOKER###')],

for e in newprog:
    count = 0
    if type(e) == type(tuple()):
        count = e[1]
        e = e[0]
    for i,insn in enumerate(remap[e]):
        print '  progn[%d] = %d;'%(index+i*2,insn)

    if count != 0:
        assert i == 0
        print '  progn[%d] = %d;'%(index+1,count)

    if e == '[': # this is a cgoto
        stack.append(index)
    elif e == ']':
        backto = stack.pop()
        print '  progn[%d] = %d;'%(backto+1,index*4-4)
        print '  progn[%d] = %d;'%(backto+3,index*4-4)
        print '  progn[%d] = %d;'%(backto+5,index*4-4)
        
        print '  progn[%d] = %d;'%(index+1,(backto-2)*4) # we always increment PC by 1

    index += 2*len(remap[e])

print txt[txt.find('###TOKER###')+11:],

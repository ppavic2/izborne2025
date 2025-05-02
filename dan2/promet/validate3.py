#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending
    
    n, p = map(int, lines[0].strip().split())
    nl.append('{} {}{}'.format(n, p, E))  
    
    assert 2 <= n <= 2000, "krivi n"
    assert 10 ** 8 <= p <= 10 ** 9 + 100, "krivi p"
    
    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n' : n} 

# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'s1': 1, 's2' : 1, 's3' : 1, 's4' : 1, 's5' : 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    where = ['s6']
    if data['n'] <= 7: where += ['s1']
    if data['n'] <= 18: where += ['s2']
    if data['n'] <= 50: where += ['s3']
    if data['n'] <= 100: where += ['s4']
    if data['n'] <= 300: where += ['s5']
    return where;


################### Zadatak-specifican kod iznad ove linije #########################

import sys
import glob
import hashlib


def group_in_batches(files):
    # mnozenje.in.1a, mnozenje.in.1b sprema u isti batch

    files.sort()
    B = []
    for f in files:
        if len(B) == 0:
            B.append([f])            
            continue
        if "dummy" in f:
            B.append([f])
            continue
        s = f
        i = -1
        while s[i].isalpha():
            i -= 1
        ss = B[-1][-1]
        j = -1
        while ss[j].isalpha():
            j -= 1
        if ss[j] == s[i]:
            B[-1].append(f)
        else:
            B.append([f])
    return B


if __name__ == "__main__":
    f = []
    for pattern in sys.argv[1:]:
        for filename in glob.glob(pattern):
            f.append(filename)

    bc = []
    for batch in group_in_batches(f):
        if 'dummy' not in batch[0]:
            bc.append([])
        for filename in batch:
            print("{}: ".format(filename), end="")
            try:
                lines = open(filename).readlines()
                summary = check(lines)
                c = what_cluster(summary)
                if not 'dummy' in filename:
                    i = -1
                    while filename[i].isalpha(): i -= 1
                    s = int(filename[i])
                    assert ("s" + str(s)) in c, "primjer ne pripada subtasku"
                    
                if 'dummy' not in batch[0]:
                    bc[-1].append(c)
            except Exception as e:
                print("Greska! (summary = {})".format(summary), e)
                raise
            else:
                print("Sve ok! (cluster {}, summary = {})".format(c, summary))


# Bolji validator! - ppavic, 2023

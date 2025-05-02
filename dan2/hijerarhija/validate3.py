#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending
    
    n, k = map(int, lines[0].strip().split())
    nl.append('{} {}{}'.format(n, k, E))  
    
    assert 2 <= n <= 5000, "krivi n"
    assert 1 <= k <= 5000, "krivi p"
    
    pars = list(map(int, lines[1].strip().split()))
    ps = list(map(int, lines[2].strip().split()))
    cs = list(map(int, lines[3].strip().split()))
    
    assert len(pars) == n - 1, "kriva duljina roditelja"
    assert len(ps) == n, "krivi broj p-ova"
    assert len(cs) == n, "krivi broj c-ova"
    
    nl.append(" ".join([str(x) for x in pars]) + E)
    nl.append(" ".join([str(x) for x in ps]) + E)
    nl.append(" ".join([str(x) for x in cs]) + E)
    
    lanac = 1
    
    for i in range(n - 1):
    	assert 1 <= pars[i] <= i + 1, "krivi parent"
    	if pars[i] != i + 1:
    		lanac = 0
    max_c = max(cs)
    heap = 1
    
    for i in range(1, n):
        if ps[pars[i - 1] - 1] < ps[i]:
            heap = 0
    for x in ps: 
    	assert 1 <= x <= 10 ** 5, "krivi p"
    for x in cs:
    	assert 1 <= x <= 5000, "krivi c"
    
    
    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n' : n, 'k' : k, 'heap' : heap, 'max_c' : max_c, 'lanac' : lanac} 

# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'s1': 1, 's2' : 1, 's3' : 1, 's4' : 1, 's5' : 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    where = ['s6']
    if data['n'] <= 20: where += ['s1']
    if data['max_c'] == 1 and data['heap'] == 1: where += ['s2']
    if data['lanac']: where += ['s3']
    if data['n'] <= 500 and data['k'] <= 500: where += ['s4']
    if data['n'] <= 100: where += ['s5']
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

#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending
    
    n, q = map(int, lines[0].strip().split())
    nl.append('{} {}{}'.format(n, q, E))  
    
    
    assert 2 <= n <= 512, "krivi n"
    assert 0 <= q <= 2048, "krivi q"
    
    p = list(map(int, lines[1].strip().split()))
    nl.append(" ".join([str(x) for x in p]) + E)
    
    assert len(p) == n
    
    ps = sorted(p)
    
    for i in range(n):
        assert ps[i] == i + 1, "p nije permutacija"
        
    ima_dol = 0
    ima_gor = 0
    prvi = (p[0] == n)
    
    for i in range(1, n - 1):
        if p[i - 1] > p[i] and p[i + 1] > p[i]:
            ima_dol = 1
        if p[i - 1] < p[i] and p[i + 1] < p[i]:
            ima_gor = 1
    
    for t in range(q):
        l, r = map(int, lines[2 + t].strip().split())
        assert 1 <= l < r <= n, "krivi kveri"
        nl.append("{} {}{}".format(l, r, E))
            
    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n' : n, 'prvi' : prvi, 'ima_dol' : ima_dol, 'ima_gor' : ima_gor} 

# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'s1': 1, 's2' : 1, 's3' : 1, 's4' : 1, 's5' : 1, 's6' : 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    where = ['s6']
    if data['n'] <= 64: where += ['s1']
    if data['ima_gor'] == False: where += ['s2']
    if data['prvi'] == True: where += ['s3']
    if data['ima_dol'] == False: where += ['s4']
    if data['n'] <= 256: where += ['s5']
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

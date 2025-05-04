#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending
    n, q = map(int, lines[0].split())
    assert 1 <= n <= 500000, "n kriv"
    assert 1 <= q <= 500000, 'q kriv'
    nl.append("{} {}{}".format(n, q, E))
    a = list(map(int, lines[1].split()))
    assert 1 <= min(a) <= max(a) <= 10**9, 'cudni brojevi u nizu'
    nl.append("{}{}".format(' '.join(map(str, a)), E))
    plus = True
    s = set()
    for i in range(q):
        op, k = lines[i + 2].split()
        k = int(k)
        assert op == '?' or op == '+', 'cudna operacija'
        assert 1 <= k <= n, 'cudan broj u operaciji'
        nl.append("{} {}{}".format(op, k, E))
        if op == '+':
            a[k - 1] += 1
            plus = False
        if op == '?':
            s.add(k)

    maksi = max(a)
    ista = len(s) == 1

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n' : n, 'q' : q, 'plus' : plus, 'maksi' : maksi, 'ista' : ista}

def what_cluster(data):
    where = ['s6']
    if data['n'] <= 7000 and data['q'] <= 7000: 
    	where += ['s1']
    if data['plus']:
    	where += ['s2']
    elif data['maksi'] <= 10:
    	where += ['s3']
    elif data['ista']:
    	where += ['s4']
    elif data['n'] <= 10**5 and data['q'] <= 10**5:
    	where += ['s5']
    return where


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



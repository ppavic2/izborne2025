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


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'p1' :  1, 'p2' : 1, 'p3' : 1, 'p4' : 1, 'p5' : 1, 'ostalo' : 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    if data['n'] <= 7000 and data['q'] <= 7000:
        return 'p1'
    elif data['plus']:
        return 'p2'
    elif data['maksi'] <= 10:
        return 'p3'
    elif data['ista']:
        return 'p4'
    elif data['n'] <= 10**5 and data['q'] <= 10**5:
        return 'p5'
    return 'ostalo'


################### Zadatak-specifican kod iznad ove linije #########################

import sys
import glob
import hashlib


def group_in_batches(files):
    # mnozenje.in.1a, mnozenje.in.1b sprema u isti batch

    files.sort()
    B = []
    for f in files:
        if f[-1].islower() and len(B) > 0 and f[:-1] == B[-1][-1][:-1]:
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
                if 'dummy' not in batch[0]:
                    bc[-1].append(c)
            except Exception as e:
                print("Greska!", e)
                raise
            else:
                print("Sve ok! (cluster {}, summary = {})".format(c, summary))

    clusters = {}
    for b in bc:
        for c in b:
            assert c == b[0], "Ima razlicitih cluster-a unutar batcha"
        if not b[0] in clusters:
            clusters[b[0]] = 0
        clusters[b[0]] += 1

    assert clusters == expected_clusters, "Kriva raspodjela clustera ({} vs {})".format(clusters, expected_clusters)

    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    assert len(hashes) == len(f), "Ima duplikata!"

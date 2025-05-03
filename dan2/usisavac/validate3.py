#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string

from typing import List, Tuple

def classify_graph(nodes: int, edges: List[Tuple[int, int]]) -> str:
    """
    Determine whether an undirected graph is a tree.

    A graph is a tree if:
      - It is simple: no loops (edges u–u) and no parallel (multiple) edges.
      - It is connected.
      - It has exactly nodes - 1 edges (so no cycles).

    Returns:
      "Tree" if the graph meets all the criteria;
      "Not a tree" otherwise.
    """
    # 1. Basic sanity: must have at least one node
    if nodes < 1:
        return "Not a tree"

    # 2. Check all edge endpoints are valid node labels
    for u, v in edges:
        if not (1 <= u <= nodes) or not (1 <= v <= nodes):
            return "Not a tree"

    # 3. Check for loops and multiple edges
    seen_edges = set()
    for u, v in edges:
        # loop?
        if u == v:
            return "Not a tree"
        # undirected edge as an ordered pair
        e = (u, v) if u < v else (v, u)
        if e in seen_edges:
            # duplicate edge
            return "Not a tree"
        seen_edges.add(e)

    # 4. A tree on n nodes must have exactly n - 1 edges
    if len(edges) != nodes - 1:
        return "Not a tree"

    # 5. Union-Find to check connectivity and absence of cycles
    parent = list(range(nodes + 1))

    def find(x: int) -> int:
        # path compression
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a: int, b: int) -> bool:
        ra, rb = find(a), find(b)
        if ra == rb:
            # would form a cycle
            return False
        parent[rb] = ra
        return True

    # process each edge
    for u, v in edges:
        if not union(u, v):
            return "Not a tree"

    # 6. Check connectivity: all nodes share the same root
    root0 = find(1)
    for node in range(2, nodes + 1):
        if find(node) != root0:
            return "Not a tree"

    return "Tree"


def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending
    
    n, q = map(int, lines[0].strip().split())
    nl.append('{} {}{}'.format(n, q, E))  
    
    assert 2 <= n <= 3 * 10 ** 5, "krivi n"
    assert 1 <= q <= 3 * 10 ** 5, "krivi q"
    
    lanac = 1
    edges = []
    
    for i in range(n - 1):
        a, b = map(int, lines[i + 1].strip().split())
        nl.append('{} {}{}'.format(a, b, E))
        if a > b:
            a, b = b, a
        assert 1 <= a <= n, "krivi a"
        assert 1 <= b <= n, "krivi b"
        assert a != b, "loop"
        if a != i + 1 or b != i + 2: 
            lanac = 0
        edges.append([a, b])
    
    qs = list(map(int, lines[n].strip().split()))
    
    for x in qs:
    	assert 1 <= x <= n
    nl.append(' '.join([str(x) for x in qs]) + E)
    
    assert classify_graph(n, edges) == "Tree"
    
    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {'n' : n, 'q' : q, 'lanac' : lanac} 

# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'s1': 1, 's2' : 1, 's3' : 1, 's4' : 1, 's5' : 1}


def what_cluster(data):
    # na temelju povratne informacije iz check(lines)
    # zakljucuje za TP u kojoj je bodovnoj sekciji
    where = ['s5']
    if data['n'] <= 1000 and data['q'] <= 1000: where += ['s1']
    if data['lanac'] == True: where += ['s2']
    if data['q'] == 1: where += ['s3']
    if data['n'] <= 10 ** 5 and data['q'] <= 10 ** 5: where += ['s4']
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

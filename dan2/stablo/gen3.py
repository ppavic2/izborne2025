#!/usr/bin/python3

import sys
import glob
import os
import random
import subprocess
import math
from collections import defaultdict

PROBLEM = "binarni"
sys.setrecursionlimit(1000010)

N = 511

def validate_tree(n: int, p: list[int]) -> None:
    # Step 1: Assert the tree has no more than 3 degrees per node
    degree = [0] * (n + 1)  # Degree array, counting children for each node
    
    for child in range(1, n + 1):
        parent = p[child - 1]
        if parent != -1:
            degree[parent] += 1
            assert degree[parent] <= 2, f"Node {parent} has more than 2 children."
    
    # Step 2: Check that the tree is connected
    # Find the root (the node with parent -1)
    root = p.index(-1) + 1  # Adding 1 because p is 0-indexed
    
    # Perform DFS or BFS to check connectivity
    visited = [False] * (n + 1)  # visited array to mark visited nodes
    def dfs(node):
        visited[node] = True
        for child in range(1, n + 1):
            if p[child - 1] == node and not visited[child]:
                dfs(child)
    
    dfs(root)  # Start DFS from the root
    
    # Step 3: Ensure all nodes are visited (tree is connected)
    for i in range(1, n + 1):
        assert visited[i], f"Node {i} is not connected."

    # If all assertions pass, the tree is valid
    print("Tree is valid!")


class Test(object):
	def __init__(self, n, p):
		self.n = n
		self.p = p

	def validate(self):
		assert 3 <= self.n <= N, "neispravan n"
		assert len(self.p) == self.n, "neispravan p"
		cnt = 0
		for i in range(self.n):
			if self.p[i] == -1:
				cnt += 1
			else:
				assert 1 <= self.p[i] <= self.n, "neispravan p"
			assert self.p[i] != i + 1
		assert cnt == 1, "nije tocno jedan root"
		validate_tree(self.n, self.p)

	def write(self, fd=sys.stdout):
		print(self.n, file=fd)
		for i in range(self.n):
			print(self.p[i], end = " \n"[i == self.n - 1], file = fd)

def remove_cases():
	cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
	cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
	cases += glob.glob('test/%s.in.*' % PROBLEM)
	cases += glob.glob('test/%s.out.*' % PROBLEM)
	for c in cases:
		print('Removing ' + c, file=sys.stderr)
		os.remove(c)

import random

def gen_chain(n: int, o = 0) -> list[int]:
	nodes = list(range(n))
	random.shuffle(nodes)
	
	if o != 0:
		nodes = list(range(n))
		if o == 2:
			nodes.reverse()

	p = [-1] * n
	for i in range(1, n):
		p[nodes[i]] = nodes[i - 1] + 1

	return Test(n, p)

def gen_complete(x: int, o = 0) -> list[int]:
    n = 2**x - 1

    labels = list(range(1, n + 1))
    random.shuffle(labels)
    
    if o != 0:
    	labels = list(range(1, n + 1))
    	if o == 2:
    		labels.reverse()

    p = [-1] * (n + 1)  # p[i] is parent of node i; index 0 unused

    for i in range(1, n):  # node at position i has parent at (i - 1) // 2
        child = labels[i]
        parent = labels[(i - 1) // 2]
        p[child] = parent

    return Test(n, p[1:])  # return p[1] to p[n]

def gen_random(n: int) -> list[int]:
    if n <= 0:
        return []

    labels = list(range(1, n + 1))
    random.shuffle(labels)

    root = labels[0]
    p = [-1] * (n + 1)  # p[i] = parent of node i; index 0 unused
    p[root] = -1

    # Track which nodes can accept more children (max 2 per node)
    available = {root: 0}  # node -> number of children

    for label in labels[1:]:
        # Pick a parent with <2 children
        parent = random.choice(list(available.keys()))
        p[label] = parent
        available[parent] += 1

        # If parent now has 2 children, remove it from available list
        if available[parent] == 2:
            del available[parent]

        # Add current node as a potential parent
        available[label] = 0

    return Test(n, p[1:])  # return p[1] to p[n]

def gen_almost_complete(n: int) -> list[int]:
    if n <= 0:
        return []

    labels = list(range(1, n + 1))
    random.shuffle(labels)

    p = [-1] * (n + 1)  # p[i] is parent of node i; index 0 unused

    for i in range(1, n):
        child = labels[i]
        parent = labels[(i - 1) // 2]
        p[child] = parent

    return Test(n, p[1:])  # return p[1] to p[n]

def gen_partial(n: int, x: int):
    full_size = 2**x - 1
    if n < full_size:
        raise ValueError("n must be at least 2^x - 1 for full binary tree of depth x")

    labels = list(range(1, n + 1))
    random.shuffle(labels)

    p = [-1] * (n + 1)  # index 0 unused
    full_labels = labels[:full_size]
    extra_labels = labels[full_size:]

    # Step 1: Build full binary tree
    degree = [0] * (n + 1)  # To track the number of children of each node
    for i in range(1, full_size):
        child = full_labels[i]
        parent = full_labels[(i - 1) // 2]
        p[child] = parent
        degree[parent] += 1

    # Step 2: Identify leaves in the full binary tree (nodes with < 2 children)
    leaves = [node for node in full_labels if degree[node] < 2]

    # Step 3: Attach extra nodes as chains to leaves
    for label in extra_labels:
        if not leaves:
            raise RuntimeError("Ran out of leaves to attach chains (this shouldn't happen)")

        # Select a random leaf and attach the new node
        parent = random.choice(leaves)
        p[label] = parent
        degree[parent] += 1

        # If the parent has now 2 children, it can no longer be a leaf
        if degree[parent] == 2:
            leaves.remove(parent)

        # The new node is a leaf now
        leaves.append(label)

    return Test(n, p[1:])  # return from node 1 to n

def gen_tails(n: int, x: int) -> list[int]:
    full_tree_size = 2**x - 1
    if n < full_tree_size + 1:
        raise ValueError("n must be at least 2^x + 1 to fit the chain and full tree")

    chain_len = n - full_tree_size - 1  # excluding root
    labels = list(range(1, n + 1))
    random.shuffle(labels)

    p = [-1] * (n + 1)  # p[i] is parent of node i, index 0 unused

    # Step 1: Assign roles
    root = labels[0]
    chain_nodes = labels[1 : 1 + chain_len]
    tree_nodes = labels[1 + chain_len:]

    # Step 2: Build chain
    prev = root
    for node in chain_nodes:
        p[node] = prev
        prev = node

    # Step 3: Attach full binary tree to last chain node
    base = prev  # root of full binary tree
    for i in range(full_tree_size):
        if i == 0:
            p[tree_nodes[i]] = base
        else:
            p[tree_nodes[i]] = tree_nodes[(i - 1) // 2]

    return Test(n, p[1:])  # return p[1] to p[n]


def gen_cases():
	remove_cases()

	dummy = [gen_chain(4, o = 1)]

	# N <= 512
	subtask1 = [] # lanac
	subtask2 = [] # potpuno binarno
	subtask3 = [] # sve

	subtask1.append(gen_chain(3))
	for i in range(15):
		subtask1.append(gen_chain(N))
	subtask1.append(gen_chain(N, o = 1))
	subtask1.append(gen_chain(N, o = 1))

	subtask2.append(gen_complete(2))
	for i in range(15):
		subtask2.append(gen_complete(9))
	subtask2.append(gen_complete(9, o = 1))
	subtask2.append(gen_complete(9, o = 2))

	subtask3.append(gen_chain(3))
	subtask3.append(gen_complete(2))
	for i in range(10):
		subtask3.append(gen_chain(N))
	for i in range(10):
		subtask3.append(gen_complete(9))
	for i in range(10):
		subtask3.append(gen_random(N)) #bf
	for i in range(4):
		subtask3.append(gen_almost_complete(N))
	for d in range(2, 9):
		subtask3.append(gen_partial(N, d))
	for i in range(3):
		subtask3.append(gen_partial(N, 3))
	for d in range(2, 9):
		subtask3.append(gen_tails(N, d))
	for i in range(2):
		subtask3.append(gen_tails(N, 7))
	subtask3.append(gen_chain(N, o = 1))
	subtask3.append(gen_chain(N, o = 1))
	subtask3.append(gen_complete(9, o = 1))
	subtask3.append(gen_complete(9, o = 2))
	

	real = [
		subtask1,
		subtask2,
		subtask3
	]

	for i, test in enumerate(dummy):
		test.validate()
		filename = f"test/{PROBLEM}.dummy.in.{i+1}"
		print(f'Generating {filename}', file=sys.stderr)
		with open(filename, 'wt+') as fp:
			test.write(fp)

	for i, batch in enumerate(real):
		for j, test in enumerate(batch):
			test.validate()
			filename = f"test/{PROBLEM}.in.{i+1}{chr(ord('a')+j//26)}{chr(ord('a')+j%26)}"
			print(f'Generating {filename}', file=sys.stderr)
			with open(filename, 'wt+') as fp:
				test.write(fp)


def main():
	random.seed(2349857)
	gen_cases()

if __name__ == "__main__":
	main()


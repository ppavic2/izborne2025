#!/usr/bin/python3

import sys
import glob
import os
import random
import subprocess
import math

PROBLEM = "hijerarhija"
sys.setrecursionlimit(1000010)

N = 5000
V = 10**5

class Test(object):
	def __init__(self, n, k, p, v, c):
		self.n = n
		self.k = k
		self.p = p
		self.v = v
		self.c = c

	def validate(self):
		assert 2 <= self.n <= N, "neispravan n"
		assert 1 <= self.k <= N, "neispravan k"
		assert len(self.p) == self.n - 1, "neispravan p"
		for i in range(self.n - 1):
			assert 1 <= self.p[i] <= i + 1, "neispravan p_i"
		assert len(self.v) == self.n, "neispravan v"
		assert len(self.c) == self.n, "neispravan c"
		for vi in self.v:
			assert 1 <= vi <= V, "neispravan v_i"
		for ci in self.c:
			assert 1 <= ci <= N, "neispravan c_i"

	def write(self, fd=sys.stdout):
		print(self.n, self.k, file=fd)
		for i in range(self.n - 1):
			print(self.p[i], end = " \n"[i == self.n - 2], file = fd)
		for i in range(self.n):
			print(self.v[i], end = " \n"[i == self.n - 1], file = fd)
		for i in range(self.n):
			print(self.c[i], end = " \n"[i == self.n - 1], file = fd)

def remove_cases():
	cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
	cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
	cases += glob.glob('test/%s.in.*' % PROBLEM)
	cases += glob.glob('test/%s.out.*' % PROBLEM)
	for c in cases:
		print('Removing ' + c, file=sys.stderr)
		os.remove(c)

class Tree:
	@staticmethod
	def random(n: int):
		p = [random.randint(1, i) for i in range(1, n)]
		return p
	@staticmethod
	def chain(n: int):
		return [i for i in range(1, n)]
	@staticmethod
	def star(n: int):
		return [1] * (n - 1)

class Decorator:
	@staticmethod
	def create(p, decoration_strategy = 'random', k = 5000):
		n = len(p) + 1
		if decoration_strategy == 'random':
			return Decorator.random(n, p, k)
		if decoration_strategy == 'leaf_only':
			return Decorator.leaf_only(n, p, k)
		if decoration_strategy == 'all':
			return Decorator.all(n, p, k)
		if decoration_strategy == 'almost_all':
			return Decorator.almost_all(n, p, k)
		if decoration_strategy == 'single':
			return Decorator.single(n, p, k)
		if decoration_strategy == 'root':
			return Decorator.root(n, p, k)
		if decoration_strategy == 'heap':
			return Decorator.heap(n, p, k)
		else:
			raise ValueError(f"Unknown decoration strategy: {decoration_strategy}")

	@staticmethod
	def random(n, p, k):
		v = [random.randint(1, V) for _ in range(n)]
		c = [random.randint(1, k) for _ in range(n)]
		return Test(n, k, p, v, c)
	
	@staticmethod
	def leaf_only(n, p, k):
		children = [0] * n
		for parent in p:
			children[parent - 1] += 1
		v = []
		c = []
		for i in range(n):
			if children[i] == 0:
				v.append(1)
				c.append(1)
			else:
				v.append(random.randint(2, V))
				c.append(k)
		return Test(n, k - 1, p, v, c)
	
	@staticmethod
	def all(n, p, k):
		v = [random.randint(1, V) for _ in range(n)]
		cuts = sorted(random.sample(range(1, k), n - 1))
		c = [cuts[0]] + \
			[cuts[i] - cuts[i - 1] for i in range(1, n - 1)] + \
			[k - cuts[-1]]
		random.shuffle(c)
		return Test(n, k, p, v, c)

	@staticmethod
	def almost_all(n, p, k):
		v = [random.randint(1, V) for _ in range(n)]
		cuts = sorted(random.sample(range(1, k), n - 1))
		c = [cuts[0]] + \
			[cuts[i] - cuts[i - 1] for i in range(1, n - 1)] + \
			[k - cuts[-1]]
		random.shuffle(c)
		return Test(n, k - 1, p, v, c)

	@staticmethod
	def single(n, p, k):
		low = k // 2 + 1
		v = [random.randint(1, V) for _ in range(n)]
		c = [random.randint(low, k) for _ in range(n)]
		return Test(n, k, p, v, c)

	@staticmethod
	def root(n, p, k):
		low = k // 2 + 1
		v = [random.randint(1, V - 1) for _ in range(n)]
		v[0] = V
		c = [random.randint(low, k) for _ in range(n)]
		return Test(n, k, p, v, c)
	
	@staticmethod
	def heap(n, p, k):
		# 1) generate random values
		v = [random.randint(1, V) for _ in range(n)]
		c = [1] * n

		# 2) build children lists
		children = [[] for _ in range(n)]
		for i, parent in enumerate(p):
			children[parent - 1].append(i + 1)

		# 3) compute post-order
		post = []
		def dfs(u):
			for w in children[u]:
				dfs(w)
			post.append(u)
		dfs(0)

		def heapify(u):
			while True:
				max_node = u
				for w in children[u]:
					if v[w] > v[max_node]:
						max_node = w
				if max_node == u:
					return
				v[u], v[max_node] = v[max_node], v[u]
				u = max_node

		for u in post:
			heapify(u)

		return Test(n, k, p, v, c)

def gen_cases():
	remove_cases()

	dummy = [
		Test(2, 100, [1], [10, 10], [101, 100]),
		Test(5, 7, [1, 1, 2, 2], [2, 1, 2, 3, 3], [4, 2, 4, 2, 3]),
		Test(4, 9, [1, 2, 2], [3, 4, 4, 2], [2, 5, 5, 4]),
	]

	# N, K <= 5000
	# c_i <= 5000, v_i <= 10**5
	subtask1 = [] # N <= 20
	subtask2 = [] # c_i = 1, v_p >= v_i
	subtask3 = [] # p_i = i - 1
	subtask4 = [] # N, K <= 500
	subtask5 = [] # N <= 100
	subtask6 = [] # NDO

	for i in range(10):
		subtask1.append(Decorator.create(Tree.random(20), 'random'))
	for i in range(3):
		subtask1.append(Decorator.create(Tree.random(20), 'leaf_only'))
	for i in range(3):
		subtask1.append(Decorator.create(Tree.random(20), 'all'))
	subtask1.append(Decorator.create(Tree.random(20), 'single'))
	subtask1.append(Decorator.create(Tree.random(20), 'root'))
	for i in range(3):
		subtask1.append(Decorator.create(Tree.random(20), 'heap', k = random.randint(1, 20)))
	for i in range(2):
		subtask1.append(Decorator.create(Tree.chain(20), 'random'))
	subtask1.append(Decorator.create(Tree.chain(20), 'leaf_only'))
	subtask1.append(Decorator.create(Tree.chain(20), 'all'))
	subtask1.append(Decorator.create(Tree.chain(20), 'root'))
	for i in range(2):
		subtask1.append(Decorator.create(Tree.chain(20), 'heap', k = random.randint(1, 20)))
	for i in range(3):
		subtask1.append(Decorator.create(Tree.star(20), 'random'))
	subtask1.append(Decorator.create(Tree.star(20), 'leaf_only'))
	subtask1.append(Decorator.create(Tree.star(20), 'all'))
	subtask1.append(Decorator.create(Tree.star(20), 'root'))
	for i in range(2):
		subtask1.append(Decorator.create(Tree.star(20), 'heap', k = random.randint(1, 20)))
	
	for i in range(15):
		subtask2.append(Decorator.create(Tree.random(N), 'heap', k = random.randint(1, N)))
	subtask2.append(Decorator.create(Tree.random(N), 'heap', k = 1))
	subtask2.append(Decorator.create(Tree.random(N), 'heap', k = N))
	for i in range(6):
		subtask2.append(Decorator.create(Tree.chain(N), 'heap', k = random.randint(1, N)))
	subtask2.append(Decorator.create(Tree.chain(N), 'heap', k = 1))
	subtask2.append(Decorator.create(Tree.chain(N), 'heap', k = N))
	for i in range(6):
		subtask2.append(Decorator.create(Tree.star(N), 'heap', k = random.randint(1, N)))
	subtask2.append(Decorator.create(Tree.star(N), 'heap', k = 1))
	subtask2.append(Decorator.create(Tree.star(N), 'heap', k = N))
	
	for i in range(15):
		subtask3.append(Decorator.create(Tree.chain(N), 'random'))
	for i in range(2):
		subtask3.append(Decorator.create(Tree.chain(N), 'leaf_only'))
	for i in range(3):
		subtask3.append(Decorator.create(Tree.chain(N), 'all'))
	for i in range(2):
		subtask3.append(Decorator.create(Tree.chain(N), 'almost_all'))
	for i in range(2):
		subtask3.append(Decorator.create(Tree.chain(N), 'single'))
	for i in range(2):
		subtask3.append(Decorator.create(Tree.chain(N), 'root'))
	
	for i in range(10):
		subtask4.append(Decorator.create(Tree.random(500), 'random', k=500))
	for i in range(3):
		subtask4.append(Decorator.create(Tree.random(500), 'leaf_only', k=500))
	for i in range(3):
		subtask4.append(Decorator.create(Tree.random(500), 'all', k=500))
	subtask4.append(Decorator.create(Tree.random(500), 'single', k=500))
	subtask4.append(Decorator.create(Tree.random(500), 'root', k=500))
	for i in range(3):
		subtask4.append(Decorator.create(Tree.random(500), 'heap', k = random.randint(1, 500)))
	for i in range(2):
		subtask4.append(Decorator.create(Tree.chain(500), 'random', k=500))
	subtask4.append(Decorator.create(Tree.chain(500), 'leaf_only', k=500))
	subtask4.append(Decorator.create(Tree.chain(500), 'all', k=500))
	subtask4.append(Decorator.create(Tree.chain(500), 'root', k=500))
	for i in range(2):
		subtask4.append(Decorator.create(Tree.chain(500), 'heap', k = random.randint(1, 500)))
	for i in range(3):
		subtask4.append(Decorator.create(Tree.star(500), 'random', k=500))
	subtask4.append(Decorator.create(Tree.star(500), 'leaf_only', k=500))
	subtask4.append(Decorator.create(Tree.star(500), 'all', k=500))
	subtask4.append(Decorator.create(Tree.star(500), 'root', k=500))
	for i in range(2):
		subtask4.append(Decorator.create(Tree.star(500), 'heap', k = random.randint(1, 500)))

	for i in range(10):
		subtask5.append(Decorator.create(Tree.random(100), 'random'))
	for i in range(3):
	    subtask5.append(Decorator.create(Tree.random(100), 'leaf_only'))
	for i in range(3):
		subtask5.append(Decorator.create(Tree.random(100), 'all'))
	subtask5.append(Decorator.create(Tree.random(100), 'single'))
	subtask5.append(Decorator.create(Tree.random(100), 'root'))
	for i in range(3):
		subtask5.append(Decorator.create(Tree.random(100), 'heap', k = random.randint(1, 100)))
	for i in range(2):
		subtask5.append(Decorator.create(Tree.chain(100), 'random'))
	subtask5.append(Decorator.create(Tree.chain(100), 'leaf_only'))
	subtask5.append(Decorator.create(Tree.chain(100), 'all'))
	subtask5.append(Decorator.create(Tree.chain(100), 'root'))
	for i in range(2):
		subtask5.append(Decorator.create(Tree.chain(100), 'heap', k = random.randint(1, 100)))
	for i in range(3):
		subtask5.append(Decorator.create(Tree.star(100), 'random'))
	subtask5.append(Decorator.create(Tree.star(100), 'leaf_only'))
	subtask5.append(Decorator.create(Tree.star(100), 'all'))
	subtask5.append(Decorator.create(Tree.star(100), 'root'))
	for i in range(2):
		subtask5.append(Decorator.create(Tree.star(100), 'heap', k = random.randint(1, 100)))

	for i in range(10):
		subtask6.append(Decorator.create(Tree.random(N), 'random'))
	for i in range(3):
		subtask6.append(Decorator.create(Tree.random(N), 'leaf_only'))
	for i in range(3):
		subtask6.append(Decorator.create(Tree.random(N), 'all'))
	subtask6.append(Decorator.create(Tree.random(N), 'single'))
	subtask6.append(Decorator.create(Tree.random(N), 'root'))
	for i in range(3):
		subtask6.append(Decorator.create(Tree.random(N), 'heap', k = random.randint(1, N)))
	for i in range(2):
		subtask6.append(Decorator.create(Tree.chain(N), 'random'))
	subtask6.append(Decorator.create(Tree.chain(N), 'leaf_only'))
	subtask6.append(Decorator.create(Tree.chain(N), 'all'))
	subtask6.append(Decorator.create(Tree.chain(N), 'root'))
	for i in range(2):
		subtask6.append(Decorator.create(Tree.chain(N), 'heap', k = random.randint(1, N)))
	for i in range(3):
		subtask6.append(Decorator.create(Tree.star(N), 'random'))
	subtask6.append(Decorator.create(Tree.star(N), 'leaf_only'))
	subtask6.append(Decorator.create(Tree.star(N), 'all'))
	subtask6.append(Decorator.create(Tree.star(N), 'root'))
	for i in range(2):
		subtask6.append(Decorator.create(Tree.star(N), 'heap', k = random.randint(1, N)))


	real = [
		subtask1,
		subtask2,
		subtask3,
		subtask4,
		subtask5,
		subtask6
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


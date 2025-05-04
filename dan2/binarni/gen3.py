#!/usr/bin/python3

import sys
import glob
import os
import random
import subprocess
import math

PROBLEM = "vrsta"
sys.setrecursionlimit(1000010)

N = 500

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
		assert cnt == 1, "nije tocno jedan root"

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

def gen_chain(n: int) -> list[int]:
	if n <= 0:
		return []

	nodes = list(range(n))
	random.shuffle(nodes)

	p = [-1] * n
	for i in range(1, n):
		p[nodes[i]] = nodes[i - 1] + 1

	return Test(n, p)

def gen_cases():
	remove_cases()

	dummy = []

	# N <= 500
	subtask1 = [] # lanac
	subtask2 = [] # potpuno binarno
	subtask3 = [] # sve


	for i in range(8):
		subtask1.append(gen_chain(N))

	for i in range(8):
		subtask3.append(gen_chain(N))

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


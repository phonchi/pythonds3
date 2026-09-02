# pythonds3

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![Supported Python versions](https://img.shields.io/pypi/pyversions/pythonds3)](https://img.shields.io/pypi/pyversions/pythonds3) [![PyPI version](https://badge.fury.io/py/pythonds3.svg)](https://badge.fury.io/py/pythonds3) [![Build Status](https://travis-ci.com/yasinovskyy/pythonds3.svg?branch=master)](https://travis-ci.com/yasinovskyy/pythonds3) [![codecov](https://codecov.io/gh/yasinovskyy/pythonds3/branch/master/graph/badge.svg)](https://codecov.io/gh/yasinovskyy/pythonds3)

Data Structures package for _Problem Solving with Algorithms and Data Structures using Python_ by Brad Miller and David Ranum.

The package is a supplement to [Problem Solving with Algorithms and Data Structures using Python](https://runestone.academy/runestone/static/pythonds/index.html). It contains implementations of basic data structures, searching and sorting algorithms, trees, and graphs. Some implementation details are intentionally left out and readers are encouraged to complete them on their own.

## Object-oriented programming

- Typical class implementation
- Use of getters, setters, and properties
- Overriding _magic_ methods (len, str, contains etc)

## Basic data structures

- Stack
- Queue
- Deque
- Ordered linked list
- Unordered linked list

## Searching

- HashMap

## Sorting

- Bubble sort
- Selection sort
- Insertion sort
- Shell sort
- Mergesort
- Quicksort
- Heapsort

## Trees

- Binary tree
- Binary search tree
- AVL tree
- Binary heap
- Priority queue

## Graphs

- Breadth first search
- Depth first search
- Dijkstra's shortest path algorithm
- Bellman-Ford shortest path algorithm
- Prim's spanning tree algorithm

## C++ headers for NSYSU MATH208 (`cppds/*.hpp`)

The header-only C++ implementations used by the NSYSU MATH208 lecture notebooks
live directly in `cppds/`. Clone this repository next to your notebooks (i.e. in
the directory where you start `jupyter lab`):

```
git clone https://github.com/phonchi/pythonds3
```

Your working directory then looks like:

```
.
├── 05_Linear_Structure.ipynb
└── pythonds3/
    └── cppds/
        ├── stack.hpp
        └── ...
```

Include them with the full path and compile with `-I.` (the notebook C++17
kernel already does this):

```cpp
#include "pythonds3/cppds/stack.hpp"
```

```
g++ -std=c++17 -I. main.cpp -o main
```

Available headers:

`anagram.hpp`, `arraylist.hpp`, `binaryheap.hpp`, `binarytree.hpp`, `bst.hpp`,
`deque.hpp`, `dstimer.hpp`, `expression.hpp`, `fraction.hpp`, `gates.hpp`,
`graph.hpp`, `graph_algos.hpp`, `hashtable.hpp`, `linked_list.hpp`, `maze.hpp`,
`queue.hpp`, `searching.hpp`, `sorting.hpp`, `sparsematrix.hpp`, `stack.hpp`

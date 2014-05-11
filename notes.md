Notes of 'Introduction to Algorithms'
==================================================

_Created: 04/16/2014, Modified: 05/11/2014_

Note: Solutions of exercises and problems in Chapter 1 to 10 can be found at http://clrs.skanev.com.

# Part I. Foundations

## Chapter 02. Getting Started

* Insertion sort: P18, as an example of loop invariant.
* Merge sort: P30~34, as an example of divide-and-conquer.
* Bubble sort: P40.
* Number of inversions: P41~42. Modification of merge sort.

## Chapter 03. Growth of Functions

* Theta-notation: P44.

## Chapter 04. Divide-and-Conquer

* Maximum-subarray problem: P68~74. And an O(n) solution: P75.
* Solving computational complexity of recurrences: (I think they are not very important for me currently)
  - Substitution method: P83~87.
  - Recursion-tree: P88~92.
  - The master method: P93~97.

# Part II. Sorting and Order Statistics

* Running time comparison of sort algorithms: P150.

## Chapter 06. Heapsort

* Heap property: P152.
* m x n Young tableus: P167~168.

## Chapter 07. Quicksort
Since 04/16/2014

# Part I. Foundations

## Chapter 02. Getting Started

* Insertion sort: P18, as an example of loop invariant.
* Merge sort: P30~34, as an example of divide-and-conquer.
* Bubble sort: P40.
* Number of inversions: P41~42. Modification of merge sort.

## Chapter 03. Growth of Functions

* Theta-notation: P44.

## Chapter 04. Divide-and-Conquer

* Maximum-subarray problem: P68~74. And an O(n) solution: P75.
* Solving computational complexity of recurrences: (I think they are not very important for me currently)
  - Substitution method: P83~87.
  - Recursion-tree: P88~92.
  - The master method: P93~97.

# Part II. Sorting and Order Statistics

* Running time comparison of sort algorithms: P150.

## Chapter 06. Heapsort

* Heap property: P152.
* m x n Young tableus: P167~168.

## Chapter 07. Quicksort

* Partition in quicksort: P171.
* Performance: P174.

## Chapter 09. Medians and Order Statistics

* Min-max algorithm in with \\(3 \cdot n / 2\\) comparisons: P214.
* Find the second minimum element with \\(n + \lg n - 2\\) comparisons in worst cast: P215. Ref: http://goo.gl/nZ4dBH.
* RANDOMIZED-SELECT in \\(O(n)\\) (expected) and \\(O(n^2)\\) (worse case): P215~219.
* SELECT in \\(O(n)\\) in worse case: P220~222.
* Excercise 9.3-1: Group of 7 and group of 3: http://clrs.skanev.com/09/03/01.html.

# Part V. Advanced Data Structures

## Chapter 18. B-Trees

### Data Structures on Secondary Storage

* **Access speed**: main memory is 10,000 times faster than a magnetic disk.
* **Data transfer speed**: main memory is 50 times faster than a magnetic disk. (Also refer to Figure 1.11 in the book _Operating System Concepts, 9th Edition_, page 28)
* So the bottle neck for a disk-based data structure is its total number of **disk accesses** (a disk access is defined as a read/write operation of a page) during operation -- the less the better.

### Definition of a B-Tree

* According to CSDN (http://blog.csdn.net/v_JULY_v/article/details/6530142): 'B' is for **Balanced**.
* Each node is a whole disk page.
* Data values are stored side-by-side with their keys in a B-tree.
* B-tree properties:
    1. Every node \\(x\\) has \\(n\\) keys: \\(k_1 \ldots k_n\\), corresponding to \\(n + 1\\) children, each has keys ranging from \\(k_{i - 1}\\) to \\(k_i\\), where \\(i \in [1, n + 1]\\), \\(k_0 \triangleq -\infty\\), and \\(k_{n + 1} \triangleq +\infty\\).
    2. Nodes have lower and upper bounds on the number of keys:
        - Every node other than the root must contain at least \\(t - 1\\) keys. 
        - Every node must contain at most \\(2 \cdot t - 1\\) keys.
    3. All leaf nodes are on the same level.
* Balance: According to Theorem 18.1 on page 489, for any \\(n\\)-key B-tree, its height is at most \\(\log_t \left ( \frac{n + 1}{2} \right ) \\). <!-- _. -->

### Basic Operations

* Schemes:
    - **Disk access scheme**:
        1. Root node is always in main memory.
        2. All non-root nodes should be loaded from disk before read.
        3. All nodes should be written to disk after being updated.
    - **One-pass scheme**: To minimize disk accesses, all algorithms should go downward only.
* Search: Very similar to binary tree search. Use linear search for finding target child (or target key) in a node.
* Insert:
    - **Root splitting**: If we found that the root is full, then create a new root and then split the original root. Tree grows only by means of root splitting.
    - **Subtree splitting**: if we found the destination child of node \\(x\\) is full, then split this child and move its median key to \\(x\\).
* Delete: Too complicated. I'll leave it here for now.

# Part VI. Graph Algorithms

//

//

//

//

//

//

//

//

//

//

//

//

//

//

//

<!--




























-->


# raticHash

My first C project, a possibly weak custom primitive hash function, with a chance of architecture-dependant code.

Please do not use in production. Or anywhere.

# Motivation

I first started thinking about this project when I was learning about constructing a exponential function to fit a table of values in Maths. The triangle of differences you had to write to do this piqued my interest, and I thought, by adding the sum of each 'row' in this triangle, you could create a one-way function, with the 'y-values' being each character of the input. Substituting addition for XOR, and with the addition of a modified LCG PRNG, I have managed to create a simple variable-length hash function that has the avalanche effect.

## Specification

Code in repository may or may not match up with the specifications below.

# State

Instead of creating a 2D matrix to preform calculations on, meaning the hash has a space complexity of O(n^2), raticHash uses 2 arrays (O(2n)), `state`, and `prev_state`. `state` being the 'total' for each row on the 'triangle', while `prev_state` stores the last column of the triangle, required for calculating the next element in `state`

```
Total   2D Matrix
23      1 2 4 6 10
10      1 2 3 4
3       1 1 1
0       0 0
0       0

2 Arrays

state   prev_state
23      10
10      4
3       1
0       0
0       0
```
Figure 1: Comparison of 2 methods.

The seed of the LCG is set to 0xaa.

# Updating

A modified version of the LCG is used.

`//TODO`


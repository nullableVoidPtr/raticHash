# raticHash

My first C project, a possibly weak custom primitive hash function, with a chance of architecture-dependant code.

Please do not use in production. Or anywhere.

# Motivation

I first started thinking about this project when I was learning about constructing a exponential function to fit a table of values in Maths. The triangle of differences you had to write to do this piqued my interest, and I thought, by adding the sum of each 'row' in this triangle, you could create a one-way function, with the 'y-values' being each character of the input. Substituting addition for XOR, and with the addition of a PRNG, I have managed to create a simple variable-length hash function (with unknown security).

## Specification

Code in repository may or may not match up with the specifications below.

# State

Instead of creating a 2D matrix to preform calculations on, meaning the hash has a space complexity of O(n^2), raticHash uses 2 arrays, with a space complexity of O(2n); `state`, and `prev_state`. `state` being the 'total' for each row on the 'triangle', while `prev_state` stores the last column of the triangle, required for calculating the next element in `state`.

```
total   matrix
31      1 2 4 8 16
15      1 2 4 8 R
7       1 2 4 R R
3       1 2 R R R
1       1 R R R R
Rs are unused elements in the matrix

state   prev_state
31      16
8       8
7       4
3       2
1       1
```
Figure 1: Comparison of 2 methods.


# Updating

To increase entropy, a custom PRNG is utilized. With its state stored in `ratic_context`, this PRNG is constantly seeded by the carryover (initialized to the input byte of the data), XORed with the output length. If a different byte is used for the seed, then the output would be different, creating an avalanche effect:

```
PRNG = ~(PRNG ^ seed) % 256
```

The state is XORed with the output of the RNG, and the carryover is set to the previous state (the last column). The previous state is then set to the output of the RNG.

The preceding process is then iterated for each row of the state, for each byte of data.

# Finalizing

Length padding is used to prevent length extension attacks. As such, the padding must be different, if the input length is different. As such, the pad length should be at least as long as the length of the output digest.

The padding consists of the counter (initialized to length of the message modulo 256), then its NOT value. The counter is then subtracted by the digest length (underflowing intentional), and the process is iterated.

The state is then updated with the padding, which then becomes the output.

# Assignment Submission

## Introduction

It is an submission for WovenPlanet challange assignment.

## Analysis

### Correctness of the given algorithm

#### Pseudocode of the algorithm

```
    flag[2]: boolean
    turn := 0
```

```
    // Algorithm for obtaining exclusive access for P0
    flag[0] := True
    while turn != 0 do
        while flag[1] do
            // do nothing
        turn := 0

    // P0 now has exclusive access, critical code section here
    flag[0] := False
```

```
    // Algorithm for obtaining exclusive access for P1
    flag[1] := True
    while turn != 1 do
        while flag[0] do
            // do nothing
        turn := 1

    // P1 now has exclusive access, critical code section here
    flag[1] := False
```

#### Mutual Exclusion

The algorithm **doesn't meet mutual exclusion requirements**.
That is, P0 and P1 can be in the critical section at the same time in some cases.
Here is an example scenario.

| P0 | P1 | Variables |
|---|---|---|
| | // ..P1 was in the critical section |flag: { False, True }, turn: 1|
|// ..idle | flag[1] := False |flag: { False, False }, turn: 1|
|// P0 tries to enter in the critical section<br>flag[0] := True| |flag: { True, False }, turn: 1|
|while turn != 0 do| |flag: { True, False }, turn: 1|
|&nbsp;&nbsp;&nbsp;&nbsp;while flag[1] do // bypass| |flag: { True, False }, turn: 1|
| | // P1 tries to enter in the critical section<br>flag[1] := True|flag: { True, True }, turn: 1|
| | while turn != 1 do // bypass|flag: { True, True }, turn: 1|
|&nbsp;&nbsp;&nbsp;&nbsp;turn:=0| |flag: { True, True }, turn: 0|
|**// P0 is in the critical section**|**// P1 is in the critical section**| |

#### Progress

The algorithm **meets progress requirements**.
Any uninterested process won't stop the other processes from entering to the critical section.

#### Bounded waiting

The algorithm **doesn't meet bounded waiting requirements**.
It doesn't stop giving turns to the same process even if there are other waiting processes in some cases.

### Alternative algorithms

Here are alternative algorithms that I have implemented in this submission.
For real time feature, I have selected the algorithms which meets bounded waiting requirements.
It would be required to make every processes have reasonable waiting times for their accesses to the critical resource on environments having short processing times and minimum latency requirements.

#### Peterson algorithm

Peterson algorithm is a famous concurrent programming algorithm for mutual exclusion.
It looks similar to the given algorithm but is known to meet all 3 requirements; mutual exclusion, progress and bounded waiting for 2 processes.
Therefore it would be a quick fix to the given algorithm considering similarity between them.
To work on Moden CPUs, some operations need to be atomic due to potential reordering of memory accesses.

Here are more detailed information about Perterson algorithm at [Wiki](https://en.wikipedia.org/wiki/Peterson%27s_algorithm).

#### Bounded-waiting Mutual Exclusion with test_and_set

This algorithm is another well known concurrent programming algorithm.
It also meets 3 requirements; mutual exclusion, progress and bounded waiting and because it supports N processes I took it as another alternative algorithm.

There are many references for this algorithm though I couldn't point the origin of this algorithm.
Here is a pseudo code for this algorithm. ([source](https://stackoverflow.com/questions/31084724/bounded-waiting-mutual-exclusion-with-test-and-set) page)
```
do {
    waiting[i] = true;
    key = true;  // <-- Boolean variable that I do not see its utility
    while (waiting[i] && key) // <-- the value of the key variable here is always true
        key = test_and_set(&lock); // <-- it might become false here, but what is the point?
    waiting[i] = false;

    /* critical section */

    j = (i + 1) % n;
    while ((j != i) && !waiting[j])
        j = (j + 1) % n;
    if (j == i)
        lock = false;
    else
        waiting[j] = false;

    /* remainder section */
} while (true);
```

## Implementation

### APIs



### Prerequisites

Following dependencies are required.

```
> g++ 7.x
> cmake 3.10.0
> gtest 1.8.0
```

##### Ubuntu

```bash
sudo apt-get install build-essential libgtest-dev cmake
```

##### M1 Mac OS

```bash
brew install cmake
brew install gtest
```

### How to build

Run following commands at the top directory of your repo.
```bash
$ mkdir build
$ cd build
$ cmake ../   # or
$ cmake -DCMAKE_INSTALL_PREFIX={install path} ..
$ make&&make install
```

### How to test

The submission provides a test binary to run tests on various synchronous algorithms.
Tests run multiple threads with a specific logic to detect failures on mutual exclusion of algorithms.

#### Test the given algorithm

#### Ubuntu
```bash
$ LD_LIBRARY_PATH={install path}/lib {install path}/bin/test_lock -a prob
```

#### M1 Mac OS
```bash
$ DYLD_LIBRARY_PATH={install path}/lib {install path}/bin/test_lock -a prob
```

#### Expected result
```bash
algorithm: prob, iteration: 100000, size: 30, threads: 2
Tests failed ##### time
```

#### Test Peterson algorithm

#### Ubuntu
```bash
$ LD_LIBRARY_PATH={install path}/lib {install path}/bin/test_lock -a peterson
```

#### M1 Mac OS
```bash
$ DYLD_LIBRARY_PATH={install path}/lib {install path}/bin/test_lock -a peterson
```

#### Expected result
```bash
algorithm: peterson, iteration: 100000, size: 30, threads: 2
Tests passed successfully.
```

#### Test the bounded waiting test_set algorithm

#### Ubuntu
```bash
$ LD_LIBRARY_PATH={install path}/lib {install path}/bin/test_lock -a test_set -t 10
```

#### M1 Mac OS
```bash
$ DYLD_LIBRARY_PATH={install path}/lib {install path}/bin/test_lock -a test_set -t 10
```

#### Expected result
```bash
algorithm: test_set, iteration: 100000, size: 30, threads: 10
Tests passed successfully.
```

## Conclusions

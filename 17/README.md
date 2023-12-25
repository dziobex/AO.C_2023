# Day 17: Clumsy Crucible

## Part 1

### Problem

For example:
```
2413432311323
3215453535623
3255245654254
3446585845452
4546657867536
1438598798454
4457876987766
3637877979653
4654967986887
4564679986453
1224686865563
2546548887735
4322674655533
```
Each city block is marked by a single digit that represents the amount of heat loss if the crucible enters that block. The starting point, the lava pool, is the top-left city block; the destination, the machine parts factory, is the bottom-right city block. (Because you already start in the top-left block, you don't incur that block's heat loss unless you leave that block and then return to it.)

Because it is difficult to keep the top-heavy crucible going in a straight line for very long, it can move at most three blocks in a single direction before it must turn 90 degrees left or right. The crucible also can't reverse direction; after entering each city block, it may only turn left, continue straight, or turn right.

One way to minimize heat loss is this path:
```
2>>34^>>>1323
32v>>>35v5623
32552456v>>54
3446585845v52
4546657867v>6
14385987984v4
44578769877v6
36378779796v>
465496798688v
456467998645v
12246868655<v
25465488877v5
43226746555v>
```
This path never moves more than three consecutive blocks in the same direction and incurs a heat loss of only 102.

Directing the crucible from the lava pool to the machine parts factory, but not moving more than three consecutive blocks in the same direction, **what is the least heat loss it can incur?**

### Theory

This task looks like a classical path-finding problem. I used the **Dijkstra Path-Finding Algorithm**, as the data didn't look complex:

```
Q - set with all unvisited nodes in the graph
S - set with all visited nodes in the graph

1. Set the minimum path of all elements of Q to ∞
2. Set the minimum path of the starting node to 0
3. Choose first element from Q - V - that has the minimum path weight
4. Remove V from Q and add it to S
5. Apply relaxation to each neighbour U of node V: if d[V] + weight(V, U) < d[U], then d[U] = d[V] + weight(V, U)
6. Repeat the 3rd step (until the Q set has at least one element)
7. All nodes contains the weight of the smallest possible path that goes to that node
```

Dijkstra works fine with the data structure (type of sets Q, S) named **heap** - it make the whole checking for the smallest distance a lot more effecient due to heap's properties.

```
Heap is a graph with the following node-hierarchy: depending on the rule, all children of each parenting node, must be greater/lesser or equal to their parent node.
The top of the heap (with no parents) is called "root".
```

**Priority queue** might be the array'ed implementation of heap - it may not be always 100% sorted data structure!

### Solution

The main difficulty in the task was to handle the fact that you can do limited amount of steps in one go. <br/>
After analyzing the text of the problem, I put together the following clues:
1. There are two main directions: horizontal (left/right) and vertical (up/down)
2. You can do up to 3 moves in one direction in one go
3. All nodes (cells) are put in matrix


The node locations were elegantly placed in the matrix, with elements close to each other being neighbors.<br/>
In order to apply DA here, I needed to find how to define the label of each node.<br/>
The first, obvious parameters are matrix's locations: y, x. Clues that I gathered also suggest the importance of the "direction" variable. <br/>

**So: each node will be represented by `y, x, direction` where direction is either horizontal or vertical.**

Then, from each node, I would do the mini-jumps between nodes up to 3 steps away (we want to check all the paths in one direction in one go) and then check them in opposite direction.<br/>

*You can imagine it as a living check board :)*

Below I placed the C code that implemented the algorithm above.

```c
for ( int sg = -1; sg <= 1; sg += 2 ) {
    int dist = popped->min_path;
    
    for ( int i = 1; i <= _max; ++i ) {
        int n_x = x + sg * i, n_y = y + sg * i;

        if ( popped->dir == '|'                             // teraz sprawdzamy elementy poziome ---
        && n_x >= 0 && n_x < grid_size ) { 
            dist += grid[y][n_x][0].heat_loss;
            if ( i >= _min && grid[y][n_x][0].min_path > dist ) {
                grid[y][n_x][0].min_path = dist;
                push_q( &pq, &grid[y][n_x][0] );
            }
        }

        if ( popped->dir == '-'                             // teraz sprawdzamy elementy pionowe |||
        && n_y >= 0 && n_y < grid_size ) {
            dist += grid[n_y][x][1].heat_loss;
            if ( i >= _min && grid[n_y][x][1].min_path > dist ) {
                grid[n_y][x][1].min_path = dist;
                push_q( &pq, &grid[n_y][x][1] );
            }
        }
    }
}
```

Putting it together with the rest of the dijkstra implementation, I found the answer in a resonable time. Good!

## Part 2
### Problem
Once an ultra crucible starts moving in a direction, it needs to move a minimum of four blocks in that direction before it can turn (or even before it can stop at the end). However, it will eventually start to get wobbly: an ultra crucible can move a maximum of ten consecutive blocks without turning.

In the above example, an ultra crucible could follow this path to minimize heat loss:

```
2>>>>>>>>1323
32154535v5623
32552456v4254
34465858v5452
45466578v>>>>
143859879845v
445787698776v
363787797965v
465496798688v
456467998645v
122468686556v
254654888773v
432267465553v
```
In the above example, an ultra crucible would incur the minimum possible heat loss of 94.

Here's another example:
```
111111111111
999999999991
999999999991
999999999991
999999999991
```
Sadly, an ultra crucible would need to take an unfortunate path like this one:
```
1>>>>>>>1111
9999999v9991
9999999v9991
9999999v9991
9999999v>>>>
```
This route causes the ultra crucible to incur the minimum possible heat loss of 71.

Directing the ultra crucible from the lava pool to the machine parts factory, **what is the least heat loss it can incur?**
### Solution
I used the whole algorithm from the solution to P1. I only changed the limit of steps to 10 and I set the _min parameter (the minimum amount of steps to do) to 4.
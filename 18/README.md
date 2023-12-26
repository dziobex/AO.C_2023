# [Day 18: Lavaduct Lagoon](https://adventofcode.com/2023/day/18)
*The digger starts in a 1 meter cube hole in the ground. They then dig the specified number of meters up (U), down (D), left (L), or right (R), clearing full 1 meter cubes as they go. The directions are given as seen from above, so if "up" were north, then "right" would be east, and so on. Each trench is also listed with the color that the edge of the trench should be painted as an RGB hexadecimal color code.The next step is to dig out the interior so that it is one meter deep as well.*

**How many cubic meters of lava could it hold?**

## Part 1

### Approach
Today's problem looks similar to the 10th day one, however processing input is a bit easier this time.

We can assume, that the whole trench is one big loop which can't loop itself inside the loop - there's one, continues field inside the trench.

In order to "dig out" the field that the trench surrounds, I used the **flood fill** algorithm (flooding algorithm) which dug out the field inside the trench. It works by adding the neighbours of the current node inside the field which were not signed as "dug out". The loop works until the stack (where I put to-visit nodes) is empty.

## Part 2

### Aproach
The data appears to be too large to handle it by the algorithm presented in part 1 approach.

I moved to the **Gauss formulas'** with the additional **Prick's formula**.

In other words: `field = gauss + 1/2 perimeter + 1`
# Lem_in

## Intro
Lem_in is an algorithm project about graph traversal and flow optimization.</br></br>
You start with a given number of ants, located in a starting room of an anthill.</br>
An anthill is made of 'rooms' (or nodes in a graph) and each room is linked to other rooms by 'tunnels' (or edges).</br>
There are two special rooms among them, the starting and the ending rooms.</br>
The goal is to make all ants going from the starting room to the ending room within the minimum number of rounds.</br>
**The difficulty is that a room (except for starting and ending rooms) can only contain 1 ant at a time.**</br>
An ant can move once a round to a linked room (using a 'tunnel').</br>
Therefore, to optimize the solution, we usually have to find multiple distinct paths to reduce the number of rounds.

## Visual
You can type ```./visual.sh [existing_map]``` or ```./visual.sh --flow-thousand``` (using the generator).</br>
```./generator --help``` </br>
![alt text](https://github.com/bwan-nan/lem_in/blob/master/small-map.gif)

## Input
```
10          // Number of ants in starting room at the beginning
A 200 200   // [Room name] [X coordinate] [Y coordinates]
B 550 150
C 550 450
##start     // Next room will be the starting room -> room 'D'
D 250 450
##end       // Next room will be the ending room -> room 'E'
E 850 450
F 850 150
A-B         // Room 'A' and 'B' are linked by a tunnel
A-C
A-D
B-D
B-F
B-E
C-D
C-E
C-F
E-F
```

## Output
```./lem_in --solution < [map_above]``` </br>
L[ant]-[room]
```
L1-B L2-C       //Round 1 : Ant number 1 goes to room B. Ant number 2 goes to room C.
L1-E L2-E L3-B L4-C
L3-E L4-E L5-B L6-C
L5-E L6-E L7-B L8-C
L7-E L8-E L9-B L10-C
L9-E L10-E
```

## Algorithm

We adapted Edmonds-Karp max-flow algorithm to fit our problem. 
We use a BFS (Breadth First Search) to find paths in the graph.
What we do is:
- We find the shortest path:</br>
 -> We calculate how many rounds the ants would take to go from starting to ending room using this path.</br>
- Then we look for an additional path. If we find one, we test the new solution:</br>
 -> While the solution is better, we continue searching for one more path.
 
 -> Else, the new solution is not better so we keep the previous one.
 
 ## Example
 ```./lem_in --paths < maps/tricky2```
 
```
Initialized 1 path:
This solution would take 23 rounds    // 23 rounds using 1 path
#  1: A-B-C-End
Initialized 2 paths:
This solution would take 15 rounds    // 15 rounds using 2 paths (15 < 23, so we keep searching)
#  2: A-B-C-End
#  3: K-4-M-N-O-P-End
Initialized 3 paths:
This solution would take 12 rounds    // 12 rounds using 3 paths (12 < 15, so we keep searching)
#  5: D-E-B-C-End
#  4: A-G-H-I-J-End
#  6: K-4-M-N-O-P-End
Initialized 4 paths:
This solution would take 12 rounds    // 12 using 4 paths so we keep the previous solution (3 paths)

L1-D L2-A L3-K
L1-E L2-G L3-4 L4-D L5-A L6-K
L1-B L2-H L3-M L4-E L5-G L6-4 L7-D L8-A L9-K
L1-C L2-I L3-N L4-B L5-H L6-M L7-E L8-G L9-4 L10-D L11-A L12-K
L1-End L2-J L3-O L4-C L5-I L6-N L7-B L8-H L9-M L10-E L11-G L12-4 L13-D L14-A L15-K
L2-End L3-P L4-End L5-J L6-O L7-C L8-I L9-N L10-B L11-H L12-M L13-E L14-G L15-4 L16-D L17-A
L3-End L5-End L6-P L7-End L8-J L9-O L10-C L11-I L12-N L13-B L14-H L15-M L16-E L17-G L18-D L19-A
L6-End L8-End L9-P L10-End L11-J L12-O L13-C L14-I L15-N L16-B L17-H L18-E L19-G L20-D
L9-End L11-End L12-P L13-End L14-J L15-O L16-C L17-I L18-B L19-H L20-E
L12-End L14-End L15-P L16-End L17-J L18-C L19-I L20-B
L15-End L17-End L18-End L19-J L20-C
L19-End L20-End
```
</br>

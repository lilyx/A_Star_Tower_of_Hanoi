A_Star_Tower_of_Hanoi
=====================

Implement Tower of Hanoi by A* algorithm

For any input N disks, there are N^3 possible states. Take N=2,3 as example, 
we could come up with graph representation.Each node represents a state of the tower,
and each edge represents a step movement.


According to A star algorithm, we need to move through the nodes base on the minimum 
value of f (x)=g (x)+h (x). Use g(x)=depth of the node, and h (x)= (the total number 
of disks of left and middle poles) + 2*（number of disks that in the right pole and 
smaller than any disk that in left or middle poles）. 

Generate two lists Open and Close. Open list all the states that could arrive after 
current movements, and Close list that all the states arrived after take current movements. 

Start from the initial state that all the disks are in the left pole, and append the
node into Close list. Then expand the graph by get all the states could reach by all the
current states that already listed in Close, and append them to Open list. Then calculate 
the A* function for all the node in Open list to choose the one that have the minimum function
value, move the node from Open list to Close list.

Keep tracking the nodes until the final goal reached.

Print out the movement in the format:
n d p d p ...

N -> move
d -> disk#
p -> pole#




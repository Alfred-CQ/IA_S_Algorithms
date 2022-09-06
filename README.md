# Searching Algorithms

The present repository stores blind searching algorithms and heuristic algorithms to find a path between two given nodes in a graph (which obvioulsy need to have at least an undirected connection).

### Install libraries 

This project make use of python libraries for graph plotting, csv reader functions and graph functions, so install the next libraries if you haven't before.

```
$ pip install matplotlib
$ pip install pandas
$ pip install networkx
```

### Compile the project

To compile the project run (make sure you've got one version of g++ installed before) the following comands and type a source and a target node:

```
$ cd src
$ g++ -o main.exe main.cpp
$ .\main.exe
Start: A
End: V
```

After this, there will be created two csv files per algorithm with the following names "$algorithm_name$_path.csv" containing the needed nodes to get to the target and "$algorithm_name$_expn.csv" containing the edges visited during the execution of the respective algorithm.

### Get Graph Plotting

To see the plot of the graph and the path given by every algorithm, run:

```
$ python .\main.py
```
You'll see a plotting of the graph like this:

![Graph Plotting](https://media.discordapp.net/attachments/886256698640171008/1016564175960547389/unknown.png)

You will be prompted a source and target node again so make sure you type the ones given before
```
Enter source node: A
Enter target node: V
```

And you'll get to see a plotting like [this](https://media.discordapp.net/attachments/886256698640171008/1016564072784859137/unknown.png) for each algorithm, where the dashed edges means the edges visited by the algorithm. 

![A* Plotting](https://cdn.discordapp.com/attachments/886256698640171008/1016599474778407012/unknown.png)

### About Logs

You can also see the costs taken by each algorithm and its respective time to find the path in console where whe can distinguish on how close is the cost found by Hill Climbing and A star algorithms (In fact dijkstra's cost and A star's cost is the same but time taken by dijkstra is longer while A star is the quickest) in relation to Dijkstra algorithm (shortest path) .

![](https://cdn.discordapp.com/attachments/886256698640171008/1016570550501527572/unknown.png)



---
### Contributors
- Chillitupa Quispihuanca, Alfred Addison
- Gomez Del Carpio, Alexander Sebastian
- Muñoz Curi, Rayver Aimar
- Quispe Salcedo, Josep Marko
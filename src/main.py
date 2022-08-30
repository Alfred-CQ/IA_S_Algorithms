import networkx as nx
import pandas as pd
import matplotlib.pyplot as plt

N_NODES = 26

vertices = [chr(e + 65) for e in range(0, N_NODES)]

graph = nx.Graph()

edges = []

df = pd.read_csv("../datasets/random_coords.csv", index_col = None)

coords = []
cur_letter = 65
for i in df.index:
    coords.append([chr(cur_letter), (df["x"][i], df["y"][i])])
    cur_letter = cur_letter + 1
pos = dict(coords)

df = pd.read_csv("../datasets/ady_matrix.csv", index_col = None)

ady_matrix = []

for i in df.index:
    row = []
    for j in df.columns:
        row.append(df[i][j])
    ady_matrix.append(row)

for i in range(0, len(ady_matrix)):
    for j in range(0, len(ady_matrix[i])):
        if(ady_matrix[i][j] == 1):
            cur_edge = (chr(i + 65), chr(j + 65))
            if(not cur_edge[::-1]  in edges):
                edges.append(cur_edge)
                
graph.add_nodes_from(vertices)
graph.add_edges_from(edges)

nx.draw(graph, pos = pos, node_color = "#add8e6", with_labels = True)

plt.show()
import networkx as nx
import pandas as pd
import matplotlib.pyplot as plt
import math
from queue import PriorityQueue

N_NODES = 26
INF = 1e7

vertices = [chr(e + 65) for e in range(N_NODES)]

def get_pos():

    df = pd.read_csv("../datasets/random_coords.csv", index_col = None)

    coords = []
    cur_letter = 65
    for i in df.index:
        coords.append([chr(cur_letter), (df["x"][i], df["y"][i])])
        cur_letter = cur_letter + 1
    pos = dict(coords)

    return pos

def get_adj_matrix():

    df = pd.read_csv("../datasets/ady_matrix.csv", index_col = None)
    
    adj_matrix = []

    for i in df.index:
        row = []
        for j in df.columns:
            row.append(df[j][i])
        adj_matrix.append(row)

    return adj_matrix

def get_edges(adj_matrix):
    
    edges = []

    for i in range(0, len(adj_matrix)):
        for j in range(0, len(adj_matrix[i])):
            if(adj_matrix[i][j] == 1):
                cur_edge = (vertices[i], vertices[j])
                if(not cur_edge[::-1]  in edges):
                    edges.append(cur_edge)
    return edges

def euclideanDistance(one, two):
    """
    Args:
        one, two -> tuple (x, y)

    Returns:
        float: Distance between those two coordinates
    """

    result = 0.0
    result += (((one[0] - two[0]) * (one[0] - two[0])) + ((one[1] - two[1]) * (one[1] - two[1])))
    return math.sqrt(result)

def next_node(distances, visited):
    min = INF
    for i in range(N_NODES):
        if(distances[i][0] < min and visited[i] == False):
            min = distances[i][0]
            min_node = i
    return min_node

def dijkstra(graph, source, target):
    distances = [[INF, -1] for i in range(N_NODES)]
    distances[source][0] = 0
    visited = [[False] for i in range(N_NODES)]
    pq = PriorityQueue()
    edges_visited = []
    last = vertices[source]
    pq.put((0, source))

    while(not pq.empty()):
        if visited[target] == True:
            break
        cur_item = pq.get()
        cur_node = cur_item[1]
        if visited[cur_node] == True:
            continue
        visited[cur_node] = True
        for children in graph[vertices[cur_node]]:
            edges_visited.append((vertices[cur_node], children ))
            cur_distance = euclideanDistance(graph.nodes[vertices[cur_node]]["pos"], graph.nodes[children]["pos"])
            if distances[cur_node][0] + cur_distance < distances[ord(children) - 65][0]:
                distances[ord(children) - 65][0] = distances[cur_node][0] + cur_distance
                distances[ord(children) - 65][1] = cur_node
                pq.put((distances[ord(children) - 65][0], ord(children) - 65))
        
    path = []
    edges = []
    pos = target

    while(pos != -1):
        path.append(pos)
        edges.append((vertices[pos], vertices[distances[pos][1]]))
        pos = distances[pos][1]

    edges.pop()
    path = [vertices[path[i]] for i in range(len(path))]
    return edges, path, edges_visited

def plot_dfs(graph, source, target):
    not_visited_edges = []
    visited_edges = []
    path_edges = []
    path = []
    df = pd.read_csv("../datasets/DFS_expn.csv", index_col = None)
    
    for i in df.index:
        visited_edges.append((df["from"][i], df["to"][i]))
    df = pd.read_csv("../datasets/DFS_path.csv", index_col = None)
    for i in df.index:
        path.append(df["label"][i])
    last = path[0]
    for i in path:
        path_edges.append((last, i))
        last = i
    path_edges.remove(path_edges[0])
    for i in edges:
        if (not i in visited_edges) and (not i in path_edges) and (not i[::-1] in visited_edges) and (not i[::-1] in path_edges):
            not_visited_edges.append(i)
    
    nx.draw_networkx(graph, pos = pos, node_color = "#add8e6", edgelist = not_visited_edges, with_labels = True, width = 1) #not_visited edges
    ax = plt.gca()
    ax.collections[0].set_edgecolor("#000000")

    nx.draw_networkx(graph, pos, nodelist=path,node_color="yellow", edgelist=path_edges, edge_color="red", node_size=210, width=3) #path edges
 
    nx.draw_networkx_edges(graph, pos, edgelist=visited_edges, edge_color="red", node_size=210, width=1, style = "dashed") #visited edges
    plt.axis("off")
    plt.title("DFS Algorithm")
    plt.show()

def plot_bfs(graph, source, target):
    not_visited_edges = []
    visited_edges = []
    path_edges = []
    path = []
    df = pd.read_csv("../datasets/BFS_expn.csv", index_col = None)
    
    for i in df.index:
        visited_edges.append((df["from"][i], df["to"][i]))
    df = pd.read_csv("../datasets/BFS_path.csv", index_col = None)
    for i in df.index:
        path.append(df["label"][i])
    last = path[0]
    for i in path:
        path_edges.append((last, i))
        last = i
    path_edges.remove(path_edges[0])
    for i in edges:
        if (not i in visited_edges) and (not i in path_edges) and (not i[::-1] in visited_edges) and (not i[::-1] in path_edges):
            not_visited_edges.append(i)
    
    nx.draw_networkx(graph, pos = pos, node_color = "#add8e6", edgelist = not_visited_edges, with_labels = True, width = 1) #not_visited edges
    ax = plt.gca()
    ax.collections[0].set_edgecolor("#000000")

    nx.draw_networkx(graph, pos, nodelist=path,node_color="yellow", edgelist=path_edges, edge_color="red", node_size=210, width=3) #path edges
 
    nx.draw_networkx_edges(graph, pos, edgelist=visited_edges, edge_color="red", node_size=210, width=1, style = "dashed") #visited edges
    plt.axis("off")
    plt.title("BFS Algorithm")
    plt.show()

def plot_dijkstra(graph, source, target):
    not_visited_edges = []

    path_edges, path, visited_edges = dijkstra(graph, source, target)

    for i in edges: #not_visited_edges
        if (not i in visited_edges) and (not i in path_edges) and (not i[::-1] in visited_edges) and (not i[::-1] in path_edges):
            not_visited_edges.append(i)

    for i in visited_edges: #visited_edges
        if i[::-1] in visited_edges:
            visited_edges.remove(i[::-1])

    for i in path_edges: #path_edges
        if i in visited_edges:
            visited_edges.remove(i)
        if i[::-1] in visited_edges:
            visited_edges.remove(i[::-1])

    nx.draw_networkx(graph, pos = pos, node_color = "#add8e6", edgelist = not_visited_edges, with_labels = True, width = 1) #not_visited edges
    ax = plt.gca()
    ax.collections[0].set_edgecolor("#000000")

    nx.draw_networkx(graph, pos, nodelist=path,node_color="yellow", edgelist=path_edges, edge_color="red", node_size=210, width=3) #path edges
 
    nx.draw_networkx_edges(graph, pos, edgelist=visited_edges, edge_color="red", node_size=210, width=1, style = "dashed") #visited edges
    plt.axis("off")
    plt.title("Dijkstra Algorithm")
    plt.show()

def plot_HillClimbing(graph, source, target):
    not_visited_edges = []
    visited_edges = []
    path_edges = []
    path = []
    df = pd.read_csv("../datasets/HC_expn.csv", index_col = None)
    
    for i in df.index:
        visited_edges.append((df["from"][i], df["to"][i]))
    df = pd.read_csv("../datasets/HC_path.csv", index_col = None)
    for i in df.index:
        path.append(df["label"][i])
    last = path[0]
    for i in path:
        path_edges.append((last, i))
        last = i
    path_edges.remove(path_edges[0])
    for i in edges:
        if (not i in visited_edges) and (not i in path_edges) and (not i[::-1] in visited_edges) and (not i[::-1] in path_edges):
            not_visited_edges.append(i)
    
    nx.draw_networkx(graph, pos = pos, node_color = "#add8e6", edgelist = not_visited_edges, with_labels = True, width = 1) #not_visited edges
    ax = plt.gca()
    ax.collections[0].set_edgecolor("#000000")

    nx.draw_networkx(graph, pos, nodelist=path,node_color="yellow", edgelist=path_edges, edge_color="red", node_size=210, width=3) #path edges
 
    nx.draw_networkx_edges(graph, pos, edgelist=visited_edges, edge_color="red", node_size=210, width=1, style = "dashed") #visited edges
    plt.axis("off")
    plt.title("Hill Climbing Algorithm")
    plt.show()

def plot_AStar(graph, source, target):
    not_visited_edges = []
    visited_edges = []
    path_edges = []
    path = []
    df = pd.read_csv("../datasets/AStar_expn.csv", index_col = None)
    
    for i in df.index:
        visited_edges.append((df["from"][i], df["to"][i]))
    df = pd.read_csv("../datasets/AStar_path.csv", index_col = None)
    for i in df.index:
        path.append(df["label"][i])
    last = path[0]
    for i in path:
        path_edges.append((last, i))
        last = i
    path_edges.remove(path_edges[0])
    for i in edges:
        if (not i in visited_edges) and (not i in path_edges) and (not i[::-1] in visited_edges) and (not i[::-1] in path_edges):
            not_visited_edges.append(i)
    
    nx.draw_networkx(graph, pos = pos, node_color = "#add8e6", edgelist = not_visited_edges, with_labels = True, width = 1) #not_visited edges
    ax = plt.gca()
    ax.collections[0].set_edgecolor("#000000")

    nx.draw_networkx(graph, pos, nodelist=path,node_color="yellow", edgelist=path_edges, edge_color="red", node_size=210, width=3) #path edges
 
    nx.draw_networkx_edges(graph, pos, edgelist=visited_edges, edge_color="red", node_size=210, width=1, style = "dashed") #visited edges
    plt.axis("off")
    plt.title("A* Algorithm")
    plt.show()


if __name__ == '__main__':

    #Graph setter
    graph = nx.Graph()
    pos = get_pos()
    adj_matrix = get_adj_matrix()
    edges = get_edges(adj_matrix)
    graph.add_nodes_from(vertices)
    nx.set_node_attributes(graph, pos, "pos")
    graph.add_edges_from(edges)

    nx.draw(graph, pos = pos, node_color = "#add8e6", with_labels = True)
    plt.show()

    source = str(input("Enter source node: "))
    target = str(input("Enter target node: "))

    #--------------------------------------------
    plot_dfs            (graph, ord(source) - 65, ord(target) - 65)             #DFS algorithm
    plot_bfs            (graph, ord(source) - 65, ord(target) - 65)             #BFS algorithm
    plot_dijkstra       (graph, ord(source) - 65, ord(target) - 65)             #Dijkstra algorithm
    plot_HillClimbing   (graph, ord(source) - 65, ord(target) - 65)             #Hill Climbing algorithm
    plot_AStar          (graph, ord(source) - 65, ord(target) - 65)             #A* algorithm

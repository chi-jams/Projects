
import networkx as nx

grid = [[2, 2, 1, 2, 1, 3, 6],
        [1, 1, 5, 3, 3, 3, 5],
        [4, 2, 3, 5, 2, 1, 3],
        [1, 1, 5, 1, 2, 4, 3],
        [2, 3, 4, 3, 3, 2, 5],
        [3, 4, 1, 3, 1, 5, 3],
        [2, 5, 5, 4, 2, 2, 0]]

maze = nx.DiGraph()

for y in range(0,7):
    for x in range(0, 7):
        node_name = "%s%s" % (chr(ord('A') + y), 1 + x)
        print(node_name)
        maze.add_node(node_name)
        #print("This is tile %s%s has value %s" % (chr(ord('A') + y), 1 + x, grid[y][x]))

for y in range(0,7):
    for x in range(0, 7):
        node_name = "%s%s" % (chr(ord('A') + y), 1 + x)
        jump = grid[y][x]
        if not y - jump < 0:
            maze.add_edge(node_name, "%s%s" % (chr(ord('A') + y - jump), 1 + x))
        if not y + jump > 7:
            maze.add_edge(node_name, "%s%s" % (chr(ord('A') + y + jump), 1 + x))

        if not x - jump < 0:
            maze.add_edge(node_name, "%s%s" % (chr(ord('A') + y), 1 + x - jump))
        if not x + jump > 7:
            maze.add_edge(node_name, "%s%s" % (chr(ord('A') + y), 1 + x + jump))

print(' '.join(nx.shortest_path(maze, source='A1', target='G7')))
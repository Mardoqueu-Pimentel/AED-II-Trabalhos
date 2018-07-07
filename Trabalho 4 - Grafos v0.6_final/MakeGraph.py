from graphviz import Graph
from graphviz import Digraph

for k in range(30):
	with open("it-" + str(k)) as file:

		G = file.read().split('\n')
		G = [gs.split(' = ') for gs in G]

		dot = Graph(str(k) + 'graph', format='png')

		for roll in G:
			if (len(roll) > 1):
				dot.node(roll[0], roll[0])

		for roll in G:
			if (len(roll) > 1):
				for children in roll[1].split(' '):
					if children > roll[0]:
						dot.edge(roll[0], children)

			dot.render('it-' + str(k) + '.gv')

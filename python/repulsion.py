
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

fig = plt.figure(figsize=(7,7))

axes = fig.add_axes([0, 0, 1, 1], frameon=False)
axes.set_xlim(0, 1)
axes.set_xticks([])
axes.set_ylim(0, 1)
axes.set_yticks([])

plt.show()
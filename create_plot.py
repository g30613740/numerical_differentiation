import matplotlib.pyplot as plt
import numpy as np
import math
import sys


f = open ("parameters.txt", "r")

M_viz = int (f.readline ())
M = int (f.readline ())
shredded_M = int (f.readline ())

x_viz = (f.readline ()).split ()
y_viz = (f.readline ()).split ()

x = (f.readline ()).split ()
nm_derivative = (f.readline ()).split ()

shredded_x = (f.readline ()).split ()
shredded_nm_derivative = (f.readline ()).split ()

updated_runge_solution = (f.readline ()).split ()

f.close ()

for i in range (M_viz):
       x_viz[i] = float (x_viz[i])
       y_viz[i] = float (y_viz[i])

for i in range (M):
       x[i] = float (x[i])
       nm_derivative[i] = float (nm_derivative[i])
       updated_runge_solution[i] = float (updated_runge_solution[i])

for i in range (shredded_M):
       shredded_x[i] = float (shredded_x[i])
       shredded_nm_derivative[i] = float (shredded_nm_derivative[i])

fig, ax = plt.subplots ()                                                                         # create plot
ax.plot (x_viz, y_viz, linewidth = 1.5, label = "math")                                           # draw f'(x)
ax.plot (x, nm_derivative, "o", color = 'green', label = "h")
ax.plot (shredded_x, shredded_nm_derivative, "o", color = 'red', label = "0.5h")
ax.plot (x, updated_runge_solution, "o", color = 'blue', label = "Runge")
ax.legend ()                                                                                      # draw legend 

ax.grid ()                                                                                        # draw grid

plt.show ()                                                                                       # show the figure
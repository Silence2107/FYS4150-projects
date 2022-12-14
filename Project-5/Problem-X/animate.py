import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter

import pyarma as pa

#Credits: 
#Much of this source code is copied from https://anderkve.github.io/FYS3150/book/projects/project5.html
#Some also taken from https://anderkve.github.io/FYS3150/book/introduction_to_cpp/intro_to_armadillo.html

#
# Let's generate a dummy time series for a function z(x,y,t)
#

# Set up a 2D xy grid
h = 0.005
x_points = np.arange(0, 1, h)
y_points = np.arange(0, 1, h)
x, y = np.meshgrid(x_points, y_points, sparse=True)

# Array of time points
dt = 2.5E-5
t_points = np.linspace(0, 80*dt, 80)

#Loading the data set of probabilities exported from Problem 8. 
#This is a cube in x,y,time and should be used in place of the previous example function of this scrpit.
A = pa.cube() #Create pa.mat object (just as arma::mat in C++)
# Load the content of the matrix you saved into your Python program.
A.load("Project-5/Problem-X/data3d.out")
#This A has [cube size: 199x199x81]
#TODO: replace z-function below with this data. Perhaps by taking slices like z_data = pa.mat(A[ :, : , t/dt ])
#However need to make sure t/dt is an integer, and there are other places we may run index out of bounds too.

# A function for a Gaussian that is travelling 
# in the x direction and broadening as time passes
def z(xpar,ypar,tpar):
    # turn matrix A into function
    i,j,k = int(xpar//h), int(ypar//h), int(tpar//dt)

    return A[i,j,k]

# Fill z_data_list with f(x,y,t)
z_data_list = []
for t in t_points:
    z_data = np.zeros((len(x_points), len(y_points)))
    for x in x_points:
        for y in y_points:
            z_data[int(x//h),int(y//h)] = z(x,y,t)
    z_data_list.append(z_data)


#
# Now the list z_data_list contains a series of "frames" of z(x,y,t), 
# where each frame can be plotted as a 2D image using imshow. Let's
# animate it!
#

# Some settings
fontsize = 12
t_min = t_points[0]
x_min, x_max = x_points[0], x_points[-1]
y_min, y_max = y_points[0], y_points[-1]

# Create figure
fig = plt.figure()
ax = plt.gca()

# Create a colour scale normalization according to the max z value in the first frame
norm = matplotlib.cm.colors.Normalize(vmin=0.0, vmax=np.max(z_data_list[0]))

# Plot the first frame
img = ax.imshow(z_data_list[0], extent=[x_min,x_max,y_min,y_max], cmap=plt.get_cmap("viridis"), norm=norm)

# Axis labels
plt.xlabel("x", fontsize=fontsize)
plt.ylabel("y", fontsize=fontsize)
plt.xticks(fontsize=fontsize)
plt.yticks(fontsize=fontsize)

# Add a colourbar
cbar = fig.colorbar(img, ax=ax)
cbar.set_label("z(x,y,t)", fontsize=fontsize)
cbar.ax.tick_params(labelsize=fontsize)

# Add a text element showing the time
time_txt = plt.text(0.95, 0.95, "t = {:.3e}".format(t_min), color="white", 
                    horizontalalignment="right", verticalalignment="top", fontsize=fontsize)

# Function that takes care of updating the z data and other things for each frame
def animation(i):
    # Normalize the colour scale to the current frame?
    norm = matplotlib.cm.colors.Normalize(vmin=0.0, vmax=np.max(z_data_list[i]))
    img.set_norm(norm)

    # Update z data
    img.set_data(z_data_list[i])

    # Update the time label
    current_time = t_min + i * dt
    time_txt.set_text("t = {:.3e}".format(current_time))

    return img

# Use matplotlib.animation.FuncAnimation to put it all together
anim = FuncAnimation(fig, animation, interval=1, frames=np.arange(0, len(z_data_list), 2), repeat=False, blit=0)

# Run the animation!
#plt.show()

# # Save the animation
writergif = PillowWriter(fps=30)
anim.save('Project-5/Problem-X/animation.gif', writer=writergif)

import math
import serial
from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation

# Initialize the serial port (update COM port as needed)
ser = serial.Serial('COM4', 9600, timeout=0.1)

# Set up the polar plot
fig = plt.figure()
ax = fig.add_subplot(111, polar=True)

def update(frame):
    # Read serial data
    line = ser.readline().decode().strip()
    
    if line:
        print(line)  # Print the data for debugging
        
        # Parse the angle and distance from the serial input
        try:
            angle, distance = map(int, line.split(','))
        except ValueError:
            return  # Ignore any malformed data lines
        
        # Convert angle to radians for polar plotting
        angle_rad = math.radians(angle)
        
        # Set the color of the dot based on distance
        color = 'red' if distance < 10 else 'blue'
        
        # Clear plot if the angle is 0 (indicating a new cycle)
        if angle == 0:
            ax.clear()
            ax.set_ylim(0, max(20, distance))  # Set a reasonable radial limit
        
        # Plot the current point
        ax.plot([angle_rad], [distance], 'o', color=color)
    else:
        print('loading...')  # Indicate no data

# Set up the animation
animation = FuncAnimation(fig, update)

plt.show()

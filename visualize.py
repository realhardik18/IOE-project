import math
import serial
from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation
from collections import deque

plt.title('IOE project 2024')
ser = serial.Serial('COM4', 9600, timeout=0.1)

# Set up the polar plot
fig = plt.figure()
ax = fig.add_subplot(111, polar=True)
ax.set_ylim(0, 15)  # Set the radial limit to range from 0 to 15

# Store points (angle, distance, and intensity for fade effect)
points = deque(maxlen=500)  # Limit the number of dots to avoid clutter

# Current angle for the sweeping line
current_angle_rad = 0

def update(frame):
    global current_angle_rad

    # Read serial data
    line = ser.readline().decode().strip()
    
    if line:
        print(line)  # Print the data for debugging

        # Parse the data based on the format
        if line.startswith("ALERT"):
            try:
                _, angle, distance = line.split(",")
                angle = int(angle)
                distance = int(distance)
                alert = True
            except ValueError:
                return  # Ignore malformed data
        else:
            try:
                angle = int(line)
                distance = None
                alert = False
            except ValueError:
                return  # Ignore malformed data

        # Convert angle to radians for polar plotting
        current_angle_rad = math.radians(angle)
        
        # If alert, plot the point and add to deque
        if alert and distance is not None:
            points.append((current_angle_rad, distance, 1.0))  # (angle, distance, intensity)

            # Print alert on console for debugging
            print(f"ALERT: Angle {angle}, Distance {distance}")
        
        # Update plot
        ax.clear()  # Clear the plot
        ax.set_ylim(0, 15)  # Set radial limit to 15

        # Draw the sweeping line
        ax.plot([current_angle_rad, current_angle_rad], [0, 15], color='green', linewidth=1.5, alpha=0.8)

        # Plot points with fading effect
        updated_points = []
        for angle_rad, dist, intensity in points:
            if intensity > 0:  # Only plot points with intensity > 0
                ax.plot([angle_rad], [dist], 'o', color=(1, 0, 0, intensity))  # Red with fade
                updated_points.append((angle_rad, dist, intensity - 0.5))  # Gradually fade
        points.clear()
        points.extend(updated_points)  # Update points with new intensities

# Set up the animation
animation = FuncAnimation(fig, update, interval=50)  # Lower interval for smoother updates

plt.show()

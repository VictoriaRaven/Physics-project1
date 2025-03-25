import tkinter as tk
from tkinter import filedialog, messagebox
import math
import ctypes

#Idea made: 2024
# add code for reading file: 2024
# add code for the rest (concepts of physics, math, and securing data on the file): 2025
# added comments: 2025
# later on, I want to secure this so maybe enable security IT/cybersecurity concepts

'''
This project is a Python application that analyzes weather data from a file, 
using concepts from physics, math, and cybersecurity to interpret the information. 
It processes data such as temperature, humidity, wind speed, and atmospheric pressure 
to identify potential weather threats, like storms or high winds, based on predefined 
thresholds. The math is used to calculate wind force, while physics is used to detect 
low pressure, which could indicate a storm. A few cybersecurity concepts makes this
data secure and in the ranges (boundaries) to prevent alerts/intent input. 
This can be used by meteorologists or emergency services to quickly identify 
dangerous weather conditions and take preventive measures.
'''

# Enable DPI awareness (for high-DPI displays)
# prevents a Blurry GUI
if ctypes.windll.shcore.SetProcessDpiAwareness:
    ctypes.windll.shcore.SetProcessDpiAwareness(1)

# Function to process the weather data from the file
def analyze_weather(file_path):
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()

            # Process each line (weather report)
            for line in lines:
                # Split the line into individual data points
                data = list(map(float, line.split()))

                if len(data) != 4:
                    print(f"Invalid data format: {line}")
                    continue

                temperature, humidity, wind_speed, pressure = data

                # Print the raw data
                print(
                    f"Temperature: {temperature}°C, Humidity: {humidity}%, Wind Speed: {wind_speed} km/h, Pressure: {pressure} mb")

                # PHYSICS: Analyze pressure drop (indicating storms) and wind speed
                if pressure < 1009:  # Low pressure may indicate storms
                    print("Physics Alert: Low pressure detected! Possible storm conditions.")

                # MATH: Wind Speed to Force Calculation (Wind Force = 0.5 * air density * wind speed^2)
                air_density = 1.225  # kg/m³ at sea level
                wind_force = 0.5 * air_density * math.pow(wind_speed, 2)
                print(f"Math Insight: Wind Force = {wind_force:.2f} N (Newton)")

                # CYBERSECURITY: File and input handling (safe reading of data)
                # Checking if values are within expected ranges to prevent erroneous or malicious data.
                if temperature < -50 or temperature > 60:  # Out of normal temperature range
                    print("Cybersecurity Alert: Unlikely temperature data detected!")
                if wind_speed < 0 or wind_speed > 300:  # Out of reasonable wind speed range
                    print("Cybersecurity Alert: Unlikely wind speed data detected!")
                if pressure < 950 or pressure > 1050:  # Pressure outside expected range
                    print("Cybersecurity Alert: Unlikely atmospheric pressure data detected!")

                # Extreme weather alerts based on predefined thresholds (MATH)
                if temperature > 30:
                    print("Math Alert: High temperature detected!")

                if humidity > 55:
                    print("Math Alert: High humidity detected!")

                if wind_speed > 20:
                    print("Math Alert: High wind speed detected!")
                print("-" * 40)  # Separator between reports

    except Exception as e:
        messagebox.showerror("Error", f"Error reading the file: {e}")

# Function to open the file chooser dialog
def open_file():
    file_path = filedialog.askopenfilename(title="Select Weather Report",
                                           filetypes=(("Text Files", "*.txt"), ("All Files", "*.*")))
    if file_path:
        analyze_weather(file_path)

# Set up the main GUI window
def main():
    root = tk.Tk()
    root.title("WeatherRPT DataAnalyzer")
    root.geometry("300x150")

    label = tk.Label(root, text="Select a weather report file")
    label.pack(pady=20)

    open_button = tk.Button(root, text="Open File", command=open_file)
    open_button.pack()

    root.mainloop()

if __name__ == "__main__":
    main()
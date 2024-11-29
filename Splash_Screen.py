import tkinter as tk
from PIL import Image, ImageTk
import os

# Function to switch from splash screen to new Python file
def run_new_file():
    splash.destroy()  # Close the splash screen
    os.system(r"C:\Users\Prateek\Collectors\FrontEndUI.py")  # Replace with the full path to your new Python file

# Create the splash screen
splash = tk.Tk()
splash.title("Splash Screen")

# Get screen dimensions
screen_width = splash.winfo_screenwidth()
screen_height = splash.winfo_screenheight()
splash.geometry(f"{screen_width}x{screen_height}")
splash.configure(bg="#4B3621")  # Dark brown background

# Add background image resized to full screen with reduced opacity
bg_image = Image.open(r"C:\Users\Prateek\Collectors\assets\vintage-science-education-background_23-2148492740.png").convert("RGBA")
bg_image = bg_image.resize((screen_width, screen_height), Image.Resampling.LANCZOS)

# Create a white overlay with adjustable transparency
white_overlay = Image.new("RGBA", bg_image.size, (255, 255, 255, int(255 * 0.4)))  # 0.4 = 40% opacity
bg_image = Image.alpha_composite(bg_image, white_overlay)

bg_photo = ImageTk.PhotoImage(bg_image)

bg_label = tk.Label(splash, image=bg_photo)
bg_label.place(relwidth=1, relheight=1)  # Make it cover the entire screen

# Add logo image
logo_path = r"C:\Users\Prateek\Collectors\assets\Ask_Sure_Logo.jpg"
logo_image = Image.open(logo_path).convert("RGBA")
logo_image = logo_image.resize((300, 300), Image.Resampling.LANCZOS)  # Resize logo to fit on the screen
logo_photo = ImageTk.PhotoImage(logo_image)

# Create a Canvas to display the background and logo
canvas = tk.Canvas(splash, width=screen_width, height=screen_height, bg="#4B3621", bd=0, highlightthickness=0)
canvas.place(relwidth=1, relheight=1)  # Make it cover the entire screen

# Add the logo on top of the background
logo_label = tk.Label(splash, image=logo_photo, bg="#4B3621")
logo_label.place(relx=0.5, rely=0.4, anchor="center")  # Position the logo at the center of the splash screen

# Display the splash screen for 6 seconds and then run the new Python file
splash.after(9000, run_new_file)  # 1000 ms = 6 seconds
splash.mainloop()

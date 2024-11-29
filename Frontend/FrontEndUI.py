import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk  # For handling images

# Function to handle button click
def get_answer():
    question = question_entry.get()
    if question.strip():
        response_text.set(f"Response for your question: '{question}'")
    else:
        response_text.set("Please enter a question.")

# Function to resize content dynamically
def resize(event):
    canvas.configure(scrollregion=canvas.bbox("all"))
    canvas.itemconfig(canvas_window, width=event.width)

    # Resize background image to fit window
    new_width = event.width
    new_height = event.height
    bg_image_resized = bg_image_original.resize((new_width, new_height), Image.Resampling.LANCZOS)
    bg_photo_resized = ImageTk.PhotoImage(bg_image_resized)

    # Update the background image without adding multiple instances
    canvas.itemconfig(background_image_id, image=bg_photo_resized)
    canvas.bg_image_resized = bg_photo_resized  # Keep a reference to avoid garbage collection

# Create the main window
root = tk.Tk()
root.title("ASK ME")
root.geometry("600x800")  # Default size
root.minsize(600, 800)  # Minimum size
root.configure(bg="#D2B48C")  # Light brown background color

# Load the background image with reduced opacity
background_image_path = "./assets/vintage-science-education-background.png"  # Path to the uploaded image
bg_image_original = Image.open(background_image_path).convert("RGBA")
bg_image_original = bg_image_original.resize((600, 800), Image.Resampling.LANCZOS)  # Resize to initial window size
bg_image_original.putalpha(90)  # Set opacity (0-255, lower = more transparent)
bg_photo_resized = ImageTk.PhotoImage(bg_image_original)

# Main frame for scrollability
main_frame = ttk.Frame(root)
main_frame.pack(fill=tk.BOTH, expand=True)

# Scrollable canvas
canvas = tk.Canvas(main_frame, bg="#D2B48C", highlightthickness=0)
scrollbar = ttk.Scrollbar(main_frame, orient=tk.VERTICAL, command=canvas.yview)
canvas.configure(yscrollcommand=scrollbar.set)

# Create the background image on the canvas (initially)
background_image_id = canvas.create_image(0, 0, image=bg_photo_resized, anchor="nw")

scrollable_frame = ttk.Frame(canvas)
scrollable_frame.bind("<Configure>", lambda e: canvas.configure(scrollregion=canvas.bbox("all")))
canvas_window = canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")

canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

# Bind resize event to dynamically adjust content
canvas.bind("<Configure>", resize)

# "ASK ME" Heading with curved effect
heading_label = tk.Label(
    scrollable_frame,
    text="ASK ME",
    font=("Arial", 36, "bold"),
    bg="#4B3621",  # Dark brown background
    fg="#D2B48C",  # Light brown text
    relief="ridge",  # Slight curvature
    borderwidth=10,
    padx=20,  # Extra padding for rounded look
    pady=10
)
heading_label.pack(pady=20, fill=tk.X, expand=True)

# "Enter your question below:" Label with curved effect
question_label = tk.Label(
    scrollable_frame,
    text="Enter your question below:",
    font=("Arial", 14),
    bg="#8B4513",  # Saddle brown background
    fg="#D2B48C",  # Light brown text
    relief="ridge",  # Slight curvature
    borderwidth=5,
    padx=10,  # Extra padding for rounded look
    pady=5
)
question_label.pack(pady=(10, 5), fill=tk.X, expand=True)

# Input field styled like ChatGPT
style = ttk.Style()
style.configure(
    "CustomEntry.TEntry",
    font=("Arial", 14),
    padding=10,
    relief="flat"
)
question_entry = ttk.Entry(
    scrollable_frame,
    style="CustomEntry.TEntry",
    width=70  # Wider input box
)
question_entry.pack(pady=10, fill=tk.X, expand=True)

# "Get Answer" button with light brown color
style.configure(
    "CustomButton.TButton",
    font=("Arial", 14, "bold"),
    background="#D2B48C",  # Light brown button
    foreground="#4B3621",  # Dark brown text
    padding=10
)
style.map(
    "CustomButton.TButton",
    background=[("active", "#8B4513")],
    foreground=[("active", "#FFD700")]
)
get_answer_button = ttk.Button(
    scrollable_frame,
    text="Get Answer",
    command=get_answer,
    style="CustomButton.TButton"
)
get_answer_button.pack(pady=20)

# Response display with default text
response_text = tk.StringVar(value="Your response will be shown here...")
response_label = tk.Label(
    scrollable_frame,
    textvariable=response_text,
    font=("Arial", 14),
    bg="#F5DEB3",  # Light wheat background for response box
    fg="#4B3621",  # Dark brown text
    wraplength=500,
    justify="left",
    relief="groove",
    padx=10,
    pady=10
)
response_label.pack(pady=20, fill=tk.X, expand=True)

# Run the application
root.mainloop()

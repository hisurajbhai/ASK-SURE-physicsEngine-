import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk
import os

class EnhancedSplashScreen:
    def __init__(self, master):
        self.master = master
        master.title("Ask Sure")
        
        # Screen dimensions
        screen_width = master.winfo_screenwidth()
        screen_height = master.winfo_screenheight()
        master.geometry(f"{screen_width}x{screen_height}")
        master.configure(bg="#2C1810")  # Deep dark brown base

        # Color Palette (Brown Shades)
        self.colors = {
            'dark_brown': '#2C1810',   # Deep dark brown
            'medium_brown': '#6F4E37', # Rich coffee brown
            'light_brown': '#A0522D',  # Sienna
            'accent_brown': '#D2691E', # Warm terracotta
        }

        # Create a gradient background
        self.create_gradient_background(screen_width, screen_height)

        # Add logo with sophisticated styling
        self.add_logo()

        # Add loading elements
        self.add_loading_elements()

        # Schedule transition
        master.after(4000, self.run_main_application)

    def create_gradient_background(self, width, height):
        # Create a canvas for gradient background
        self.canvas = tk.Canvas(self.master, width=width, height=height, highlightthickness=0)
        self.canvas.place(x=0, y=0)

        # Create gradient effect
        for i in range(height):
            # Interpolate between dark brown and medium brown
            r = int(44 * (height - i) / height + 111 * i / height)
            g = int(30 * (height - i) / height + 78 * i / height)
            b = int(16 * (height - i) / height + 55 * i / height)
            color = f'#{r:02x}{g:02x}{b:02x}'
            self.canvas.create_line(0, i, width, i, fill=color)

    def add_logo(self):
        try:
            # Load and process logo
            logo_path = r"C:\Users\Prateek\Collectors\assets\Ask_Sure_Logo.jpg"
            logo_image = Image.open(logo_path).convert("RGBA")
            
            # Circular crop and apply shadow effect
            logo_image = self.create_circular_logo(logo_image, (350, 350))
            
            self.logo_photo = ImageTk.PhotoImage(logo_image)
            
            # Logo with subtle shadow
            logo_label = tk.Label(
                self.master, 
                image=self.logo_photo, 
                bg=self.colors['dark_brown'], 
                borderwidth=0
            )
            logo_label.place(relx=0.5, rely=0.4, anchor="center")

        except Exception as e:
            print(f"Error loading logo: {e}")

    def create_circular_logo(self, image, size):
        # Resize and create circular mask
        image = image.resize(size, Image.Resampling.LANCZOS)
        
        # Create circular mask
        mask = Image.new('L', image.size, 0)
        from PIL import ImageDraw
        draw = ImageDraw.Draw(mask) 
        draw.ellipse((0, 0, image.width, image.height), fill=255)
        
        output = Image.new('RGBA', image.size, (0, 0, 0, 0))
        output.paste(image, (0, 0), mask)
        return output

    def add_loading_elements(self):
        # Sophisticated loading text
        loading_text = tk.Label(
            self.master, 
            text="Ask Sure", 
            font=("Segoe UI", 24, "bold"),
            fg=self.colors['accent_brown'], 
            bg=self.colors['dark_brown']
        )
        loading_text.place(relx=0.5, rely=0.6, anchor="center")

        # Custom progress bar
        style = ttk.Style()
        style.theme_use('default')
        style.configure(
            "Custom.Horizontal.TProgressbar", 
            background=self.colors['light_brown'], 
            troughcolor=self.colors['medium_brown']
        )
        
        self.progress = ttk.Progressbar(
            self.master, 
            style="Custom.Horizontal.TProgressbar",
            orient="horizontal", 
            length=300, 
            mode='indeterminate'
        )
        self.progress.place(relx=0.5, rely=0.7, anchor="center")
        
        # Start progress bar animation
        self.progress.start(10)

    def run_main_application(self):
        # Stop progress bar
        self.progress.stop()
        
        # Close splash screen
        self.master.destroy()
        
        # Launch main application
        os.system(r"C:\Users\Prateek\Collectors\FrontEndUI.py")

def main():
    root = tk.Tk()
    app = EnhancedSplashScreen(root)
    root.mainloop()

if __name__ == "__main__":
    main()
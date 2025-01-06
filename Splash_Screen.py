import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk
import os
import sys
from dummyt1 import PhysicsAIGUI  # Import the main application class

class EnhancedSplashScreen:
    def __init__(self, master):
        self.master = master
        self.animation_running = True  # Flag to control animation
        master.title("ASK SURE")
        
        # Get screen dimensions
        screen_width = master.winfo_screenwidth()
        screen_height = master.winfo_screenheight()
        master.geometry(f"{screen_width}x{screen_height}")
        master.configure(bg="#1E1E1E")  # Dark modern background

        # Modern Color Palette
        self.colors = {
            'bg_dark': '#1E1E1E',      # Main background
            'bg_light': '#2D2D2D',      # Secondary background
            'accent': '#00FF00',        # Matrix green accent
            'text_primary': '#FFFFFF',   # Primary text
            'text_secondary': '#888888', # Secondary text
            'button': '#00AA00',        # Button color
        }

        # Create main container
        self.container = tk.Frame(master, bg="#1E1E1E")
        self.container.place(relx=0, rely=0, relwidth=1, relheight=1)

        # Add modern elements
        self.create_splash_content()

        # Schedule transition
        master.after(4000, self.run_main_application)

    def create_splash_content(self):
        # Create center frame
        center_frame = tk.Frame(
            self.container,
            bg=self.colors['bg_dark'],
            padx=50,
            pady=50
        )
        center_frame.place(relx=0.5, rely=0.5, anchor="center")

        try:
            # Load logo with new path handling
            logo_path = get_resource_path("assets/Ask_Sure_Logo.jpg")
            logo_image = Image.open(logo_path)
            logo_image = self.create_circular_logo(logo_image, (300, 300))
            self.logo_photo = ImageTk.PhotoImage(logo_image)
            
            # Modern logo container
            logo_frame = tk.Frame(
                center_frame,
                bg=self.colors['bg_light'],
                relief="flat",
                bd=0
            )
            logo_frame.pack(pady=(0, 30))

            logo_label = tk.Label(
                logo_frame,
                image=self.logo_photo,
                bg=self.colors['bg_light'],
                bd=0
            )
            logo_label.pack(padx=20, pady=20)

        except Exception as e:
            print(f"Error loading logo: {e}")

        # Modern title with matrix effect
        title_label = tk.Label(
            center_frame,
            text="ASK SURE",
            font=("Helvetica", 36, "bold"),
            fg=self.colors['accent'],
            bg=self.colors['bg_dark'],
            pady=20
        )
        title_label.pack()

        # Subtitle
        subtitle_label = tk.Label(
            center_frame,
            text="Your Intelligent Physics Problem Solver",
            font=("Helvetica", 14),
            fg=self.colors['text_secondary'],
            bg=self.colors['bg_dark']
        )
        subtitle_label.pack(pady=(0, 30))

        # Modern progress bar
        style = ttk.Style()
        style.theme_use('default')
        style.configure(
            "Modern.Horizontal.TProgressbar",
            troughcolor=self.colors['bg_light'],
            background=self.colors['accent'],
            thickness=8
        )
        
        # Progress bar frame
        progress_frame = tk.Frame(
            center_frame,
            bg=self.colors['bg_dark'],
            pady=20
        )
        progress_frame.pack(fill=tk.X)

        self.progress = ttk.Progressbar(
            progress_frame,
            style="Modern.Horizontal.TProgressbar",
            orient="horizontal",
            length=400,
            mode='indeterminate'
        )
        self.progress.pack()

        # Loading text
        self.loading_label = tk.Label(
            center_frame,
            text="Initializing...",
            font=("Helvetica", 10),
            fg=self.colors['text_secondary'],
            bg=self.colors['bg_dark']
        )
        self.loading_label.pack(pady=10)
        
        # Start progress animation
        self.progress.start(15)
        self.animate_loading_text()

    def animate_loading_text(self):
        """
        Animate loading text with error handling
        """
        if not self.animation_running:
            return
            
        try:
            loading_texts = ["Initializing...", "Loading Models...", "Preparing AI...", "Almost Ready..."]
            current = getattr(self, '_loading_index', 0)
            
            # Check if label still exists
            if hasattr(self, 'loading_label') and self.loading_label.winfo_exists():
                self.loading_label.config(text=loading_texts[current])
                current = (current + 1) % len(loading_texts)
                self._loading_index = current
                self.master.after(1000, self.animate_loading_text)
        except Exception as e:
            print(f"Animation error: {e}")
            self.animation_running = False

    def create_circular_logo(self, image, size):
        # Resize image
        image = image.resize(size, Image.Resampling.LANCZOS)
        
        # Create circular mask
        mask = Image.new('L', size, 0)
        from PIL import ImageDraw
        draw = ImageDraw.Draw(mask)
        draw.ellipse((0, 0) + size, fill=255)
        
        # Apply mask
        output = Image.new('RGBA', size, (0, 0, 0, 0))
        output.paste(image, (0, 0), mask)
        return output

    def run_main_application(self):
        """
        Launch the main application after splash screen
        """
        try:
            # Stop animations
            self.animation_running = False
            self.progress.stop()
            
            # Remove splash screen contents
            self.container.destroy()
            
            # Initialize main application with current window
            main_app = PhysicsAIGUI(self.master)
            
            # Update the window
            self.master.update()
            
        except Exception as e:
            print(f"Error launching main application: {e}")
            sys.exit(1)

    def __del__(self):
        """
        Cleanup when object is destroyed
        """
        self.animation_running = False

def main():
    root = tk.Tk()
    app = EnhancedSplashScreen(root)
    root.mainloop()

if __name__ == "__main__":
    main()
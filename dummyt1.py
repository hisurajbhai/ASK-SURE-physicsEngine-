import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk
import json
import nlpcloud
from dotenv import load_dotenv
import os
import sys

# Load environment variables
load_dotenv()

def get_resource_path(relative_path):
    try:
        base_path = sys._MEIPASS
    except Exception:
        base_path = os.path.abspath(".")
    return os.path.join(base_path, relative_path)

# Use this for loading files
logo_path = get_resource_path("assets/Ask_Sure_Logo.jpg")

class PhysicsAIAssistant:
    def __init__(self):
        # NLP Cloud client initialization with your specific configuration
        self.client = nlpcloud.Client(
            "finetuned-llama-3-70b", 
            "278ce0a3551fc8faa5f499bfa7f7649e886fc444", 
            gpu=True
        )

    def format_response(self, text):
        """
        Format the response to make it more readable
        """
        # Remove LaTeX formatting
        formatted_text = text.replace('\\[', '')
        formatted_text = formatted_text.replace('\\]', '')
        formatted_text = formatted_text.replace('\\(', '')
        formatted_text = formatted_text.replace('\\)', '')
        formatted_text = formatted_text.replace('\\text', '')
        
        # Split into lines and clean up
        lines = formatted_text.split('\n')
        cleaned_lines = []
        
        for line in lines:
            line = line.strip()
            if line:  # Only add non-empty lines
                # Remove extra spaces and clean up mathematical expressions
                line = ' '.join(line.split())
                line = line.replace('  ', ' ')
                cleaned_lines.append(line)
        
        # Rebuild the response in a structured format
        final_response = ""
        
        # Add sections with clear headers
        for line in cleaned_lines:
            if "Thus" in line or "Therefore" in line:
                final_response += "\nFinal Answer:\n" + line + "\n"
            elif "=" in line:
                final_response += "\nCalculation Step:\n" + line + "\n"
            elif "where:" in line:
                final_response += "\nGiven Variables:\n" + line + "\n"
            else:
                final_response += line + "\n"
                
        return final_response.strip()

    def get_response(self, question):
        """
        Get response from NLP Cloud using question method
        """
        try:
            response = self.client.question(
                question=question,
                context="""We have built security into every component of the network. 
                Cloudflare's 155 Tbps network blocks an average of 70 billion threats per day, 
                including some of the largest DDoS attacks ever recorded. Each and every login, 
                request, and response that goes through our network strengthens the machine learning 
                that we apply to detect and block threats at the edge, before they ever reach your organization."""
            )
            
            if 'answer' in response:
                # Format the response before returning
                formatted_response = self.format_response(response['answer'])
                return formatted_response
            return "No answer found"
            
        except Exception as e:
            return f"Error: {str(e)}"

class PhysicsAIGUI:
    def __init__(self, root=None):
        self.root = root if root else tk.Tk()
        self.root.title("ASK SURE")
        self.root.geometry("1000x800")
        self.root.minsize(800, 600)
        self.root.configure(bg="#1E1E1E")
        
        self.ai_assistant = PhysicsAIAssistant()
        self.setup_gui()
        
        # Force update of the window
        self.root.update_idletasks()

    def setup_gui(self):
        # Main container with padding
        main_container = tk.Frame(self.root, bg="#1E1E1E", padx=20, pady=20)
        main_container.pack(fill=tk.BOTH, expand=True)

        # Header frame
        header_frame = tk.Frame(main_container, bg="#1E1E1E")
        header_frame.pack(fill=tk.X, pady=(0, 20))

        # Logo/Title
        title_label = tk.Label(
            header_frame,
            text="ASK SURE",
            font=("Helvetica", 32, "bold"),
            bg="#1E1E1E",
            fg="#00FF00",  # Matrix green
            pady=20
        )
        title_label.pack()

        # Subtitle
        subtitle_label = tk.Label(
            header_frame,
            text="Your Intelligent Physics Problem Solver",
            font=("Helvetica", 14),
            bg="#1E1E1E",
            fg="#888888"
        )
        subtitle_label.pack()

        # Main content frame
        content_frame = tk.Frame(main_container, bg="#1E1E1E")
        content_frame.pack(fill=tk.BOTH, expand=True)

        # Question section
        question_frame = tk.Frame(content_frame, bg="#2D2D2D", relief="flat", bd=2)
        question_frame.pack(fill=tk.X, pady=(0, 20))

        question_label = tk.Label(
            question_frame,
            text="Enter Your Physics Question",
            font=("Helvetica", 16, "bold"),
            bg="#2D2D2D",
            fg="#FFFFFF",
            pady=10
        )
        question_label.pack(padx=20)

        # Question entry with modern styling
        self.question_entry = tk.Text(
            question_frame,
            height=4,
            font=("Consolas", 12),
            wrap=tk.WORD,
            bg="#363636",
            fg="#FFFFFF",
            insertbackground="#FFFFFF",  # Cursor color
            relief="flat",
            padx=10,
            pady=10
        )
        self.question_entry.pack(fill=tk.X, padx=20, pady=(0, 20))

        # Buttons frame
        button_frame = tk.Frame(content_frame, bg="#1E1E1E")
        button_frame.pack(fill=tk.X, pady=20)

        # Modern styled buttons
        submit_button = tk.Button(
            button_frame,
            text="Get Answer",
            command=self.get_ai_response,
            font=("Helvetica", 12, "bold"),
            bg="#00AA00",  # Softer green
            fg="#FFFFFF",
            relief="flat",
            padx=30,
            pady=15,
            cursor="hand2"
        )
        submit_button.pack(side=tk.LEFT, padx=(20, 10))

        new_question_button = tk.Button(
            button_frame,
            text="New Question",
            command=self.clear_screen,
            font=("Helvetica", 12, "bold"),
            bg="#404040",
            fg="#FFFFFF",
            relief="flat",
            padx=30,
            pady=15,
            cursor="hand2"
        )
        new_question_button.pack(side=tk.LEFT, padx=10)

        # Response section
        response_frame = tk.Frame(content_frame, bg="#2D2D2D", relief="flat", bd=2)
        response_frame.pack(fill=tk.BOTH, expand=True, pady=(20, 0))

        response_label = tk.Label(
            response_frame,
            text="AI Response",
            font=("Helvetica", 16, "bold"),
            bg="#2D2D2D",
            fg="#FFFFFF",
            pady=10
        )
        response_label.pack(padx=20)

        # Response text area with modern styling
        self.response_text = tk.Text(
            response_frame,
            height=12,
            font=("Consolas", 12),
            wrap=tk.WORD,
            bg="#363636",
            fg="#FFFFFF",
            relief="flat",
            padx=10,
            pady=10,
            state='disabled'
        )
        self.response_text.pack(fill=tk.BOTH, expand=True, padx=20, pady=(0, 20))

        # Add hover effects
        def on_enter(e):
            if e.widget['text'] == "Get Answer":
                e.widget['background'] = '#00CC00'
            else:
                e.widget['background'] = '#505050'

        def on_leave(e):
            if e.widget['text'] == "Get Answer":
                e.widget['background'] = '#00AA00'
            else:
                e.widget['background'] = '#404040'

        # Bind hover events
        for button in [submit_button, new_question_button]:
            button.bind("<Enter>", on_enter)
            button.bind("<Leave>", on_leave)

    def get_ai_response(self):
        question = self.question_entry.get("1.0", tk.END).strip()
        
        if not question:
            self.update_response("Please enter a question.")
            return

        self.update_response("Getting response...")
        self.root.update()

        try:
            response = self.ai_assistant.get_response(question)
            self.update_response(response)
        except Exception as e:
            self.update_response(f"Error: {str(e)}")

    def update_response(self, text):
        self.response_text.config(state='normal')
        self.response_text.delete("1.0", tk.END)
        self.response_text.insert("1.0", text)
        self.response_text.config(state='disabled')

    def clear_screen(self):
        self.question_entry.delete("1.0", tk.END)
        self.update_response("Ready for your question...")
        self.question_entry.focus()

    def run(self):
        if not isinstance(self.root, tk.Tk):
            self.root.mainloop()

def main():
    app = PhysicsAIGUI()
    app.run()

if __name__ == "__main__":
    main()
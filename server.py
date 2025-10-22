from flask import Flask, request, render_template
import subprocess
import os

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def home():
    output = None
    if request.method == "POST":
        user_input = request.form["user_input"]

        # Figure out the path to your compiled C++ program
        exe_path = "./program"
        if os.name == "nt":  # Windows
            exe_path = "program.exe"

        # Run your C++ program with the provided input
        result = subprocess.run(
            [exe_path],
            input=user_input,
            text=True,
            capture_output=True
        )

        output = result.stdout or result.stderr

    return render_template("index.html", output=output)

if __name__ == "__main__":
    app.run(debug=True)

from flask import Flask, request, render_template, session
import subprocess
import os

app = Flask(__name__)
app.secret_key = "wowAkey"

@app.route("/", methods=["GET", "POST"])
def home():
    output = ""
    traversal = session.get("traversal", "breadth")  

    if request.method == "POST":
        action = request.form.get("action")
        user_input = request.form.get("user_input", "")

        # path to c++
        exe_path = "./program"
        if os.name == "nt":  # Windows
            exe_path = "program.exe"

        # run c++
        if action == "depth":
            traversal = "depth"
            session["traversal"] = traversal
        elif action == "breadth":
            traversal = "breadth"
            session["traversal"] = traversal
        elif action == "search" and user_input:
            result = subprocess.run(
                [exe_path, user_input, traversal],
                text=True,
                capture_output=True
            )
            output = result.stdout or result.stderr

    return render_template("index.html", output=output, traversal=traversal)

if __name__ == "__main__":
    app.run(debug=True)

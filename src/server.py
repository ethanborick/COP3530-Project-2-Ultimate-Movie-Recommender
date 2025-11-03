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
        exe_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "program")
        if os.name == "nt":
            exe_path += ".exe"
        print("Executable exists:", os.path.exists(exe_path))
        print("Exe path:", exe_path)

        # run c++
        if action == "depth":
            traversal = "depth"
            session["traversal"] = traversal
        elif action == "breadth":
            traversal = "breadth"
            session["traversal"] = traversal
        elif action == "search" and user_input:
            print("Executable exists:", os.path.exists(exe_path))
            print("Exe path:", exe_path)
            result = subprocess.run(
                [exe_path, user_input, traversal],
                text=True,
                capture_output=True
            )
            output = result.stdout or result.stderr

    return render_template("index.html", output=output, traversal=traversal)

if __name__ == "__main__":
    app.run(debug=True)

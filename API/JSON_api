from flask import Flask, request, jsonify, render_template_string, make_response
import json
from flask_cors import CORS

app = Flask(__name__)
CORS(app)


data = {
    "Create new JSON": "http://127.0.0.1/new_json",
    "key1": "string1",
    "key2": 100,
    "key3": ["a", "b", "c"]
}


@app.route('/', methods=['GET', 'POST'])
def get_data():
    global data
    if request.method == 'POST' and 'new_json' in request.form:
        try:
            data = request.form['new_json']
            new_json = json.loads(data)
            return jsonify(new_json)
        except json.JSONDecodeError:
            return jsonify({"ERROR": "Invalid JSON!    Create new JSON: http://127.0.0.1/new_json"}), 400
    else:
        return jsonify(data)


@app.route('/new_json', methods=['GET'])
def new_json():
    host_url = request.host_url
    return render_template_string("""
    <style>
      body {
        background-color: #f0f0f0;
        font-family: Arial, sans-serif;
        color: navy;
      }
    </style>
    <br /><br />
    <div style="text-align: center">
      <h3>- - Create new JSON - -</h3>
      <br />
      <div style="font-size: 14px">
        <p>Example:</p>
        <p>{"name_1":"string","name_2":2,"name_3":["ABC", 123]}</p>
      </div>
      <br />
      <form action="/" method="POST">
        <textarea
          name="new_json"
          style="height: 200px; width: 400px"
        ></textarea>
        <br /><br />
        <input
          type="submit"
          value="CREATE"
          style="width: 400px; height: 30px; cursor: pointer"
        />
      </form>
      <br /><br />
    </div>
    """)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)

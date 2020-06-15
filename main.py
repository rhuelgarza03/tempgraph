from flask import Flask, render_template, url_for, flash, request, jsonify
from time import sleep
import serial
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime

import json

app = Flask(__name__)

app.config["SECRET_KEY"] = "yeah this isn't really secret"
app.config['SQLALCHEMY_DATABASE_URI'] = "sqlite:///site.db"
db = SQLAlchemy(app)

currentTime = datetime.now()


class Log(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    temp = db.Column(db.String(20), nullable=False)
    #time = db.Column(db.DateTime, nullable=False, default=currentTime.strftime("%I:%M:%S:%p"))
    time = db.Column(db.String(20), nullable=False)

    # how each item will be displayed when called // Temp("my note", "4/13/2020")
    def __repr__(self):
        return f"Log('{self.temp}', '{self.time}')"


'''
# just kinda happens before the first request from the user, (ex: happens before the /home page loads)
@app.before_first_request
def serialSetup():
    global ser
    ser = serial.Serial('COM5', 9600, timeout=1)
    return
'''

@app.route("/test", methods=["GET", "POST"])
def test():
    if request.method == 'POST':
        #thing = request.data

        temp = request.json['temp']
        time = request.json['time']
        #print(thing)

        log = Log(temp=temp, time=time)
        db.session.add(log)
        db.session.commit()
        return 'huh'
    return 'no'



@app.route("/")
@app.route("/home")
def home():
    logs = Log.query.order_by(Log.time.desc()).all()
    #tdata = ser.readline()
    #final = tdata.decode('utf-8')
    #print(final)
    #return render_template("home.html", title="ok", data=final)
    return render_template("home.html", title="ok", logs=logs)

#app.run(host="0.0.0.0", port=80, debug=True, use_reloader=False)
app.run(host="0.0.0.0", port=80, debug=True)
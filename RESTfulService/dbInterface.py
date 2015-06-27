"""
Created by James

I'm still pretty new with python, but hopefully nothing is too broken.
This file will (hopefully) act as a conduit between the sql server, and the REST interface
"""
from __future__ import with_statement
import os
import mysql.connector
from flask import Flask, request, session, flash, g, redirect, url_for, abort, render_template


application = Flask(__name__)
application.debug = True
def connect_to_db():
    cnx = mysql.connector.connect(user ='testuser',
                              password ='test',
                              database ='ShyftWrk',
                              host = 'localhost',
                              port= 4454)
    return cnx

@application.before_first_request
def before_request():
    g.db = connect_to_db()

@application.route('/')
def show_names():
    cursor = g.db.cursor()
    query = 'select id, Name, Position from Employees'
    cursor.execute(query)
    returnstring = 'names    Position' + '\n'
    for row in cursor.fetchall():
        entries ={'name': row[1].decode('utf-8'), 'position': row[2].decode('utf-8')}
        returnstring+= entries['name'] + "     " + entries['position'] +' \n '
    print(returnstring)
    cursor.close()
    return "niggers"

@application.after_request
def after_request(response):
    g.db.close()
    return response



if __name__ == '__main__':
    application.run()
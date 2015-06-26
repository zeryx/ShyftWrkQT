"""
    this python module defines the interface between ShyftWrks mySQL db
    and the RESTful service.

    My python is pretty shakey comapred to my C++, but this shouldn't be TOO bad.
"""
from __future__ import with_statement
import os
from contextlib import closing
import random
import mysql.connector
from flask import flash, g, Flask, request, session, g, redirect, url_for, abort, \
    render_template

#configuration
DEBUG = True
SECRET_KEY = 'development key'
USERNAME = 'admin'
PASSWORD = 'default'


application = Flask(__name__)

@application.route('/')
def default():
    dbconnect = mysql.connector.connect(user='root',
                                passwd='test',
                                db='mysql',
                                host='127.0.0.1')
    cursor = dbconnect.cursor(buffered=True)
    cursor.execute("SHOW DATABASES")
    print(cursor.column_names)
    cursor.close()
    dbconnect.close()
    return

@application.route('/close')
def close_connection():
    application

# @application.route('/add', methods=['POST'])
# def add_entry():
#     if not session.get('logged_in'):
#         abort(401)
#     cur = g.db.cursor()
#     cur.execute('insert into entries (title, text) values(%s,%s)',
#                 [request.form['title'].encode('utf-8'), request.form['text'].encode('utf-8')])
#     cur.close()
#     g.db.commit()
#
#     flash('New entry was successfully posted')
#     return redirect(url_for('show_entries'))
#

#
# @application.route('/logout')
# def logout():
#     session.pop('logged_in', None)
#     flash('You were logged out')
#     return redirect(url_for('show_entries'))

if __name__ == '__main__':
    application.run()
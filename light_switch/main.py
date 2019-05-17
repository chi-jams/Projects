#!/usr/bin/python3

from bottle import jinja2_view, Bottle, route, run
from jinja2 import Template

@route('/')
@jinja2_view('index.html', template_lookup=['templates'])
def index():
    return {}

run(host='localhost', port=8080)

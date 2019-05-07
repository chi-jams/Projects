#!/usr/bin/python3

from bottle import request, run, post
import json

@post('/')
def okay():
    for k, v in request.forms.decode().items():
        print("{}: {}".format(k, v))
    return ''

run(host='localhost', port=8080)

# pylint: disable-all

from importlib import import_module


def import_class(name):
    module_path = name.split('.')
    module = import_module(module_path[0])

    return module


cool_class = import_module('multiple_imports.a.a')

thing = cool_class.a(3)

thing.show_cool_var()
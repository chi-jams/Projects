#pylint: disable-all

from importlib import import_module


def my_import(name):
    components = name.split('.')
    mod = import_module(components[0])
    for comp in components[1:]:
        mod = getattr(mod, comp)
    return mod

thingy = my_import('b.b')

print(thingy)

a = thingy(3)

print('ver:', a.cool_var)
a.show_cool_var()
a.change_cool_var()
a.show_cool_var()
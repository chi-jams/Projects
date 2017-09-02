#pylint: disable-all

import os

modules = [thing.replace('.py', '') for thing in os.listdir(
    __file__[:__file__.rfind('\\')]) if '.py' in thing]
if '__init__' in modules: modules.remove('__init__')

print(modules)
__all__ = modules
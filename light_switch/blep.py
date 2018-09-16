#!/usr/bin/python3

from phue import Bridge
import yaml

DEFAULT_CFG = "cfg.yaml"

if __name__ == "__main__":
    cfg = yaml.load(open(DEFAULT_CFG, 'r').read())

    print(cfg)

    b = Bridge(cfg['ip'])
    b.connect()

    room = b.get_group(cfg['group'])

    print(room)
    b.set_light([int(i) for i in room["lights"]], "on", True)

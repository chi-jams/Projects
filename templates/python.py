#!/usr/bin/python3

import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: {} <arg>".format(sys.argv[0]))
        sys.exit(-1)

    print("ohai")

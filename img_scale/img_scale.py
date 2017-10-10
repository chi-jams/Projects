#!/usr/bin/python3
import sys
import pyscreenshot as ImageGrab

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: ./img_scale.py <output_file>")
        exit(-1)
    ImageGrab.grab().save(sys.argv[1])

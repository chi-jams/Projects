#!/usr/bin/python3
import sys
from PIL import Image

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: ./img_scale.py <input_file> <output_file>")
        exit(-1)
    Image.open(sys.argv[1]).save(sys.argv[2])

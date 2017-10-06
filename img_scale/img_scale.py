#!/usr/bin/python3
import sys
import png

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: ./img_scale.py <input_file> <output_file>")
        exit(-1)

    in_file = png.Reader(filename=sys.argv[0]) 
    img = in_file.read()
    in_file.close()

    png.Writer(sys.argv[2], img)

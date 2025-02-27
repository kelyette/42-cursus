#!/usr/bin/env python3
import sys
from PIL import Image, ImageOps
import numpy as np

def main():
    if len(sys.argv) != 5:
        print(f"Usage: {sys.argv[0]} <input file> <output file> <width> <height>")
        sys.exit(1)
    input_file = sys.argv[1]
    output_file = sys.argv[2]
    try:
        width = int(sys.argv[3])
        height = int(sys.argv[4])
    except ValueError:
        print("Width and height must be integers.")
        sys.exit(1)
    img = Image.open(input_file)
    if (img.mode == "I;16"):
        arr = np.array(img, dtype=np.uint16)
        arr = (arr / 256).astype(np.uint8)
        img = Image.fromarray(arr, mode="L")
    else:
        img = img.convert('L')
    img = img.resize((width, height))
    with open(output_file, "w") as f:
        for y in range(height):
            row = []
            for x in range(width):
                pixel_value = img.getpixel((x, y))
                z_value = int(pixel_value)
                row.append(str(z_value))
            # Write the row to the file with space-separated values
            f.write(" ".join(row) + "\n")

if __name__ == "__main__":
    main()

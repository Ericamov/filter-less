# CS50 – Filter

## Description

This program applies basic image filters to 24-bit BMP files. It supports grayscale conversion, sepia tone, horizontal reflection, and box blur effects.

## How it works

The program:

- Reads a BMP image and applies a selected filter
- Processes each pixel according to the chosen transformation
- Supports grayscale, sepia, reflection, and blur effects
- Outputs a new image with the filter applied

## Usage

```
make filter
./filter -g image.bmp grayscale.bmp
./filter -s image.bmp sepia.bmp
./filter -r image.bmp reflected.bmp
./filter -b image.bmp blurred.bmp
```

## Example

```
./filter -g courtyard.bmp grayscale.bmp
```

This converts courtyard.bmp to grayscale and saves the result as grayscale.bmp.

## Concepts

- Image processing
- RGB color representation
- Two-dimensional arrays
- Pointers
- Pixel transformations

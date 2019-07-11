# Mandebrot generator

A mandelbrot image generator written in C++.

[Mandelbrot set wikipedia](https://en.wikipedia.org/wiki/Mandelbrot_set)

![Mandelbrot-big](/images/mandelbrot-big2048.png)

![Mandelbrot-1](/images/mandelbrot-1-2048.png)

![Mandelbrot-2](/images/mandelbrot-2-2048.png)

![Mandelbrot-3](/images/mandelbrot-3-2048.png)

![Mandelbrot-6](/images/mandelbrot-6-2048.png)

### How to build

Make sure you have cmake installad and a compiler that supports at least C++11

Checkout this repo then run in the root folder
```
cmake
make
```

Then to execute the program you run:

``` ./mandelbrot-gen -w640 -h480 ```

**Syntax**:

Command | Type | required | description | example
--------|------|----------|-------------|--------
-h      | int  | yes      |img height   | -h640
-w      | int  | yes      |img width    | -h480
-f      | int  | no       |img width    | -fmyImage.png

Program only supports `PNG` image format and if no filename is supplied the default name is `default.png` (suprise!)

### Color smoothing
THe color is selected by the iteration count (default is set to 80) and then the colors are smoothed using the "renormalized" iteration count. You can read about it here [Smooth Shading for the Mandelbrot Exterior](https://linas.org/art-gallery/escape/smooth.html).

#### Todos:

* Make iteration count adjustable
* be able to deactivate smoothing
* ability to only render certain portions of the mandelbrot set

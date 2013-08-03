TessendorfOceanMax
==================

Tessendorf's FFT ocean simulation for 3ds Max.
Visual Studio 2010 is required to build plug-ins using the Autodesk 3ds Max 2014 SDK.
However, you can also use a later version of Visual Studio as long as VS 2010 is installed to provide access to the build tools.

By default, the project compiles into `TessendorfOcean.dlo`, a 3ds Max object plug-in.
The plug-in will automatically be placed into `...\3ds Max 2014\plugins` once compiled.
The default parameters will produce a calm, rippling ocean surface; increase the speed to produce more turbulent waves.

Features:
* Animatable by keying the Time parameter
* Customizable scale, amplitude, speed, direction, choppiness
* Resolution can be specified through length and width segments, as in a normal plane
* Automatically generates UV texture coordinates

For more information on how Tessendorf's equations are used to generate waves, see [Jerry Tessendorf's course notes](http://people.clemson.edu/~jtessen/papers_files/coursenotes2002.pdf).
The comments in `tessendorf.cpp` will direct you to the corresponding equation in the course notes.

This project minimally uses Autodesk sample code.

This project uses the [FFTW library](http://fftw.org), which is licensed under the GPL. Please see `LICENSE` for more information.

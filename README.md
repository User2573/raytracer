# Raytracer
## (incomplete)
---
# Description
The compiled program takes a filename and outputs a PPM image. If you want to modify the scene, modify the code in main.cpp.
# File contents
## [`image/`](/image/)
* `fcolor.hpp`       : contains the `FColor` class, which is used for writing RGB colors to a PPM file.
* `image.hpp`        : contains the `Image` class.
## [`math/`](/math/)
* `vector.hpp`       : contains the `Vector` class (with aliases `Point` and `Color`).
* `ray.hpp`          : contains the `Ray` class.
* `random.hpp`       : contains the `random01` functor and the functions `randomVectorInSphere` / `randomUnitVector`.
## [`camera/`](/camera/)
* `icamera.hpp`      : contains the `ICamera` interface class. (do not instantiate)
* `perspective.hpp`  : contains the `PerspectiveCamera` class.
* `orthographic.hpp` : contains the `OrthographicCamera` class.
## material/
## object/
# Reference
I'll be using https://raytracing.github.io/ as a reference project to build atop.

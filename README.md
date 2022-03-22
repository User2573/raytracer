# Raytracer
## (incomplete)
---
# Description
* The compiled program outputs a PNG image, through the use of ffmpeg. If you don't have ffmpeg available in the current path, change the code in main.cpp to output a PPM image.
* If you want to modify the scene, modify the code in main.cpp. Sorry.
# File contents
## [`image/`](/image/)
* `fcolor.hpp`       : `FColor` class, which is used for writing RGB colors to a PPM file.
* `image.hpp`        : `Image` class.
## [`math/`](/math/)
* `vector.hpp`       : `Vector` class (with aliases `Point` and `Color`).
* `ray.hpp`          : `Ray` class.
* `random.hpp`       : `random01` functor and some functions for random vector generation.
## [`camera/`](/camera/)
* `camera.hpp`       : `Camera` abstract class, for generating a `Ray` from two coordinates.
* `perspective.hpp`  : `PerspectiveCamera : Camera` class.
* `orthographic.hpp` : `OrthographicCamera : Camera` class.
## [`hittable/`](/hittable/)
* `hitrecord.hpp`    : `HitRecord` class.
* `hittable.hpp`     : `Hittable` abstract class, for all things a `Ray` can intersect.
* `sphere.hpp`       : `Sphere : Hittable` class.
## [`texture/`](/texture/) TODO
* `texture.hpp`      : `Texture` abstract class, for representing a surface's (possibly varying) color.
* `constant.hpp`     : `ConstantTexture : Texture` class.
## [`material/`](/material/) TODO
* `material.hpp`     : `Material` abstract class, for scattering `Ray`s and getting emitted light.
# Reference
https://raytracing.github.io/, occasionally https://pbr-book.org/

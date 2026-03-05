# RayTracer

A 3D ray tracer written in C++20, built as part of the **B-OOP-400** Epitech project.  
It renders scenes defined in `.cfg` configuration files and outputs the result both in an SFML window and as a `.ppm` image file.

## Features

- **Primitives**: Sphere, Plane, Cylinder, Cone, Cube
- **Lighting**: Ambient and Directional lights (with shadow casting)
- **Materials**: Flat color with diffuse shading
- **Scene parser**: `.cfg` files via `libconfig++`
- **Live rendering**: optional progressive display during render
- **PPM export**: rendered image automatically saved as a `.ppm` file

## Dependencies

| Library | Purpose |
|---------|---------|
| [SFML](https://www.sfml-dev.org/) | Window display & image rendering |
| [libconfig++](https://hyperrealm.github.io/libconfig/) | Scene file parsing |

Install on Debian/Ubuntu:
```sh
sudo apt install libsfml-dev libconfig++-dev
```

## Build

```sh
make        # standard build
make debug  # build with debug symbols (-g3 -O0)
make re     # clean rebuild
make fclean # remove binary and .ppm output
```

## Usage

```sh
./raytracer <SCENE_FILE> [--liverender]
```

| Argument | Description |
|----------|-------------|
| `<SCENE_FILE>` | Path to a `.cfg` scene configuration file |
| `--liverender` | Display rendering progress live in the window |

**Example:**
```sh
./raytracer scenes/basic_scene.cfg --liverender
```

The output image is automatically saved as `<scene_name>.ppm` in the current directory. Press **ESC** to close the window once rendering is complete.

## Scene File Format

Scene files use the `libconfig++` syntax. Here is a minimal example:

```cfg
camera = {
  resolution = { width = 1280; height = 720 };
  position   = { x = 0.0; y = 0.0; z = 0.0 };
  rotation   = { x = 0.0; y = 0.0; z = 0.0 };
  fieldOfView = 72.0;
};

primitives = {
  spheres = (
    { x = 0.0; y = 0.0; z = -5.0; r = 1.0; color = { r = 255; g = 0; b = 0 } }
  );
  planes = (
    { axis = "Y"; position = -1.0; color = { r = 150; g = 150; b = 150 } }
  );
};

lights = {
  ambient = 0.2;
  diffuse = 0.8;
  directional = (
    { x = 1.0; y = -1.0; z = -1.0 }
  );
};
```

Ready-to-use scenes are available in the `scenes/` directory.

## Project Structure

```
.
├── main.cpp               # Entry point
├── RayTracer.hpp          # Ray & Camera classes
├── HitRecord.hpp          # Ray–object intersection record
├── Rectangle3D.hpp        # Camera viewport helper
├── ppmConverter.hpp       # PPM export utility
├── math/
│   ├── Vector3D.hpp
│   ├── Point3D.hpp
│   └── Matrix4x4.hpp
├── objects/               # Shape primitives (IShape interface)
│   ├── Sphere.hpp
│   ├── Plane.hpp
│   ├── Cylinder.hpp
│   ├── Cone.hpp
│   └── Cube.hpp
├── lights/                # Light types (ILight interface)
│   ├── AmbientLight.hpp
│   └── DirectionalLight.hpp
├── materials/             # Material system (IMaterial interface)
│   ├── Color3.hpp
│   └── FlatColor.hpp
├── scene/
│   ├── Scene.hpp/cpp      # Scene graph & ray tracing loop
│   └── SceneParser.hpp/cpp# libconfig++ scene loader
└── scenes/                # Example .cfg scene files
```

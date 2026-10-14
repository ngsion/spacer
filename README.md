# Spacer: Constraint-Based Microstructure Layout Design for Electrowetting Displays

**C++ research code for algorithm-assisted design and pattern generation of non-uniform microstructure arrays.**

## Overview

This repository contains research-oriented C++ programs developed for the computational design of non-uniform microstructure arrays in electrowetting display (EWD) devices.

In electrowetting displays, the spatial arrangement of microstructures influences the motion and confinement of colored oil within individual pixels. Notch structures can guide directional oil retraction, while spacer structures provide mechanical support. Inappropriate arrangements may lead to unwanted interactions between neighboring pixels, compromising electro-optical performance.

This project addresses these design constraints through **algorithm-assisted microstructure layout generation**, combining geometric rules, neighboring-pixel compatibility checks, backtracking search, and pattern visualisation.

The resulting computational layouts support the design and subsequent fabrication of electrowetting microstructure arrays.

## Research Objectives

The main objectives are to:

- Translate geometric and neighboring-pixel design requirements into computational constraints.
- Generate candidate non-uniform notch and spacer arrangements that satisfy predefined compatibility rules.
- Explore spatial configurations under different spacing and boundary conditions.
- Convert computational results into matrix data and bitmap patterns for subsequent structural design.

## Computational Approach

The codebase implements several complementary computational procedures.

### 1. Constraint-Based Pixel Representation

Local pixel configurations are represented using discrete states that describe microstructure arrangements around neighboring pixel positions.

The software enumerates candidate configurations, evaluates their validity, and constructs compatibility relationships between adjacent units.

### 2. Backtracking and Layout Search

Backtracking-based search procedures are used to construct larger arrays from compatible local configurations.

Candidate placements are evaluated against neighboring-pixel constraints, allowing invalid arrangements to be rejected during the search process.

Additional distance-based heuristics are explored for distributing spacer positions while considering minimum separation and boundary offsets.

### 3. Array Assembly and Pattern Generation

Compatible arrangements can be combined or extended to produce larger spatial layouts.

The resulting configurations are exported as numerical matrices and bitmap images for visual inspection and subsequent pattern design.

Additional utilities support spatial pattern generation for multilayer cyan–magenta–yellow (CMY) electrowetting structures.

## Code Structure

| Files | Main Function |
|---|---|
| `Pixel.h`, `PixelHelper.h` | Pixel-state representation, configuration validation, and neighboring-pixel compatibility |
| `Calculate.cpp`, `Ca1.cpp`, `Cal11.cpp`, `Cal22.cpp` | Constraint-based layout search and backtracking procedures |
| `dfs.cpp` | Distance-based spacer placement search |
| `Merge.cpp`, `Merge22.cpp`, `Combine.cpp` | Combination and extension of computed layouts |
| `PlotBmp.cpp`, `PlotPatterns.cpp`, `PlotCircle.cpp` | Bitmap visualisation and spatial pattern generation |
| `Screen.h`, `Point.h`, `Utility.h` | Supporting data structures, matrix operations, and utilities |

## Usage

### Requirements

- A C++ compiler, such as GCC or Clang
- A POSIX-compatible development environment for programs using `<unistd.h>`
- Standard C/C++ libraries

The repository contains several independent research programs with separate `main()` functions. They should be compiled individually rather than linked into a single executable.

For example, the bitmap pattern generator can be built using:

```bash
g++ -std=gnu++14 -O2 PlotPatterns.cpp -o plot_patterns
./plot_patterns
```

This program is intended to generate bitmap visualisations of predefined spatial patterns.

Other computational programs may require configuration of array dimensions, input filenames, output directories, and search parameters in the source code.

**Note:** This repository preserves research-stage implementations rather than a fully packaged software application. The complete computational workflow may require local configuration, intermediate data files, and further validation.

## Research Relevance

This project demonstrates an approach to connecting **physical device-design requirements with computational constraint solving and automated pattern generation**.

The research combines experimental considerations in electrowetting devices with C++ programming, discrete-state modelling, algorithmic search, and structured output generation.

The computational work contributed to research on non-uniform microstructure arrangements intended to improve liquid confinement and reduce undesired interactions between neighboring electrowetting pixels.

## License

This repository is distributed under the **BSD 3-Clause License**. See [LICENSE](LICENSE) for details.

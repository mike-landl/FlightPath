# Flight Path

[![Build](https://github.com/mike-landl/FlightPath/actions/workflows/build.yml/badge.svg)](https://github.com/mike-landl/FlightPath/actions/workflows/build.yml)
[![Tests](https://github.com/mike-landl/FlightPath/actions/workflows/tests.yml/badge.svg)](https://github.com/mike-landl/FlightPath/actions/workflows/tests.yml)
[![codecov](https://codecov.io/gh/mike-landl/FlightPath/graph/badge.svg?token=VZGEK5J99D)](https://codecov.io/gh/mike-landl/FlightPath)
[![C++23 Standard](https://img.shields.io/badge/Standard-C++23-yellow.svg)](https://isocpp.org/std/the-standard)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This project processes a datalogger file from a flight simulator and reconstructs the flight path using only data from the onboard **inertial measurement unit (IMU)**.
(i.e. body-fixed linear acceleration and angular velocity)

The output is a **`.kml` file** (stored in the `data/` folder) that can be opened in **Google Earth** to visualize the reconstructed flight path alongside the original.

For example:
![Example](Example.png)

## Notes
- This repository primarily serves as a sandbox for experimenting with GitHub workflows, with a focus on automated testing, test coverage, the release process, and GitHub Pages.
- This codebase makes use of **trailing return types**, just because I wanted to try them out.

## Features
- ✅ Unit Testing\
Uses Catch2 and CTest for unit testing.

- 🖥️ Cross-Platform Support\
Supports both windows and linux environments.

- 🐳 Docker Support\
Dockerized environment for dependency management and easier setup.

- 🔄 Continuous Integration\
Integrated with GitHub Actions for automatic testing, test coverage, build verification and automated releases.

- 📚 Full Documentation\
Generated with Doxygen. Available for download under the Releases section or can be compiled locally.

- 🌍 Google Earth Integration\
Outputs .kml files for visualization in Google Earth.

---

## Quickstart

Begin by cloning the repository and navigating into its directory:
```sh
git clone https://github.com/mike-landl/FlightPath.git
cd FlightPath
```

You can then use the following commands to build the project, run tests (optionally generating a coverage report), and build the documentation.
Tested under Linux using `clang18` and `ninja`. Building coverage reports additionally requires `LLVM` and `lcov`.
Consider using the docker for dependency management and easier setup.

### Application
```sh
cmake --preset release-app
cmake --build --preset build-app --target FlightPath
./build/release-app/src/FlightPath
```
### Tests
```sh
cmake --preset tests-coverage
cmake --build --preset build-tests-coverage --target RunTests
(cd build/tests-coverage/tests && ctest)
```
### Tests with Coverage Report
```sh
cmake --preset tests-coverage
cmake --build --preset build-tests-coverage --target RunTests
(cd build/tests-coverage/tests && \
ctest && \
llvm-profdata merge -sparse default.profraw -o coverage.profdata && \
llvm-cov export RunTests --instr-profile=coverage.profdata --format=lcov --ignore-filename-regex='(tests|_deps)' > coverage.lcov
genhtml coverage.lcov --output-directory ../../../coverage/html)
firefox coverage/html/index.html
```
### Documentation
```sh
cmake --preset release-docs
doxygen doxygen/Doxyfile
firefox doxygen/html/index.html
```

---

## Usage

### Linux

#### Flight Path Reconstruction
1. Clone the repository:
```sh
git clone https://github.com/mike-landl/FlightPath.git
cd FlightPath
```
2. Configure the project with CMake
```sh
cmake --preset release-app
```
3. Build the project:
```sh
cmake --build --preset build-app --target FlightPath
```
4. Run the binary:
```sh
./build/release-app/src/FlightPath
```
5. The .kml output will be available in the data/ folder and can be imported into Google Earth.


#### Run Unit Tests
1. Configure the project with CMake
```sh
cmake --preset tests-coverage
```
2. Build the test target:
```sh
cmake --build --preset build-tests-coverage --target RunTests
```
3. Navigate to the test output directory:
```sh
cd build/tests-coverage/tests
```
4. Run the tests:
```sh
ctest
```

### Docker Support
This project includes a Docker setup for consistent builds and easy dependency management.

#### Prerequisites
Make sure Docker and Docker Compose are installed on your system.

- [Docker installation guide](https://docs.docker.com/engine/install/)

Add your user to the Docker group to avoid needing `sudo`:

```sh
sudo usermod -aG docker $USER
newgrp docker
```

#### Build & Run
1. Navigate to the `docker/` directory:
```sh
cd docker
```
2. Start the Docker container:
```sh
docker compose up --detach
```
3. Access the development container with bash:
```sh
docker compose exec flight_path bash
```
4. Inside the container, you can run the standard build and test commands as if you were on your local (host) system.

5. When finished, shut down the container:
```sh
docker compose down
```

### Build the Documentation
You can build the documentation locally if you prefer.

#### Prerequisites
Make sure you have **Doxygen** and **Graphviz** installed:
```sh
sudo apt-get install doxygen graphviz -y
```

#### Build Instructions
1. Clone the repository:
```sh
git clone https://github.com/mike-landl/FlightPath.git
cd FlightPath
```

2. Configure the project with CMake
This step downloads doxygen-awesome-css and generates the Doxyfile from the template (Doxyfile.in):
```sh
cmake --preset release-docs
```

3. Generate the documentation using Doxygen:
```sh
doxygen doxygen/Doxyfile
```

4. View the documentation
Open the generated index.html file in your browser. For example using firefox:
```sh
firefox doxygen/html/index.html
```

### Windows
#### Flight Path Reconstruction (Windows)
1. Clone the repository:
```sh
git clone https://github.com/mike-landl/FlightPath.git
```
2. Open the folder with Visual Studio (ensure CMake support is enabled).
3. Build and run from within Visual Studio.
4. Output is stored in the data/ folder and can be opened with Google Earth.

#### Run Unit Tests (Windows)
Select the RunTests target in Visual Studio and run it.

## Attribution
This project incorporates guidance from [docker-for-robotics](https://github.com/2b-t/docker-for-robotics), which is licensed under the [MIT License](https://github.com/2b-t/docker-for-robotics/blob/master/LICENSE).

## License
Distributed under the MIT License. See [License.txt](License.txt) for more information.

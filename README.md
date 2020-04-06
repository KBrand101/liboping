# liboping

## Building from source

### Create build directory and make files

```sh
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make && make install
```

Note: You can choose another build type by replacing `Release` with either
- `Debug` for debug symbols and assertion checks
- `RelWithDebInfo` (release with debug info)
- `MinSizeRel` (minimum size release).

## Run Tests

To run the test executable successfully you have to options:
1. Execute as root user (not recommended)
2. Add capabilities to the executable

### Why add capabilities?
By default, linux requires root privileges to open a raw socket. Since the library and therefore the test program is using those internally you either need to execute the program as root or expand its capabilities to allow it to create raw sockets.

### How to add capabilites?
You can add the capability to read and write raw sockets by running the following command in terminal:
```sh
sudo setcap cap_net_raw=eip ping-spectator
```
To check the capabilities you need to run:
```sh
sudo getcap ping-specator
```
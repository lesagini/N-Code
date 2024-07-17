# N-Code
A simple program to decode NMEA sentences. The sentences are logged on a text file 

### Prerequisites 
1. cmake
    [Install](https://cmake.org/download/)
2. GPS source file [`<filename>.txt`](https://github.com/lesagini/N-Code/blob/main/data/jogging_path.txt)


## Build

To build and run the program
```
1. cmake -B build
2. cmake --build build --target N-Code
```
1. Windows:
    ```
    .\Debug\N-Code [options]
    ```
2. Linux:
    ```
    ./N-Code [options]
    ```
    example `` .\Debug\N-Code data/jogging_path.txt``


##### .TXT file format
The data in the .txt file should follow a certain format and iclude line breaks for different entries. 

| Type    | Parameters        |
|-----------|-----------------|
| $<'type'> | x,x,x,x,x,x,x,x,|

###### Example:
> $GPRMC,060000.00,A,0126.8000,S,03648.5000,E,2.0,45.0,080724,,E*76

> It should begin with a `$` sign

###
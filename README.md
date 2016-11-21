# bmpify

*Turn any file into a 16-bit bitmap image.*

## Usage

A Windows `.exe` is available from the releases [here](../../releases/).

Use the `Makefile` for other systems.

```
Usage: ./bmpify input-file [output-file]

  input-file        file used to generate the bitmap image
  output-file       optional filename for the bitmap image
                    default file if none specified is "output.bmp"
```

**Alternatively on Windows you can just drag the input file onto `bmpify.exe`.**

Here's what the `bmpify` ELF looks like as a bitmap image:

`./bmpify bmpify example.bmp`

![bmpify example](example.png "bmpify example")

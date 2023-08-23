
# Recover

A program that recovers JPEGs from a forensic image, per the below.
```
$ ./recover card.raw
```

## Background

A program that iterates over a forensic image file, looking for JPEGs’ signatures. Each time you find a signature, you can open a new file for writing and start filling that file with bytes from the forensic image file, closing that file only once you encounter another signature. 

## Usage/Examples

```
$ ./recover
Usage: ./recover IMAGE
```
where IMAGE is the name of the forensic image. For example:

```
$ ./recover card.raw
```

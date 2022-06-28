[![ci](https://github.com/mjx-project/tenhou-wall-reproducer/actions/workflows/ci.yml/badge.svg)](https://github.com/mjx-project/tenhou-wall-reproducer/actions/workflows/ci.yml)
![pypi](https://img.shields.io/pypi/v/tenhou-wall-reproducer)

# Tenhou wall reproducer

Utility for reproducing the wall and dice information from the game seed in [Tenhou](https://tenhou.net/) platform.

## Install

**Tenhou wall reproducer** supports Python 3.7, 3.8, and 3.9 in Linux and Intel Mac environments.

```sh
$ pip install tenhou-wall-reproducer
```

## Usage

```py
>>> import tenhou_wall_reproducer
>>> tenhou_wall_reproducer.reproduce("""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""", 1)
[([124, 122, 37, 27, 80, 127, 125, 87, 104, 67, 115, 95, 8, 57, 92, 130, 69, 118, 20, 128, 35, 6, 123, 56, 103, 96, 55, 85, 109, 88, 32, 63, 26, 117, 16, 17, 82, 47, 68, 23, 9, 25, 65, 5, 39, 94, 76, 58, 97, 36, 14, 99, 111, 7, 133, 113, 31, 100, 131, 70, 28, 46, 30, 60, 79, 41, 74, 116, 75, 93, 105, 49, 91, 135, 114, 42, 45, 132, 21, 119, 18, 24, 129, 51, 121, 3, 81, 40, 29, 13, 34, 19, 86, 78, 53, 64, 50, 71, 120, 83, 66, 84, 126, 4, 12, 10, 101, 102, 22, 112, 15, 48, 134, 77, 0, 11, 108, 98, 61, 1, 107, 110, 59, 90, 2, 44, 54, 38, 89, 33, 62, 43, 73, 106, 72, 52], [4, 5])]
```

Data is collected from http://tenhou.net/0/?log=2017020100gm-00e1-0000-17d39cdb.

## Build from source

```sh
$ make install
$ python3 tests/test.py
```

## License

MIT

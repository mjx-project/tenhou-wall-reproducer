install: src/tenhou_wall_reproducer.cpp src/mt19937ar.c submodules
	which python3
	python3 -m pip install .

submodules:
	git submodule update --init

src/mt19937ar.c:
	cd src && curl -OL http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/CODES/mt19937ar.sep.tgz && tar -xzvf mt19937ar.sep.tgz && rm -rf mt19937ar.sep.tgz

venv:
	which python3
	python3 -m venv venv

clean:
	rm -rf venv
	rm -rf src/mt*
	rm -rf src/readme-mt.txt
	rm -rf src/openssl-cmake
	rm -rf src/pybind11
	rm -rf build
	rm -rf cmake-build-debug

.PHONY: clean install submodules

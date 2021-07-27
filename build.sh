#! /usr/bin/env bash

set -e -u -o pipefail -v

cd "$(dirname "$BASH_SOURCE")"

cargo build --release

cbindgen --lang c > blake3_bindings.h

gcc test.c target/release/libexample.a -o test -O3 -Wall -pedantic -lpthread -ldl -lm

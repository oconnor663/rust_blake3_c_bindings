#! /usr/bin/env bash

set -e -u -o pipefail -v

cd "$(dirname "$BASH_SOURCE")"

cargo build --target x86_64-unknown-linux-musl --release

cbindgen --lang c > blake3_bindings.h

musl-gcc -O3 -Wall -pedantic -o test test.c target/x86_64-unknown-linux-musl/release/libscratch.a

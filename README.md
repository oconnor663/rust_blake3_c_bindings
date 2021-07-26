A proof-of-concept of generating C bindings for the Rust BLAKE3 implementation.

Dependencies:

- GCC
- Rust and Cargo
- `rustup target add x86_64-unknown-linux-musl`
- `cargo install cbindgen`

To build:

```
./build.sh
```

To run:

```
./test
```

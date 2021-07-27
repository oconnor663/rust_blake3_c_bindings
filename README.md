A proof-of-concept of generating C bindings for the Rust BLAKE3 implementation.

Dependencies:

- `musl-gcc`
- Rust and Cargo
- `rustup target add x86_64-unknown-linux-musl`
- `cargo install cbindgen`

To build:

```
./build.sh
```

To run:

```
./test <FILE>
```

This will mmap the target file and then hash it with the Rust multithreaded
implementation.

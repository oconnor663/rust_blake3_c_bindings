#[allow(non_camel_case_types)]
pub struct blake3_hasher(blake3::Hasher);

#[no_mangle]
pub extern "C" fn blake3_hasher_new() -> *mut blake3_hasher {
    let box_hasher = Box::new(blake3_hasher(blake3::Hasher::new()));
    Box::into_raw(box_hasher)
}

#[no_mangle]
pub extern "C" fn blake3_hasher_update(hasher: *mut blake3_hasher, buf: *const u8, len: usize) {
    unsafe {
        let hasher = &mut *(hasher as *mut blake3_hasher);
        let slice = std::slice::from_raw_parts(buf, len);
        hasher.0.update_rayon(slice);
    }
}

#[no_mangle]
pub extern "C" fn blake3_hasher_finalize(hasher: *const blake3_hasher, out: *mut [u8; 32]) {
    unsafe {
        let hasher = &*(hasher as *const blake3_hasher);
        *out = hasher.0.finalize().into();
    }
}

#[no_mangle]
pub extern "C" fn blake3_hasher_free(hasher: *mut blake3_hasher) {
    unsafe {
        Box::from_raw(hasher as *mut blake3_hasher);
    }
}

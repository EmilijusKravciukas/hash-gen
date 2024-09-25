# hash-gen

## Hashing algorithm pseudo-code:

for(char in inputString) {
    hash = hash ^ (big_prime_number * char.bit) + (hash.bit_shift(5) + char.bit);
    hash.bit_rotate_left(15)
    hexHash = to_hex(hash.64bit_mask());
}

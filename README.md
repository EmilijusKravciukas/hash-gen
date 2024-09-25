# hash-gen

## Hashing algorithm pseudo-code:
```
for(char in inputString) {
    hash = hash ^ (big_prime_number * char.bit) + (hash.bit_shift(5) + char.bit);
    hash.bit_rotate_left(15);
    hexHash = to_hex(hash.64bit_mask());
}
```

## Testing results
Test files are available in the Testing branch.
### Test 1
Testing file A result
```
hash output: 360000189cca8000
```
Testing file B result
```
hash output: 34000018995e8000
```
### Test 2
Testing file A result
```
hash output: b2a16ec1e7118af8
```
Testing file B result
```
hash output: f0fbe652dfd8842
```
### Test 3
Testing file A result
```
hash output: 87c3fde5faa2c850
```
Testing file B result
```
hash output: 4e3c56a4ec09bcd7
```

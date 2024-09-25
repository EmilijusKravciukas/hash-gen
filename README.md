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
### Algorithm speed test (Horizontal - Lines hashed, Vertical - Time (Microseconds))
![image](https://github.com/user-attachments/assets/32c227f6-9519-4c10-8c20-d3fcae2df1bf)

### Test 4 (Collision testing)
Testing file result
```
collision count: 0
```
### Test 5 (Avalanche testing)
Testing file result
```
Bit comparison results: 
High Difference (>66%): 202
Medium Difference (<=66%): 99158
Low Difference (<=33%): 640

Hex comparison results:
High Difference (>66%): 99959
Medium Difference (<=66%): 41
Low Difference (<=33%): 0
```




# The Affine Cipher: Encryption Guide

## Table of Contents

1. Introduction to the Affine Cipher
2. Mathematical Foundation
3. The Two Keys: Understanding a and b
4. Detailed Code Analysis
5. Implementation Considerations
6. Examples and Usage

## 1. Introduction to the Affine Cipher

The Affine Cipher is a monoalphabetic substitution cipher that uses mathematical functions to convert plaintext to ciphertext. It's an extension of the shift cipher (like Caesar cipher) but adds multiplication to the encryption process, providing additional complexity in the encryption process.

## 2. Mathematical Foundation

### Encryption Formula:

```
E(x) = (ax + b) mod m
```

Where:

- x is the position of the plaintext letter (A=0, B=1, ..., Z=25)
- a and b are the cipher keys
- m is the size of the alphabet (26 for English alphabet)
- the result gives the position of the ciphertext letter

## 3. The Two Keys: Understanding a and b

### Key 'a':

- Must be coprime with the modulus (26 for letters)
- Valid values for m=26 are: 1, 3, 5, 7, 11, 15, 17, 19, 21, 23, 25
- This requirement ensures a unique mapping for each letter
- The multiplicative component makes the cipher more complex than a simple shift cipher

### Key 'b':

- Can be any integer
- Acts as a shift value
- Similar to the key in a Caesar cipher
- Range is typically 0-25 for the English alphabet

## 4. Detailed Code Analysis

### Core Functions

#### 1. Custom Modulo Function

```cpp
int mod(int a, int b) {
    return (a % b + b) % b;
}
```

This handles negative numbers correctly in modular arithmetic, ensuring proper wrapping around the alphabet.

#### 2. Encryption Function

```cpp
char cipherChar(char ch, int a, int b, int m) {
    if (isalpha(ch)) {
        bool upper = isupper(ch);
        ch = tolower(ch);
        int x = ch - 'a';
        int res = mod((a * x + b), m);
        char c = res + 'a';
        return upper ? toupper(c) : c;
    }

    if (isdigit(ch)) {
        int x = ch - '0';
        int res = mod((a * x + b), 10);
        return res + '0';
    }

    if (ispunct(ch) || ch == ' ') return ch;
    return ch;
}
```

This function:

- Preserves case of letters
- Converts letter to position (0-25)
- Applies affine transformation
- Converts position back to letter
- Handles non-alphabetic characters separately

#### 3. Key Validation

```cpp
bool checkKey(int a, int m) {
    int tmp_a = a;
    int tmp_m = m;
    while (tmp_m != 0) {
        int t = tmp_m;
        tmp_m = tmp_a % tmp_m;
        tmp_a = t;
    }
    return tmp_a == 1;
}
```

Implements the Euclidean algorithm to verify that 'a' and 'm' are coprime.

## 5. Implementation Considerations

### Extended Features

1. **Case Preservation**

   - Original case of letters is maintained
   - Implemented using boolean flags and case conversion functions

2. **Special Character Handling**

   - Punctuation marks remain unchanged
   - Spaces are preserved
   - Numbers are encrypted using modulo 10

3. **Input Validation**
   - Checks if key 'a' is valid
   - Provides helpful error messages
   - Prevents invalid encryptions

## 6. Examples and Usage

### Example 1: Basic Encryption

```
Message: "HELLO"
Key a: 5
Key b: 8
Encrypted: "RCLLA"
```

### Example 2: Mixed Case and Special Characters

```
Message: "Hello, World! 123"
Key a: 7
Key b: 3
Encrypted: "Zclla, Vaplx! 123"
```

### Program Usage Steps

1. Run the program
2. Enter the message to encrypt
3. Enter key 'a' (must be coprime with 26)
4. Enter key 'b' (any integer)
5. Program displays:
   - Original message
   - Encrypted message

## Conclusion

The Affine Cipher represents an interesting approach to encryption that combines multiplicative and additive transformations. Its implementation in modern programming languages allows for additional features like case preservation and special character handling while maintaining the mathematical integrity of the cipher. The use of two keys and modular arithmetic makes it a more sophisticated option compared to simpler substitution ciphers.

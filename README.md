### PRESENT-80
Implementation of PRESENT-80 in C.

### Testing
`make`
`./test_present`
Or
`make test`

### Usage
The files plaintext.txt, ciphertext.txt, and key.txt are used for encryption and decryption.

To encrypt a message, write it into plaintext.txt and add the key to key.txt. Then,
run `make encrypt` or `./cipher encrypt` to encrypt the message and store it in ciphertext.txt

To decrypt the ciphertext, use the same key and run `make decrypt` or `./cipher decrypt`

Currently the program is limited to strings less than 200 characters long.
The key should be 20 hexadecimal characters

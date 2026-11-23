### Decryption difficulty proof

* No key is rejected when decrypting a One-time pad (perfect secrecy).
  Complete brute-force gives you all the plaintext that can ever be written.
  And you can't know which was intended even though you have it.

* Step down from perfect secrecy by rolling the key instead of throwing it away.
  Still no key is rejected.
  You're forced to brute-force key transformations that would lead to making sense of the data.
  A cipher can have identifying properties and/or data in its plaintext.

* This proof describes a problem classifiable under NP (easily verifiable solutions)
  but not under P (easily discoverable solutions) therefore P != NP.

<sup>Nikolay Valentinovich Repnitskiy - February 21 2020</sup>

<br>

### Perfect secrecy proof

```text
                                                                  0 1 2 3 4 5 6 7 8 9

                                                              0   0 1 2 3 4 5 6 7 8 9
                                                              1   1 2 3 4 5 6 7 8 9 0
                                                              2   2 3 4 5 6 7 8 9 0 1
             key  523872537481693327099241416092              3   3 4 5 6 7 8 9 0 1 2
       plaintext  792342222222222000000945053749              4   4 5 6 7 8 9 0 1 2 3
      ciphertext  215114759603815327099186469731              5   5 6 7 8 9 0 1 2 3 4
                  ^                                           6   6 7 8 9 0 1 2 3 4 5
                                                              7   7 8 9 0 1 2 3 4 5 6
                                                              8   8 9 0 1 2 3 4 5 6 7
                                                              9   9 0 1 2 3 4 5 6 7 8
```

(5+7) mod 10 = 2. The full 10-symbol mod table on the right proves
the plaintext could be any of 10 digits (2 appears 10 times in the table).
No key is rejected when decrypting a One-time pad (perfect secrecy).
Complete brute-force gives you all the plaintext that can ever be written.
And you can't know which was intended even though you have it.
Only the key owners know that 7 was intended for that byte.
Extend the table to 255 for files.

<sup>Rediscovered by Nikolay Valentinovich Repnitskiy - ~December 2019</sup>

<br>

### The case for the infinity of primes who differ by evens 2+

Because a repeating wheel of primes leaves fixed prime gaps along an
infinite number line, and additional prime sieves periodically drift
into and out of alignment with those gaps, the gaps themselves should
never permanently vanish, suggesting why prime pairs separated by any
even gap would continue showing up.

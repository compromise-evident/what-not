### Decryption difficulty proof

* No key is rejected when decrypting a One-time pad (perfect secrecy).
  Complete brute-force cannot determine the usefulness of any key.
  You end up with all the plaintext that can ever be written.
  And there are no algebraic traps because no key is rejected.

* Step down from the One-time pad by rolling the key instead of
  throwing it away (the key becomes a rolling-code).
  You're forced to brute-force key transformations
  that would lead to making sense of the data.
  Yet still no key is rejected as there are no algebraic traps.
  And a cipher can have identifying data and/or properties
  in its plaintext so that keys can be rejected.
  This proof describes a problem classifiable under NP
  (easily verifiable solutions) but not under P
  (easily discoverable solutions) therefore P != NP.

<sup>Nikolay Valentinovich Repnitskiy - February 21 2020</sup>

<br>

### Perfect secrecy proof

```text
             key  523872537481693327099241416092                  0 1 2 3 4 5 6 7 8 9
       plaintext  792342222222222000000945053749
      ciphertext  215114759603815327099186469731              0   0 1 2 3 4 5 6 7 8 9
                  ^                                           1   1 2 3 4 5 6 7 8 9 0
                                                              2   2 3 4 5 6 7 8 9 0 1
                                                              3   3 4 5 6 7 8 9 0 1 2
(5+7) mod 10 = 2. The full 10-symbol mod table on the         4   4 5 6 7 8 9 0 1 2 3
right proves the plaintext could be any of  10 digits         5   5 6 7 8 9 0 1 2 3 4
(2 appears 10 times  in the table).  No guess-key  is         6   6 7 8 9 0 1 2 3 4 5
rejected; complete brute-force  cannot  determine the         7   7 8 9 0 1 2 3 4 5 6
usefulness of any key.  Only the key owners know that         8   8 9 0 1 2 3 4 5 6 7
7 was intended.  Extend the table  to 255 for  files.         9   9 0 1 2 3 4 5 6 7 8
```

<sup>Rediscovered by Nikolay Valentinovich Repnitskiy - ~December 2019</sup>

<br>

### The case for the infinity of primes who differ by evens 2+

Because a repeating wheel of primes leaves fixed prime gaps along an
infinite number line, and additional prime sieves periodically drift
into and out of alignment with those gaps, the gaps themselves should
never permanently vanish, suggesting why prime pairs separated by any
even gap would continue showing up.

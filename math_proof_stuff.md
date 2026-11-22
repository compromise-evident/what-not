### The case for the existence of decryption difficulty

* No key is rejected when decrypting a One-time pad (perfect secrecy).
  Complete brute-force cannot determine the usefulness of any key.
  You'll end up with all possible plaintext that can ever be written.

* Step down from the One-time pad by transforming the key instead of
  throwing it away. Because you're so close to perfect secrecy,
  it has to be difficult to find the key.

* Now some keys can be rejected. You're forced to brute-force
  key transformations that would lead to making sense of the data.
  You can determine the usefulness of keys.
  This proof describes a problem classifiable under NP
  (easily verifiable solutions) but not under P
  (easily discoverable solutions) therefore P != NP.

<br>

### The case for the infinity of primes who differ by evens 2+

Because a repeating wheel of primes leaves fixed prime gaps along an
infinite number line, and additional prime sieves periodically drift
into and out of alignment with those gaps, the gaps themselves should
never permanently vanish, suggesting why prime pairs separated by any
even gap would continue showing up.

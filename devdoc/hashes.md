# Hashes
There's no one-size-fits-all solution when it comes to hashes.
This framework use some hash functions for specific tasks like the following table show.
| Hash Function | Bits | Usage | Description |
|-|-|-|-|
| **CRC-32** | 32 | data integrity checks | used in many protocols and other software libraries |
| **CRC-32C** | 32 | data integrity checks | modified version used by some products and SSE4.2 integration |
| **xxh3-64-low** | 32 | small hashtables like caches | Non-cryptographic, well distributed, very fast |
| **rapidhash-nano** | 64 |1-48 bytes input, hash/symbol-tables | Non-cryptographic, well distributed, very fast |
| **rapidhash-micro** | 64 | 48-512 bytes input, hash/symbol-tables | Non-cryptographic, well distributed, very fast |
| **rapidhash** | 64 | 512+ bytes input, hash/symbol-tables, small size checksum | Non-cryptographic, well distributed, very fast |
| **xxh3-128** | 128 | databases, checksum, fingerprint | Non-cryptographic, well distributed, fast |
| **md5** | 128 | checksum, fingerprint | cryptographic, just for compatibility |
| **sha1** | 160 | checksum, fingerprint | cryptographic, just for compatibility |
| **sha2** | 256 | checksum, fingerprint | cryptographic, just for compatibility |
| **sha3** | 256 | checksum, fingerprint | cryptographic |
| **sha2** | 512 | checksum, fingerprint | cryptographic, just for compatibility |
| **sha3** | 512 | checksum, fingerprint | cryptographic |

## Reason for choosing the specified functions.
This [smasher](https://github.com/rurban/smhasher) fork is used to evaluate hash functions for their properties and selecting the best ones for specific tasks. [This](https://github.com/rurban/perl-hash-stats) project is maintained by the same person and looks at small input hash functions which need to be very fast for hash tables or symbol tables.
It's important that the collision rate stays low for these hash functions to be a real candidate.

* [rapidhash](https://github.com/Nicoshev/rapidhash/blob/master/README.md) is the successor of wyhash, very simple code and provides some special implementations for different input sizes.
* [ahash64](https://github.com/tkaitchuck/aHash) is tiny bit faster than `rapidhash` on small inputs but slower on larger inputs. The `rapidhash-nano` and `rapidhash-micro` are faster on smaller inputs, but the performance difference diminishes with increasing input size. The function is unstable across systems.
* [xxh3-64](https://github.com/Cyan4973/xxHash?tab=readme-ov-file) is a very fast hash function and provides good collision resistance for different data sizee. The low 32bit still pass the smasher tests with very high performance.The 64bit version is slightly slower than `rapidhash`.
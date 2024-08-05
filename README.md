# LZ Compressor

## Documentation

It compresses data for sure, just not most of the time...

The only function you need to use for compression is:
```c
int LZ_compress( u8 *src, u8 *dest, size_t dest_size );
```

This function will attempt to compress an array of bytes into a smaller array of bytes.
It will only work well on fairly large samples (100+ bytes) with repeating data. It is awful at text compression.

### Returns
| code | meaning |
| :--: | ------- |
|  0   | Success |
|  1   | Destination too small |
|  2   | Pattern list grew too large |
|  3   | Compression bytes are larger than source bytes |

If I come around to using this, I'll write a decompress function.


## References
- [Lempel–Ziv–Welch - Wikipedia](https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Welch)
- [The Beauty of Lempel-Ziv Compression - Art of the Problem](https://youtu.be/RV5aUr8sZD0?si=QIxUTOib1UKczFJF)
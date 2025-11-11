This simple implementation is inspired by Chapter 3 of DDIA. I'm building a log-structured
KV with hash indexes. For simplicity, we only support 4 bytes integer key and 4 bytes integer value.
A in-memory hash map is maintained to serve as the index of our KV, where the index key is
the key of our data, and value is the offset.


For now, we don't support concurrent accesses, so we just need one page in memory for buffering.
Once this page is full, we write it to a file. We also have a background thread to compact files
periodically to remove duplicates and handle deletion marker.


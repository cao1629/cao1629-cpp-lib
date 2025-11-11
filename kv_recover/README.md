A standalone KV store with recovery support. For simplicity, `unordered_map` is used to simulate
a KV store. Write-ahead-log is used to recover a KV instance after  a crash.
We focus on the implementation of WAL, so we don't consider concurrent accesses so far.

interview question from Zilliz, 2025.11.07


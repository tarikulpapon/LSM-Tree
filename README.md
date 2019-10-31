# LSM-Tree
You can find a very simple LSM Tree emulation in this repository where some key, value pairs are generated randomly and then inserted into the tree.
You can view the tree after the insertion is complete. One can add additional functionalities on top of this basic implementation.

How to run:

Just clone the repo and run `make`.

Then you can run the following command:
```
./lsm_tree -I50 -P4 -B2 -E32 -T2

```
### Understanding the input
T : Size Ratio of the LSM Tree

P : Size of the memory buffer in terms of pages

B : No of entries that can fit in one page 

E : Size of each entry in bytes

I : Number of inserts to 

V : Verbosity

For example, in the above mentioned command we are issuing 50 inserts 
with buffer size of 4 pages, each page containing 2 entries, each entries having size 32 bytes on an LSM tree of size ratio 2.

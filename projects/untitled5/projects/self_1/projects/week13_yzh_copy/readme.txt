使用了strategy的设计模式。
值得注意的是，这个项目在编写时只适配了Windows系统。对于Mac OS X或Linux系统，请将两个read()过程中的路径都改成'/'的形式，并且将Makefile中clean事件下的行为改成"rm -f *.o *.exe"（我没记错的话是这样的）

随机选的十个串如下：
friendvoidprotobuf
Thisfilewasgenerate
google/protobuf
_repeated_packed_
staticconst
DONOTEDIT!
constEnumDescriptor
Bufferheaders
ImportNoArenaNested
_google_2fprotobuf_

根据运行结果，两种算法表现相近。手工构造一组数据：
aaaaaaaaaa在src6.txt中查询，可以将KMP算法的优势体现出来。

KarpRabin算法表现不如KMP的原因是，KMP算法是严格O(n+m)的，而KarpRabin的最坏复杂度为O(nm)。在相同的串反复出现的情况下，KarpRabin算法性能较差，这是因为此时需要反复挨个比较，哈希算法没有优势；而KMP算法只要按照next数组跳转继续匹配即可。
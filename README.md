# bitcoin源码解析
目标设定是看完bitcoin的代码，需要掌握哪些内容。前期这部分内容可能会随着代码的深入发生变动。
从空工程，一步一步移植bitcoin代码过来，保证每个版本都可运行，直到最终一致。这样可以保证对代码运行了解透特。不浮在表面。
主要包括：
1.	P2P通信（分布式）。
2.	POW共识机制（去信任）。
3.	加密算法应用
4.	交易
5.	挖矿
6.	区块、区块链
7.	存储
8.	UTXO模型
9.	脚本

希望最终能达成的效果是，对bitcoin代码了如指掌，熟悉其设计理念，构建自己的区块链知识体系。如果自己实现公链，有所启发。
阅读代码之前，如果对区块链不是很熟悉，建议先阅读这些[资料](https://github.com/maodoutech/my-bitcoin/tree/master/doc/res.md)，对后面的学习有比较好的帮助。

## 编译
### Mac下编译
环境准备
brew install boost

复制源代码
git clone https://github.com/maodoutech/my-bitcoin.git
cd my-bitcoin

编译
cmake .
make

输出见bin目录

### Ubuntu下编译
// todo

## 说明
1. 为了简化，不支持windows
2. 每个版本在doc下都有一个简要说明
3. 每个版本基本都是一天左右的工作量，与上版本的diff可以参考doc的说明
4. 每个版本都会打一个tag与doc下的文档对应

区块链技术并不是一项新技术，而是通过分布式存储、密码学、共识机制、P2P的集成创新，因此在代码阅读的过程中其实很多是在看它的
设计理念。我在阅读代码过程中主要是参考[精通比特币](http://book.8btc.com/masterbitcoin2cn)和[WIKI](https://en.bitcoin.it/wiki/Main_Page)

## 文档

### 理论
1. [代码结构](https://github.com/maodoutech/my-bitcoin/tree/master/doc/overview.md)
2. [交易](https://github.com/maodoutech/my-bitcoin/tree/master/doc/theory_transaction.md)

### 版本

1. [环境搭建](https://github.com/maodoutech/my-bitcoin/blob/master/doc/v1.md)
2. [AppInit](https://github.com/maodoutech/my-bitcoin/blob/master/doc/v2.md)
3. [日志模块和琐](https://github.com/maodoutech/my-bitcoin/blob/master/doc/v3.md)
4. [任务池](https://github.com/maodoutech/my-bitcoin/blob/master/doc/v4.md)
5. [AppInit2前三步](https://github.com/maodoutech/my-bitcoin/blob/master/doc/v5.md)

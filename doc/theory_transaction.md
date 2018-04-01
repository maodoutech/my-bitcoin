# 交易
交易作为价值转移的载体在bitcoin系统中是非常重要的组成部分。交易最先由节点产生，打包并将交易广播并将交易广播
出去，挖矿节点对交易进行验证，验证通过之后会将将交易添加进区块，并广播区块给同步给节点。

**类图**

Transaction

![tx](https://github.com/maodoutech/my-bitcoin/blob/master/res/transaction.png)

Storage

![Storage](https://github.com/maodoutech/my-bitcoin/blob/master/res/storage.png)

## 存储

bitcoin磁盘存储
![存储](https://github.com/maodoutech/my-bitcoin/blob/master/res/storage_disk.png)

主要存储4中数据：

1. blocks/blk\*.dat，区块文件，从网络接收之后dump到磁盘，与leveldb无关。
2. blocks/index/\*，区块索引文件，存储已知区块的原信息，加快区块检索速度。
3. chainstate/\*，存储UTXO集合，对应内存中CBlockIndex结构。
4. blocks/rev\*.dat，"undo" data，在org的时候回滚chainstate。

目前只介绍其结构，具体怎么生成，怎么存储等添加代码的时候详细描述。

## UTXO
bitcoin交易不同于我们法币交易，而是记录的交易过程。CTxIn交易的输入、CTxOut交易的输出，一个交易CTransaction
包含多个CTxIn、CTxOut。CTxIn一定是来自上一个交易的CTxOut，prevout记录了来时哪个交易（hash）以及哪一个CTxout
（n）。Transaction类库图中可以看到，对于一个交易包含多个输入vin和多个输出vout，随着交易的进行一部分vout也会
被交易，UTXO就是就是记录这部分还没有被交易的vout，对于CCoins类。

另外CTxIn包含的scriptSig是获取CTxOut的凭证（钥匙），CTxOut的scriptPubKey是这个输出的琐。详细会在下面的章节
说明。

盗用参考文档的图，说的还是比较清晰的。

![交易](https://github.com/maodoutech/my-bitcoin/blob/master/res/2.jpg)

## 脚本

脚本是一种可编程的语言，运行环境是bitcoin节点环境。由于不支持循环语句，所以不是图灵完备，基于栈的方式运行。
那它是如何生效的呢，scriptPubKey是一个需要解答的题目，比如  x + 3 = 5，scriptSig需要解答出这道题，才能使用
vout。只是在bitcoin中，这道题目是和用户公密钥相关的题目，只有有密钥的节点才能解答出来。

下面是脚本支持命令：

```c++
enum opcodetype
{
    // push value  这部分的指令相当于表示这个指令后面的数据是怎么样的组织性质，
    OP_0=0,
    OP_FALSE=OP_0,
    OP_PUSHDATA1=76,  // 0x4c 为什么是这个值其实我不太清楚，不过可以肯定的是，这个值是76那么 OP_1 就是81 也就是0x51
    OP_PUSHDATA2,
    OP_PUSHDATA4,
    OP_1NEGATE,
    OP_RESERVED,  // 80
    OP_1,  // 81 也就是 0x51，但是为什么要求这个值是81不太清楚，但是感觉很特别
    OP_TRUE=OP_1, // 81 
    OP_2,
    OP_3,
//... 一直到Op_16

    // control  // 以下是控制流指令，比如 if 这类的指令，就是作为控制流存在的了
    OP_NOP,
    OP_VER,
    OP_IF,
    OP_NOTIF,
    OP_VERIF,
    OP_VERNOTIF,
    OP_ELSE,
    OP_ENDIF,
    OP_VERIFY,
    OP_RETURN,

    // stack ops  // 以下是对于栈的操作，这里可以理解为，栈用来保存了数据当前所处于的状态，
  // 这些指令相当于控制栈当前的状态，可以比作在编程中对当前操作对象的把控？。下文会对整体流程进行讲解
    OP_TOALTSTACK,
    OP_FROMALTSTACK,
    OP_2DROP,
    OP_2DUP,
    OP_3DUP,
    OP_2OVER,
    // ...

    // splice ops  // 这些也是对数据的一些处理操作，但是这些是对栈中数据本身的内容进行操作
    OP_CAT,
    OP_SUBSTR,
    OP_LEFT,
    OP_RIGHT,
    OP_SIZE,

    // bit logic  // 这个和上者一样，不过是位操作
    OP_INVERT,
    OP_AND,
    OP_OR,
    OP_XOR,
    // ...

    // numeric  // 这个和上者一样，不过是数字逻辑操作
    OP_1ADD,
    OP_1SUB,
    OP_2MUL,
    OP_2DIV,
    OP_NEGATE,
    OP_ABS,
    OP_NOT,
    OP_0NOTEQUAL,

    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    //...

    // crypto   // 这个和上者一样，但是操作的是和hash加密等相关的内容，可以理解为对bitcoin系统的特有的DSL
    OP_RIPEMD160,
    OP_SHA1,
    OP_SHA256,
    OP_HASH160,
    OP_HASH256,
    OP_CODESEPARATOR,
    OP_CHECKSIG,  // 这个是用的最多的，就是来判定签名是否符合的指令
    OP_CHECKSIGVERIFY,
    OP_CHECKMULTISIG,
    OP_CHECKMULTISIGVERIFY,

    // multi-byte opcodes
    OP_SINGLEBYTE_END = 0xF0,
    OP_DOUBLEBYTE_BEGIN = 0xF000,

    // template matching params  // 下面这两个代表bitcoin特别的数据结构，公钥(地址)
    OP_PUBKEY,
    OP_PUBKEYHASH,

    OP_INVALIDOPCODE = 0xFFFF,
};
```

以太坊的智能合约估计也是参考脚本的可编程特点提出的。之前参与EOS的众筹，大体是先调用智能合约将以太坊转到
合约地址，这个智能合约大体的功能是计算当天参与众筹的eth数量，计算出每个eth得到多少EOS，再将EOS与一个难题
绑定，然后我们再调用智能合约的方法根据自己的密钥解决这道难题，把我们的EOS区块。

## 参考文档

**交易**

https://zhuanlan.zhihu.com/p/25443501

https://zhuanlan.zhihu.com/p/26306458

https://zhuanlan.zhihu.com/p/27512347

http://book.8btc.com/books/6/masterbitcoin2cn/_book/ch06.html

https://blog.csdn.net/lizhe_dashuju/article/details/79186389

**存储**

https://en.bitcoin.it/wiki/Bitcoin_Core_0.11_(ch_2):_Data_Storage

http://baya.github.io/2017/05/11/7daystalk.html

**脚本**

http://book.8btc.com/books/6/masterbitcoin2cn/_book/appdx-scriptops.html

https://en.bitcoin.it/wiki/Script

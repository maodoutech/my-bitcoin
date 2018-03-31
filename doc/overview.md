# 代码概述

## 整体架构

由下至上
> Validating transactions; Managing blockchain, mempool, peers  (Consensus and Policy code)

> Scripting engine / Signatures (Consensus code)

> Network layer  (P2P code)

> P2P Messages

## 源文件描述

**文件**

| 文件      | 描述     |
| --------  | :-----        |
| net.\*    | Manages the network (peer connections, etc.). <br/>The while(true) loop in ThreadMessageHandler controls the program's flow, signalling main.cpp when there is work to do.  <br/> Key dependencies: None. |
| init.\*	| Initializes the node, calling functions in main.cpp as necessary. <br\> Key dependencies: main.h       |
| main.\*   | main.h declares some key global variables (mapBlockIndex, chainActive, mempool, etc), constants, and functions. <br/> main.cpp is the program's longest source file (5,237 lines). <br/> main.cpp has most of the key functions for managing the blockchain, such as connecting, disconnecting, validating and storing blocks; identifying a certain block as the tip of the longest chain; and so forth.<br/> The "entry point" for most of the code is ProcessMessages (which listens for a signal from the message-handling thread.).<br/> Some of the code is run during initialization, called directly from init.cpp.  <br/>Key dependencies: net.h       |
| chain.\*  | The header file (chain.h) is the more notable of the two, as it declares the type definitions for the metadata about the block (CBlockIndex) and the longest blockchain (CChain).</br> chain.cpp contains a few handy functions for managing the blockchain (e.g., locating blocks and finding a fork point between two chains.)        |
| coins.\*  | The header file declares a CCoin, which is, conceptually, "a bitcoin." <br/> The source file contains methods for manipulating coins (retrieving, spending, etc.) |
| miner.\*  | Contains the mining code, including block creation and generating new bitcoins.|

**子目录**

组件

| 目录      | 描述     |
| --------  | :-----        |
| leveldb   | C++ source code, docs, etc. for the LevelDB build. |
| qt        | The GUI code (QT). |
| secp256k1 | Library implementing ECDSA cryptography. <br/> Purpose: This proprietary C library eliminates reliance on SSL for signature checking. <br/> This is important because SSL was susceptible to introducing consensus bugs, because newly released versions do not guarantee bug-for-bug compatibility. <br/ >This library was written/released in early 2015. |
| zmq       | From the ZMQ wiki:<br/>ZMQ (or ZeroMQ or 0MQ) is a high-performance asynchronous messaging library.<br/>It provides a message queue, but unlike message-oriented middleware, a ZMQ system can run without a dedicated message broker. <br/>The library is designed to have a familiar socket-style API. |

模块

| 目录      | 文件     | 描述   |
| --------  | :-----   | :----- |
| consensus |consensus.\* <br/> merkle.\*<br/> params.\* <br/>validation.\* | Code implementing (or defining, as the case may be) the block & transaction validation rules. <br/>Purpose: Moving this code into a subdirectory is a step towards modularizing the consensus code. <br/>The idea is that in a future version of bitcoin, the consensus code should be packaged as a library, so that alternative implementations of the protocol could simply include this library and guarantee validation compatibility. "...[T]he goal is not reimplementing the consensus rules but rather extract them from Bitcoin Core so that nobody needs to re-implement them again. It is not only exposing it but also separating it from Bitcoin Core so that they can be changed without having to also change take into account non-consensus Bitcoin Core specific things." -- Jorge Timon, on bitcoin-development mailing list, 20 Aug 2015. |
| crypto    | ripemd.\* <br/> sha256.\* | 	Cryptographic hash functions. <br/> Both RIPEMD and SHA-256 are used in transforming a bitcoin address to Base-58 encoding. |
| policy    | policy.\* <br/>fees.\* | Move validation code that is a matter of policy (as opposed to consensus) into a separate directory. |
| primitives| block.\* <br/> transaction.\* | Definitions of certain basic data types (blocks, transactions, etc.) |
| script    | interpreter.\* <br/> script.\* <br/> standard.\* | The script engine. <br/>Defines the op_codes (script.h). <br/>Parses and evaluates the validation script. (interpreter.cpp:EvalScript()) <br/>Defines what is a "standard" transaction (standard.h).<br/>Purpose: the Script engine validates basic transactions but also makes contracts possible. It could be said that in large part, what a platform like Ethereum does is provide a more robust script engine (and language in which to express script) - so in a sense, deploying such as system consists of replacing this sub-directory with something more powerful. |
| wallet   | wallet.\* | Wallet code. |

其他

| 目录      | 描述   |
| --------  | :----- |
| compat    | A few minor, low-level files dealing with compatibility details. |
| config <br/>obj <br/>obj-tes| These directories relate to the build process. |
| test      | Unit tests. |
| univalue  | Per the README: <br/>"A universal value object, with JSON encoding (output) and decoding (input). <br/>Built as a single dynamic RAII C++ object class, and no templates." |

另外代码中有大量全局函数和变量，面向对象风格不是很强。很多也是线性集成，即一个基类只有一个子类。

## 类图
目前这部分主要是依据参考链接，在阅读代码过程中慢慢补充这部分内容。

## 参考链接

https://en.bitcoin.it/wiki/Bitcoin_Core_0.11_(ch_1):_Overview

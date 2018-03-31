# 代码概述

## 整体架构

由下至上
> Validating transactions; Managing blockchain, mempool, peers  (Consensus and Policy code)

> Scripting engine / Signatures (Consensus code)

> Network layer  (P2P code)

> P2P Messages

## 源文件描述

| 文件      | 描述     |
| --------   | -----:        |
| net.\*      | Manages the network (peer connections, etc.). <br/>The while(true) loop in ThreadMessageHandler controls the program's flow, signalling main.cpp when there is work to do.  <br/> Key dependencies: None. |

## 参考链接

https://en.bitcoin.it/wiki/Bitcoin_Core_0.11_(ch_1):_Overview

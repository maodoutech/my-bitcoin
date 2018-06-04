# 一致性算法

## 拜占庭将军问题
点对点通信的一个基本问题。存在消息丢失的不可靠信道上试图通过消息传递的方式达到一致性
是不可能的。一般只有在N ≥ 3M+1时才有解。其中M为作恶节点数，N为总节点数。

## PBFT算法

![pbft](https://github.com/maodoutech/my-bitcoin/blob/master/res/pbft.png)

其中C为发送请求端，0123为服务端，3为宕机的服务端，具体步骤如下：

A）Request：请求端C发送请求到任意一节点，这里是0

B）Pre-Prepare：服务端0收到C的请求后进行广播，扩散至123

C）Prepare：123,收到后记录并再次广播，1->023，2->013，3因为宕机无法广播

D）Commit：0123节点在Prepare阶段，若收到超过一定数量的相同请求，则进入Commit阶段，广播Commit请求

E）Reply：0123节点在Commit阶段，若收到超过一定数量的相同请求，则对C进行反馈


## RAFT

A）3种角色

Leader: 处理所有客户端交互，日志复制等，一般一次只有一个Leader.

Follower: 类似选民，完全被动

Candidate候选人: 类似Proposer律师，可以被选为一个新的领导人。

B）2个过程

选主

日志复制

演示

http://thesecretlivesofdata.com/raft/

## POW

区块头

![pow](https://github.com/maodoutech/my-bitcoin/blob/master/res/pow.png)

合格的区块条件如下：

SHA256D(Blockherder) < F(nBits)


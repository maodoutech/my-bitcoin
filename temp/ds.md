# 数据服务

## 总体架构

![architecture](https://github.com/maodoutech/my-bitcoin/blob/master/temp/ds.png)

## 基础组件

### 抓取平台
快速地获取结构化数据，打造从网页获取、解析、到生成数据的一体化流程，托管所有的网页抓取任务。
优点是可能统一网页数据入口，规范输入获取规范。另外抓取不需要开发，直接配置即可，节省开发
资源。

> 输入： url集、提取规则
> 输出： 结构化数据，输出到消息队列，相关消息如下proto

**实现难点：**

1. 任务资源隔离、优先级
2. 任务分布式调度，如多实例抓取（前期可先单机实现）
3. 流控
4. 可视化配置抓取
5. 验证码

**数据量预估**

1. token持有数据

每个token按30W算，100种token需要3000万条记录

2. 交易数据

每个token按300W算，100种token需要3亿记录

3. ....


```proto
package ds.proto.rawdata;

message PubKey {
    enum IdType {
        ERC2 = 1;    // 以太坊
        BTC  = 2；   // 比特币
    };

    required IdType id_type = 1;
    required bytes id = 2;         // 公钥地址
};

// @brief 消息类别
// 唯一确定一种消息
message MessageDescriptionProto
{
    // 表示消息类型
    enum message_type_t
    {
        // token信息
        TOKEN_TX = 0;
        TOKEN_ACCOUNT = 1;
        TOKEN_SOURCE = 2;

        // 挂单买单
        ORDERS = 3;
    }
    required message_type_t message_type = 1

    // 表示消息来源
    enum message_src_t
    {
        PAGE = 0;
        BLOCK = 1;
        EXCHANGE = 2;
    }
    required message_src_t message_src = 2;
};

// 交易数据
message TxProto
{
    // token名字
    required bytes token_name = 1;

    required PubKey from = 2;

    required PubKey to = 3;

    // 时间戳
    optional uint64 timestamp = 4;

    // 数量
    optional float quantity = 5;

    // 交易hash
    optional bytes hash = 6;
};

// 账户信息
message AccountProto
{
    // 地址
    required PubKey address = 1;

    // 时间戳
    optional uint64 timestamp = 2;

    // 数量
    optional float quantity = 3;
};

// 开发信息
message DevelopProto
{
    // 开始时间
    optional uint64 start_ts = 1;

    // 结束时间
    optional uint64 end_ts = 2;

    optional int32 authors = 3;

    // 提交数
    optional int32 commits = 4;

    // 新增行数
    optional int32 add_lines = 5;

    // 更新行数
    optional int32 update_lines = 6;

    // 删除行数
    optional int32 del_lines = 7;

    // 提交地址
    optional bytes addr = 8;
};

// @brief 消息proto定义
message MessageProto
{
    // 消息类别
    optional MessageDescriptionProto message_desc = 1;

    // timestamp格式时间
    required fixed32 timestamp = 2;

    // 消息来源具体信息[网页地址或交易所地址]
    optional bytes message_src = 3;

    // 消息数据
    optional TxProto tx = 3;
    optional AccountProto account = 4;
    optional DevelopProto develop = 5;
    optional bytes ext_data = 6;
};
```

### 区块解析服务
   支持从原始区块获取交易数据，对于不同公链解析逻辑不一致，区块解析服务需要托管所有的解析服务，
新增一个公链只需要注册解析逻辑和输入数据。这个服务稳定之后理论上相关交易、持有信息可以不通
过区块链浏览器抓取。

> 输入： 公链区块数据
> 输出： 区块交易数据，输出到消息队列

**数据量**
预计和抓取差不多

### 数据接入服务
   订阅从消息队列接受到的各种消息，每种消息都有会有注册的回调函数进行处理，开发人员只要注册
消息处理函数，数据接入服务就会进行自动化调用。

> 输入： 各种抓取、区块解析消息
> 输出： 存储

## 数据接入

  基于插件模式，解析从消息队列获取到的数据，调用相应插入进行处理入库。根据数据量和单机性能，
可分PIPE订阅处理。

### 存储设计

   根据数据量、TPS和查询选择合理的存储引擎，目前看数据量并不大，使用关系型数据库如mysql可以搞定。

#### 数据hive迁移方案

### 插件Example
// todo

## 服务

### 量化分析



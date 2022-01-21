#pragma once

/*
coder:nash
date:2022/1/21
desc:跨进程通信（在两个进程之间发送数据包),基于共享内存和wins的系统消息
*/


//ProcessChanAccept 消息接收端
class ProcessChanAccept
{
public:
	ProcessChanAccept();
	virtual ~ProcessChanAccept();
};



//ProcessChanAccept 消息发送端
class ProcessChanSend
{
public:
	ProcessChanSend();
	virtual ~ProcessChanSend();
};

#pragma once

#define MSG_HEADER_FLAG  "nash"
#define MSG_HEADER_VERSION 0x05







//MSG_TYPE
#define MSG_HEADER_TYPE_CONTROL 0x01

//MSG_CODE
#define MSG_HEADER_CODE_TEST 0x01
#define MSG_HEADER_CODE_TEST_OK 0x02

#define MSG_HEADER_CODE_CONNECT 0x03
#define MSG_HEADER_CODE_DISCONNECT 0x04

#define MSG_HEADER

//MSG_ERROR_CODE

#define	 MSG_HEADER_ERROR_FLAG 0x01
#define  MSG_HEADER_ERROR_VERSION 0x02

struct MsgHeader
{
	char Flag[6]; //! 必须是 "nash"

	unsigned char Type; //! 消息类型
	unsigned char MsgCode; //! 消息代码，不同消息类型有不同代码
	unsigned char ErrorCode; //! 备用，不同消息类型有不同用处
	unsigned char Version; //! 结构版本号，目前为5
	MsgHeader();
};
struct MsgParameter
{
	int Command;
	char Accessory;//是否带附件,0无，1有
	int ParameterSize;//参数字节大小
	MsgParameter();
};


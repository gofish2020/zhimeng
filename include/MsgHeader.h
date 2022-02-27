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
	char Flag[6]; //! ������ "nash"

	unsigned char Type; //! ��Ϣ����
	unsigned char MsgCode; //! ��Ϣ���룬��ͬ��Ϣ�����в�ͬ����
	unsigned char ErrorCode; //! ���ã���ͬ��Ϣ�����в�ͬ�ô�
	unsigned char Version; //! �ṹ�汾�ţ�ĿǰΪ5
	MsgHeader();
};
struct MsgParameter
{
	int Command;
	char Accessory;//�Ƿ������,0�ޣ�1��
	int ParameterSize;//�����ֽڴ�С
	MsgParameter();
};


#include "stdafx.h"
#include "..\include\MsgHeader.h"


MsgHeader::MsgHeader()
{
	memset(this, 0, sizeof(MsgHeader));
	strcpy(Flag, MSG_HEADER_FLAG);
	Version = MSG_HEADER_VERSION;
}


MsgParameter::MsgParameter()
{
	memset(this, 0, sizeof(MsgParameter));
}

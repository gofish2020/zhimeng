// TestDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"




class log
{
private:
	log();
	virtual ~log();
	static log flog;
	int a = 0;
public:
	static log* instance();
	static void Set();
	void test();
};

log log::flog;
log::log()
{
	printf("1");
}

log::~log()
{
	printf("2");
}

log* log::instance()
{
	return &flog;
}

void log::test()
{
	
	printf("%d",a);
}

void log::Set()
{
	flog.a = 1;
}

int main()
{
	
	log::instance()->test();
	log::Set();
	log::instance()->test();
    return 0;
}


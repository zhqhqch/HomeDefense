/*
 * Util.cpp
 *
 *  Created on: 2015年3月12日
 *      Author: hqch
 */


#include "Util.h"
#include <time.h>
#include <stdlib.h>

int * Util::randomOrder(int total, int quantity){
	int *d;
	int i,a,b,t;

	srand(time(NULL));
	d=(int *)malloc((total)*sizeof(int));

	for (i=0;i<total;i++) d[i]=i;/* 填写0～n */
	for (i=total;i>0;i--) {/* 打乱0～n */
		a=i-1;
		b=rand()%i;
		if (a!=b) {t=d[a];d[a]=d[b];d[b]=t;}
	}
	return d;
}

//字符串分割函数
cocos2d::Array * Util::split(const char* srcStr, const char* sSep) {
	cocos2d::Array* stringList = cocos2d::Array::create();
	int size = strlen(srcStr);
	/* 将数据转换为Cocos2d-x字符串对象 */
	cocos2d::String* str = cocos2d::String::create(srcStr);
	int startIndex = 0;
	int endIndex = 0;
	endIndex = str->_string.find(sSep);
	cocos2d::String* spliStr = NULL;
	/* 根据分隔符拆分字符串，并添加到列表中 */
	while (endIndex > 0) {
		spliStr = cocos2d::String::create("");
		/* 截取字符串 */
		spliStr->_string = str->_string.substr(startIndex, endIndex);
		/* 添加字符串到列表 */
		stringList->addObject(spliStr);
		/* 截取剩下的字符串 */
		str->_string = str->_string.substr(endIndex + 1, size);
		/* 查找下一个分隔符所在下标 */
		endIndex = str->_string.find(sSep);
	}
	/* 剩下的字符串也添加进列表 */
	if (str->_string.compare("") != 0) {
		stringList->addObject(cocos2d::String::create(str->_string));
	}
	return stringList;
}

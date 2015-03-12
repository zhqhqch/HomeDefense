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


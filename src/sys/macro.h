#pragma once

#define  MAXPATHLEN         260        // �ļ�|����|ע�����󳤶�
#define  MAXNAMELEN         64         // �û�����󳤶�

#define	 RUN_ONCE	\
{ \
	static  BOOLEAN bUninit = FALSE;\
	if (bUninit==TRUE)\
	{\
		return;\
	}\
	bUninit = TRUE;\
}
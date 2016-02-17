#pragma once

#define		LONG_NAME_LEN		300
#define		SHORT_NAME_LEN		64
#define		DRIVER_LETTER_LEN	8

#define		STATUS_SB_TRY_REPARSE			0xe0000001
#define		STATUS_SB_REPARSED				0xe0000002
#define		STATUS_SB_DIR_CREATED			0xe0000005
#define		MAX_VOLUME_CHARS				26	

#define EMPTY_UNICODE_STRING {0, 0, NULL}

#define MyNew(_type, _count) \
(_type*)ExAllocatePoolWithTag(NonPagedPool, sizeof(_type) * (_count), 'FCLM')

#define MyDelete(_p) \
do{if(!(_p)) break; ExFreePool((_p)); (_p) = NULL;}while(0)


#define	 RUN_ONCE	\
{ \
	static  BOOLEAN bUninit = FALSE;\
	if (bUninit==TRUE)\
	{\
		return;\
	}\
	bUninit = TRUE;\
}

#define UNICODE_STRING_CONST(x) \
{sizeof(L##x)-2, sizeof(L##x), L##x}

#define DECLARE_UNICODE_STRING(_var, _string) \
WCHAR _var ## _buffer[] = _string; \
__pragma(warning(push)) \
__pragma(warning(disable:4221)) __pragma(warning(disable:4204)) \
UNICODE_STRING _var = { sizeof(_string) - sizeof(WCHAR), sizeof(_string), (PWCH) _var ## _buffer } \
__pragma(warning(pop))

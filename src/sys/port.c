#include "main.h"
#include "port.h"


static PFLT_PORT g_ServerPort = NULL; 
static PFLT_PORT g_ClientPort = NULL;
static PFLT_FILTER g_Filter = NULL;

#define DELAY_ONE_MICROSECOND ( -10 )
#define DELAY_ONE_MILLISECOND	( DELAY_ONE_MICROSECOND * 1000 )

VOID 		PortDisconnect( PVOID ConnectionCookie);
NTSTATUS 	PortConnect(PFLT_PORT ClientPort,PVOID ServerPortCookie, PVOID ConnectionContext, ULONG SizeOfContext,PVOID *ConnectionCookie);

#ifdef ALLOC_PRAGMA
    #pragma alloc_text(PAGE, PortConnect)
    #pragma alloc_text(PAGE, PortDisconnect)
#endif


NTSTATUS
PortConnect(PFLT_PORT ClientPort,PVOID ServerPortCookie, PVOID ConnectionContext, ULONG SizeOfContext,PVOID *ConnectionCookie)
{
	PAGED_CODE();

	UNREFERENCED_PARAMETER(ServerPortCookie);
	UNREFERENCED_PARAMETER(ConnectionContext);
	UNREFERENCED_PARAMETER(SizeOfContext);
	UNREFERENCED_PARAMETER(ConnectionCookie);

	g_ClientPort = ClientPort;

	return STATUS_SUCCESS;
}


VOID PortDisconnect( PVOID ConnectionCookie)
{
	UNREFERENCED_PARAMETER(ConnectionCookie);
	PAGED_CODE();
	if (g_ClientPort)
	{
		FltCloseClientPort(g_Filter, &g_ClientPort);
		g_ClientPort = NULL;
	}
}

void UnInitPortComm()
{
	if (g_ServerPort)
	{
		FltCloseCommunicationPort(g_ServerPort);
		g_ServerPort = NULL;
	}
}



NTSTATUS InitPortComm(PWCHAR port_name, PFLT_FILTER filter)
{
	OBJECT_ATTRIBUTES		oa;
	UNICODE_STRING			uniString;
	PSECURITY_DESCRIPTOR	sd;
	NTSTATUS				status;

	g_Filter = filter;
	RtlInitUnicodeString(&uniString, port_name);
	status = FltBuildDefaultSecurityDescriptor(&sd, FLT_PORT_ALL_ACCESS);
	if (NT_SUCCESS(status)) 
	{

		InitializeObjectAttributes(&oa,&uniString,OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,NULL,sd);
		status = FltCreateCommunicationPort(filter,
			&g_ServerPort,
			&oa,
			NULL,
			(PFLT_CONNECT_NOTIFY)PortConnect,
			(PFLT_DISCONNECT_NOTIFY)PortDisconnect,
			NULL,
			1);
		FltFreeSecurityDescriptor(sd);
	}
	return status;
}
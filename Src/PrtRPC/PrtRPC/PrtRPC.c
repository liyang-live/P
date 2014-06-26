#include "PrtCmd.h"
#include"PrtTypes.h"
#include"PrtValues.h"
#include<pthread.h>
#include"../PrtCmdIDL/PrtRPC_Types_h.h"
#include"../PrtCmdIDL/PrtRPC_Types_s.c"

PRT_VALUE ReceivedValue;



void TypeCreateTest()
{
	//// Make the integer type
	PRT_TYPE intType = PrtMkPrimitiveType(PRT_KIND_INT);

	//// Make the bool type
	PRT_TYPE boolType = PrtMkPrimitiveType(PRT_KIND_BOOL);

	//// Make the sequence of booleans type
	PRT_SEQTYPE *seqBoolType = PrtMkSeqType(boolType);

	//// Make the int -> seq of bool type.
	PRT_MAPTYPE *int2seqType = PrtMkMapType(intType, (PRT_TYPE)seqBoolType);

	//// Clone the type
	PRT_TYPE clone = PrtCloneType((PRT_TYPE)int2seqType);

	//// Print it
	PrtCmdPrintType((PRT_TYPE)int2seqType);

	//// Free the type
	PrtFreeType((PRT_TYPE)int2seqType);

	//// Print the clone
	printf_s("\n");
	PrtCmdPrintType(clone);

	//// Free the clone
	PrtFreeType(clone);

	//// Free the remainder
	PrtFreeType(intType);
	PrtFreeType(boolType);
	PrtFreeType((PRT_TYPE)seqBoolType);
}

void TupleTest()
{
	PRT_TYPE anyType = PrtMkPrimitiveType(PRT_KIND_ANY);
	PRT_TYPE anyPairType = (PRT_TYPE)PrtMkTupType(2);
	
	PrtSetFieldType(anyPairType, 0, anyType);
	PrtSetFieldType(anyPairType, 1, anyType);

	PRT_VALUE oneVal = (PRT_VALUE)PrtMkIntValue(1);
	PRT_VALUE boolVal = (PRT_VALUE)PrtMkBoolValue(PRT_TRUE);
	PRT_VALUE anyPair = PrtMkDefaultValue(anyPairType);
	
	PrtCmdPrintValueAndType(anyPair);
	printf_s("\n");

	PrtTupleSet((PRT_TUPVALUE *)anyPair, 0, oneVal);

	PrtCmdPrintValueAndType(anyPair);
	printf_s("\n");

	PrtTupleSet((PRT_TUPVALUE *)anyPair, 1, boolVal);

	PrtCmdPrintValueAndType(anyPair);
	printf_s("\n");

	PrtCmdPrintValueAndType((PRT_VALUE)PrtTupleGet((PRT_TUPVALUE *)anyPair, 0));
	printf_s("\n");

	PrtCmdPrintValueAndType((PRT_VALUE)PrtTupleGet((PRT_TUPVALUE *)anyPair, 1));
	printf_s("\n");
}

void NamedTupleTest()
{
	PRT_TYPE anyType = PrtMkPrimitiveType(PRT_KIND_ANY);
	PRT_NMDTUPTYPE *anyPairType = PrtMkNmdTupType(2);

	PrtSetFieldName(anyPairType, 0, "foo");
	PrtSetFieldType((PRT_TYPE)anyPairType, 0, anyType);
	PrtSetFieldName(anyPairType, 1, "bar");
	PrtSetFieldType((PRT_TYPE)anyPairType, 1, anyType);

	PRT_VALUE oneVal = (PRT_VALUE)PrtMkIntValue(1);
	PRT_VALUE boolVal = (PRT_VALUE)PrtMkBoolValue(PRT_TRUE);
	PRT_VALUE anyPair = PrtMkDefaultValue((PRT_TYPE)anyPairType);

	PrtCmdPrintValueAndType(anyPair);
	printf_s("\n");

	PrtNmdTupleSet((PRT_TUPVALUE *)anyPair, "foo", oneVal);

	PrtCmdPrintValueAndType(anyPair);
	printf_s("\n");

	PrtNmdTupleSet((PRT_TUPVALUE *)anyPair, "bar", boolVal);

	PrtCmdPrintValueAndType(anyPair);
	printf_s("\n");

	PrtCmdPrintValueAndType((PRT_VALUE)PrtNmdTupleGet((PRT_TUPVALUE *)anyPair, "foo"));
	printf_s("\n");

	PrtCmdPrintValueAndType((PRT_VALUE)PrtNmdTupleGet((PRT_TUPVALUE *)anyPair, "bar"));
	printf_s("\n");
}

void SeqAppendTest()
{
	PRT_INT32 i;
	PRT_TYPE intType = PrtMkPrimitiveType(PRT_KIND_INT);
	PRT_SEQTYPE *iseqType = PrtMkSeqType(intType);
	PRT_SEQVALUE *seq = (PRT_SEQVALUE *)PrtMkDefaultValue((PRT_TYPE)iseqType);
	
	PrtCmdPrintValueAndType((PRT_VALUE)seq);
	printf_s("\n");

	for (i = 0; i <= 10; ++i)
	{
		PrtSeqInsert(seq, seq->size, (PRT_VALUE)PrtMkIntValue(i));
	}

	PrtCmdPrintValueAndType((PRT_VALUE)seq);
	printf_s("\n");

	for (i = 10; i >= 0; --i)
	{
		PrtSeqInsert(seq, seq->size, (PRT_VALUE)PrtMkIntValue(i));
	}

	PrtCmdPrintValueAndType((PRT_VALUE)seq);
	printf_s("\n");
}

void SeqPrependTest()
{
	PRT_INT32 i;
	PRT_TYPE intType = PrtMkPrimitiveType(PRT_KIND_INT);
	PRT_SEQTYPE *iseqType = PrtMkSeqType(intType);
	PRT_SEQVALUE *seq = (PRT_SEQVALUE *)PrtMkDefaultValue((PRT_TYPE)iseqType);

	PrtCmdPrintValueAndType((PRT_VALUE)seq);
	printf_s("\n");

	for (i = 0; i <= 10; ++i)
	{
		PrtSeqInsert(seq, 0, (PRT_VALUE)PrtMkIntValue(i));
	}

	PrtCmdPrintValueAndType((PRT_VALUE)seq);
	printf_s("\n");

	for (i = 10; i >= 0; --i)
	{
		PrtSeqInsert(seq, 0, (PRT_VALUE)PrtMkIntValue(i));
	}

	PrtCmdPrintValueAndType((PRT_VALUE)seq);
	printf_s("\n");
}

void SeqAppendRemoveTest()
{
	PRT_INT32 i;
	PRT_INT32 j;
	PRT_TYPE intType = PrtMkPrimitiveType(PRT_KIND_INT);
	PRT_SEQTYPE *iseqType = PrtMkSeqType(intType);
	PRT_SEQVALUE *seq = (PRT_SEQVALUE *)PrtMkDefaultValue((PRT_TYPE)iseqType);

	PrtCmdPrintValueAndType((PRT_VALUE)seq);
	printf_s("\n");

	for (i = 1; i < 10; ++i)
	{
		for (j = 0; j < i; ++j)
		{
			PrtSeqInsert(seq, seq->size, (PRT_VALUE)PrtMkIntValue(j));
		}

		PrtCmdPrintValueAndType((PRT_VALUE)seq);
		printf_s("\n");

		if (i % 2 == 0)
		{
			for (j = 0; j < i; ++j)
			{
				PrtSeqRemove(seq, 0);
				PrtCmdPrintValueAndType((PRT_VALUE)seq);
				printf_s("\n");
			}
		}
		else 
		{
			for (j = i - 1; j >= 0; --j)
			{
				PrtSeqRemove(seq, j);
				PrtCmdPrintValueAndType((PRT_VALUE)seq);
				printf_s("\n");

				if (j == 0)
				{
					break;
				}
			}
		}
	}
}

void SeqNestedTest()
{
	PRT_INT32 i;
	PRT_TYPE anyType = PrtMkPrimitiveType(PRT_KIND_ANY);
	PRT_SEQTYPE *aseqType = PrtMkSeqType(anyType);
	PRT_SEQVALUE *seq = (PRT_SEQVALUE *)PrtMkDefaultValue((PRT_TYPE)aseqType);

	PrtCmdPrintValueAndType((PRT_VALUE)seq);
	printf_s("\n");

	for (i = 0; i < 10; ++i)
	{
		PrtSeqInsert(seq, seq->size, (PRT_VALUE)seq);
		PrtCmdPrintValueAndType((PRT_VALUE)seq);
		printf_s("\n");
	}
}

void TupleTest2()
{
	PRT_TYPE intType = PrtMkPrimitiveType(PRT_KIND_INT);
	PRT_TYPE intPairType = (PRT_TYPE)PrtMkTupType(2);

	PrtSetFieldType(intPairType, 0, intType);
	PrtSetFieldType(intPairType, 1, intType);

	PRT_VALUE oneVal = (PRT_VALUE)PrtMkIntValue(1);
	PRT_VALUE boolVal = (PRT_VALUE)PrtMkBoolValue(PRT_TRUE);
	PRT_VALUE intPair = PrtMkDefaultValue(intPairType);

	PrtCmdPrintValueAndType(intPair);
	printf_s("\n");

	PrtTupleSet((PRT_TUPVALUE *)intPair, 0, oneVal);

	PrtCmdPrintValueAndType(intPair);
	printf_s("\n");

	PrtTupleSet((PRT_TUPVALUE *)intPair, 1, boolVal);

	PrtCmdPrintValueAndType(intPair);
	printf_s("\n");
}

void MapTest1()
{
	PRT_TYPE anyType = PrtMkPrimitiveType(PRT_KIND_ANY);
	PRT_MAPTYPE *any2anyType = PrtMkMapType(anyType, anyType);
	PRT_MAPVALUE *a2aMap = (PRT_MAPVALUE *)PrtMkDefaultValue((PRT_TYPE)any2anyType);

	PrtCmdPrintValueAndType((PRT_VALUE)a2aMap);
	printf_s("\n");

	PRT_VALUE falseVal = (PRT_VALUE)PrtMkBoolValue(PRT_FALSE);
	PrtMapUpdate(a2aMap, (PRT_VALUE)falseVal, (PRT_VALUE)falseVal);

	PRT_UINT32 i;
	for (i = 0; i < 5; ++i)
	{
		PrtMapUpdate(a2aMap, (PRT_VALUE)PrtMkIntValue(i), (PRT_VALUE)PrtMkIntValue(i));
		PrtCmdPrintValueAndType((PRT_VALUE)a2aMap);
		printf_s("\n");
	}

	PrtMapUpdate(a2aMap, (PRT_VALUE)falseVal, (PRT_VALUE)PrtMkIntValue(10));
	PrtCmdPrintValueAndType((PRT_VALUE)a2aMap);
	printf_s("\n");

	PrtCmdPrintValueAndType((PRT_VALUE)PrtMapGetKeys(a2aMap));
	printf_s("\n");

	PrtCmdPrintValueAndType((PRT_VALUE)PrtMapGetValues(a2aMap));
	printf_s("\n");
}



void BinaryBoolFunTest()
{
	PRT_TYPE boolType = (PRT_TYPE)PrtMkPrimitiveType(PRT_KIND_BOOL);
	PRT_TYPE intType = (PRT_TYPE)PrtMkPrimitiveType(PRT_KIND_INT);
	PRT_TYPE boolTupType = (PRT_TYPE)PrtMkTupType(2);
	PrtSetFieldType(boolTupType, 0, boolType);
	PrtSetFieldType(boolTupType, 1, boolType);
	PRT_MAPTYPE *binFunType = PrtMkMapType(boolTupType, boolType);
	PRT_MAPTYPE *popFunType = PrtMkMapType((PRT_TYPE)binFunType, intType);

	printf_s("Bool fun type = ");
	PrtCmdPrintType((PRT_TYPE)binFunType);
	printf_s("\n");

	printf_s("Population fun type = ");
	PrtCmdPrintType((PRT_TYPE)popFunType);
	printf_s("\n");

	PRT_UINT32 funImg;
	PRT_UINT32 funRng;
	PRT_VALUE boolVal;
	PRT_VALUE popCntVal;
	PRT_TUPVALUE *boolTup;
	PRT_MAPVALUE *popFun = (PRT_MAPVALUE *)PrtMkDefaultValue((PRT_TYPE)popFunType);
	for (funImg = 0; funImg < 16; ++funImg)
	{
		PRT_MAPVALUE *fun = (PRT_MAPVALUE *)PrtMkDefaultValue((PRT_TYPE)binFunType);
		for (funRng = 0; funRng < 4; ++funRng)
		{
			//// Set (funRng_1, funRng_0) -> img_0
			boolTup = (PRT_TUPVALUE *)PrtMkDefaultValue(boolTupType);

			boolVal = (PRT_VALUE)PrtMkBoolValue((funRng & 0x00000002) == 0 ? PRT_FALSE : PRT_TRUE);
			PrtTupleSet(boolTup, 0, boolVal);
			PrtFreeValue(boolVal);

			boolVal = (PRT_VALUE)PrtMkBoolValue((funRng & 0x00000001) == 0 ? PRT_FALSE : PRT_TRUE);
			PrtTupleSet(boolTup, 1, boolVal);
			PrtFreeValue(boolVal);

			boolVal = (PRT_VALUE)PrtMkBoolValue(((funImg >> funRng) & 0x00000001) == 0 ? PRT_FALSE : PRT_TRUE);
			PrtMapUpdate(fun, (PRT_VALUE)boolTup, boolVal);
			PrtFreeValue(boolVal);
			PrtFreeValue((PRT_VALUE)boolTup);
		}

		popCntVal = (PRT_VALUE)PrtMkIntValue(
			(0x00000001 & funImg) +
			(0x00000001 & (funImg >> 1)) +
			(0x00000001 & (funImg >> 2)) +
			(0x00000001 & (funImg >> 3)));

		PrtCmdPrintValue((PRT_VALUE)fun);
		printf_s("\n");

		PrtMapUpdate(popFun, (PRT_VALUE)fun, popCntVal);

		PrtFreeValue(popCntVal);
		PrtFreeValue((PRT_VALUE)fun);
	}

	PrtCmdPrintValue((PRT_VALUE)popFun);
	printf_s("\n");

	//// Build the population function in reverse.
	//// Get the keys of the population function.
	PRT_UINT32 i;
	PRT_SEQVALUE *popKeys = PrtMapGetKeys(popFun);
	PRT_MAPVALUE *revPopFun = (PRT_MAPVALUE *)PrtMkDefaultValue((PRT_TYPE)popFunType);
	for (i = 1; i <= 16; ++i)
	{
		popCntVal = PrtMapGet(popFun, popKeys->values[16 - i]);
		PrtMapUpdate(revPopFun, popKeys->values[16 - i], popCntVal);
		PrtFreeValue(popCntVal);
	}

	PrtFreeValue((PRT_VALUE)popKeys);
	PrtCmdPrintValue((PRT_VALUE)revPopFun);
	printf_s("\n");

	PrtAssert(PrtGetHashCodeValue((PRT_VALUE)popFun) == PrtGetHashCodeValue((PRT_VALUE)revPopFun), "Equivalent maps should have equivalent hash codes");

	PrtFreeValue((PRT_VALUE)revPopFun);
	PrtFreeValue((PRT_VALUE)popFun);
	PrtFreeType(intType);
	PrtFreeType(boolType);
	PrtFreeType(boolTupType);
	PrtFreeType((PRT_TYPE)binFunType);
	PrtFreeType((PRT_TYPE)popFunType);
}



/*
int main(int argc, char *argv[])
{
	PRT_DBG_START_MEM_BALANCED_REGION
	{
		BinaryBoolFunTest();
	}
	PRT_DBG_END_MEM_BALANCED_REGION

	/*
	TupleTest();
	NamedTupleTest();
	SeqAppendTest();
	SeqPrependTest();
	SeqAppendRemoveTest();
	SeqNestedTest();
	MapTest1();
	MapTest2();
	

	return 0;
}
*/
void* __cdecl WaitThreadForRPCListen(void* i)
{
	printf("Thread - WaitThreadForRPCListen listening ...\n");
	RPC_STATUS status;
	status = RpcMgmtWaitServerListen();
	if (status)
		exit(status);
	printf("In WaitThreadForRPCListen - Wait Server Listen Stopped");
	pthread_exit(NULL);
	return NULL;
}


void s_SendValue1(
	handle_t handleM,
	PRT_PRIMVALUE* value
	)
{
	ReceivedValue = PrtCloneValue((PRT_VALUE)value);
	printf("In SendValue1 Value Received :");
	PrtCmdPrintValue(ReceivedValue);
}

void s_SendValue2(
	handle_t handleM,
	PRT_PRIMVALUE* value
	)
{
	printf("\nIn SendValue2");
	PrtAssert(PrtIsEqualValue(ReceivedValue, (PRT_VALUE)value), "Not Equal in SendValue2");
	printf("\nLastReceived : ");
	PrtCmdPrintValue(ReceivedValue);
	printf("\nReceived : ");
	PrtCmdPrintValue(value);
}

void s_SendValueMap1(
	handle_t handleM,
	PRT_MAPVALUE* value
	)
{
	ReceivedValue = PrtCloneValue((PRT_VALUE)value);
	printf("In SendValue1 Value Received :");
	PrtCmdPrintValue(ReceivedValue);
}

void s_SendValueMap2(
	handle_t handleM,
	PRT_MAPVALUE* value
	)
{
	printf("\nIn SendValue2");
	PrtAssert(PrtIsEqualValue(ReceivedValue, (PRT_VALUE)value), "Not Equal in SendValue2");
	printf("\nLastReceived : ");
	PrtCmdPrintValue(ReceivedValue);
	printf("\nReceived : ");
	PrtCmdPrintValue(value);
}

void CreateRPCTestServer()
{
	printf("Creating RPC server for PService ....\n");

	RPC_STATUS status;

	status = RpcServerUseProtseqEp(
		(unsigned char*)("ncacn_ip_tcp"), // Use TCP/IP protocol.
		RPC_C_PROTSEQ_MAX_REQS_DEFAULT, // Backlog queue length for TCP/IP.
		(unsigned char*)"4747", // TCP/IP port to use.
		NULL);

	if (status)
	{
		printf(stderr, "Runtime reported exception in RpcServerUseProtseqEp"); 
		exit(status);
	}

	status = RpcServerRegisterIf2(
		s_PrtRPC_v1_0_s_ifspec, // Interface to register.
		NULL, // Use the MIDL generated entry-point vector.
		NULL, // Use the MIDL generated entry-point vector.
		RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH, // Forces use of security callback.
		RPC_C_LISTEN_MAX_CALLS_DEFAULT, // Use default number of concurrent calls.
		(unsigned)-1, // Infinite max size of incoming data blocks.
		NULL); // Naive security callback.

	if (status)
	{
		printf(stderr, "Runtime reported exception in RpcServerRegisterIf2");
		exit(status);
	}

	// Start to listen for remote procedure calls for all registered interfaces.
	// This call will not return until RpcMgmtStopServerListening is called.
	status = RpcServerListen(
		1, // Recommended minimum number of threads.
		RPC_C_LISTEN_MAX_CALLS_DEFAULT, // Recommended maximum number of threads.
		1);

	pthread_t workerThread;
	int s = pthread_create(&workerThread, NULL, WaitThreadForRPCListen, NULL);
	if (s)
	{
		printf(stderr, "Runtime reported exception in pthread_create");
		exit(status);
	}

}

void* __RPC_API
MIDL_user_allocate(size_t size)
{
	unsigned char* ptr;
	ptr = (unsigned char*)malloc(size);
	return (void*)ptr;
}

void __RPC_API
MIDL_user_free(void* object)

{
	free(object);
}


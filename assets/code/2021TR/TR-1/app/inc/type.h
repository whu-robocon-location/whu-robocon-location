#ifndef TYPE_H
#define TYPE_H

#ifdef __cplusplus
extern "C"
{
	#endif

	/*
	;*****************************************************************************************************
	;* ��    �� : ����ϵͳ���������͡�
	;*****************************************************************************************************
	;*/
	typedef unsigned char 		boolean;		/*�޷��ַ��� 				*/
	typedef unsigned char 		uint8; 			/*�޷��ַ��� 		Unsigned  8 bit quantity                            */
	typedef signed 	 char 		int8; 			/*�ַ��� 				Signed    8 bit quantity                            */
	typedef unsigned short 		uint16; 		/*�޷������� 		Unsigned 16 bit quantity                            */
	typedef signed 	 short 		int16; 			/*������ 				Signed   16 bit quantity                            */
	typedef unsigned int 			uint32; 		/*�޷�32λ���� 	Unsigned 32 bit quantity                            */
	typedef signed 	 int 			int32; 			/*32λ���� 			Signed   32 bit quantity                            */
	typedef float 						fp32; 			/*�������� 			Single precision floating point                     */

	typedef unsigned char 		BYTE;				/*�޷��ַ��� 				*/
	typedef unsigned short 		WORD;				/*�޷������� 				*/
	typedef unsigned long 		DWORD;			/*�޷������� 				*/
	typedef unsigned int 			BOOL;				/*�޷��ַ��� 				*/

	typedef unsigned char 		uint8_t; 		/*�޷��ַ��� 		Unsigned  8 bit quantity                            */
	typedef signed 	 char 		int8_t; 		/*�ַ��� 				Signed    8 bit quantity                            */
	typedef unsigned short 		uint16_t; 	/*�޷������� 		Unsigned 16 bit quantity                            */
	typedef signed 	 short 		int16_t; 		/*������ 				Signed   16 bit quantity                            */
	typedef unsigned int 			uint32_t; 	/*�޷�32λ���� 	Unsigned 32 bit quantity                            */
	typedef signed 	 int 			int32; 			/*32λ���� 			Signed   32 bit quantity                            */


	typedef unsigned char 		u_int8_t; 	/*�޷��ַ��� 		Unsigned  8 bit quantity                            */
	typedef unsigned short 		u_int16_t; 	/*�޷������� 		Unsigned 16 bit quantity                            */
	typedef unsigned int 			u_int32_t; 	/*�޷�32λ���� 	Unsigned 32 bit quantity                            */
	typedef signed 	 int 			int32_t; 		/*32λ���� 			Signed 	 32 bit quantity                            */
	typedef __int64 					int64_t;		/*64λ���� 					*/
	typedef unsigned __int64 	uint64_t;		/*64λ�޷����� 			*/
	typedef unsigned short 		u_short;
	

	typedef unsigned char 		u_char;			/*�޷��ַ��� 				*/

	typedef unsigned char 		u8_t;				/*�޷��ַ��� 				*/
	typedef signed 	 char 		s8_t;				/*�ַ��� 						*/
	typedef unsigned short 		u16_t;			/*�޷������� 				*/
	typedef signed 	 short 		s16_t;			/*�޷������� 				*/
	typedef unsigned int 			u32_t;			/*�޷�32λ���� 			*/
	typedef signed 	 int 			s32_t;			/*32λ���� 					*/

//	typedef uint32_t 					u32;				/*�޷�32λ���� 			*/
//	typedef uint16_t 					u16;				/*�޷������� 				*/
//	typedef uint8_t 					u8;					/*�޷��ַ��� 				*/

	typedef unsigned short 		__le16;			/*�޷������� 				*/
	typedef unsigned int 			__le32;			/*�޷�32λ���� 			*/
	typedef unsigned __int64 	__le64;			/*64λ�޷����� 			*/

	typedef unsigned short		__be16;			/*�޷������� 				*/
	typedef unsigned int 			__be32;			/*�޷�32λ���� 			*/
	//typedef unsigned __int64  __be64;
	typedef unsigned short 		__u16;			/*�޷������� 				*/
	typedef unsigned char 		__u8;				/*�޷��ַ��� 				*/
	typedef unsigned __int64 	u64; 				/*64λ�޷����� 			*/
	typedef unsigned int 			__u32;			/*�޷�32λ���� 			*/

	typedef signed char 			__s8;				/*�ַ��� 						*/
	typedef signed char 			s8;					/*�ַ��� 						*/
	typedef signed short 			s16;				/*������ 						*/
	typedef signed int 				s32;				/*32λ���� 					*/
	//typedef  signed __int64  s64;

	typedef unsigned int 			size_t;			/*�޷�32λ���� 			*/

	typedef unsigned char			UINT8;			/*�޷��ַ��� 				*/
	typedef unsigned short		UINT16;			/*�޷������� 				*/
	typedef unsigned int			UINT32;			/*�޷�32λ���� 			*/
	typedef unsigned __int64	UINT64;			/*64λ�޷����� 			*/

	typedef char							INT8;				/*�ַ��� 						*/
	typedef short							INT16;			/*������ 						*/
	typedef int								INT32;			/*32λ���� 					*/
	typedef __int64						INT64;			/*64λ�޷����� 			*/

		
	typedef unsigned char 		UCHAR;			/*�޷��ַ��� 				*/
	typedef unsigned short 		USHORT;			/*�޷������� 				*/
	typedef unsigned int 			UINT;				/*�޷�32λ���� 			*/
	typedef unsigned long 		ULONG;			/*�޷������� 				*/

	typedef unsigned char 		*PUINT8;		/*�޷��ַ���ָ�� 		*/
	typedef unsigned short		*PUINT16;		/*�޷�������ָ�� 		*/
	typedef unsigned int 	 		*PUINT32;		/*�޷�32λ����ָ�� 	*/
	typedef unsigned __int64 	*PUINT64;		/*64λ�޷�����ָ�� 	*/
	typedef int 							*PINT32;		/*32λ����ָ�� 			*/
	typedef long long 				*PINT64;		/*64λ�޷�����ָ�� 	*/

	/* modified for fixing compile warning on Sigma 8634 platform */
	typedef char STRING;

	typedef signed char 			CHAR;				/*�ַ��� 						*/

	typedef signed short 			SHORT;			/*������ 						*/
	typedef signed int 				INT;				/*32λ���� 					*/
	typedef signed long 			LONG;				/*������ 						*/
	typedef __int64 					LONGLONG;		/*64λ�޷����� 			*/

	typedef unsigned __int64 	ULONGLONG;	/*64λ�޷����� 			*/

	typedef unsigned char 		BOOLEAN;		/*�޷��ַ��� 				*/

	typedef void 		VOID;

	typedef char 						 *PSTRING;		/*�ַ���ָ�� 				*/
	typedef VOID 						 *PVOID;			/*��ָ�� 						*/
	typedef CHAR 						 *PCHAR;			/*�ַ���ָ�� 				*/
	typedef UCHAR 					 *PUCHAR;			/*�޷��ַ���ָ�� 		*/
	typedef USHORT 					 *PUSHORT;		/*�޷�������ָ�� 		*/
	typedef LONG 						 *PLONG;			/*������ָ�� 				*/
	typedef ULONG 					 *PULONG;			/*�޷������� 				*/
	typedef UINT 						 *PUINT;			/*�޷�32λ����ָ�� 	*/

	#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
	
	#define BITS_PER_LONG 32

	#define BIT(nr)						(1UL << (nr))
	#define BIT_MASK(nr)			(1UL << ((nr) % BITS_PER_LONG))
	#define BIT_WORD(nr)			((nr) / BITS_PER_LONG)
	#define BITS_PER_BYTE			8
	#define BITS_TO_LONGS(nr)	DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))

	typedef enum
	{
		FALSE = 0, TRUE = !FALSE
	} bool;

	#define NETDEV_ALIGN				32
	#define ETHTOOL_BUSINFO_LEN	32

	typedef unsigned gfp_t;
	typedef unsigned fmode_t;

	#define __packed	__attribute__((packed))	//ʹ�������߽ṹ���Աʹ����С�Ķ��뷽ʽ, ���Ա���һ�ֽڶ���, ������λ����

	#define false FALSE
	#define true  TRUE


	#ifndef NULL
	#define NULL    ((void *)0)
	#endif

	#ifdef __cplusplus
}

#endif

#endif

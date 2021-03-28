#ifndef __BT_USER_H__
#define __BT_USER_H__

#include "bsp.h"
#include "api.h"
#include "debug.h"

#define CONFIG_BT_L2CAP


#define mdelay sleep	//�ӳ� ms

//����ͷ
struct list_head {
	struct list_head *next, *prev;
};
//˫����
struct list {
	struct list *next, *prev;
};

#define cpu_to_le16(X) 		(X)
#define __cpu_to_le16(X) 	(X)
#define cpu_to_le32(X) 		(X)
#define __cpu_to_le32(X) 	(X)
#define __le16_to_cpu(X)	(X)
#define le16_to_cpu(X)		(X)
#define __le32_to_cpu(X)	(X)
#define le32_to_cpu(X)		(X)
#define IN
#define OUT
#define INOUT

#define POISON_POINTER_DELTA 0

#define ZEROSIZE	1

#define ASSERT assert

#define EXPORT_SYMBOL(x)

#define rcu_read_lock()
#define rcu_read_unlock()

#define rcu_dereference(x) x

#define get_random_bytes os_get_random

#define kmalloc_node_track_caller(x,y,z) mem_malloc(x)

#define kmem_cache_free(x,y) mem_free(y)

#define NUMA_NO_NODE 1
#define ETH_ALEN		6
#define IFNAMSIZ 		16

typedef u16  __sum16;	//16λ�޷���
typedef u32  __wsum;	//32λ�޷���

typedef unsigned short	sa_family_t;	//�޷�������

#define spinlock_t  int	//����

#define LIST_POISON1  ((void *) 0x00100100)
#define LIST_POISON2  ((void *) 0x00200200)

void __list_add(struct list_head *new,
								struct list_head *prev,
								struct list_head *next);
void list_add(struct list_head *new, struct list_head *head);
void list_add_tail(struct list_head *new, struct list_head *head);
void list_del(struct list_head *entry);

void INIT_LIST_HEAD(struct list_head *list);

#define URB_SHORT_NOT_OK				0x0001	/* report short reads as errors */
#define URB_ISO_ASAP						0x0002	/* iso-only, urb->start_frame
					 * ignored */
#define URB_NO_TRANSFER_DMA_MAP	0x0004	/* urb->transfer_dma valid on submit */
#define URB_NO_FSBR							0x0020	/* UHCI-specific */
#define URB_ZERO_PACKET					0x0040	/* Finish bulk OUT with short packet */
#define URB_NO_INTERRUPT				0x0080	/* HINT: no non-error interrupt
					 * needed */
#define URB_FREE_BUFFER					0x0100	/* Free transfer buffer with the URB */

/* The following flags are used internally by usbcore and HCDs */
#define URB_DIR_IN							0x0200	/*�豸������ Transfer from device to host */
#define URB_DIR_OUT							0				/*�������豸 Transfer from host to device */
#define URB_DIR_MASK						URB_DIR_IN	//���ݴ��䷽��

#define URB_DMA_MAP_SINGLE			0x00010000	/* Non-scatter-gather mapping */
#define URB_DMA_MAP_PAGE				0x00020000	/* HCD-unsupported S-G */
#define URB_DMA_MAP_SG					0x00040000	/* HCD-supported S-G */
#define URB_MAP_LOCAL						0x00080000	/* HCD-local-memory mapping */
#define URB_SETUP_MAP_SINGLE		0x00100000	/* Setup packet DMA mapped */
#define URB_SETUP_MAP_LOCAL			0x00200000	/* HCD-local setup packet */
#define URB_DMA_SG_COMBINED			0x00400000	/* S-G entries were combined */
#define URB_ALIGNED_TEMP_BUFFER	0x00800000	/* Temp buffer was alloc'd */


#define os_alloc_mem(X, Y, Z)	(*(PUCHAR*)(Y) = (PUCHAR)kmalloc((Z), GFP_ATOMIC),\
		(*(PUCHAR*)(Y) == 0)?NDIS_STATUS_FAILURE:NDIS_STATUS_SUCCESS)



#define EXPORT_SYMBOL_GPL(x);	

#define msleep	mdelay			//�ӳ� ms

#define usleep	delay_us		//�ӳ� us

#define udelay	delay_us		//�ӳ� us

#define __user

#define get_user(X, Y)  	 ((X) = *(Y))
#define PAGE_SIZE	4096

#define HZ 100
/********* name = { &(name), &(name) } <=> name.next = &name; name.prev = &name;*********/
#define LIST_HEAD_INIT(name) { &(name), &(name) }
/*************** ��ʼ������ **************/
#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define test_bit(nr, addr)   (*addr & (1L << nr))		//���� nr λ��״̬

#define __set_bit(nr, addr)   *addr |=  (1L << nr)	//�� nr λ��һ
#define __clr_bit(nr, addr)   *addr &=  ~(1L << nr)	//�� nr λ����

#define set_bit 	__set_bit	//��λ
#define clear_bit __clr_bit	//����

#define msecs_to_jiffies(x)	(x/10)

#ifdef htons
#undef htons
#endif /* htons */
#ifdef htonl
#undef htonl
#endif /* htonl */
#ifdef ntohs
#undef ntohs
#endif /* ntohs */
#ifdef ntohl
#undef ntohl
#endif /* ntohl */

/*********** �� 16 λ x �ĵͰ�λ��߰�λ����λ�� ************/
#define lwip_htons(x)	((u16_t)((((x) & 0xff) << 8) | (((x)& 0xff00) >> 8)))
/*********** �� 16 λ x �ĵͰ�λ��߰�λ����λ�� ************/
#define lwip_ntohs(x)	lwip_htons(x)
/*********** �� 32 λ x �ĵͰ�λ��߰�λ���еͰ�λ���и߰�λ����λ�� ************/
#define	lwip_htonl(x)		\
	((u32_t)((((x) & 0xff)  			 << 24) |	\
					 (((x) & 0xff00) 			 << 8 ) |	\
					 (((x) & 0xff0000UL) 	 >> 8 ) |	\
					 (((x) & 0xff000000UL) >> 24)))

/*********** �� 32 λ x �ĵͰ�λ��߰�λ���еͰ�λ���и߰�λ����λ�� ************/
#define	lwip_ntohl(x) lwip_htonl(x)



#define htons(x) lwip_htons(x)	//�� 16 λ x �ĵͰ�λ��߰�λ����λ��
#define ntohs(x) lwip_ntohs(x)	//�� 16 λ x �ĵͰ�λ��߰�λ����λ��
#define htonl(x) lwip_htonl(x)	//�� 32 λ x �ĵͰ�λ��߰�λ���еͰ�λ���и߰�λ����λ��
#define ntohl(x) lwip_ntohl(x)	//�� 32 λ x �ĵͰ�λ��߰�λ���еͰ�λ���и߰�λ����λ��


#define 	BUG_ON(x) 			assert_param(!(x))

#define 	WARN_ON(x) 			assert_param(!(x))
#define 	BUILD_BUG_ON(x)	assert_param(!(x))

#define 	BUG()		p_err_fun			//��ӡ����

//#define RTMP_OS_MAX_SCAN_DATA_GET		RtmpOsMaxScanDataGet
#define vmalloc							mem_malloc	//�����ڴ�. ��֤������ڴ��������ַ�ռ�����������, ����Ĵ�С��Խϴ�
#define vfree								mem_free		//�ͷ��ڴ�. �ͷ��� vmalloc ����������ڴ�
#define simple_strtol				strtol

typedef u32_t socklen_t;	//�޷���32λ

extern int copy_from_user(void *dst, void *src, int size) ;	//�� src �и��� size �����ݵ� dst ��

#define copy_to_user  copy_from_user	//�� src �и��� size �����ݵ� dst ��

#define kmalloc(x,y) 	mem_malloc(x)	//�����ڴ�. ��֤������ڴ��������ַ����������, ���ܷ���Ĵ�С����

#define GFP_KERNEL	0	//�����Ľ���, ����˯��
#define GFP_ATOMIC 	0	//�����Ľ���, ������˯��

#define kcalloc(x,y,z)	mem_calloc(x, y)
#define kzalloc(x,y) 		mem_calloc(x, 1)
#define kfree						mem_free

#define inline __inline

#define unlikely
#define likely

#ifndef min
#define min(_a, _b)     (((_a) < (_b)) ? (_a) : (_b))	//�Ƚϵó���Сֵ
#endif

#ifndef max
#define max(_a, _b)     (((_a) > (_b)) ? (_a) : (_b))	//�Ƚϵó��ϴ�ֵ
#endif

#ifndef min_t
#define min_t(_t, _a, _b)     (((_t)(_a) < (_t)(_b)) ? (_t)(_a) : (_t)(_b))
#endif

#ifndef max_t
#define max_t(_t, _a, _b)     (((_t)(_a) > (_t)(_b)) ? (_t)(_a) : (_t)(_b))
#endif

#if !defined(FIONREAD) || !defined(FIONBIO)
#define IOCPARM_MASK    0x7fU           /* parameters must be < 128 bytes */
#define IOC_VOID        0x20000000UL    /* no parameters */
#define IOC_OUT         0x40000000UL    /* copy out parameters */
#define IOC_IN          0x80000000UL    /* copy in parameters */
#define IOC_INOUT       (IOC_IN|IOC_OUT)
                                        /* 0x20000000 distinguishes new &
                                           old ioctl's */
#define _IO(x,y)        (IOC_VOID|((x)<<8)|(y))

#define _IOR(x,y,t)     (IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define _IOW(x,y,t)     (IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))
#endif /* !defined(FIONREAD) || !defined(FIONBIO) */

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define  SOL_SOCKET  0xfff    /* options for socket level */


#define AF_UNSPEC       0
#define AF_INET         2
#define PF_INET         AF_INET
#define PF_UNSPEC       AF_UNSPEC

#define IPPROTO_IP      0
#define IPPROTO_TCP     6
#define IPPROTO_UDP     17
#define IPPROTO_UDPLITE 136

/* Flags we can use with send and recv. */
#define MSG_PEEK       0x01    /* Peeks at an incoming message */
#define MSG_WAITALL    0x02    /* Unimplemented: Requests that the function block until the full amount of data requested can be returned */
#define MSG_OOB        0x04    /* Unimplemented: Requests out-of-band data. The significance and semantics of out-of-band data are protocol-specific */
#define MSG_DONTWAIT   0x08    /* Nonblocking i/o for this operation only */
#define MSG_MORE       0x10    /* Sender will send more */


/***** ��ȡ member ��type �����е�ƫ�Ƶ�ַ, ��ת��Ϊ long���� ******
**1. ((type *) 0) �� 0 ת��Ϊtype ���͵�ָ��
**2. ((type *) 0)->member ���ʽṹ�е����ݳ�Ա
**3. &((type *) 0)->member) ȡ�����ݳ�Ա�ĵ�ַ; ���ʵ���൱�ڻ�ȡ����
**member��Ա����������ڽṹ���ƫ��, Ҳ�������ڶ�Ӧ�ṹ���е�λ��
**4. (long) &((type *) 0)->member ���ת������. ����֮�����ڽ�0 ת����(type *),
**�ṹ���ڴ�ռ��׵�ַ0 ��Ϊ��ʼ��ַ, ���Ա��ַ��ȻΪƫ�Ƶ�ַ
*/
#ifndef offsetof
#define offsetof(type, member) ((long) &((type *) 0)->member)	//��ȡ��Ա member �ڽṹ�� type ��ƫ����
#endif

/***** ���ذ��� ptrָ��ı���member ���ڵ� type���ͽṹ���� ��ָ��,Ҳ���Ǵ�һ���ṹ�ĳ�Աָ���ҵ���������ָ�� *****
**1. ptr ��ָ������ʹ�õ�ĳ���ͱ���ָ��;
**2. type �ǰ��� ptr ָ��ı������͵Ľṹ����;
**3. member �� type �ṹ���еĳ�Ա, ������ ptr ָ��ı�������һ��
*/
#define container_of(ptr, type, member)  ((type *)((char *)ptr - offsetof(type,member)))

/***** ��� ptrָ��ı��� member ���ڵ� type���ͽṹ���� ��ָ�� *****/
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/***** ѭ������������ÿһ�� pos �� member ���� *****
** ��ʵ������һ�� for ѭ��, ���ô���� pos ��Ϊѭ������, �ӱ�ͷ head ��ʼ,
** �������(next ����)�ƶ� pos, ֱ���ֻص� head
*/
#define list_for_each_entry(type, pos, head, member)	\
	for (pos = list_entry((head)->next, type, member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.next, type, member))
	     
/***** ѭ����������, ���Ҫɾ�����, ������������� *****/
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

/***** ѭ����������, ���ɾ�����, ����ʹ��������� *****/
#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)	

/***** ���ܺ�list_for_each_entry() ��ͬ, ֻ�������������ʵ�ֱ߱�����ɾ���Ĳ��� *****/
#define list_for_each_entry_safe(type, pos, n, head, member)			\
	for (pos = list_entry((head)->next, type, member),	\
		n = list_entry(pos->member.next, type, member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, type, member))
	     
/***** ��������е�һ���ֽ����ڽṹ����׵�ַ *****/
#define list_first_entry(ptr, type, member) \
			list_entry((ptr)->next, type, member)

#define time_after(a,b)		\
	 ((long)(b) - (long)(a) < 0)

static inline int
list_empty(struct list *list)	//��������Ƿ�Ϊ��, true -- ��
{
	return list->next == list;
}

	 
#define time_before(a,b)	time_after(b,a)
		
typedef struct usb_device_id{
		UINT16 uVendorIDorClass;
		UINT16 uProductIDorSubClass;
}USB_DEVICE_ID;

#define USB_DEVICE(A,B) A,B
/********* �޾��嶯��. linux���������ĳ�ʼ��, ֻ���ڴ˱���ȥ��������� *********/
#define spin_lock_init(__lock)			\
do{                                 \
}while(0)
/********* ��ó���״̬�ֲ�������ȫ�ֱ��� *(__lock) �� *********/
#define spin_lock(__lock)				\
do{															\
	*(__lock) = local_irq_save(); \
}while(0)	
/********* �� *(__lock) �ָ�����״̬�� *********/
#define spin_unlock(__lock )		\
do{															\
	local_irq_restore(*(__lock));	\
}while(0)

#define spin_lock_bh 		spin_lock			//��ó���״̬�ֲ�������ȫ�ֱ���  ��
#define spin_unlock_bh 	spin_unlock		//��  �ָ�����״̬��

#define read_unlock 		spin_unlock		//��  �ָ�����״̬��
#define read_lock 			spin_lock			//��ó���״̬�ֲ�������ȫ�ֱ���  ��

#define read_lock_bh 		spin_lock			//��ó���״̬�ֲ�������ȫ�ֱ���  ��
#define read_unlock_bh 	spin_unlock		//��  �ָ�����״̬��
#define write_lock_bh 	spin_lock			//��ó���״̬�ֲ�������ȫ�ֱ���  ��
#define write_unlock_bh spin_unlock		//��  �ָ�����״̬��

typedef u32 dma_addr_t;

#define  MODULE_AUTHOR(X,Y);
#define  MODULE_VERSION(X);
#define  MODULE_DESCRIPTION(X);
#define  MODULE_LICENSE(X);
#define  MODULE_SUPPORTED_DEVICE(X);
#define  MODULE_DEVICE_TABLE(x, y);
#define  MODULE_FIRMWARE(x);
#define  module_param_named(A, B, C, D);
#define  MODULE_PARM_DESC(A, B);
#define module_param(A,B,C);

#define MAX_ERRNO	4095

#define IS_ERR_VALUE(x) unlikely((x) >= (unsigned long)-MAX_ERRNO)

static inline void *ERR_PTR(long error)
{
	return (void*)error;
}

static inline long PTR_ERR(const void *ptr)
{
	return (long)ptr;
}

static inline long IS_ERR(const void *ptr)
{
	return IS_ERR_VALUE((unsigned long)ptr);
}

static inline long IS_ERR_OR_NULL(const void *ptr)
{
	return !ptr || IS_ERR_VALUE((unsigned long)ptr);
}

#define USB_ENDPOINT_NUMBER_MASK	0x0f	/* in bEndpointAddress */
#define USB_ENDPOINT_DIR_MASK			0x80	/* ���䷽������ */

#define USB_ENDPOINT_SYNCTYPE				0x0c
#define USB_ENDPOINT_SYNC_NONE			(0 << 2)
#define USB_ENDPOINT_SYNC_ASYNC			(1 << 2)
#define USB_ENDPOINT_SYNC_ADAPTIVE	(2 << 2)
#define USB_ENDPOINT_SYNC_SYNC			(3 << 2)

#define USB_ENDPOINT_XFERTYPE_MASK	0x03	/*�˵��������� in bmAttributes */
#define USB_ENDPOINT_XFER_CONTROL		0			/*���ƶ˵� */
#define USB_ENDPOINT_XFER_ISOC			1			/*��ʱ�˵� */
#define USB_ENDPOINT_XFER_BULK			2			/*�����˵� */
#define USB_ENDPOINT_XFER_INT				3			/*�ж϶˵� */
#define USB_ENDPOINT_MAX_ADJUSTABLE	0x80

#define USB_DIR_OUT			0				/*����˵� to device */
#define USB_DIR_IN			0x80		/*����˵� to host */

/*
 * USB types, the second of three bRequestType fields
 */
#define USB_TYPE_MASK				(0x03 << 5)	/* ������������ */
#define USB_TYPE_STANDARD		(0x00 << 5)	/* ��׼���� */
#define USB_TYPE_CLASS			(0x01 << 5)	/* ������*/
#define USB_TYPE_VENDOR			(0x02 << 5)	/* �������� */
#define USB_TYPE_RESERVED		(0x03 << 5)	/* ���� */

/*
 * USB recipients, the third of three bRequestType fields
 */
#define USB_RECIP_MASK				0x1f
#define USB_RECIP_DEVICE			0x00	//�豸������
#define USB_RECIP_INTERFACE		0x01	//�ӿڽ�����
#define USB_RECIP_ENDPOINT		0x02	//�˵������
#define USB_RECIP_OTHER				0x03	//����������
/* From Wireless USB 1.0 ����USB1.0*/
#define USB_RECIP_PORT				0x04	//�˿ڽ�����
#define USB_RECIP_RPIPE				0x05	//

/*
 * Standard requests, for the bRequest field of a SETUP packet.
 *
 * These are qualified by the bRequestType field, so that for example
 * TYPE_CLASS or TYPE_VENDOR specific feature flags could be retrieved
 * by a GET_STATUS request.
 */
#define USB_REQ_GET_STATUS					0x00	//��ȡ״̬����
#define USB_REQ_CLEAR_FEATURE				0x01	//�����������
#define USB_REQ_SET_FEATURE					0x03	//������������
#define USB_REQ_SET_ADDRESS					0x05	//���õ�ַ����
#define USB_REQ_GET_DESCRIPTOR			0x06	//��ȡ����������
#define USB_REQ_SET_DESCRIPTOR			0x07	//��������������
#define USB_REQ_GET_CONFIGURATION		0x08	//��ȡ��������
#define USB_REQ_SET_CONFIGURATION		0x09	//������������
#define USB_REQ_GET_INTERFACE				0x0A	//��ȡ�ӿ�����
#define USB_REQ_SET_INTERFACE				0x0B	//���ýӿ�����
#define USB_REQ_SYNCH_FRAME					0x0C	//

#define USB_REQ_SET_ENCRYPTION			0x0D	/* Wireless USB */
#define USB_REQ_GET_ENCRYPTION			0x0E
#define USB_REQ_RPIPE_ABORT					0x0E
#define USB_REQ_SET_HANDSHAKE				0x0F
#define USB_REQ_RPIPE_RESET					0x0F
#define USB_REQ_GET_HANDSHAKE				0x10
#define USB_REQ_SET_CONNECTION			0x11
#define USB_REQ_SET_SECURITY_DATA		0x12
#define USB_REQ_GET_SECURITY_DATA		0x13
#define USB_REQ_SET_WUSB_DATA				0x14
#define USB_REQ_LOOPBACK_DATA_WRITE	0x15
#define USB_REQ_LOOPBACK_DATA_READ	0x16
#define USB_REQ_SET_INTERFACE_DS		0x17

/* The Link Power Management (LPM) ECN defines USB_REQ_TEST_AND_SET command,
 * used by hubs to put ports into a new L1 suspend state, except that it
 * forgot to define its number ...
 */

/*
 * USB feature flags are written using USB_REQ_{CLEAR,SET}_FEATURE, and
 * are read as a bit array returned by USB_REQ_GET_STATUS.  (So there
 * are at most sixteen features of each type.)  Hubs may also support a
 * new USB_REQ_TEST_AND_SET_FEATURE to put ports into L1 suspend.
 */
#define USB_DEVICE_SELF_POWERED		0	/*�豸�Թ��� (read only) */
#define USB_DEVICE_REMOTE_WAKEUP	1	/*�豸Զ�̻��� dev may initiate wakeup */
#define USB_DEVICE_TEST_MODE			2	/*�豸����ģʽ (wired high speed only) */
#define USB_DEVICE_BATTERY				2	/* (wireless) */
#define USB_DEVICE_B_HNP_ENABLE		3	/* (otg) dev may initiate HNP */
#define USB_DEVICE_WUSB_DEVICE		3	/* (wireless)*/
#define USB_DEVICE_A_HNP_SUPPORT	4	/* (otg) RH port supports HNP */
#define USB_DEVICE_A_ALT_HNP_SUPPORT	5	/* (otg) other RH port does */
#define USB_DEVICE_DEBUG_MODE			6	/* (special devices only) */

/*
 * Test Mode Selectors
 * See USB 2.0 spec Table 9-7
 */
#define	TEST_J				1
#define	TEST_K				2
#define	TEST_SE0_NAK	3
#define	TEST_PACKET		4
#define	TEST_FORCE_EN	5

/*
 * New Feature Selectors as added by USB 3.0
 * See USB 3.0 spec Table 9-6
 */
#define USB_DEVICE_U1_ENABLE		48	/* dev may initiate U1 transition */
#define USB_DEVICE_U2_ENABLE		49	/* dev may initiate U2 transition */
#define USB_DEVICE_LTM_ENABLE		50	/* dev may send LTM */
#define USB_INTRF_FUNC_SUSPEND	0		/* function suspend */

#define USB_INTR_FUNC_SUSPEND_OPT_MASK	0xFF00

#define USB_ENDPOINT_HALT				0		/* IN/OUT will STALL */

/* Bit array elements as returned by the USB_REQ_GET_STATUS request. */
#define USB_DEV_STAT_U1_ENABLED		2	/* transition into U1 state */
#define USB_DEV_STAT_U2_ENABLED		3	/* transition into U2 state */
#define USB_DEV_STAT_LTM_ENABLED	4	/* Latency tolerance messages */

/*-------------------------------------------------------------------------*/

/*
 * STANDARD DESCRIPTORS ... as returned by GET_DESCRIPTOR, or
 * (rarely) accepted by SET_DESCRIPTOR.
 *
 * Note that all multi-byte values here are encoded in little endian
 * byte order "on the wire".  Within the kernel and when exposed
 * through the Linux-USB APIs, they are not converted to cpu byte
 * order; it is the responsibility of the client code to do this.
 * The single exception is when device and configuration descriptors (but
 * not other descriptors) are read from usbfs (i.e. /proc/bus/usb/BBB/DDD);
 * in this case the fields are converted to host endianness by the kernel.
 */

/*
 * Descriptor types ... USB 2.0 spec table 9.5
 */
#define USB_DT_DEVICE							0x01	//�豸������
#define USB_DT_CONFIG							0x02	//����������
#define USB_DT_STRING							0x03	//�ַ���������
#define USB_DT_INTERFACE					0x04	//�ӿ�������
#define USB_DT_ENDPOINT						0x05	//�˵�������
#define USB_DT_DEVICE_QUALIFIER		0x06	//
#define USB_DT_OTHER_SPEED_CONFIG	0x07	//
#define USB_DT_INTERFACE_POWER		0x08	//
/* these are from a minor usb 2.0 revision (ECN) */
#define USB_DT_OTG								0x09
#define USB_DT_DEBUG							0x0a
#define USB_DT_INTERFACE_ASSOCIATION	0x0b
/* these are from the Wireless USB spec */
#define USB_DT_SECURITY						0x0c
#define USB_DT_KEY								0x0d
#define USB_DT_ENCRYPTION_TYPE		0x0e
#define USB_DT_BOS								0x0f
#define USB_DT_DEVICE_CAPABILITY	0x10
#define USB_DT_WIRELESS_ENDPOINT_COMP	0x11
#define USB_DT_WIRE_ADAPTER				0x21
#define USB_DT_RPIPE							0x22
#define USB_DT_CS_RADIO_CONTROL		0x23
/* From the T10 UAS specification */
#define USB_DT_PIPE_USAGE					0x24
/* From the USB 3.0 spec */
#define	USB_DT_SS_ENDPOINT_COMP		0x30

/* Conventional codes for class-specific descriptors.  The convention is
 * defined in the USB "Common Class" Spec (3.11).  Individual class specs
 * are authoritative for their usage, not the "common class" writeup.
 */
#define USB_DT_CS_DEVICE			(USB_TYPE_CLASS | USB_DT_DEVICE)
#define USB_DT_CS_CONFIG			(USB_TYPE_CLASS | USB_DT_CONFIG)
#define USB_DT_CS_STRING			(USB_TYPE_CLASS | USB_DT_STRING)
#define USB_DT_CS_INTERFACE		(USB_TYPE_CLASS | USB_DT_INTERFACE)
#define USB_DT_CS_ENDPOINT		(USB_TYPE_CLASS | USB_DT_ENDPOINT)

/* All standard descriptors have these 2 fields at the beginning */
struct usb_descriptor_header {
	__u8  bLength;
	__u8  bDescriptorType;
} __packed;	//usb������ͷ�� -- һ�ֽڶ���


/*-------------------------------------------------------------------------*/

/* USB_DT_DEVICE: Device descriptor */
struct usb_device_descriptor {
	__u8  bLength;
	__u8  bDescriptorType;

	__le16 bcdUSB;
	__u8  bDeviceClass;
	__u8  bDeviceSubClass;
	__u8  bDeviceProtocol;
	__u8  bMaxPacketSize0;
	__le16 idVendor;
	__le16 idProduct;
	__le16 bcdDevice;
	__u8  iManufacturer;
	__u8  iProduct;
	__u8  iSerialNumber;
	__u8  bNumConfigurations;
} __packed;	//usb�豸������ -- һ�ֽڶ���

#define USB_DT_DEVICE_SIZE		18


/*
 * Device and/or Interface Class codes
 * as found in bDeviceClass or bInterfaceClass
 * and defined by www.usb.org documents
 * USB�豸���ͱ���
 */
#define USB_CLASS_PER_INTERFACE		0	/* for DeviceClass */
#define USB_CLASS_AUDIO						1
#define USB_CLASS_COMM						2
#define USB_CLASS_HID							3
#define USB_CLASS_PHYSICAL				5
#define USB_CLASS_STILL_IMAGE			6
#define USB_CLASS_PRINTER					7
#define USB_CLASS_MASS_STORAGE		8
#define USB_CLASS_HUB							9
#define USB_CLASS_CDC_DATA				0x0a
#define USB_CLASS_CSCID						0x0b	/* chip+ smart card */
#define USB_CLASS_CONTENT_SEC			0x0d	/* content security */
#define USB_CLASS_VIDEO						0x0e
#define USB_CLASS_WIRELESS_CONTROLLER	0xe0
#define USB_CLASS_MISC						0xef
#define USB_CLASS_APP_SPEC				0xfe
#define USB_CLASS_VENDOR_SPEC			0xff

#define USB_SUBCLASS_VENDOR_SPEC	0xff

struct usb_ctrlrequest {
	__u8 bRequestType;
	__u8 bRequest;
	__le16 wValue;
	__le16 wIndex;
	__le16 wLength;
} __packed; //usb�������� -- һ�ֽڶ���

static inline u16 __get_unaligned_memmove16(const void *p)
{
	u16 tmp;
	memmove(&tmp, p, 2);
	return tmp;
}

static inline u32 __get_unaligned_memmove32(const void *p)
{
	u32 tmp;
	memmove(&tmp, p, 4);
	return tmp;
}

static inline u64 __get_unaligned_memmove64(const void *p)
{
	u64 tmp;
	memmove(&tmp, p, 8);
	return tmp;
}

static inline void __put_unaligned_memmove16(u16 val, void *p)
{
	memmove(p, &val, 2);
}

static inline void __put_unaligned_memmove32(u32 val, void *p)
{
	memmove(p, &val, 4);
}

static inline void __put_unaligned_memmove64(u64 val, void *p)
{
	memmove(p, &val, 8);
}

static inline u16 get_unaligned_le16(const void *p)
{
	return __get_unaligned_memmove16((const u8 *)p);
}

static inline u32 get_unaligned_le32(const void *p)
{
	return __get_unaligned_memmove32((const u8 *)p);
}

static inline u64 get_unaligned_le64(const void *p)
{
	return __get_unaligned_memmove64((const u8 *)p);
}

static inline void put_unaligned_le16(u16 val, void *p)
{
	__put_unaligned_memmove16(val, p);
}

static inline void put_unaligned_le32(u32 val, void *p)
{
	__put_unaligned_memmove32(val, p);
}

static inline void put_unaligned_le64(u64 val, void *p)
{
	__put_unaligned_memmove64(val, p);
}

extern u16 const crc16_table[256];

static inline u16 crc16_byte(u16 crc, const u8 data)
{
	return (crc >> 8) ^ crc16_table[(crc ^ data) & 0xff];
}

u16 crc16(u16 crc, u8 const *buffer, size_t len);

//int verify_iovec(struct msghdr *m, struct iovec *iov, struct sockaddr *address, int mode);


#endif

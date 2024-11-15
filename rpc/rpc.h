/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) 2019 KapaXL (kapa.xl@outlook.com)
 *
 * RPC structures and macros between REE and TEE
 *
 * Current implementation follows GlobalPlatform Style...
 * Current implementation partially follows SMCCC Style...
 */

#ifndef _TEE_RPC_H
#define _TEE_RPC_H

#define RPC_FASTCALL            (1u << 31)
#define RPC_IS_FASTCALL(fn)     ((fn) & RPC_FASTCALL)
#define RPC_FUNC_MASK           (0xFFFF | RPC_FASTCALL)

/* REE->TEE Fast calls */
#define RPC_VERSION             (0x0000 | RPC_FASTCALL) /* PSCI_0_2_FN_PSCI_VERSION */
#define RPC_CPU_SUSPEND         (0x0001 | RPC_FASTCALL) /* PSCI_0_2_FN_CPU_SUSPEND - unuse */
#define RPC_CPU_OFF             (0x0002 | RPC_FASTCALL) /* PSCI_0_2_FN_CPU_OFF */
#define RPC_CPU_ON              (0x0003 | RPC_FASTCALL) /* PSCI_0_2_FN_CPU_ON */
#define RPC_KILL_SECONDARY      (0x0004 | RPC_FASTCALL) /* PSCI_0_2_FN_AFFINITY_INFO ? */
#define RPC_MIGRATE             (0x0005 | RPC_FASTCALL) /* PSCI_0_2_FN_MIGRATE - unuse */
#define RPC_MIGRATE_INFO_TYPE   (0x0006 | RPC_FASTCALL)
#define RPC_MIGRATE_INFO_UP_CPU (0x0007 | RPC_FASTCALL)
#define RPC_SYSTEM_OFF          (0x0008 | RPC_FASTCALL)
#define RPC_SYSTEM_RESET        (0x0009 | RPC_FASTCALL)
#define RPC_SYSTEM_SUSPEND      (0x000E | RPC_FASTCALL)
#define RPC_SET_SUSPEND_MODE    (0x000F | RPC_FASTCALL)

#define RPC_OS_VERSION          (0x0100 | RPC_FASTCALL)
#define RPC_SUPPORT_YIELD       (0x0101 | RPC_FASTCALL)
#define RPC_COMPLETE_TEE        (0x0102 | RPC_FASTCALL)

/* REE->TEE Yield calls */
#define RPC_OPEN_SESSION        1
#define RPC_INVOKE_SESSION      2
#define RPC_CLOSE_SESSION       3
#define RPC_FREE_SHM            4
#define RPC_REGISTER_SHM        5
#define RPC_UNREGISTER_SHM      6
#define RPC_CANCEL              7

/* TEE->REE RPC calls */
#define RPC_COMPLETE_REE        0
#define RPC_REETIME             1u
#define RPC_REEFS               2u
#define RPC_REENR               3u

#define TEE_PAGE_SIZE           (4096UL)

/*
 * REE<->TEE RPC call command
 */
struct rpc_cmd {
	/* function id */
	unsigned int id;

	/* size of the #shm or #data, could be zero */
	unsigned short size;

	/* interrupted or cancelled ? */
	char interrupted;

	/* return value */
	long ret;

	/*
	 * Non-NULL for caller to wait. Caller issues the rpc-call, and
	 * when the rpc-call needs a return to the caller, this param can be
	 * used for the REE/TEE OS to complete()/wakeup() the caller(waiter).
	 */
	unsigned long waiter;

	/* physical shared memory passed to callee, could be NULL */
	unsigned long shm;

	/* cmd data */
	unsigned long data[0];
};

/*
 * REE->TEE pages for GP SHM
 */
struct rpc_memref {
	uint64_t id;
	unsigned long pages;
	off_t offset;
	size_t size;
	size_t cnt;
};

/*
 * REE->TEE, TEE paramter entry, value or SHM union
 */
union rpc_tee_param {
	struct rpc_memref memref;

	struct {
		uint32_t a;
		uint32_t b;
	} value;
};

/*
 * REE->TEE Parameters for RPC session ops
 * RPC_XXXX_SESSION
 */
struct rpc_param {
	/* session id */
	int session_id;

	/* session cmd id */
	unsigned int cmd_id;

	/* origin of the return code */
	unsigned int ret_origin;

	uint32_t params_type;

	union rpc_tee_param params[4];

	/* target uuid */
	unsigned char uuid[16];

	/* client uuid */
	unsigned char clnt_uuid[16];
};

/*
 * TEE<->REE RPC ring CMD buffer definition
 */
struct rpc_ringbuf {
	unsigned int wr;
	unsigned int rd;
	unsigned char mem[0];
};

#endif

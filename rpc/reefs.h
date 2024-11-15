/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) 2019 KapaXL (kapa.xl@outlook.com)
 *
 * Define the structures and macros for REEFS rpc
 */

#ifndef _RPC_REEFS_H
#define _RPC_REEFS_H

/*
 * supplicant types
 */
#define SUPP_REEFS		 1
#define SUPP_MAX		 10

/*
 * REEFS functions
 */
#define REEFS_OPEN       1
#define REEFS_CLOSE      2
#define REEFS_READ       3
#define REEFS_WRITE      4
#define REEFS_SEEK       5
#define REEFS_UNLINK     6
#define REEFS_RENAME     7
#define REEFS_TRUNC      8
#define REEFS_MKDIR      9
#define REEFS_OPENDIR   10
#define REEFS_CLOSEDIR  11
#define REEFS_READDIR   12
#define REEFS_SEEKDIR   13
#define REEFS_RMDIR     14

struct reefs_cmd {
	int op;

	int flags;
	int fd;

	int ret;

	long len;

	char data[0];
};

struct reefs_dirent {
	unsigned long	d_off;
	unsigned short	d_reclen;
	unsigned char	d_type;
	char		d_name[1];
};

#endif

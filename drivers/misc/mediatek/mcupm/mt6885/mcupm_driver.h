/*
 * Copyright (C) 2016 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */
#ifndef __MCUPM_DEFINE_H__
#define __MCUPM_DEFINE_H__

/* MCUPM MBOX */
#define MCUPM_MBOX_SLOT_SIZE		0x4

#define MCUPM_PLT_SERV_SUPPORT		(1)
#define MCUPM_LOGGER_SUPPORT		(1)
#define MCUPM_COREDUMP_SUPPORT		(1)

#define SHAREMBOX_OFFSET_MCDI		0
#define SHAREMBOX_SIZE_MCDI		20
#define SHAREMBOX_OFFSET_TIMESTAMP	(SHAREMBOX_OFFSET_MCDI + \
					SHAREMBOX_SIZE_MCDI)
#define SHAREMBOX_NO_MCDI		3

#define SYS_TIMER_MBOX			SHAREMBOX_NO_MCDI
#define SYS_TIMER_MBOX_OFFSET_BASE	SHAREMBOX_OFFSET_TIMESTAMP
#define SYS_TIMER_MBOX_TICK_H		(SYS_TIMER_MBOX_OFFSET_BASE + 0)
#define SYS_TIMER_MBOX_TICK_L		(SYS_TIMER_MBOX_OFFSET_BASE + 1)
#define SYS_TIMER_MBOX_TS_H		(SYS_TIMER_MBOX_OFFSET_BASE + 2)
#define SYS_TIMER_MBOX_TS_L		(SYS_TIMER_MBOX_OFFSET_BASE + 3)
#define SYS_TIMER_MBOX_DEBUG_TS_H	(SYS_TIMER_MBOX_OFFSET_BASE + 4)
#define SYS_TIMER_MBOX_DEBUG_TS_L	(SYS_TIMER_MBOX_OFFSET_BASE + 5)

#define MCUPM_PLT_INIT			0x504C5401
#define MCUPM_PLT_LOG_ENABLE		0x504C5402

/* MCUPM RESERVED MEM */
#define MCUPM_RESERVED_DEBUG		(1)
#define MCUPM_PLT_LOGGER_BUF_LEN	0x100000
enum {
	MCUPM_MEM_ID = 0,
	NUMS_MCUPM_MEM_ID,
};

struct mcupm_reserve_mblock {
	u32 num;
	u64 start_phys;
	u64 start_virt;
	u64 size;
};

static struct mcupm_reserve_mblock mcupm_reserve_mblock[NUMS_MCUPM_MEM_ID] = {
	{
		.num = MCUPM_MEM_ID,
		.size = 0x100 + MCUPM_PLT_LOGGER_BUF_LEN,
		/* logger header + 1M log buffer */
	},
};

/* MCUPM LOGGER */
#ifdef MCUPM_PLT_LOGGER_BUF_LEN
/* use platform-defined buffer length */
#define BUF_LEN				MCUPM_PLT_LOGGER_BUF_LEN
#else
/* otherwise use default buffer length */
#define BUF_LEN				(1 * 1024 * 1024)
#endif
#define LBUF_LEN			(4 * 1024)
#define MCUPM_TIMER_TIMEOUT		(1 * HZ) /* 1 seconds*/
#define ROUNDUP(a, b)			(((a) + ((b)-1)) & ~((b)-1))
#define ENABLE				0x101
#define DISABLE				0x1

struct log_ctrl_s {
	unsigned int base;
	unsigned int size;
	unsigned int enable;
	unsigned int info_ofs;
	unsigned int buff_ofs;
unsigned int buff_size;
};

struct buffer_info_s {
	unsigned int r_pos;
	unsigned int w_pos;
};

/* MCUPM IPI define */
struct mcupm_ipi_data_s {
	unsigned int cmd;
	union {
		struct {
			unsigned int phys;
			unsigned int size;
		} ctrl;
		struct {
			unsigned int enable;
		} logger;
		struct {
			unsigned int mode;
		} ts;
	} u;
};

extern ssize_t mcupm_log_read(char __user *data, size_t len);
extern unsigned int mcupm_log_poll(void);
extern int mcupm_mbox_write(unsigned int mbox, unsigned int slot, void *buf,
				unsigned int len);
extern int mcupm_mbox_read(unsigned int mbox, unsigned int slot, void *buf,
			unsigned int len);
#endif
/*
 * Copyright (C) 2015 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#include <linux/compat.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/printk.h>


#include "mjc_kernel_driver.h"
#include "mjc_kernel_compat_driver.h"

#define MJCDBG(string, args...)	pr_debug("MJC [pid=%d]"string, current->tgid, ##args)

/* ************************************ */
/* IO control structure */
/* ************************************ */

/* See mjc_kernel_compat_driver.h for the definition of these structs */
struct compat_MJC_READ_REG_T {
	compat_ulong_t reg;
	compat_uint_t val;
	compat_uint_t mask;
};

struct compat_MJC_WRITE_REG_T {
	compat_ulong_t reg;
	compat_uint_t val;
	compat_uint_t mask;
};

struct compat_MJC_IOCTL_REG_INFO_T {
	compat_uint_t u4StructSize;
	compat_ulong_t ulRegPAddress;
	compat_ulong_t ulRegPSize;
};


#define MJC_IOC_MAGIC    'N'

#define COMPAT_MJC_READ_REG    _IOW(MJC_IOC_MAGIC, 0x02, struct compat_MJC_READ_REG_T)
#define COMPAT_MJC_WRITE_REG   _IOW(MJC_IOC_MAGIC, 0x03, struct compat_MJC_WRITE_REG_T)
#define COMPAT_MJC_REG_INFO    _IOW(MJC_IOC_MAGIC, 0x07, struct compat_MJC_IOCTL_REG_INFO_T)

/*****************************************************************************
 * FUNCTION
 *    compat_get_mjc_read_reg
 * DESCRIPTION
 *
 * PARAMETERS
 *    None.
 * RETURNS
 *    None.
 ****************************************************************************/
static int compat_get_mjc_read_reg(struct compat_MJC_READ_REG_T __user *data32,
				   struct MJC_READ_REG_T __user *data)
{
	compat_ulong_t reg;
	compat_uint_t val;
	compat_uint_t mask;
	int err;

	err = get_user(reg, &data32->reg);
	err |= put_user(reg, &data->reg);

	err |= get_user(val, &data32->val);
	err |= put_user(val, &data->val);

	err |= get_user(mask, &data32->mask);
	err |= put_user(mask, &data->mask);

	return err;
}

/*****************************************************************************
 * FUNCTION
 *    compat_put_mjc_read_reg
 * DESCRIPTION
 *
 * PARAMETERS
 *    None.
 * RETURNS
 *    None.
 ****************************************************************************/
static int compat_put_mjc_read_reg(struct compat_MJC_READ_REG_T __user *data32,
				   struct MJC_READ_REG_T __user *data)
{
	compat_ulong_t reg;
	compat_uint_t val;
	compat_uint_t mask;
	int err;

	err = get_user(reg, &data->reg);
	err |= put_user(reg, &data32->reg);

	err |= get_user(val, &data->val);
	err |= put_user(val, &data32->val);

	err |= get_user(mask, &data->mask);
	err |= put_user(mask, &data32->mask);

	return err;
}

/*****************************************************************************
 * FUNCTION
 *    compat_get_mjc_write_reg
 * DESCRIPTION
 *
 * PARAMETERS
 *    None.
 * RETURNS
 *    None.
 ****************************************************************************/
static int compat_get_mjc_write_reg(struct compat_MJC_WRITE_REG_T __user *data32,
				    struct MJC_WRITE_REG_T __user *data)
{
	compat_ulong_t reg;
	compat_uint_t val;
	compat_uint_t mask;
	int err;

	err = get_user(reg, &data32->reg);
	err |= put_user(reg, &data->reg);

	err |= get_user(val, &data32->val);
	err |= put_user(val, &data->val);

	err |= get_user(mask, &data32->mask);
	err |= put_user(mask, &data->mask);

	return err;
}

/*****************************************************************************
 * FUNCTION
 *    compat_get_mjc_reg_info
 * DESCRIPTION
 *
 * PARAMETERS
 *    None.
 * RETURNS
 *    None.
 ****************************************************************************/
static int compat_get_mjc_reg_info(struct compat_MJC_IOCTL_REG_INFO_T __user *data32,
				   struct MJC_IOCTL_REG_INFO_T __user *data)
{
	compat_uint_t u4StructSize;
	compat_ulong_t ulRegPAddress;
	compat_ulong_t ulRegPSize;
	int err;

	err = get_user(u4StructSize, &data32->u4StructSize);
	if (u4StructSize != sizeof(struct compat_MJC_IOCTL_REG_INFO_T)) {
		MJCDBG("[Error] compat_get_mjc_reg_info() structure size mismatch (%d, %ld)",
		       u4StructSize, sizeof(struct compat_MJC_IOCTL_REG_INFO_T));
		err = -EFAULT;
	}
	u4StructSize = sizeof(struct MJC_IOCTL_REG_INFO_T);
	err |= put_user(u4StructSize, &data->u4StructSize);

	err |= get_user(ulRegPAddress, &data32->ulRegPAddress);
	err |= put_user(ulRegPAddress, &data->ulRegPAddress);

	err |= get_user(ulRegPSize, &data32->ulRegPSize);
	err |= put_user(ulRegPSize, &data->ulRegPSize);

	return err;
}

/*****************************************************************************
 * FUNCTION
 *    compat_put_mjc_reg_info
 * DESCRIPTION
 *
 * PARAMETERS
 *    None.
 * RETURNS
 *    None.
 ****************************************************************************/
static int compat_put_mjc_reg_info(struct compat_MJC_IOCTL_REG_INFO_T __user *data32,
				   struct MJC_IOCTL_REG_INFO_T __user *data)
{
	/* compat_uint_t u4StructSize; */
	compat_ulong_t ulRegPAddress;
	compat_ulong_t ulRegPSize;
	int err;

	/* err = get_user(u4StructSize, &data->u4StructSize); */
	/* err |= put_user(u4StructSize, &data32->u4StructSize); */

	err = get_user(ulRegPAddress, &data->ulRegPAddress);
	err |= put_user(ulRegPAddress, &data32->ulRegPAddress);

	err |= get_user(ulRegPSize, &data->ulRegPSize);
	err |= put_user(ulRegPSize, &data32->ulRegPSize);

	return err;
}

/*****************************************************************************
 * FUNCTION
 *    compat_mjc_ioctls
 * DESCRIPTION
 *
 * PARAMETERS
 *    None.
 * RETURNS
 *    None.
 ****************************************************************************/
long compat_mjc_ioctl(struct file *pfile, unsigned int u4cmd, unsigned long u4arg)
{
	long ret = 0;

	if (!pfile->f_op || !pfile->f_op->unlocked_ioctl) {
		MJCDBG("[Error] compat_mjc_ioctl() null pointer");
		return -ENOTTY;
	}

	switch (u4cmd) {
	case COMPAT_MJC_READ_REG:
		{
			struct compat_MJC_READ_REG_T __user *data32;
			struct MJC_READ_REG_T __user *data;
			int err;

			data32 = compat_ptr(u4arg);
			data = compat_alloc_user_space(sizeof(*data));
			if (data == NULL) {
				MJCDBG
				    ("[Error] compat_mjc_ioctl() can't allocate user sapce");
				return -EFAULT;
			}

			err = compat_get_mjc_read_reg(data32, data);
			if (err) {
				MJCDBG
				    ("[Error] compat_mjc_ioctl(), compat_get_mjc_read_reg() error");
				return err;
			}

			ret = pfile->f_op->unlocked_ioctl(pfile, MJC_READ_REG, (unsigned long)data);

			err = compat_put_mjc_read_reg(data32, data);
			if (err) {
				MJCDBG
				    ("[Error] compat_mjc_ioctl(), compat_put_mjc_read_reg() error");
				return err;
			}
		}
		break;

	case COMPAT_MJC_WRITE_REG:
		{
			struct compat_MJC_WRITE_REG_T __user *data32;
			struct MJC_WRITE_REG_T __user *data;
			int err;

			data32 = compat_ptr(u4arg);
			data = compat_alloc_user_space(sizeof(*data));
			if (data == NULL) {
				MJCDBG
				    ("[Error] compat_mjc_ioctl() can't allocate user sapce");
				return -EFAULT;
			}

			err = compat_get_mjc_write_reg(data32, data);
			if (err) {
				MJCDBG
				    ("[Error] compat_mjc_ioctl(), compat_get_mjc_write_reg() error");
				return err;
			}

			ret =
			    pfile->f_op->unlocked_ioctl(pfile, MJC_WRITE_REG, (unsigned long)data);
		}
		break;

	case COMPAT_MJC_REG_INFO:
		{
			struct compat_MJC_IOCTL_REG_INFO_T __user *data32;
			struct MJC_IOCTL_REG_INFO_T __user *data;
			int err;

			data32 = compat_ptr(u4arg);
			data = compat_alloc_user_space(sizeof(*data));
			if (data == NULL) {
				MJCDBG
				    ("[Error] compat_mjc_ioctl() can't allocate user sapce");
				return -EFAULT;
			}

			err = compat_get_mjc_reg_info(data32, data);
			if (err) {
				MJCDBG
				    ("[Error] compat_mjc_ioctl(), compat_get_mjc_reg_info() error");
				return err;
			}

			ret = pfile->f_op->unlocked_ioctl(pfile, MJC_REG_INFO, (unsigned long)data);

			err = compat_put_mjc_reg_info(data32, data);
			if (err) {
				MJCDBG
				    ("[Error] compat_mjc_ioctl(), compat_put_mjc_reg_info() error");
				return err;
			}
		}
		break;

	case MJC_LOCKHW:
	case MJC_WAITISR:
	case MJC_WRITE_REG_TBL:
	case MJC_CLEAR_REG_TBL:
	case MJC_SOURCE_CLK:
		{
			ret =
			    pfile->f_op->unlocked_ioctl(pfile, u4cmd,
							(unsigned long)compat_ptr(u4arg));
		}
		break;

	default:
		MJCDBG("[ERROR] compat_mjc_ioctl() No such command 0x%x!!\n", u4cmd);
		break;
	}

	return ret;
}

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/file.h>
#include <linux/netdevice.h>
#include <linux/ioctl.h>
#include "../common/cmd.h"

#define DEV_ID 110
static int g_start = 1;
static char s_name[MAX_NAME_SIZE] = "hello_ioctl";

static int test_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int test_close(struct inode *inode, struct file *file)
{
    return 0;
}

static ssize_t test_read(struct file *filep, char *buff, size_t sz, loff_t *off)
{
    int msg_len = 0;
    static char msg[256];
    snprintf(msg, sizeof(msg), "start=%d, name=%s\n", g_start, s_name);
    msg_len = strlen(msg) + 1;
    if (!buff || sz < msg_len)
    {
        return -EINVAL;
    }
    if (*off)
    {
        return 0;
    }
    if (copy_to_user(buff, msg, msg_len))
    {
        return -EINVAL;
    }
    *off += msg_len;
    return msg_len;
}

static ssize_t test_write(struct file *filep, const char *buff, size_t sz, loff_t *off)
{
    printk("test_write: name=%s\n", s_name);
    return sz;
}

static long test_ioctl(struct file *file, unsigned int cmd, unsigned long args)
{
    int ret = 0;

    switch (cmd)
    {
        case IOC_TEST_START:
            g_start = 1;
            break;
        case IOC_TEST_STOP:
            g_start = 0;
            synchronize_rcu();  //一般用于同步，代码这里没有用
            break;
        case IOC_TEST_SET_NAME:
            if (copy_from_user(s_name, (void*)args, sizeof(s_name)) != 0)
            {
                ret = -EINVAL;
            }
            break;
        case IOC_TEST_GET_NAME:
            if (copy_to_user((void*)args, s_name, sizeof(s_name)) != 0)
            {
                ret = -EINVAL;
            }
            break;
        default:
            printk("invalid cmd %x\n", cmd);
            ret = -EINVAL;
    }
    return 0;
}

static struct file_operations drv_fops =
{
    owner:          THIS_MODULE,
    open:           test_open,
    release:        test_close,
    unlocked_ioctl: test_ioctl,
    read:           test_read,
    write:          test_write,
};

static int __init module_test_init(void)
{
    int ret = register_chrdev(DEV_ID, DEV_NAME, &drv_fops);
    if (ret < 0)
    {
        printk("register_chrdev failed.\n");
        return -1;
    }

    printk("module_test_init!\n");
    return 0;
}

static void __exit module_test_fini(void)
{
    printk("module_test_fini!\n");
    unregister_chrdev(DEV_ID, DEV_NAME);
}

module_init(module_test_init);
module_exit(module_test_fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("dtt");

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/err.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/uacces.h>

#define bufferSize 1024
int8_t deviceBuffer;
static int readIndex = 0;
static int writeIndex = 0;
static int dataSize = 0

    dev_t dev = 0;
static struct class *helloClass;
static struct cdev helloCdev;
static struct semaphore helloSemaphore;

static int driverOpen(struct inode *inode, struct file *file)
{
    pr_info("Hello | Open");
    return 0;
}

static int driverClose(struct inode *inode, struct file *file)
{
    pr_info("Hello | Close");
    return 0;
}

static ssize_t driverRead(struct file *file, char __user *userBuffer, size_t size, loff_t off)
{
    pr_info("Hello | Read");
    if (dataSize == 0)
    {
        pr_err("Hello | read error, no buffer available to read.");
        return -1;
    }

    down(&helloSemaphore);
    copy_to_user(userBuffer, deviceBuffer + readIndex, size);
    datasize -= size;
    readIndex = (readIndex + size) % bufferSize;
    up(&helloSemaphore);

    return size;
}

static ssize_t driverWrite(struct file *file, const char __user *userBuffer, size_t size, loff_t off)
{
    pr_info("Hello | Write");
    if (size > bufferSize - dataSize)
    {
        pr_err("Hello | write error, no buffer available to write.");
        return -1;
    }

    down(&helloSemaphore);
    copy_from_user(deviceBuffer + writeIndex, userBuffer, size);
    writeIndex = (writeIndex + size) % bufferSize;
    dataSize += size;
    up(&helloSemaphore);

    return size;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driverOpen,
    .release = driverClose,
    .read = driverRead,
    .write = driverWrite}

static int __init
helloInit(void)
{
    pr_info("Hello | Init");
    sema_init(&helloSemaphore, 1);
    return 0;
}

static void __exit helloExit(void)
{
    pr_info("Hello | Exit"); 
    return 0;
}

module_init(helloInit);
module_exit(helloExit);
MODULE_LICENSE("GPL");
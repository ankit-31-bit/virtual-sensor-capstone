#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/atomic.h>
#include <linux/string.h>

static atomic_t temperature = ATOMIC_INIT(25);

static ssize_t vsensor_read(struct file *file,
    char __user *buffer,
    size_t count, loff_t *position)
{
    char output[32];
    int length;

    length = scnprintf(output, sizeof(output), "%d\n",
        atomic_read(&temperature));

    return simple_read_from_buffer(buffer, count, position,
        output, length);
}

static ssize_t vsensor_write(struct file *file,
    const char __user *buffer,
    size_t count, loff_t *position)
{
    char input[32];
    int value;
    int result;

    if (count == 0)
        return 0;

    if (count >= sizeof(input))
        return -EINVAL;

    if (copy_from_user(input, buffer, count))
        return -EFAULT;

    if (memchr(input, '\0', count))
        return -EINVAL;

    input[count] = '\0';

    result = kstrtoint(input, 10, &value);

    if (result)
        return result;

    if (value < -40 || value > 125)
        return -ERANGE;

    atomic_set(&temperature, value);

    return count;
}

static const struct file_operations vsensor_operations = {
    .owner = THIS_MODULE,
    .read = vsensor_read,
    .write = vsensor_write,
    .llseek = noop_llseek,
};

static struct miscdevice vsensor_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "vsensor",
    .fops = &vsensor_operations,
    .mode = 0600,
};

static int __init vsensor_init(void)
{
    int result = misc_register(&vsensor_device);

    if (result)
        return result;

    pr_info("vsensor: registered; initial temperature 25 C\n");

    return 0;
}

static void __exit vsensor_exit(void)
{
    misc_deregister(&vsensor_device);
    pr_info("vsensor: removed\n");
}

module_init(vsensor_init);
module_exit(vsensor_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Virtual temperature sensor character device");

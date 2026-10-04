#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/init.h>

#define DEVICE_NAME "patient_monitor"

static int major;
static struct class *monitor_class;
static struct device *monitor_device;

static const char monitor_data[] =
    "Patient ID: P101\n"
    "Heart Rate: 78 BPM\n"
    "Temperature: 98.4 F\n"
    "SpO2: 98%\n"
    "Status: NORMAL\n";

static ssize_t device_read(struct file *file,
                           char __user *buffer,
                           size_t length,
                           loff_t *offset)
{
    return simple_read_from_buffer(
        buffer,
        length,
        offset,
        monitor_data,
        sizeof(monitor_data) - 1
    );
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = device_read,
};

static int __init monitor_init(void)
{
    major = register_chrdev(0, DEVICE_NAME, &fops);

    if (major < 0) {
        printk(KERN_ERR "Patient Monitor: registration failed\n");
        return major;
    }

    monitor_class = class_create(DEVICE_NAME);

    if (IS_ERR(monitor_class)) {
        unregister_chrdev(major, DEVICE_NAME);
        return PTR_ERR(monitor_class);
    }

    monitor_device = device_create(
        monitor_class,
        NULL,
        MKDEV(major, 0),
        NULL,
        DEVICE_NAME
    );

    if (IS_ERR(monitor_device)) {
        class_destroy(monitor_class);
        unregister_chrdev(major, DEVICE_NAME);
        return PTR_ERR(monitor_device);
    }

    printk(KERN_INFO "Patient Monitor Driver Loaded\n");

    return 0;
}

static void __exit monitor_exit(void)
{
    device_destroy(monitor_class, MKDEV(major, 0));
    class_destroy(monitor_class);
    unregister_chrdev(major, DEVICE_NAME);

    printk(KERN_INFO "Patient Monitor Driver Removed\n");
}

module_init(monitor_init);
module_exit(monitor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hospital Management Project");
MODULE_DESCRIPTION("Simulated Patient Monitor Character Device Driver");

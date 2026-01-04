/*                                                              big-kernel-lock
ioctl ---> sys_ioctl(sys fs call)--> do_ioctl(kernel function)----------------------->
                                                                    unlock
        -->fops-->ioctl(kernel instanse ) ------>char_dev_ioctl()                                                           
*/

/*
open()--->
*/
/*
write()-->
*/
/*
cdev_add() registers a character device with the kernel,
 linking the struct cdev and its file_operations to a device number.()-->

 alloc_chrdev_region() dynamically allocates a major number; 
 register_chrdev_region() registers a specified major/minor range (static allocation).
 struct file_operations?
It defines the set of callback functions that implement device behavior for file-like operations.

kmalloc() allocates physically contiguous kernel memory suitable for DMA (depending on flags); 
kfree() frees it.
vmalloc() returns virtually contiguous but physically non-contiguous memory, 
with higher overhead.

*/


#include<linux/module.h>
#include<linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include<linux/device.h>
#include <linux/sysfs.h>




static struct my_data my_data{
    .i = -100;
    .x = 100;
    .s = "LINUX KERNEL"
};
static long char_dev_ioctl(struct file *fp, unsigned int cmd, unsigned long arg)
{

    /*first verify  arguments*/
    int size, rc, directions;
    void __user *ioargp = (void  __user*) arg;
    if(__IOC_TYPE (cmp) != VEDA_MAGIC ){
        printk(KERNEL_INFO "got invalid CMD %ld",cmd);
        return _EINVAL;
    }
    directions = _IOC_DIR(cmd);
    size = _IOC_SIZE(cmd);


    switch (directions)
    {
    case _IOC_WRITE:
        printk(KERNEL_INFO "reading from user data " );
        rc = copy_from_user(&mydata, ioargp, size);
        return rc;
        break;
    case _IOC_READ;
        break;
    default:
        break;
    }


}
/*
 this is function pointer this functions defined in linux/fs.h header file 
*/
static struct file_oprations char_dev_fops = {
    .owener = THIS_MODULE,
    .ioctl = char_dev_ioctl,
    .read = char_dev_read,
    .write = char_dev_write,
    .open = char_dev_open,
    .release = char_dev_release,
    .llseek = char_dev_lseek 
};

module_inti(char_dev_init)
module_exit(char_dev_exit)

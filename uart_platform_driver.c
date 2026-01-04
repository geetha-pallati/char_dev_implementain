#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

#define DRV_NAME "my_uart"

#define UART_TX      0x00
#define UART_RX      0x04
#define UART_STATUS  0x08
#define UART_CTRL    0x0C

static void __iomem *base;
static int irq;
static dev_t dev;
static struct cdev my_cdev;

/* ---------------- IRQ HANDLER ---------------- */
static irqreturn_t uart_irq_handler(int irq, void *dev_id)
{
    u32 status = ioread32(base + UART_STATUS);
    pr_info("UART IRQ: status=0x%x\n", status);
    return IRQ_HANDLED;
}

/* ---------------- FILE OPS ---------------- */
static ssize_t uart_write(struct file *file, const char __user *buf,
                          size_t len, loff_t *ppos)
{
    char c;
    if (copy_from_user(&c, buf, 1))
        return -EFAULT;

    iowrite32(c, base + UART_TX);
    return 1;
}

static ssize_t uart_read(struct file *file, char __user *buf,
                         size_t len, loff_t *ppos)
{
    u32 val = ioread32(base + UART_RX);
    if (copy_to_user(buf, &val, 1))
        return -EFAULT;

    return 1;
}

static struct file_operations uart_fops = {
    .owner  = THIS_MODULE,
    .read   = uart_read,
    .write  = uart_write,
};

/* ---------------- PROBE ---------------- */
static int my_uart_probe(struct platform_device *pdev)
{
    struct resource *res;
    int ret;

    /* Get memory region */
    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    base = devm_ioremap_resource(&pdev->dev, res);
    if (IS_ERR(base)) return PTR_ERR(base);

    /* Get IRQ */
    irq = platform_get_irq(pdev, 0);
    if (irq < 0) return irq;

    ret = devm_request_irq(&pdev->dev, irq, uart_irq_handler, 0,
                           DRV_NAME, NULL);
                           /*int devm_request_irq(struct device *dev, unsigned int irq,
                     irq_handler_t handler, unsigned long flags,
                     const char *name, void *dev_id);*/
    if (ret) return ret;

    /* Create character device */
    alloc_chrdev_region(&dev, 0, 1, DRV_NAME);
    cdev_init(&my_cdev, &uart_fops);
    cdev_add(&my_cdev, dev, 1);

    pr_info("UART driver probed\n");
    return 0;
}

/* ---------------- REMOVE ---------------- */
static int my_uart_remove(struct platform_device *pdev)
{
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev, 1);
    pr_info("UART driver removed\n");
    return 0;
}

/* ---------------- DT MATCH TABLE ---------------- */
static const struct of_device_id my_uart_dt_ids[] = {
    { .compatible = "myvendor,my-uart" },
    {}
};
MODULE_DEVICE_TABLE(of, my_uart_dt_ids);

/* ---------------- PLATFORM DRIVER ---------------- */
static struct platform_driver my_uart_driver = {
    .probe  = my_uart_probe,
    .remove = my_uart_remove,
    .driver = {
        .name           = DRV_NAME,
        .of_match_table = my_uart_dt_ids,
    },
};

module_platform_driver(my_uart_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Geetha Pallati");
MODULE_DESCRIPTION("Simple UART Platform Driver");

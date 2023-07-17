#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/hardirq.h>
#define TIMER_INTERVAL (2*HZ)
static struct timer_list s_timer;

static void timer_cb(unsigned long nParam)
{
    printk("jiffies:%lu, in_irq:%lu, in_softirq:%lu, interupt:%lu\n",
        jiffies, in_irq(), in_softirq(), in_interrupt());
    mod_timer(&s_timer, jiffies + TIMER_INTERVAL);
}

static int __init module_hello_init(void)
{
    printk("Hello World!\n");
    printk("in_irq:%lu, in_softirq:%lu, interupt:%lu\n",
        in_irq(), in_softirq(), in_interrupt());
    init_timer(&s_timer);
    s_timer.expires = jiffies + TIMER_INTERVAL;
    s_timer.data = 0;
    s_timer.function = timer_cb;
    add_timer(&s_timer);
    return 0;
}

static void __exit module_hello_fini(void)
{
    printk("Goodbye World!\n");
    del_timer(&s_timer);
}

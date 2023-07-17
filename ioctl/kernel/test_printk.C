
void test_print(void)
{
    printk(KERN_EMERG "0 emerg msg\n");
    printk(KERN_ALERT "1 alert msg\n");
    printk(KERN_CRIT "2 crit msg\n");
    printk(KERN_ERR "3 err msg\n");
    printk(KERN_WARNING "4 warning msg\n");
    printk(KERN_NOTICE "5 notice msg\n");
    printk(KERN_INFO "6 info msg\n");
    printk(KERN_DEBUG "7 debug msg\n");
    printk("Hello World!\n");
}
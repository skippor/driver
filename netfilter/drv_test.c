#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netdevice.h>
#include <linux/ip.h>
#include <linux/tcp.h>

static unsigned int test_hook(void *priv, struct sk_buff *skb,
                        const struct nf_hook_state *state)
{
    struct iphdr *iph;
    struct tcphdr *th;
    unsigned short dst_port;

    if (!skb)
        return NF_ACCEPT;

    iph = ip_hdr(skb);
    if (!iph)
        return NF_ACCEPT;

    if (iph->protocol != IPPROTO_TCP)
        return NF_ACCEPT;

    th = (struct tcphdr*)((void*)iph + (iph->ihl << 2));
    dst_port = ntohs(th->dest);
    if (dst_port == 80)
    {
        if (net_ratelimit())
            printk("Drop tcp port 80 packet.\n");
        return NF_DROP;
    }

    return NF_ACCEPT;
}

static struct nf_hook_ops test_ops =
{
    hook:      test_hook,
    pf:        PF_INET,
    hooknum:   NF_INET_PRE_ROUTING,
    priority:  NF_IP_PRI_FIRST,
};

static int __init module_test_init(void)
{
    printk("module_test_init\n");
    if (nf_register_net_hook(&init_net, &test_ops) < 0)
    {
        printk("register hook failed.\n");
        return -1;
    }
    return 0;
}

static void __exit module_test_fini(void)
{
    printk("module_test_fini\n");
    nf_unregister_net_hook(&init_net, &test_ops);
}

module_init(module_test_init);
module_exit(module_test_fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("dtt");

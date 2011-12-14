#include <linux/module.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Jay, <jay's email>");
MODULE_DESCRIPTION("SMEP test module");
MODULE_LICENSE("GPL");
MODULE_VERSION("Version-0.0.1");

static int __init smep_init(void)
{
	u64 *fetch;
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	
	printk(KERN_INFO "Loading smep test module...\n");

	fetch = __vmalloc(512, GFP_KERNEL | __GFP_HIGHMEM,
			  __pgprot(_PAGE_USER | __PAGE_KERNEL_EXEC));
//	printk("fetch %p\n", fetch);
	pgd = pgd_offset(current->active_mm, (u64)fetch);
	BUG_ON(pgd_none(*pgd));
//	printk("L4: %lx\n", *pgd);
	pud = pud_offset(pgd, (u64)fetch);
	BUG_ON(pud_none(*pud));
//	printk("L3: %lx\n", *pud);
	pmd = pmd_offset(pud, (u64)fetch);
	BUG_ON(pgd_none(*pgd));
//	printk("L2: %lx\n", *pmd);
	pte = pte_offset_map(pmd, (u64)fetch);
	BUG_ON(pte_none(*pte));
//	printk("L1: %lx\n", *pte);
	asm volatile ("call *%0":: "r"(fetch));
	vfree(fetch);
	return 0;
}

static void __exit smep_exit(void)
{
	printk(KERN_INFO "Goodbye, smep test module...\n");
}

module_init(smep_init)
module_exit(smep_exit)

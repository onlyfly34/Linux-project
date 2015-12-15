#include <linux/sched.h> //task_struct
#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/mm.h> //follow_page
#include <linux/fs.h>
#include <linux/highmem.h>
#include <asm/page.h> //page_to_pfn
#include <asm/pgtable.h>
#include <asm/io.h>
#include <asm/pgtable_types.h> //pgd,pud,pmd,pte
#include <linux/mm_types.h> //mm_struct, vm_area_struct
#include <linux/path.h>
#include <linux/slab.h> //kmalloc
#include <linux/string.h> //memset

asmlinkage void linux_survey_TT(int pid, char *info)
{

	struct task_struct *task;
	struct mm_struct *mm;
	struct vm_area_struct *point;
	struct path my_path;
	struct page *page;
	char *ret_ptr = NULL;
	char *tpath = NULL;
	const unsigned char *filename = NULL;
	tpath = (char*)kmalloc(512,0);   // allocate memory
	memset(tpath,'\0',512);  //set the value to memory
	unsigned long vm_start, vm_end;
	unsigned long vm_address;
	unsigned long pfn;

	printk("Hello world! !\n");

	for_each_process(task)		//travel all process
	{
	   if(pid == task->pid)		//Catch Process
	   {
	      mm = task->mm;
	      printk("%s[%d]\n", task->comm, task->pid);	//print the process name and pid

	      for(point = mm->mmap; point; point = point->vm_next)
	      {
		  printk("Virtual Mem: 0x%lx - 0x%lx ", point->vm_start, point->vm_end);

		  if(point->vm_file != NULL)
		  {
		    my_path = point->vm_file->f_path;
		    filename = point->vm_file->f_path.dentry->d_name.name;
		    ret_ptr = d_path(&my_path,tpath,512);
		    printk(" %s ",filename);
		    printk(" %s \n",ret_ptr);
		  }
	          else
		  {
		    printk("\n");
		  }

		  printk("page frame of the interval : ");
		  for(vm_address = point->vm_start; vm_address < point->vm_end; vm_address += 0x1000)
		  {
		    page = follow_page(point, vm_address, 0);
		    if(page == NULL) continue;
		    pfn = page_to_pfn(page);
		    printk("0x%x \n", pfn);
		  }
	      }
	   }
	}
}

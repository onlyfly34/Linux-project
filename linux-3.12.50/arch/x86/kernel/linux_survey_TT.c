#include <linux/sched.h> //task_struct
#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mm.h> //follow_page
#include <linux/fs.h>
#include <linux/highmem.h>
#include <asm/page.h> //page_to_pfn
#include <asm/pgtable.h>
#include <asm/io.h>
//#include <asm/pgtable_types.h> //pgd,pud,pmd,pte
#include <linux/mm_types.h> //mm_struct, vm_area_struct
#include <linux/path.h>
#include <linux/slab.h> //kmalloc
#include <linux/vmalloc.h> //vmalloc
#include <linux/string.h> //memset, strlen
#include <asm/uaccess.h> //copy_to_user
#define BUFFER_SIZE 900000

asmlinkage void sys_linux_survey_TT(int pid, char __user * result)
{

	struct task_struct *p;
	//struct mm_struct *mm;
	struct vm_area_struct *vm;
	struct path my_path;
	struct page *page;
	char *ret_ptr = NULL;
	char *tpath = NULL;
	const unsigned char *filename = NULL;
	tpath = (char*)kmalloc(512,0);    // allocate memory
	memset(tpath,'\0',512);    //clear memory to set 0
	//unsigned long vm_start, vm_end;
	unsigned long vm_address;
	unsigned long pfn;
	char *buff;    // assign buffer
	unsigned long co;

	buff = (char *)vmalloc(BUFFER_SIZE * sizeof(char));    //allocate memory
	memset(buff, 0, BUFFER_SIZE * sizeof(char));           //clear memory to set 0

	printk("Hello world! !\n");

	for_each_process(p)		//travel all process
	{
	   if(pid == p->pid)		//Catch Process
	   {
	      printk("%s[%d]\n", p->comm, p->pid);	//print the process name and pid

	      for(vm = p->mm->mmap; vm != NULL; vm = vm->vm_next)
	      {
		  printk("Virtual Mem: 0x%lx - 0x%lx ", vm->vm_start, vm->vm_end);

		  //change to string
		  sprintf(buff + strlen(buff), "Virtual Mem: %08lx-%08lx ", vm->vm_start, vm->vm_end);  //
		  if(vm->vm_file != NULL)
		  {
		    my_path = vm->vm_file->f_path;
		    filename = vm->vm_file->f_path.dentry->d_name.name;
		    ret_ptr = d_path(&my_path,tpath,512);
		    printk(" %s ",filename);
		    printk(" %s \n",ret_ptr);
		    sprintf(buff + strlen(buff), "%s %s\n", filename, ret_ptr);
		  }
	          else
		  {
		    printk("\n");
		  }

		  printk("page frame of the interval : ");
		  for(vm_address = vm->vm_start; vm_address < vm->vm_end; vm_address += 0x1000)  //one page = 4KB
		  {
		    page = follow_page(vm, vm_address, 0);
		    if(page == NULL) continue;
		    pfn = page_to_pfn(page);
		    printk("0x%lx \n", pfn);
		    sprintf(buff + strlen(buff), "page frame of the interval : %08lx \n", pfn);  //
		  }
		  //sprintf(buff + strlen(buff), "|");  //change to string
	      }

	      co = copy_to_user(result, buff, strlen(buff)+1);
	      if(co)
                printk(KERN_ALERT"Warning: %lu bytes Copy failed!\n", co);
	   }
	}
	vfree(buff);
}

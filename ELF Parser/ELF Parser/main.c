#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/mman.h>


char* ptypeChecker(int a){
    switch(a){
    case PT_NULL:
        return "PT_NULL";
        break;
    case PT_LOAD:
        return "PT_LOAD";
        break;
    case PT_DYNAMIC:
        return "PT_DYNAMIC";
        break;
    case PT_NOTE:
        return "PT_NOTE";
    case PT_INTERP:
        return "PT_INTERP";
        break;
    case PT_SHLIB:
        return "PT_SHLIB";
        break;
    case PT_PHDR:
        return "PT_PHDR";
        break;
    case PT_TLS:
        return "PT_TLS";
        break;
    case PT_NUM:
        return "PT_NUM";
        break;
    case PT_GNU_EH_FRAME:
        return "PT_GNU_EH_FRAME";
        break;
    case PT_GNU_STACK:
        return "PT_GNU_STACK";
        break;
    case PT_GNU_RELRO:
        return "PT_GNU_RELRO";
        break;

    }


}


int main(int argc, char ** argv)
{

    int fd, i;
    uint8_t *mem;
    struct stat st;
    char *StringTable, *interp;

    Elf32_Ehdr *ehdr;
    Elf32_Phdr *phdr;
    Elf32_Shdr *shdr;

    if (argc < 2) {

    printf("*Usage: %s <executable>\n", argv[0]);
    exit(0);
    }

    if((fd = open(argv[1], O_RDONLY)) < 0) {

    perror("open");
    exit(-1);
    }


    if(fstat(fd, &st) < 0){
    perror("fstat");
    exit(-1);
    }


    mem = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    if (mem == MAP_FAILED){
    perror("mmap");
    exit(-1);
    }

    ehdr = (Elf32_Ehdr*)mem;
    printf("Size of ELF32_Ehdr: 0x%08x \n\n",sizeof(Elf32_Ehdr));
    printf("ELF32_Ehdr *      : 0x%08x size %d \n", ehdr,sizeof(ehdr));
    printf("ehdr->e_ident     : 0x%08x size %d \n", ehdr->e_ident, sizeof(ehdr->e_ident));
    printf("ehdr->e_type      : 0x%08x size %d \n", ehdr->e_type, sizeof(ehdr->e_type));
    printf("ehdr->e_machine   : 0x%08x size %d \n", ehdr->e_machine, sizeof(ehdr->e_machine));
    printf("ehdr->e_version   : 0x%08x size %d \n", ehdr->e_version, sizeof(ehdr->e_version));
    printf("ehdr->e_entry     : 0x%08x size %d \n" , ehdr->e_entry, sizeof(ehdr->e_entry));
    printf("ehdr->e_phoff     : 0x%08x size %d \n", ehdr->e_phoff, sizeof(ehdr->e_phoff));
    printf("ehdr->e_shoff     : 0x%08x size %d \n", ehdr->e_shoff, sizeof(ehdr->e_shoff));
    printf("ehdr->e_flags     : 0x%08x size %d \n", ehdr->e_flags, sizeof(ehdr->e_flags));
    printf("ehdr->e_ehsize    : 0x%08x size %d \n" , ehdr->e_ehsize, sizeof(ehdr->e_ehsize));
    printf("ehdr->e_phentsize : 0x%08x size %d \n", ehdr->e_phentsize, sizeof(ehdr->e_phentsize));
    printf("ehdr->e_phnum     : 0x%08x size %d \n", ehdr->e_phnum, sizeof(ehdr->e_phnum));
    printf("ehdr->e_shentsize : 0x%08x size %d \n", ehdr->e_shentsize, sizeof(ehdr->e_phoff));
    printf("ehdr->e_shnum     : 0x%08x size %d \n", ehdr->e_shnum, sizeof(ehdr->e_shnum));
    printf("ehdr->e_shstrndx  : 0x%08x size %d \n\n", ehdr->e_shstrndx, sizeof(ehdr->e_shstrndx));

    phdr = (Elf32_Phdr*)&mem[ehdr->e_phoff];

    printf("Size of Elf32_Phdr: 0x%08x \n", sizeof(Elf32_Phdr));
    printf("%-16s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "p_type", "p_offset","p_vaddr","p_addr","p_filesz","tp_memsz","p_flags","p_align");


    for (i=0;i<ehdr->e_phnum;i++)
        printf("%-15s  0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x \n",ptypeChecker(phdr[i].p_type), phdr[i].p_type, phdr[i].p_offset, phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_filesz,phdr[i].p_memsz, phdr[i].p_flags, phdr[i].p_align);
//        printf("phdr->p_type      : 0x%08x size %d \n", phdr[i]->p_type, sizeof(phdr[i]->p_type));
//    }

    printf("\n\n");


/*phdr[i].p_align
    printf("phdr->p_type      : 0x%08x size %d \n", phdr->p_type, sizeof(phdr->p_type));
    printf("phdr->p_offset    : 0x%08x size %d \n", phdr->p_offset, sizeof(phdr->p_offset));
    printf("phdr->p_vaddr     : 0x%08x size %d \n", phdr->p_vaddr, sizeof(phdr->p_vaddr));
    printf("phdr->p_paddr     : 0x%08x size %d \n", phdr->p_paddr, sizeof(phdr->p_paddr));
    printf("phdr->p_filesz    : 0x%08x size %d \n", phdr->p_filesz, sizeof(phdr->p_filesz));
    printf("phdr->p_memsz     : 0x%08x size %d \n", phdr->p_memsz, sizeof(phdr->p_memsz));
    printf("phdr->p_flags     : 0x%08x size %d \n", phdr->p_flags, sizeof(phdr->p_flags));
    printf("phdr->p_align     : 0x%08x size %d \n\n", phdr->p_align, sizeof(phdr->p_align));

*/
    shdr = (Elf32_Shdr*)&mem[ehdr->e_shoff];

    printf("Size of Elf32_Shdr: 0x%08x \n", sizeof(Elf32_Shdr));
    printf("%-21s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-12s %-10s \n", \
    "Name", "sh_name", "sh_type","sh_flags","sh_addr","sh_offset","sh_size","sh_link","sh_info", "sh_addralign", "sh_entsize");

    StringTable = &mem[shdr[ehdr->e_shstrndx].sh_offset];

    //

    for (i=0;i<ehdr->e_shnum;i++)
        printf("%-21s 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x  0x%08x \n", &StringTable[shdr[i].sh_name], \
        shdr[i].sh_name,shdr[i].sh_type,shdr[i].sh_flags,shdr[i].sh_addr,shdr[i].sh_offset,shdr[i].sh_size,shdr[i].sh_link,shdr[i].sh_info,shdr[i].sh_addralign,shdr[i].sh_entsize);
//    printf("sdfsdf");

/*    printf("shdr->sh_name     : 0x%08x size %d \n", shdr->sh_name, sizeof(shdr[i].sh_name));
    printf("shdr->sh_name     : 0x%08x size %d \n", shdr->sh_type, sizeof(shdr[i].sh_type));
    printf("shdr->sh_flags    : 0x%08x size %d \n", shdr->sh_flags, sizeof(shdr[i].sh_flags));
    printf("shdr->sh_addr     : 0x%08x size %d \n", shdr->sh_addr, sizeof(shdr[i].sh_addr));
    printf("shdr->sh_offset   : 0x%08x size %d \n", shdr->sh_offset, sizeof(shdr[i].sh_offset));
    printf("shdr->sh_size     : 0x%08x size %d \n", shdr->sh_size, sizeof(shdr[i].sh_size));
    printf("shdr->sh_link     : 0x%08x size %d \n", shdr->sh_link, sizeof(shdr[i].sh_link));
    printf("shdr->sh_info     : 0x%08x size %d \n", shdr->sh_info, sizeof(shdr[i].sh_info));
    printf("shdr->sh_addralign: 0x%08x size %d \n", shdr->sh_addralign, sizeof(shdr[i].sh_addralign));
    printf("shdr->sh_entsize  : 0x%08x size %d \n", shdr->sh_entsize, sizeof(shdr[i].sh_entsize));
*/


//    printf("Hello world!\n");
    getchar();
    return 0;
}

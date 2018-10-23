extern "C" unsigned long long int base_add_junk;
extern "C" unsigned long long int  dispatcher(unsigned long long int a,unsigned long long int b, unsigned long long int c, unsigned long long int d,unsigned long long int e,unsigned long long int f);
extern "C" unsigned long long int rand(unsigned long long int a,unsigned long long int b, unsigned long long int c, unsigned long long int d,unsigned long long int e,unsigned long long int f);
unsigned long long int rand (unsigned long long int a,unsigned long long int b, unsigned long long int c, unsigned long long int d,unsigned long long int e,unsigned long long int f){
    asm volatile("mov %%r14, %0" : "=r"(base_add_junk));
    return dispatcher(a,b,c,d,e,f);
}
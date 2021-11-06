

#ifndef calcbit
#define calcbit

#define setbit(reg,bin_no)    reg|=(1<<bin_no)
#define clearbit(reg,bin_no)  reg&=~(1<<bin_no)
#define getbit(reg,bit_no)   ((reg&(1<<bit_no))>>bit_no)
#define togglebit(reg,bit_no)  reg^=(1<<bit_no)

#endif /* calcbit.h */

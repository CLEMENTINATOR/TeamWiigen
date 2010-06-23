#ifndef DOL_HEADER_H_
#define DOL_HEADER_H_

typedef struct dolheader {
        u32 text_pos[7];
        u32 data_pos[11];
        u32 text_start[7];
        u32 data_start[11];
        u32 text_size[7];
        u32 data_size[11];
        u32 bss_start;
        u32 bss_size;
        u32 entry_point;
} dolheader;


#endif

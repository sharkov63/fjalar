/* dwarf.h - DWARF support header file
   Copyright (C) 2005-2021 Free Software Foundation, Inc.

   This file is part of GNU Binutils.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

// Fjalar add a typedef to reduce number of include files needed
// 2022.07.06 sharkov63: removed this typedef
// typedef int bfd_boolean;

#include "dwarf2.h" /* for enum dwarf_unit_type */

typedef unsigned HOST_WIDEST_INT  dwarf_vma;
typedef HOST_WIDEST_INT           dwarf_signed_vma;
typedef unsigned HOST_WIDEST_INT  dwarf_size_type;

/* Structure found in the .debug_line section.  */
typedef struct
{
  dwarf_vma	 li_length;
  unsigned short li_version;
  unsigned char  li_address_size;
  unsigned char  li_segment_size;
  dwarf_vma      li_prologue_length;
  unsigned char  li_min_insn_length;
  unsigned char  li_max_ops_per_insn;
  unsigned char  li_default_is_stmt;
  int            li_line_base;
  unsigned char  li_line_range;
  unsigned char  li_opcode_base;
  unsigned int   li_offset_size;
}
DWARF2_Internal_LineInfo;

/* Structure found in .debug_pubnames section.  */
typedef struct
{
  dwarf_vma	 pn_length;
  unsigned short pn_version;
  dwarf_vma	 pn_offset;
  dwarf_vma	 pn_size;
}
DWARF2_Internal_PubNames;

/* Structure found in .debug_info section.  */
typedef struct
{
  dwarf_vma	 cu_length;
  unsigned short cu_version;
  dwarf_vma	 cu_abbrev_offset;
  unsigned char  cu_pointer_size;
  enum dwarf_unit_type cu_unit_type;
}
DWARF2_Internal_CompUnit;

/* Structure found in .debug_aranges section.  */
typedef struct
{
  dwarf_vma	 ar_length;
  unsigned short ar_version;
  dwarf_vma	 ar_info_offset;
  unsigned char  ar_pointer_size;
  unsigned char  ar_segment_size;
}
DWARF2_Internal_ARange;

/* N.B. The order here must match the order in debug_displays.  */

enum dwarf_section_display_enum
{
  abbrev = 0,
  aranges,
  frame,
  info,
  line,
  pubnames,
  gnu_pubnames,
  eh_frame,
  macinfo,
  macro,
  str,
  line_str,
  loc,
  loclists,
  pubtypes,
  gnu_pubtypes,
  ranges,
  rnglists,
  static_func,
  static_vars,
  types,
  weaknames,
  gdb_index,
  debug_names,
  trace_info,
  trace_abbrev,
  trace_aranges,
  info_dwo,
  abbrev_dwo,
  types_dwo,
  line_dwo,
  loc_dwo,
  macro_dwo,
  macinfo_dwo,
  str_dwo,
  str_index,
  str_index_dwo,
  debug_addr,
  dwp_cu_index,
  dwp_tu_index,
  gnu_debuglink,
  gnu_debugaltlink,
  debug_sup,
  separate_debug_str,
  max
};

struct dwarf_section
{
  /* A debug section has a different name when it's stored compressed
     or not.  COMPRESSED_NAME and UNCOMPRESSED_NAME are the two
     possibilities.  NAME is set to whichever one is used for this
     input file, as determined by load_debug_section().  */
  const char *                     uncompressed_name;
  const char *                     compressed_name;
  const char *                     name;
  /* If non-NULL then FILENAME is the name of the separate debug info
     file containing the section.  */
  const char *                     filename;
  unsigned char *                  start;
  dwarf_vma                        address;
  dwarf_size_type                  size;
  enum dwarf_section_display_enum  abbrev_sec;
  /* Used by clients to help them implement the reloc_at callback.  */
  void *                           reloc_info;
  unsigned long                    num_relocs;
};

/* A structure containing the name of a debug section
   and a pointer to a function that can decode it.  */
struct dwarf_section_display
{
  struct dwarf_section section;
  int (*display) (struct dwarf_section *, void *);
  int *enabled;
  bool relocate;
};

extern struct dwarf_section_display debug_displays [];

/* This structure records the information that
   we extract from the.debug_info section.  */
typedef struct
{
  unsigned int   pointer_size;
  unsigned int   offset_size;
  int            dwarf_version;
  dwarf_vma	 cu_offset;
  dwarf_vma	 base_address;
  /* This field is filled in when reading the attribute DW_AT_GNU_addr_base and
     is used with the form DW_FORM_GNU_addr_index.  */
  dwarf_vma	 addr_base;
  /* This field is filled in when reading the attribute DW_AT_GNU_ranges_base and
     is used when calculating ranges.  */
  dwarf_vma	 ranges_base;
  /* This is an array of offsets to the location list table.  */
  dwarf_vma *    loc_offsets;
  /* This is an array of offsets to the location view table.  */
  dwarf_vma *    loc_views;
  int *          have_frame_base;
  unsigned int   num_loc_offsets;
  unsigned int   max_loc_offsets;
  unsigned int   num_loc_views;
  /* List of .debug_ranges offsets seen in this .debug_info.  */
  dwarf_vma *    range_lists;
  unsigned int   num_range_lists;
  unsigned int   max_range_lists;
}
debug_info;

typedef struct separate_info
{
  void *                  handle;    /* The pointer returned by open_debug_file().  */
  const char *            filename;
  struct separate_info *  next;
} separate_info;

extern separate_info * first_separate_info;

extern unsigned int eh_addr_size;

extern int do_debug_info;
extern int do_debug_abbrevs;
extern int do_debug_lines;
extern int do_debug_pubnames;
extern int do_debug_pubtypes;
extern int do_debug_aranges;
extern int do_debug_ranges;
extern int do_debug_frames;
extern int do_debug_frames_interp;
extern int do_debug_macinfo;
extern int do_debug_str;
extern int do_debug_str_offsets;
extern int do_debug_loc;
extern int do_gdb_index;
extern int do_trace_info;
extern int do_trace_abbrevs;
extern int do_trace_aranges;
extern int do_debug_addr;
extern int do_debug_cu_index;
extern int do_wide;
extern int do_debug_links;
extern int do_follow_links;
extern bool do_checks;

extern int dwarf_cutoff_level;
extern unsigned long dwarf_start_die;

extern int dwarf_check;

extern void init_dwarf_regnames_i386 (void);
extern void init_dwarf_regnames_iamcu (void);
extern void init_dwarf_regnames_x86_64 (void);
extern void init_dwarf_regnames_by_elf_machine_code (unsigned int);
#if 0  // This code is not needed for Fjalar.
extern void init_dwarf_regnames_by_bfd_arch_and_mach (enum bfd_architecture arch,
						      unsigned long mach);
#endif // This code is not needed for Fjalar.

extern bool load_debug_section (enum dwarf_section_display_enum, void *);
extern void free_debug_section (enum dwarf_section_display_enum);
extern bool load_separate_debug_files (void *, const char *);
extern void close_debug_file (void *);
extern void *open_debug_file (const char *);

extern void free_debug_memory (void);

extern void dwarf_select_sections_by_names (const char *);
extern void dwarf_select_sections_by_letters (const char *);
extern void dwarf_select_sections_all (void);

extern unsigned int * find_cu_tu_set (void *, unsigned int);

extern void * cmalloc (size_t, size_t);
extern void * xcalloc2 (size_t, size_t);
extern void * xcmalloc (size_t, size_t);
extern void * xcrealloc (void *, size_t, size_t);

/* A callback into the client.  Returns TRUE if there is a
   relocation against the given debug section at the given
   offset.  */
extern bool reloc_at (struct dwarf_section *, dwarf_vma);

extern dwarf_vma read_leb128 (unsigned char *, const unsigned char *const,
			      bool, unsigned int *, int *);

#if HAVE_LIBDEBUGINFOD
extern unsigned char * get_build_id (void *);
#endif

#if 0  // This code is not needed for Fjalar.

static inline void
report_leb_status (int status, const char *file, unsigned long lnum)
{
  if ((status & 1) != 0)
    error (_("%s:%lu: end of data encountered whilst reading LEB\n"), file, lnum);
  else if ((status & 2) != 0)
    error (_("%s:%lu: read LEB value is too large to store in destination variable\n"), file, lnum);
}

#endif // This code is not needed for Fjalar.

// start of Fjalar code
// convert report_leb_status to macro to solve duplicate 'error' definition problem

#define report_leb_status(status, file, lnum)                   \
  do                                                            \
    {                                                           \
      if ((status & 1) != 0)                                    \
        error (_("%s:%lu: end of data encountered whilst reading LEB\n"), file, lnum); \
      else if ((status & 2) != 0)                               \
        error (_("%s:%lu: read LEB value is too large to store in destination variable\n"), file, lnum); \
    } while (0)                                                 \

// end of Fjalar code

#define SKIP_ULEB(start, end)					\
  do								\
    {								\
      unsigned int _len;					\
      read_leb128 (start, end, false, &_len, NULL);		\
      start += _len;						\
    }								\
  while (0)

#define SKIP_SLEB(start, end)					\
  do								\
    {								\
      unsigned int _len;					\
      read_leb128 (start, end, true, &_len, NULL);		\
      start += _len;						\
    }								\
  while (0)

#define READ_ULEB(var, start, end)				\
  do								\
    {								\
      dwarf_vma _val;						\
      unsigned int _len;					\
      int _status;						\
								\
      _val = read_leb128 (start, end, false, &_len, &_status);	\
      start += _len;						\
      (var) = _val;						\
      if ((var) != _val)					\
	_status |= 2;						\
      report_leb_status (_status, __FILE__, __LINE__);		\
    }								\
  while (0)

#define READ_SLEB(var, start, end)				\
  do								\
    {								\
      dwarf_signed_vma _val;					\
      unsigned int _len;					\
      int _status;						\
								\
      _val = read_leb128 (start, end, true, &_len, &_status);	\
      start += _len;						\
      (var) = _val;						\
      if ((var) != _val)					\
	_status |= 2;						\
      report_leb_status (_status, __FILE__, __LINE__);		\
    }								\
  while (0)

#include "bpf_load.h"
#include <linux/bpf.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main(int argc, char **argv) {
  if (load_bpf_file("../bpf/bpf_program.o") != 0) {
    printf("The kernel didn't load the BPF program\n");
    return -1;
  }

  /* int fd = bpf_create_map_name(BPF_MAP_TYPE_HASH,
			       "Howard",
			       sizeof(int),
			       sizeof(int),
			       100,
			       BPF_F_NO_PREALLOC);*/

  sleep(20);
  int key, value, result;
  
  key = 1;
  result = bpf_map_lookup_elem(map_data[0].fd, &key, &value);
  if (result == 0)
    printf("Value read from the map: '%d'\n", value);
  else
    printf("Failed to read value from the map: %d (%s)\n", result, strerror(errno));
  

  read_trace_pipe();

  return 0;
}



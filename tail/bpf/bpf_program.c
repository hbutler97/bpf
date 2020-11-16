#include <linux/bpf.h>
//#include <uapi/linux/bpf.h>
#include "bpf_helpers.h"

struct bpf_map_def SEC("maps") my_map = {
	.type = BPF_MAP_TYPE_ARRAY,
	.key_size = sizeof(int),
	.value_size = sizeof(int),
	.max_entries = 97,
};



SEC("tracepoint/syscalls/sys_enter_execve")
int bpf_prog(void *ctx) {
  char msg[] = "Hello, BPF World! %d";
  char msg2[] = "error";
  int key = 1;
  

  int *result = (int*)bpf_map_lookup_elem(&my_map, &key);
  if(!result)
    bpf_trace_printk(msg2, sizeof(msg2));
  else {
    int value = (*result + 1);
    bpf_trace_printk(msg, sizeof(msg), value);

    bpf_map_update_elem(&my_map, &key, &value, BPF_ANY);
  }


  return 0;
}

char _license[] SEC("license") = "GPL";


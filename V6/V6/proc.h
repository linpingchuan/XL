#pragma once

#include "types.h"

#define NSEGS 7 // Segements in proc->gdt

// Per-CPU state
struct cpu{
	//uchar id; // Local APIC ID; index into cpus[] below
	struct context *scheduler; // swtch() here to enter scheduler
	//struct taskstate ts;
	//struct seddesc gdt[NSEGS];

};

// Saved registers for kernel context switches.
// Don't need to save all the segment registers(%cs,etc),
// because they are constant across kernel contexts.
// Don't need to save %eax,%ecs,%edx,because the 
// x86 convention is that the caller has saved them.
// Contexts are stored at the bottom of the stack they
// describe; the stack pointer is the address of the context.
// The layout of the context matches the layout of the stack in swtch.S
// at the "Switch stacks" comment. Switch doesn't save eip explicitly,
// but it is on the stack and allocproc() manipulates it.
struct context {
	uint edi;
	uint esi;
	uint ebx;
	uint ebp;
	uint eip;
};

enum procstate{ UNUSED,EMBRYO,SLEEPING,RUNNABLE,RUNNING,ZOMBIE};
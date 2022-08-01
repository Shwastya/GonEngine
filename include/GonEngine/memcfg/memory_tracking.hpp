#pragma once
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include <cinttypes>

#ifdef _GON_LOG
struct MemoryTracking
{
	uint32_t TotalAllocated{ 0 };
	uint32_t TotalFreed{ 0 };
};

MemoryTracking s_metrics;

#pragma warning( push )
#pragma warning( disable : 28196 )
#pragma warning( disable : 28251 )
#pragma warning( disable : 6387 )
void* operator new(const size_t size)
{
	s_metrics.TotalAllocated += static_cast<uint32_t>(size);
#if 0
	printf("  |-> Allocating %" PRIuPTR " bytes\n", size);
#endif
	return malloc(size);	// breakpoint here for allocates tracking
}
#pragma warning( pop )

void operator delete(void* memory, const size_t size)
{
	s_metrics.TotalFreed += static_cast<uint32_t>(size);
#if 0
	printf("  |-> Freeing %" PRIuPTR " bytes\n", size);
#endif
	free(memory);			// breakpoint here for freeds tracking
}

static void printfMemoryUsage()
{
	printf("\n    Total allocated: %u bytes\n", s_metrics.TotalAllocated);
	printf("    Total freeds:    %u bytes\n", s_metrics.TotalFreed);
	printf("    Memory leaks:    %u bytes\n", s_metrics.TotalAllocated - s_metrics.TotalFreed);
}
#endif // _GON_LOG



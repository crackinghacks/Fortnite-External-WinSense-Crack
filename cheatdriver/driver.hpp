#pragma once 
#include "process_handler.hpp"



typedef struct _k_get_base_module_request {
	ULONG pid;
	ULONGLONG handle;
	WCHAR name[260];
} k_get_base_module_request, * pk_get_base_module_request;

typedef struct _k_rw_request {
	ULONG pid;
	ULONGLONG src;
	ULONGLONG dst;
	ULONGLONG size;
} k_rw_request, * pk_rw_request;

typedef struct _k_alloc_mem_request { //GH2ST P2C Example by Happy Cat
	ULONG pid, allocation_type, protect;
	ULONGLONG addr;
	SIZE_T size;
} k_alloc_mem_request, * pk_alloc_mem_request;

typedef struct _k_protect_mem_request {
	ULONG pid, protect;
	ULONGLONG addr;
	SIZE_T size;
} k_protect_mem_request, * pk_protect_mem_request;

class kernelmode_proc_handler final : public process_handler {
	HANDLE handle;
	uint32_t pid;
public: //GH2ST P2C Example by Happy Cat
	kernelmode_proc_handler();

	~kernelmode_proc_handler();

	virtual bool is_attached() override;
	//GH2ST P2C Example by Happy Cat
	virtual bool attach(const char* proc_name) override;

	virtual	uint64_t get_module_base(const std::string& module_name) override;

	virtual void read_memory(uintptr_t src, uintptr_t dst, size_t size) override;

	virtual void write_memory(uintptr_t dst, uintptr_t src, size_t size) override;

	virtual uint32_t virtual_protect(uint64_t address, size_t size, uint32_t protect) override;
	//GH2ST P2C Example by Happy Cat
	virtual uint64_t virtual_alloc(size_t size, uint32_t allocation_type, uint32_t protect, uint64_t address = NULL) override;
};
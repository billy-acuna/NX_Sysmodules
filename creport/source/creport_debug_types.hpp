#pragma once
#include <switch.h>

struct AttachProcessInfo {
    u64 title_id;
    u64 process_id;
    char name[0xC];
    u32 flags;
    u64 user_exception_context_address; /* 5.0.0+ */
};

struct AttachThreadInfo {
    u64 thread_id;
    u64 tls_address;
    u64 entrypoint;
};

/* TODO: ExitProcessInfo */
/* TODO: ExitThreadInfo */

enum class DebugExceptionType : u32 {
    UndefinedInstruction = 0,
    InstructionAbort = 1,
    DataAbort = 2,
    AlignmentFault = 3,
    DebuggerAttached = 4,
    BreakPoint = 5,
    UserBreak = 6,
    DebuggerBreak = 7,
    BadSvc = 8,
    UnknownNine = 9,
};

struct UndefinedInstructionInfo {
    u32 insn;
};

struct DataAbortInfo {
    u64 address;
};

struct AlignmentFaultInfo {
    u64 address;
};

struct BadSvcInfo {
    u32 id;
};

union SpecificExceptionInfo {
    UndefinedInstructionInfo undefined_instruction;
    DataAbortInfo data_abort;
    AlignmentFaultInfo alignment_fault;
    BadSvcInfo bad_svc;
    u64 raw;
};

static_assert(sizeof(SpecificExceptionInfo) == sizeof(u64), "Bad SpecificExceptionInfo definition!");

struct ExceptionInfo {
    DebugExceptionType type;
    u64 address;
    SpecificExceptionInfo specific;
};


enum class DebugEventType : u32 {
    AttachProcess = 0,
    AttachThread = 1,
    ExitProcess = 2,
    ExitThread = 3,
    Exception = 4
};

union DebugInfo {
    AttachProcessInfo attach_process;
    AttachThreadInfo attach_thread;
    ExceptionInfo exception;
};

struct DebugEventInfo {
    DebugEventType type;
    u32 flags;
    u64 thread_id;
    DebugInfo info;
};
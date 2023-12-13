
# umocktypes_windows requirements

# Overview

`umocktypes_windows` is a module that exposes out of the box functionality for several Windows types.

The types are implemented as described [here](https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types)

# Exposed API

```c
int umocktypes_windows_register_types(void);
```

## umocktypes_windows_register_types

```c
int umocktypes_windows_register_types(void);
```

**SRS_UMOCKTYPES_WINDOWS_01_026: [** `umocktypes_windows_register_types` shall register the charptr types by calling `umocktypes_charptr_register_types`. **]**

**SRS_UMOCKTYPES_WINDOWS_01_033: [** `umocktypes_windows_register_types` shall register the wcharptr types by calling `umocktypes_wcharptr_register_types`. **]**

**SRS_UMOCKTYPES_WINDOWS_01_035: [** `umocktypes_windows_register_types` shall register the stdint types by calling `umocktypes_stdint_register_types`. **]**

**SRS_UMOCKTYPES_WINDOWS_01_009: [** `umocktypes_windows_register_types` shall register support for the following alias types: **]**

- **SRS_UMOCKTYPES_WINDOWS_01_001: [** `LONG` as an alias of `long`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_002: [** `LONGLONG` as an alias of `long long`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_003: [** `DWORD` as an alias of `unsigned long`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_004: [** `HRESULT` as an alias of `LONG`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_025: [** `BOOL` as an alias of `int`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_007: [** `PVOID` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_008: [** `LPCSTR` as an alias of `const char*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_010: [** `LPSECURITY_ATTRIBUTES` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_011: [** `HANDLE` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_012: [** `UCHAR` as an alias of `unsigned char`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_013: [** `PTP_POOL` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_014: [** `PTP_CLEANUP_GROUP` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_015: [** `PTP_CALLBACK_ENVIRON` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_016: [** `PTP_CLEANUP_GROUP_CANCEL_CALLBACK` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_017: [** `PTP_IO` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_018: [** `PTP_WIN32_IO_CALLBACK` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_019: [** `PTP_WORK_CALLBACK` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_020: [** `PTP_WORK` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_021: [** `LPCVOID` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_022: [** `LPDWORD` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_023: [** `LPOVERLAPPED` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_024: [** `LPVOID` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_027: [** `PTP_SIMPLE_CALLBACK` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_028: [** `LPLONG` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_029: [** `BYTE` as an alias of `unsigned char`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_030: [** `BOOLEAN` as an alias of `BYTE`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_031: [** `ULONG` as an alias of `unsigned long`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_032: [** `LPCWSTR` as an alias of `const wchar_t*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_034: [** `LONG64` as an alias of `int64_t`. **]**

-  **SRS_UMOCKTYPES_WINDOWS_43_036: [** `SHORT` as an alias of `int16_t`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_036: [** `SIZE_T` as an alias of `size_t`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_037: [** `PSIZE_T` as an alias of `void*`. **]**

- **SRS_UMOCKTYPES_WINDOWS_01_038: [** `PHANDLE` as an alias of `void*`. **]**

**SRS_UMOCKTYPES_WINDOWS_01_005: [** On success, `umocktypes_windows_register_types` shall return 0. **]**

**SRS_UMOCKTYPES_WINDOWS_01_006: [** If registering any of the types fails, `umocktypes_windows_register_types` shall fail and return a non-zero value. **]**

# umock_lock_factory_windows

## Overview

`umock_lock_factory_windows` is a module that implements the lock factory for `umock_c` for Windows.

## Exposed API

```c
    UMOCK_C_LOCK_HANDLE umock_lock_factory_create_lock(void* params);
```

## static lock functions

```c
static void umock_lock_windows_acquire_shared(UMOCK_C_LOCK_HANDLE lock);
static void umock_lock_windows_release_shared(UMOCK_C_LOCK_HANDLE lock);
static void umock_lock_windows_acquire_exclusive(UMOCK_C_LOCK_HANDLE lock);
static void umock_lock_windows_release_exclusive(UMOCK_C_LOCK_HANDLE lock);
static void umock_lock_windows_destroy(UMOCK_C_LOCK_HANDLE lock);
```

### umockcall_create

```c
UMOCK_C_LOCK_HANDLE umock_lock_factory_create_lock(void* params);
```

`umock_lock_factory_create_lock` creates a new lock to be used by `umock_c`.

**SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_001: [** `umock_lock_factory_create_lock` shall allocate memory for the lock. **]**

**SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_002: [** `umock_lock_factory_create_lock` shall initialize a SRW lock that is encapsulated by the new `UMOCK_C_LOCK_HANDLE`. **]**

**SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_003: [** `umock_lock_factory_create_lock` shall return a lock handle that has the function pointers set to `umock_lock_windows_acquire_shared`, `umock_lock_windows_release_shared`, `umock_lock_windows_acquire_exclusive`, `umock_lock_windows_release_exclusive` and `umock_lock_windows_destroy`. **]**

**SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_004: [** If any error occurs, `umock_lock_factory_create_lock` shall fail and return `NULL`. **]**

### umock_lock_windows_acquire_shared

```c
static void umock_lock_windows_acquire_shared(UMOCK_C_LOCK_HANDLE lock);
```

`umock_lock_windows_acquire_shared` acquires the lock in shared mode.

**SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_010: [** If `lock` is `NULL`, `umock_lock_windows_acquire_shared` shall return. **]**

**SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_005: [** `umock_lock_windows_acquire_shared` shall acquire the lock in shared mode by calling `AcquireSRWLockShared`. **]**

### umock_lock_windows_release_shared

```c
static void umock_lock_windows_release_shared(UMOCK_C_LOCK_HANDLE lock);
```

`umock_lock_windows_release_shared` releases the lock that was acquired in shared mode.

**SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_011: [** If `lock` is `NULL`, `umock_lock_windows_release_shared` shall return. **]**

**SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_006: [** `umock_lock_windows_release_shared` shall release the lock that was acquired in shared mode by calling `ReleaseSRWLockShared`. **]**

### umock_lock_windows_acquire_exclusive

```c
static void umock_lock_windows_acquire_exclusive(UMOCK_C_LOCK_HANDLE lock);
```

`umock_lock_windows_acquire_exclusive` acquires the lock in exclusive mode.

**SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_012: [** If `lock` is `NULL`, `umock_lock_windows_acquire_exclusive` shall return. **]**

**SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_007: [** `umock_lock_windows_acquire_exclusive` shall acquire the lock in exclusive mode by calling `AcquireSRWLockExclusive`. **]**

### umock_lock_windows_release_exclusive

```c
static void umock_lock_windows_release_exclusive(UMOCK_C_LOCK_HANDLE lock);
```

`umock_lock_windows_release_exclusive` releases the lock that was acquired in exclusive mode.

**SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_013: [** If `lock` is `NULL`, `umock_lock_windows_release_exclusive` shall return. **]**

**SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_008: [** `umock_lock_windows_release_exclusive` shall release the lock that was acquired in exclusive mode by calling `ReleaseSRWLockExclusive`. **]**

### umock_lock_windows_destroy

```c
static void umock_lock_windows_destroy(UMOCK_C_LOCK_HANDLE lock);
```

`umock_lock_windows_destroy` frees the resources associated with the lock.

**SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_014: [** If `lock` is `NULL`, `umock_lock_windows_destroy` shall return. **]**

**SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_009: [** `umock_lock_windows_destroy` shall free the memory associated with the lock. **]**

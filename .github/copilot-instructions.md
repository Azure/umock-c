# umock-c AI Coding Instructions

## Project Overview
umock-c is a C mocking library designed for Azure C projects, providing macro-based mock generation, expectation recording, and call verification. It enables sophisticated unit testing through compile-time mock generation and runtime call tracking with rich assertion capabilities.

## Core Architecture

### Mock Generation System
- **`MOCKABLE_FUNCTION(modifiers, result, function, ...)`**: Core macro that generates mockable function declarations and implementations
- **`ENABLE_MOCKS`**: Compilation flag that switches between production code (declarations only) and test code (full mock implementations)
- **`inc/umock_c/umock_c_prod.h`**: Production header that enables `MOCKABLE_FUNCTION` for both production and test builds
- **Macro Metaprogramming**: Heavily uses `macro-utils-c` for complex macro expansion and code generation

### Mock Control Flow
```c
// Production header (dependency.h)
#include "umock_c/umock_c_prod.h"
MOCKABLE_FUNCTION(, int, dependency_function, int, arg);

// Test file pattern
#define ENABLE_MOCKS
#include "dependency.h"  // Generates mock implementations
#undef ENABLE_MOCKS
#include "unit_under_test.h"  // Real implementation
```

### Call Recording & Verification
- **`STRICT_EXPECTED_CALL(call)`**: Records expected calls with argument validation
- **`EXPECTED_CALL(call)`**: Records expected calls without argument validation by default
- **Call Modifiers**: Chainable modifiers like `.SetReturn()`, `.IgnoreArgument()`, `.ValidateArgument()`
- **`umock_c_get_expected_calls()` / `umock_c_get_actual_calls()`**: String representations for test assertions

## Key Development Patterns

### Test Structure (AAA Pattern)
```c
TEST_FUNCTION(function_under_test_with_dependency_succeeds)
{
    // arrange
    STRICT_EXPECTED_CALL(dependency_function(42))
        .SetReturn(0);

    // act
    int result = function_under_test();

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(char_ptr, umock_c_get_expected_calls(), umock_c_get_actual_calls());
}
```

### Mock Filtering (Performance Optimization)
```c
#define ENABLE_MOCK_FILTERING
#define please_mock_specific_function MOCK_ENABLED

#define ENABLE_MOCKS
#include "large_header.h"  // Only generates mocks for selected functions
#undef ENABLE_MOCKS
```

### Global Mock Configuration
```c
// Test suite setup
REGISTER_GLOBAL_MOCK_HOOK(malloc, my_malloc_hook);
REGISTER_GLOBAL_MOCK_RETURN(function_name, success_value);
REGISTER_GLOBAL_MOCK_FAIL_RETURN(function_name, failure_value);
```

### Call Modifiers (Fluent Interface)
```c
STRICT_EXPECTED_CALL(function(arg1, arg2, buffer))
    .SetReturn(42)
    .IgnoreArgument_arg1()
    .ValidateArgumentBuffer_buffer(expected_data, data_size)
    .CopyOutArgumentBuffer_buffer(output_data, output_size);
```

## Call Modifiers Reference

Call modifiers provide a fluent interface for configuring mock expectations. Each modifier returns a structure that allows chaining further modifiers. The last modifier in a chain overrides previous modifiers if any collision occurs.

### Argument Control Modifiers

#### IgnoreArgument Family
```c
// Ignore specific argument by name (preferred)
STRICT_EXPECTED_CALL(function(42, "test", buffer))
    .IgnoreArgument_arg1()     // Ignores first argument regardless of value
    .IgnoreArgument_buffer();  // Ignores buffer argument

// Ignore argument by index (0-based)
STRICT_EXPECTED_CALL(function(42, "test", buffer))
    .IgnoreArgument(0)         // Ignores first argument (42)
    .IgnoreArgument(2);        // Ignores third argument (buffer)

// Ignore all arguments at once
STRICT_EXPECTED_CALL(function(42, "test", buffer))
    .IgnoreAllArguments();     // All arguments ignored, only function name matters

// Automatic ignore with IGNORED_ARG
STRICT_EXPECTED_CALL(function(IGNORED_ARG, "test", IGNORED_ARG));  // Equivalent to IgnoreArgument on positions 0 and 2
```

#### ValidateArgument Family
```c
// Validate specific argument by name (overrides ignore)
EXPECTED_CALL(function(42, "test", buffer))     // EXPECTED_CALL ignores all by default
    .ValidateArgument_arg1()                    // But validate first argument
    .ValidateArgument_arg2();                   // And second argument

// Validate argument by index
EXPECTED_CALL(function(42, "test", buffer))
    .ValidateArgument(0)                        // Validate first argument
    .ValidateArgument(1);                       // Validate second argument
```

### Return Value Modifiers

#### SetReturn and SetFailReturn
```c
// Set successful return value
STRICT_EXPECTED_CALL(malloc(100))
    .SetReturn((void*)0x1234);                  // Return specific pointer

// Set both success and failure return values
STRICT_EXPECTED_CALL(network_send(data, size))
    .SetReturn(0)                               // Success case
    .SetFailReturn(-1);                         // Failure case for negative testing

// Capture the return value that was actually returned
int captured_return;
STRICT_EXPECTED_CALL(get_status())
    .CaptureReturn(&captured_return);           // Store return value in variable
// After call: captured_return contains the value that was returned
```

### Buffer and Pointer Argument Modifiers

#### ValidateArgumentBuffer Family
```c
// Validate buffer contents by name
char expected_data[] = { 0x01, 0x02, 0x03, 0x04 };
STRICT_EXPECTED_CALL(write_data(buffer, 4))
    .ValidateArgumentBuffer_buffer(expected_data, sizeof(expected_data));

// Validate buffer contents by index
STRICT_EXPECTED_CALL(write_data(buffer, 4))
    .ValidateArgumentBuffer(0, expected_data, sizeof(expected_data));

// Buffer validation automatically ignores the pointer value itself
// (only contents matter, not the actual pointer address)
```

#### CopyOutArgumentBuffer Family
```c
// Copy data to output buffer by argument name
char output_data[] = { 0xAA, 0xBB, 0xCC, 0xDD };
STRICT_EXPECTED_CALL(read_data(output_buffer, buffer_size))
    .CopyOutArgumentBuffer_output_buffer(output_data, sizeof(output_data));

// Copy data to output buffer by index
STRICT_EXPECTED_CALL(read_data(output_buffer, buffer_size))
    .CopyOutArgumentBuffer(0, output_data, sizeof(output_data));

// The buffer argument is automatically ignored (marked as out parameter)
// Memory is copied, so original data can be modified after the call
```

#### CopyOutArgument (Single Values)
```c
// Copy single value to pointer argument
int output_value = 42;
STRICT_EXPECTED_CALL(get_value(&result))
    .CopyOutArgument(output_value);             // Copies value to *result

// Works with any type that has registered copy handlers
MY_STRUCT output_struct = { .field1 = 10, .field2 = "test" };
STRICT_EXPECTED_CALL(get_struct(&result_struct))
    .CopyOutArgument(output_struct);
```

### Advanced Argument Validation

#### ValidateArgumentValue Family
```c
// Validate against variable value (not literal)
int expected_id = 42;
STRICT_EXPECTED_CALL(process_item(expected_id, data))
    .ValidateArgumentValue_id(&expected_id);   // Validates against variable content

// This allows changing expected value before the call
expected_id = 99;  // Now the call expects 99 instead of 42

// Validate argument as different type
void* generic_ptr = &my_struct;
STRICT_EXPECTED_CALL(process_generic(generic_ptr))
    .ValidateArgumentValue_generic_ptr_AsType(UMOCK_TYPE(MY_STRUCT));
```

#### CaptureArgumentValue Family
```c
// Capture argument value at call time
int captured_arg;
STRICT_EXPECTED_CALL(process_value(42))
    .CaptureArgumentValue_value(&captured_arg);

// After the call, captured_arg contains the actual value passed
// This is useful for verifying computed arguments
```

### Special Behavior Modifiers

#### IgnoreAllCalls
```c
// Allow multiple matching calls without reporting errors
STRICT_EXPECTED_CALL(log_message(IGNORED_ARG))
    .IgnoreAllCalls();                          // Any number of log_message calls OK

// Useful for logging functions, cleanup functions, etc.
// No "unexpected call" errors even if called multiple times
// No "missing call" errors if never called
```

#### CallCannotFail (Negative Testing)
```c
// Mark call as unable to fail during negative testing
STRICT_EXPECTED_CALL(critical_system_call())
    .CallCannotFail();

// When using umock_c_negative_tests_fail_call(), this call is skipped
// Useful for calls that represent system state that cannot fail
```

## Call Modifier Patterns and Best Practices

### Chaining Order and Precedence
```c
// Modifiers can be chained in any order
STRICT_EXPECTED_CALL(complex_function(arg1, buffer, size, output))
    .SetReturn(0)                               // Set return value
    .IgnoreArgument_arg1()                      // Ignore first argument
    .ValidateArgumentBuffer_buffer(data, len)   // Validate buffer contents
    .CopyOutArgumentBuffer_output(result, len)  // Copy data to output
    .ValidateArgument_size();                   // But validate size argument

// Later modifiers override earlier ones for the same argument
STRICT_EXPECTED_CALL(function(arg))
    .IgnoreArgument_arg()                       // Initially ignore
    .ValidateArgument_arg();                    // Override: now validate

// This allows progressive refinement of expectations
```

### Common Patterns

#### Out Parameter Handling
```c
// Function that fills output buffer and returns status
int error_code = 0;
char response_data[] = "SUCCESS";
STRICT_EXPECTED_CALL(api_call(request, response_buffer, &status))
    .SetReturn(100)                             // Bytes written
    .CopyOutArgumentBuffer_response_buffer(response_data, strlen(response_data))
    .CopyOutArgument(error_code);               // Set *status = 0
```

#### Variable Argument Validation
```c
// When expected values are computed at runtime
TEST_FUNCTION(test_with_dynamic_values)
{
    // arrange
    int current_time = get_current_timestamp();
    char* expected_message = generate_log_message();
    
    STRICT_EXPECTED_CALL(log_with_timestamp(current_time, expected_message))
        .ValidateArgumentValue_timestamp(&current_time)
        .ValidateArgumentValue_message(&expected_message);
    
    // act
    function_under_test();
    
    // assert
    ASSERT_ARE_EQUAL(char_ptr, umock_c_get_expected_calls(), umock_c_get_actual_calls());
    
    free(expected_message);
}
```

#### Buffer Content Verification
```c
// Verify exact buffer contents while ignoring buffer address
void test_buffer_writing()
{
    // arrange
    char expected_header[] = { 0x42, 0x43, 0x44, 0x45 };
    char output_buffer[100];
    
    STRICT_EXPECTED_CALL(write_header(output_buffer))
        .ValidateArgumentBuffer_buffer(expected_header, sizeof(expected_header));
    
    // act
    result = write_data_packet(output_buffer);
    
    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(char_ptr, umock_c_get_expected_calls(), umock_c_get_actual_calls());
}
```

### Automatic Mock Generation Function
The `add_mock_library()` CMake function automatically generates mock libraries:
```cmake
# Generates library_name_mocks target with precompiled headers
add_mock_library(my_library
    HEADER_FILES
        "header1.h"
        "header2.h"
)
```

## Type System Integration

### Built-in Type Support
- **Native C Types**: All standard C types supported via `umocktypes_c.h`
- **Windows Types**: `HRESULT`, `DWORD`, `HANDLE`, etc. via `umocktypes_windows.h`
- **stdint Types**: `int32_t`, `uint64_t`, etc. via `umocktypes_stdint.h`
- **String Types**: `char*`, `const char*`, `wchar_t*` via dedicated headers

### Custom Type Registration
```c
// Define custom type handlers
IMPLEMENT_UMOCK_C_ENUM_TYPE(MY_ENUM, VALUE1, VALUE2, VALUE3);

// Register in test setup
REGISTER_UMOCK_VALUE_TYPE(MY_STRUCT);  // Auto-derives function names
REGISTER_UMOCK_ALIAS_TYPE(MY_HANDLE, void*);  // Alias existing type
```

### Type Handler Implementation
Every custom type requires four handler functions that umock-c uses for argument comparison and display:

```c
// 1. Stringify function - converts value to string representation
char* umock_stringify_MY_STRUCT(const MY_STRUCT* value)
{
    char* result;
    if (value == NULL)
    {
        result = NULL;
    }
    else
    {
        char temp_buffer[256];
        int length = sprintf(temp_buffer, "{ field1=%d, field2=%s }", value->field1, value->field2);
        if (length < 0)
        {
            result = NULL;
        }
        else
        {
            result = (char*)malloc(length + 1);
            if (result != NULL)
            {
                memcpy(result, temp_buffer, length + 1);
            }
        }
    }
    return result;
}

// 2. Are equal function - compares two values for equality
int umock_are_equal_MY_STRUCT(const MY_STRUCT* left, const MY_STRUCT* right)
{
    int result;
    if (left == right)
    {
        result = 1;  // Same pointer or both NULL
    }
    else if ((left == NULL) || (right == NULL))
    {
        result = 0;  // One is NULL, other is not
    }
    else
    {
        result = (left->field1 == right->field1 && 
                 strcmp(left->field2, right->field2) == 0) ? 1 : 0;
    }
    return result;
}

// 3. Copy function - creates a copy of the value
int umock_copy_MY_STRUCT(MY_STRUCT* destination, const MY_STRUCT* source)
{
    int result;
    if ((destination == NULL) || (source == NULL))
    {
        result = MU_FAILURE;
    }
    else
    {
        destination->field1 = source->field1;
        if (source->field2 != NULL)
        {
            destination->field2 = (char*)malloc(strlen(source->field2) + 1);
            if (destination->field2 == NULL)
            {
                result = MU_FAILURE;
            }
            else
            {
                strcpy(destination->field2, source->field2);
                result = 0;
            }
        }
        else
        {
            destination->field2 = NULL;
            result = 0;
        }
    }
    return result;
}

// 4. Free function - releases resources allocated by copy
void umock_free_MY_STRUCT(MY_STRUCT* value)
{
    if (value != NULL)
    {
        if (value->field2 != NULL)
        {
            free(value->field2);
            value->field2 = NULL;
        }
    }
}
```

### Type Registration Patterns
```c
// Manual registration with explicit function names
REGISTER_UMOCK_VALUE_TYPE(MY_STRUCT, 
    umock_stringify_MY_STRUCT, 
    umock_are_equal_MY_STRUCT, 
    umock_copy_MY_STRUCT, 
    umock_free_MY_STRUCT);

// Automatic registration (derives function names from type)
REGISTER_UMOCK_VALUE_TYPE(MY_STRUCT);

// Alias registration (reuses handlers from existing type)
REGISTER_UMOCK_ALIAS_TYPE(MY_HANDLE, void*);

// Common registration in test suite initialization
TEST_SUITE_INITIALIZE(TestClassInitialize)
{
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    REGISTER_UMOCK_VALUE_TYPE(MY_STRUCT);
    ASSERT_ARE_EQUAL(int, 0, umocktypes_charptr_register_types());
    ASSERT_ARE_EQUAL(int, 0, umocktypes_stdint_register_types());
}
```

### Advanced Type Patterns
```c
// Pointer type declaration
DECLARE_UMOCK_POINTER_TYPE_FOR_TYPE(MY_STRUCT, my_struct);

// Runtime type validation
STRICT_EXPECTED_CALL(function_with_void_ptr(&data))
    .ValidateArgumentValue_ptr_AsType(UMOCK_TYPE(MY_STRUCT));
```

## Advanced Features

### Negative Testing Framework
```c
// Automated failure injection testing
STRICT_EXPECTED_CALL(function1()).SetReturn(0).SetFailReturn(1);
STRICT_EXPECTED_CALL(function2()).SetReturn(0).SetFailReturn(1);
umock_c_negative_tests_snapshot();

for (i = 0; i < umock_c_negative_tests_call_count(); i++)
{
    umock_c_negative_tests_reset();
    umock_c_negative_tests_fail_call(i);
    
    int result = function_under_test();
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
}
```

### Paired Calls Tracking (Resource Leak Detection)
```c
// Registers create/destroy pairs for leak detection
REGISTER_UMOCKC_PAIRED_CREATE_DESTROY_CALLS(handle_create, handle_destroy);
```

### Real Function Integration
```c
// Interface definition for real function support
MOCKABLE_INTERFACE(test_interface,
    FUNCTION(, int, function1, int, arg),
    FUNCTION(, void, function2)
)

// Enable real function calls in tests
REGISTER_GLOBAL_INTERFACE_HOOKS(test_interface);
```

### Multithreading Support
```c
// Initialize with custom lock factory for thread safety
umock_c_init_with_lock_factory(error_callback, lock_factory_func, lock_params);
```

## Build System Integration

### CMake Configuration
```cmake
# Standard dependency inclusion
if ((NOT TARGET umock_c) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/umock-c/CMakeLists.txt))
    add_subdirectory(deps/umock-c)
endif()

# Link to test targets
target_link_libraries(my_test_exe umock_c)

# Test execution options
-Drun_unittests=ON
-Drun_int_tests=ON
-Duse_cppunittest=ON  # Windows CppUnitTest integration
```

### Test Categories & Organization
- **Unit Tests** (`*_ut/`): Component-level testing with mocked dependencies
- **Integration Tests** (`*_int/`): Cross-component testing with real implementations
- **Test Structure**: Each test directory has its own `CMakeLists.txt` using `build_test_folder()` function

### Mock Precompiled Headers (Performance Optimization)

The `build_test_artifacts()` function integrates with the c-testrunnerswitcher build system to provide precompiled header optimization for mock-heavy test projects:

```cmake
# CMakeLists.txt for test project
build_test_artifacts(my_component_ut ${CMAKE_CURRENT_LIST_DIR}
    MOCK_PRECOMPILE_HEADERS
        "dependency1.h"
        "dependency2.h"
        "large_dependency.h"
)
```

#### MOCK_PRECOMPILE_HEADERS
- **Purpose**: Precompiles headers that should be included between `#define ENABLE_MOCKS` and `#undef ENABLE_MOCKS`
- **Usage**: List headers that generate many mocks and are included in multiple test files
- **Generated Target**: Creates `${target_name}_mocks.h` and `${target_name}_mocks.c` with precompiled headers
- **Integration**: Automatically generates mock functions for listed headers

> **CRITICAL REQUIREMENT**: All headers that exist in the unit test file between `#define ENABLE_MOCKS` and `#undef ENABLE_MOCKS` **MUST** be listed in `MOCK_PRECOMPILE_HEADERS`. Failing to include them will cause build errors due to missing mock implementations.

```c
// Test file pattern - ALL these headers must be in MOCK_PRECOMPILE_HEADERS
#define ENABLE_MOCKS
#include "dependency1.h"           // ✅ Must be in MOCK_PRECOMPILE_HEADERS
#include "dependency2.h"           // ✅ Must be in MOCK_PRECOMPILE_HEADERS  
#include "large_dependency.h"      // ✅ Must be in MOCK_PRECOMPILE_HEADERS
#undef ENABLE_MOCKS

// Corresponding CMakeLists.txt - must match exactly
build_test_artifacts(my_component_ut ${CMAKE_CURRENT_LIST_DIR}
    MOCK_PRECOMPILE_HEADERS
        "dependency1.h"            # Must match test file includes
        "dependency2.h"            # Must match test file includes
        "large_dependency.h"       # Must match test file includes
)
```

```cmake
# This generates a precompiled header file with structure:
# #define ENABLE_MOCKS
# #define ENABLE_MOCKS_DECL
# #include "dependency1.h"
# #include "dependency2.h"
# #include "large_dependency.h"
# #undef ENABLE_MOCKS_DECL
# #undef ENABLE_MOCKS
build_test_artifacts(my_component_ut ${CMAKE_CURRENT_LIST_DIR}
    MOCK_PRECOMPILE_HEADERS
        "azure_c_shared_utility/gballoc.h"
        "azure_c_shared_utility/crt_abstractions.h"
        "azure_uamqp_c/amqp_management.h"
)
```

#### NO_MOCK_PRECOMPILE_HEADERS
- **Purpose**: Precompiles headers that should be included before and outside of `#define ENABLE_MOCKS` and `#undef ENABLE_MOCKS`
- **Usage**: Headers that should not have mocks generated but are frequently included
- **Effect**: Includes headers in the precompiled header without mock generation

> **BEST PRACTICE**: Any headers that are included in the unit test file before `#define ENABLE_MOCKS` (except standard C runtime headers like `interlocked.h`) should be listed in `NO_MOCK_PRECOMPILE_HEADERS` for optimal build performance.

```c
// Test file pattern - headers before ENABLE_MOCKS should be in NO_MOCK_PRECOMPILE_HEADERS
#include "testrunnerswitcher.h"    // ✅ Should be in NO_MOCK_PRECOMPILE_HEADERS
#include "standard_includes.h"     // ✅ Should be in NO_MOCK_PRECOMPILE_HEADERS
#include "constants.h"             // ✅ Should be in NO_MOCK_PRECOMPILE_HEADERS
#include "c_pal/interlocked.h"     // ✅ Should be in NO_MOCK_PRECOMPILE_HEADERS

#define ENABLE_MOCKS
#include "dependency1.h"           // ✅ Should be in MOCK_PRECOMPILE_HEADERS
#include "dependency2.h"           // ✅ Should be in MOCK_PRECOMPILE_HEADERS
#undef ENABLE_MOCKS

// Corresponding CMakeLists.txt
build_test_artifacts(component_ut ${CMAKE_CURRENT_LIST_DIR}
    NO_MOCK_PRECOMPILE_HEADERS
        "testrunnerswitcher.h"     # Match test file includes
        "standard_includes.h"      # Match test file includes  
        "constants.h"              # Match test file includes
        "c_pal/interlocked.h"      # c_pal repository header
    MOCK_PRECOMPILE_HEADERS
        "dependency1.h"            # Headers between ENABLE_MOCKS
        "dependency2.h"            # Headers between ENABLE_MOCKS
)
```

```cmake
# This generates headers that are included BEFORE the ENABLE_MOCKS block
build_test_artifacts(component_ut ${CMAKE_CURRENT_LIST_DIR}
    NO_MOCK_PRECOMPILE_HEADERS
        "standard_includes.h"      # Headers without mockable functions
        "constants.h"              # Configuration headers
    MOCK_PRECOMPILE_HEADERS
        "mockable_dependency.h"    # Headers with MOCKABLE_FUNCTION
)
```

#### Build Performance Considerations
```cmake
# ✅ Good candidates for MOCK_PRECOMPILE_HEADERS
MOCK_PRECOMPILE_HEADERS
    "azure_c_shared_utility/gballoc.h"      # Complex memory allocation mocks
    "azure_uamqp_c/session.h"              # Large interface with many functions
    "azure_iot_common/iothub_client.h"     # Frequently used across tests

# ✅ Good candidates for NO_MOCK_PRECOMPILE_HEADERS  
NO_MOCK_PRECOMPILE_HEADERS
    "macro_utils/macro_utils.h"            # Macro utilities without mockable functions
    "constants.h"                          # Configuration headers
    "common_includes.h"                    # Standard library wrappers

# ✅ Good candidates for MOCK_PRECOMPILE_HEADERS
MOCK_PRECOMPILE_HEADERS
    "azure_c_shared_utility/gballoc.h"      # Complex memory allocation mocks
    "azure_uamqp_c/session.h"              # Large interface with many functions
    "azure_iot_common/iothub_client.h"     # Frequently used across tests

# ❌ Poor candidates - avoid precompilation overhead
# "simple_interface.h"                     # Only 1-2 functions
# "test_specific_header.h"                 # Used by single test file
# "infrequently_used.h"                    # Rarely included
```

#### Build Performance Considerations
```cmake
# ✅ Good candidates for MOCK_PRECOMPILE_HEADERS
MOCK_PRECOMPILE_HEADERS
    "azure_c_shared_utility/gballoc.h"      # Complex memory allocation mocks
    "azure_uamqp_c/session.h"              # Large interface with many functions
    "azure_iot_common/iothub_client.h"     # Frequently used across tests

# ✅ Good candidates for NO_MOCK_PRECOMPILE_HEADERS  
NO_MOCK_PRECOMPILE_HEADERS
    "testrunnerswitcher.h"                 # Test framework headers
    "macro_utils/macro_utils.h"            # Macro utilities without mockable functions
    "constants.h"                          # Configuration headers
    "common_includes.h"                    # Standard library wrappers

# ❌ Don't precompile these
# Standard CRT headers: <interlocked.h>, <stdio.h>, <stdlib.h>
# "simple_interface.h"                     # Only 1-2 functions
# "test_specific_header.h"                 # Used by single test file
# "infrequently_used.h"                    # Rarely included
```

#### Critical Build Requirements
```cmake
# This generates a precompiled header file with structure:
# #define ENABLE_MOCKS
# #define ENABLE_MOCKS_DECL
# #include "dependency1.h"
# #include "dependency2.h"
# #include "large_dependency.h"
# #undef ENABLE_MOCKS_DECL
# #undef ENABLE_MOCKS
build_test_artifacts(my_component_ut ${CMAKE_CURRENT_LIST_DIR}
    MOCK_PRECOMPILE_HEADERS
        "azure_c_shared_utility/gballoc.h"
        "azure_c_shared_utility/crt_abstractions.h"
        "azure_uamqp_c/amqp_management.h"
)
```

#### Generated Mock Library Structure
When `MOCK_PRECOMPILE_HEADERS` or `NO_MOCK_PRECOMPILE_HEADERS` is used, the build system generates:

```cmake
# Generated automatically by build_test_artifacts()
# my_component_ut_mocks.h contains:
#ifndef MY_COMPONENT_UT_MOCKS_H
#define MY_COMPONENT_UT_MOCKS_H

// NO_MOCK_PRECOMPILE_HEADERS content (outside ENABLE_MOCKS)
#include "standard_includes.h"
#include "constants.h"

// MOCK_PRECOMPILE_HEADERS content (inside ENABLE_MOCKS)
#define ENABLE_MOCKS
#define ENABLE_MOCKS_DECL
#include "dependency1.h"
#include "dependency2.h"
#undef ENABLE_MOCKS_DECL
#undef ENABLE_MOCKS

#endif // MY_COMPONENT_UT_MOCKS_H

# Result:
# - my_component_ut_mocks.h (generated header with proper include order)
# - my_component_ut_mocks.c (generated source with mock implementations)
# - Precompiled header: my_component_ut_mocks.h.pch
```

## Project-Specific Conventions

### Header Inclusion Strategy
```c
// Production code pattern
#include "umock_c/umock_c_prod.h"  // Enables MOCKABLE_FUNCTION

// Test file pattern
#include "testrunnerswitcher.h"    // Test framework

#define ENABLE_MOCKS
#include "dependency1.h"           // Generate mocks for dependencies
#include "dependency2.h"
#undef ENABLE_MOCKS

#include "unit_under_test.h"       // Real implementation
```

### Error Handling Patterns
- **Error Callbacks**: `ON_UMOCK_C_ERROR` function pointer for custom error handling
- **Error Codes**: `UMOCK_C_ERROR_CODE` enum for specific error conditions
- **Automatic Error Reporting**: Most mock validation failures automatically call error callbacks

### Static Mock Generation
```c
// Avoid symbol collisions in multi-unit test libraries
#define UMOCK_STATIC static
#define ENABLE_MOCKS
#include "dependency.h"
#include "unit_under_test.c"  // Include source directly for static visibility
```

## Testing Best Practices

### Mock Expectation Patterns
- **Use `STRICT_EXPECTED_CALL`** for precise argument validation
- **Use `EXPECTED_CALL`** when arguments don't matter, apply modifiers selectively
- **Chain modifiers** for complex expectations: `.SetReturn().IgnoreArgument().ValidateArgumentBuffer()`
- **Always verify calls match**: `ASSERT_ARE_EQUAL(char_ptr, umock_c_get_expected_calls(), umock_c_get_actual_calls())`

### Test Initialization
```c
TEST_SUITE_INITIALIZE(TestClassInitialize)
{
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    ASSERT_ARE_EQUAL(int, 0, umocktypes_charptr_register_types());
}

TEST_FUNCTION_CLEANUP(TestMethodCleanup)
{
    umock_c_reset_all_calls();
}
```

### Custom Type Testing
```c
// Enum type support in tests
TEST_DEFINE_ENUM_TYPE(MY_ENUM, MY_ENUM_VALUES);

// Test assertions for custom types
ASSERT_ARE_EQUAL(MY_ENUM, EXPECTED_VALUE, actual_value);
```

## External Dependencies & Standards

### Dependency References
Refer to dependency-specific instructions for comprehensive patterns:
- **c-build-tools**: Build infrastructure, coding standards, quality gates (`deps/c-build-tools/.github/copilot-instructions.md`)
- **macro-utils-c**: Macro metaprogramming patterns (`deps/macro-utils-c/.github/copilot-instructions.md`)
- **c-logging**: Logging integration for debugging (`deps/c-logging/.github/copilot-instructions.md`)
- **ctest**: Test framework integration (`deps/ctest/.github/copilot-instructions.md`)
- **c-testrunnerswitcher**: Cross-platform test execution (`deps/c-testrunnerswitcher/.github/copilot-instructions.md`)

### Coding Standards Compliance
**CRITICAL**: All code must follow comprehensive standards in `deps/c-build-tools/.github/general_coding_instructions.md`:
- Function naming (snake_case with module prefixes like `umock_c_*`, `umocktypes_*`)
- Parameter validation patterns and error handling
- Header inclusion order and memory management
- Requirements traceability (`SRS_UMOCK_C_*`, `Codes_SRS_UMOCK_C_*`, `Tests_SRS_UMOCK_C_*`)
- Memory allocation patterns and cleanup protocols

## Key Files & Components
- **`inc/umock_c/umock_c.h`**: Main API with core macros and functions
- **`inc/umock_c/umock_c_prod.h`**: Production-safe header enabling `MOCKABLE_FUNCTION`
- **`src/umock_c.c`**: Core implementation with call recording and verification
- **`src/umock_c_negative_tests.c`**: Negative testing framework implementation
- **`CMakeLists.txt`**: Defines `add_mock_library()` function for automated mock generation
- **`devdoc/*.md`**: Comprehensive requirements documentation for all features

This mocking framework's strength lies in its macro-based approach that generates type-safe mocks at compile time while providing runtime flexibility for test expectations and call verification.

## Common Patterns and Anti-Patterns

### Recommended Patterns
```c
// ✅ Use stack contexts for short-lived logging
LOG_CONTEXT_LOCAL_DEFINE(local_ctx, NULL, LOG_CONTEXT_PROPERTY(int32_t, id, 123));
LOGGER_LOG(LOG_LEVEL_INFO, &local_ctx, "Operation completed");

// ✅ Check context creation results for dynamic contexts
LOG_CONTEXT_HANDLE ctx;
if (LOG_CONTEXT_CREATE(ctx, NULL, /* properties */) == 0)
{
    LOGGER_LOG(LOG_LEVEL_INFO, ctx, "Message");
    LOG_CONTEXT_DESTROY(ctx);
}

// ✅ Use appropriate log levels
LOGGER_LOG(LOG_LEVEL_CRITICAL, NULL, "System is shutting down");   // Fatal errors
LOGGER_LOG(LOG_LEVEL_ERROR, NULL, "Operation failed");             // Recoverable errors  
LOGGER_LOG(LOG_LEVEL_WARNING, NULL, "Retrying operation");         // Potential issues
LOGGER_LOG(LOG_LEVEL_INFO, NULL, "User logged in");               // Normal events
LOGGER_LOG(LOG_LEVEL_VERBOSE, NULL, "Detailed debug info");       // Debug information
```

### Critical Mistakes to Avoid

#### ❌ CopyOutArgumentBuffer with Stack Variables
```c
// DANGEROUS - stack variable goes out of scope
TEST_FUNCTION(bad_copy_out_example)
{
    // arrange
    {
        char stack_buffer[] = "temporary data";  // Stack variable
        STRICT_EXPECTED_CALL(get_data(output_buffer))
            .CopyOutArgumentBuffer_output_buffer(stack_buffer, sizeof(stack_buffer));
    }  // stack_buffer goes out of scope here!
    
    // act - UNDEFINED BEHAVIOR: stack_buffer memory is invalid
    get_data(my_buffer);
}

// ✅ CORRECT - use static or heap allocated data
TEST_FUNCTION(good_copy_out_example)
{
    // arrange
    static char persistent_buffer[] = "persistent data";  // Static storage
    STRICT_EXPECTED_CALL(get_data(output_buffer))
        .CopyOutArgumentBuffer_output_buffer(persistent_buffer, sizeof(persistent_buffer));
    
    // act - SAFE: persistent_buffer remains valid
    get_data(my_buffer);
}
```

#### ❌ Forgetting to Register Custom Types
```c
// DANGEROUS - using custom types without registration
typedef struct MY_STRUCT_TAG { int value; } MY_STRUCT;

TEST_FUNCTION(unregistered_type_failure)
{
    MY_STRUCT test_data = { 42 };
    
    // This will FAIL at runtime - MY_STRUCT not registered
    STRICT_EXPECTED_CALL(process_struct(test_data));  // Runtime error!
}

// ✅ CORRECT - register types in test suite initialization
TEST_SUITE_INITIALIZE(TestSuiteInit)
{
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    
    // Register custom types BEFORE using them
    REGISTER_UMOCK_VALUE_TYPE(MY_STRUCT);
    ASSERT_ARE_EQUAL(int, 0, umocktypes_charptr_register_types());
}

TEST_FUNCTION(registered_type_success)
{
    MY_STRUCT test_data = { 42 };
    
    // Now this works correctly
    STRICT_EXPECTED_CALL(process_struct(test_data));
}
```

#### ❌ Missing umock_c_prod.h After Disabling Mocks
```c
// DANGEROUS - missing production header after undef
#define ENABLE_MOCKS
#include "dependency1.h"           // Generates mocks
#include "dependency2.h"           // Generates mocks
#undef ENABLE_MOCKS

// Missing: #include "umock_c/umock_c_prod.h"

#include "dependency3.h"           // BROKEN - no MOCKABLE_FUNCTION support
#include "unit_under_test.h"       // May have issues with real function calls

// ✅ CORRECT - include production header after undef
#define ENABLE_MOCKS
#include "dependency1.h"           // Generates mocks
#include "dependency2.h"           // Generates mocks
#undef ENABLE_MOCKS

#include "umock_c/umock_c_prod.h"  // REQUIRED to switch back to not generating mocks

#include "dependency3.h"           // Now works correctly
#include "unit_under_test.h"       // Real function support available
```

#### ❌ Incorrect Call Expectation Verification
```c
// DANGEROUS - forgetting to verify call matching
TEST_FUNCTION(incomplete_verification)
{
    // arrange
    STRICT_EXPECTED_CALL(dependency_function(42));
    
    // act
    function_under_test();
    
    // Missing verification - test passes even if calls don't match!
    // ASSERT_ARE_EQUAL(char_ptr, umock_c_get_expected_calls(), umock_c_get_actual_calls());
}

// ✅ CORRECT - always verify call matching
TEST_FUNCTION(complete_verification)
{
    // arrange
    STRICT_EXPECTED_CALL(dependency_function(42));
    
    // act
    function_under_test();
    
    // assert - REQUIRED verification
    ASSERT_ARE_EQUAL(char_ptr, umock_c_get_expected_calls(), umock_c_get_actual_calls());
}
```

#### ❌ Memory Leaks in Test Cleanup
```c
// DANGEROUS - not cleaning up allocated test data
TEST_FUNCTION(memory_leak_example)
{
    // arrange
    char* dynamic_data = malloc(100);
    strcpy(dynamic_data, "test data");
    
    STRICT_EXPECTED_CALL(process_data(dynamic_data));
    
    // act
    process_data(dynamic_data);
    
    // Missing cleanup - MEMORY LEAK!
    // free(dynamic_data);
}

// ✅ CORRECT - always clean up in test cleanup or function end
TEST_FUNCTION(proper_cleanup_example)
{
    // arrange
    char* dynamic_data = malloc(100);
    strcpy(dynamic_data, "test data");
    
    STRICT_EXPECTED_CALL(process_data(dynamic_data));
    
    // act
    process_data(dynamic_data);
    
    // assert
    ASSERT_ARE_EQUAL(char_ptr, umock_c_get_expected_calls(), umock_c_get_actual_calls());
    
    // cleanup
    free(dynamic_data);
}
```

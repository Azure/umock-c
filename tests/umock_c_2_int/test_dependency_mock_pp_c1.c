#if 1
/*QWQWQW*/
#include "test_dependency_mock.c"
/*WEWEWE*/
#else
#include "umock_c/umock_c_internal.h"
MOCKABLE_FUNCTION_UMOCK_INTERNAL_WITH_MOCK_NO_CODE_DECL(, int, test_dependency_no_args);
MOCKABLE_FUNCTION_UMOCK_INTERNAL_WITH_MOCK_NO_CODE_IMPL(, int, test_dependency_no_args);
#endif

/*this is precompilation of "test_dependency_mock.c"*/
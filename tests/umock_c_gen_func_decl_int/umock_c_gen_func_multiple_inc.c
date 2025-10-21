// this translation unit is simply here to make sure we can generate code for mocks and raw function declarations
// even when including umock_c_prod multiple times

#include "umock_c/umock_c_ENABLE_MOCKS.h" // ============================== ENABLE_MOCKS

#include "umock_c/umock_c.h"
#include "umock_c/umock_c_prod.h"

// have a mock
MOCKABLE_FUNCTION(, void, have_a_mock);

#include "umock_c/umock_c_DISABLE_MOCKS.h" // ============================== DISABLE_MOCKS

// now include again and have no mocks
#include "umock_c/umock_c_prod.h"

// this is not supposed to generate any mock
// we simply want to make sure that we can generate the raw declaration *after* ENABLE_MOCKS was disabled
MOCKABLE_FUNCTION(, void, really_no_mock);

#include "umock_c/umock_c_ENABLE_MOCKS.h" // ============================== ENABLE_MOCKS

// and have another mock
MOCKABLE_FUNCTION(, void, have_another_mock);

#include "umock_c/umock_c_DISABLE_MOCKS.h" // ============================== DISABLE_MOCKS

void really_no_mock(void)
{
}

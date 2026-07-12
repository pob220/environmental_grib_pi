#pragma once

#include <wx/jsonval.h>

// Create the versioned fields shared by every native generator job. Keeping
// string literals here avoids wxJSON's const-char-to-bool overload trap.
wxJSONValue CreateGeneratorJobEnvelope();


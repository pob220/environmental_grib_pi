#include "GeneratorJobJson.h"

#include <iostream>

#include <wx/jsonreader.h>
#include <wx/jsonwriter.h>

int main() {
  wxJSONWriter writer;
  wxString encoded;
  writer.Write(CreateGeneratorJobEnvelope(), encoded);

  wxJSONValue decoded;
  wxJSONReader reader;
  if (reader.Parse(encoded, &decoded) != 0) {
    std::cerr << "Failed to parse generated job envelope\n";
    return 1;
  }

  const auto& operation = decoded["operation"];
  const auto& cycle = decoded["request"]["cycle"];
  const auto& password_environment =
      decoded["credentials"]["copernicusPasswordEnvironment"];
  if (decoded["schemaVersion"].AsInt() != 1 || !operation.IsString() ||
      operation.AsString() != "generateEnvironment" || !cycle.IsString() ||
      cycle.AsString() != "auto" || !password_environment.IsString() ||
      password_environment.AsString() !=
          "ENVIRONMENTAL_GRIB_COPERNICUS_PASSWORD") {
    std::cerr << "Generated job envelope does not match schema v1:\n"
              << encoded << '\n';
    return 1;
  }
  return 0;
}


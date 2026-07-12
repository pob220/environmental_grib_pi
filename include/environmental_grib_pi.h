#pragma once

#include <cstdint>
#include <memory>

#include <wx/string.h>

#include "ocpn_plugin.h"

class EnvironmentalGribDialog;

class environmental_grib_pi : public opencpn_plugin_118 {
 public:
  explicit environmental_grib_pi(void* ppimgr);
  ~environmental_grib_pi() override;

  int Init() override;
  bool DeInit() override;
  int GetAPIVersionMajor() override;
  int GetAPIVersionMinor() override;
  int GetPlugInVersionMajor() override;
  int GetPlugInVersionMinor() override;
  int GetPlugInVersionPatch() override;
  int GetPlugInVersionPost() override;
  wxString GetCommonName() override;
  wxString GetShortDescription() override;
  wxString GetLongDescription() override;
  int GetToolbarToolCount() override;
  void OnToolbarToolCallback(int id) override;
  void SetCurrentViewPort(PlugIn_ViewPort& vp) override;

 private:
  std::unique_ptr<EnvironmentalGribDialog> dialog_;
  wxWindow* m_parent_window{nullptr};
  int toolbar_id_{-1};
  PlugIn_ViewPort viewport_{};
};

#include "environmental_grib_pi.h"

#include <wx/filename.h>
#include <wx/window.h>

#include "EnvironmentalGribDialog.h"
#include "version.h"
#include "wxWTranslateCatalog.h"

#ifndef DECL_EXP
#ifdef __WXMSW__
#define DECL_EXP __declspec(dllexport)
#else
#define DECL_EXP
#endif
#endif

extern "C" DECL_EXP opencpn_plugin* create_pi(void* ppimgr) {
  return new environmental_grib_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* plugin) { delete plugin; }

environmental_grib_pi::environmental_grib_pi(void* ppimgr)
    : opencpn_plugin_118(ppimgr) {}

environmental_grib_pi::~environmental_grib_pi() = default;

int environmental_grib_pi::Init() {
  AddLocaleCatalog(PLUGIN_CATALOG_NAME);
  m_parent_window = GetOCPNCanvasWindow();

  wxFileName data(GetPluginDataDir("environmental_grib_pi"), "");
  data.AppendDir("data");
  wxFileName normal(data.GetPath(), "environmental_grib.svg");
  wxFileName rollover(data.GetPath(), "environmental_gribgrey.svg");
  wxFileName toggled(data.GetPath(), "environmental_grib-toggled.svg");
  toolbar_id_ = InsertPlugInToolSVG(
      "", normal.GetFullPath(), rollover.GetFullPath(), toggled.GetFullPath(),
      wxITEM_NORMAL, _("Generate GRIB"),
      _("Generate a combined environmental GRIB"), nullptr, -1, 0, this);

  return WANTS_TOOLBAR_CALLBACK | INSTALLS_TOOLBAR_TOOL |
         WANTS_ONPAINT_VIEWPORT | WANTS_PLUGIN_MESSAGING;
}

bool environmental_grib_pi::DeInit() {
  if (dialog_) {
    dialog_->Hide();
    dialog_.reset();
  }
  if (toolbar_id_ >= 0) RemovePlugInTool(toolbar_id_);
  toolbar_id_ = -1;
  return true;
}

int environmental_grib_pi::GetAPIVersionMajor() {
  return OCPN_API_VERSION_MAJOR;
}

int environmental_grib_pi::GetAPIVersionMinor() {
  return OCPN_API_VERSION_MINOR;
}

int environmental_grib_pi::GetPlugInVersionMajor() {
  return PLUGIN_VERSION_MAJOR;
}

int environmental_grib_pi::GetPlugInVersionMinor() {
  return PLUGIN_VERSION_MINOR;
}

int environmental_grib_pi::GetPlugInVersionPatch() {
  return PLUGIN_VERSION_PATCH;
}

int environmental_grib_pi::GetPlugInVersionPost() {
  return PLUGIN_VERSION_TWEAK;
}

wxString environmental_grib_pi::GetCommonName() { return "EnvironmentalGRIB"; }

wxString environmental_grib_pi::GetShortDescription() {
  return _("Generate combined weather, wave, and current GRIB files.");
}

wxString environmental_grib_pi::GetLongDescription() {
  return _("Downloads and converts environmental model data using an isolated "
           "native helper, producing validated GRIB files for OpenCPN.");
}

int environmental_grib_pi::GetToolbarToolCount() { return 1; }

void environmental_grib_pi::OnToolbarToolCallback(int) {
  if (!dialog_) {
    dialog_ = std::make_unique<EnvironmentalGribDialog>(
        m_parent_window, GetPluginDataDir("environmental_grib_pi"));
    if (viewport_.bValid) dialog_->SetCurrentViewPort(viewport_);
  }
  dialog_->Show();
  dialog_->Raise();
}

void environmental_grib_pi::SetCurrentViewPort(PlugIn_ViewPort& viewport) {
  viewport_ = viewport;
  if (dialog_) dialog_->SetCurrentViewPort(viewport);
}

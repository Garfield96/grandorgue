#ifndef GOSOUNDPORTSCONFIG_H
#define GOSOUNDPORTSCONFIG_H

#include <vector>
#include <wx/string.h>

class GOSoundPortsConfig {
private:
  struct PortApiConfig {
    wxString m_PortName;
    wxString m_ApiName;
    bool m_IsEnabled;
    
    PortApiConfig(const wxString &portName, const wxString &apiName, bool isEnabled)
      : m_PortName(portName), m_ApiName(apiName), m_IsEnabled(isEnabled) {}

    bool operator==(const PortApiConfig &other) const
    { 
      return m_PortName == other.m_PortName
	&& m_ApiName == other.m_ApiName
	&& m_IsEnabled == other.m_IsEnabled;
    }
    
    bool operator!=(const PortApiConfig &other) const 
    { 
      return m_PortName != other.m_PortName
	|| m_ApiName != other.m_ApiName
	|| m_IsEnabled != other.m_IsEnabled;
    }
  };
  
  std::vector<PortApiConfig> m_PortApiConfigs;
  
  int Find(const wxString &portName, const wxString &apiName) const;
  
public:
  GOSoundPortsConfig() {}
  GOSoundPortsConfig(const GOSoundPortsConfig &src): m_PortApiConfigs(src.m_PortApiConfigs) {}
  
  bool operator==(const GOSoundPortsConfig &other) const { return m_PortApiConfigs == other.m_PortApiConfigs; }
  bool operator!=(const GOSoundPortsConfig &other) const { return m_PortApiConfigs != other.m_PortApiConfigs; }

  void Clear() { m_PortApiConfigs.clear(); }
  void AssignFrom(const GOSoundPortsConfig &src) { m_PortApiConfigs = src.m_PortApiConfigs; }
  
  void SetConfigEnabled(const wxString &portName, const wxString &apiName, bool isEnabled);
  
  void SetConfigEnabled(const wxString &portName, bool isEnabled) 
  { SetConfigEnabled(portName, wxEmptyString, isEnabled); }
  
  // for setting
  bool IsConfigEnabled(const wxString &portName, const wxString &apiName) const;

  bool IsConfigEnabled(const wxString &portName) const
  { return IsConfigEnabled(portName, wxEmptyString); }
  
  // for using
  bool IsEnabled(const wxString &portName, const wxString &apiName) const
  {
    return IsConfigEnabled(portName, wxEmptyString)
      && IsConfigEnabled(portName, apiName);
  }
  
  bool IsEnabled(const wxString &portName) const 
  { return IsConfigEnabled(portName, wxEmptyString); }
};

#endif /* GOSOUNDPORTSCONFIG_H */


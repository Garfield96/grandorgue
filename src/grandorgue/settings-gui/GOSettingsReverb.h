/*
* Copyright 2006 Milan Digital Audio LLC
* Copyright 2009-2021 GrandOrgue contributors (see AUTHORS)
* License GPL-2.0 or later (https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
*/

#ifndef SETTINGSREVERB_H
#define SETTINGSREVERB_H

#include <wx/panel.h>

class GOSettings;
class wxCheckBox;
class wxChoice;
class wxFileDirPickerEvent;
class wxFilePickerCtrl;
class wxSpinButton;
class wxSpinCtrl;
class wxSpinEvent;
class wxStaticText;
class wxTextCtrl;

class SettingsReverb : public wxPanel
{
	enum {
		ID_ENABLED = 200,
		ID_DIRECT,
		ID_FILE,
		ID_CHANNEL,
		ID_START_OFFSET,
		ID_LENGTH,
		ID_DELAY,
		ID_GAIN,
		ID_GAIN_SPIN,
	};
private:
	GOSettings& m_Settings;
	wxCheckBox* m_Enabled;
	wxCheckBox* m_Direct;
	wxFilePickerCtrl* m_File;
	wxStaticText* m_FileName;
	wxChoice* m_Channel;
	wxSpinCtrl* m_StartOffset;
	wxSpinCtrl* m_Length;
	wxSpinCtrl* m_Delay;
	wxTextCtrl* m_Gain;
	wxSpinButton* m_GainSpin;

	void OnEnabled(wxCommandEvent& event);
	void OnFileChanged(wxFileDirPickerEvent& e);
	void OnGainSpinChanged(wxSpinEvent& e);
	void OnGainChanged(wxCommandEvent &e);

	void UpdateFile();
	void UpdateLimits();
	void UpdateEnabled();

	bool Validate();

public:
	SettingsReverb(GOSettings& settings, wxWindow* parent);

	void Save();

	DECLARE_EVENT_TABLE()
};

#endif

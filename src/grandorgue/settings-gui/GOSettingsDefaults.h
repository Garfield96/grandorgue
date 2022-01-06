/*
* Copyright 2006 Milan Digital Audio LLC
* Copyright 2009-2021 GrandOrgue contributors (see AUTHORS)
* License GPL-2.0 or later (https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
*/

#ifndef SETTINGSDEFAULTS_H
#define SETTINGSDEFAULTS_H

#include <wx/panel.h>

class GOSettings;
class wxDirPickerCtrl;
class wxSpinCtrl;

class SettingsDefaults : public wxPanel
{
	enum {
		ID_ORGAN_PATH = 200,
		ID_ORGANPACKAGE_PATH,
		ID_SETTING_PATH,
		ID_AUDIO_RECORDER_PATH,
		ID_MIDI_RECORDER_PATH,
		ID_MIDI_PLAYER_PATH,
		ID_METRONOME_MEASURE,
		ID_METRONOME_BPM,
		ID_VOLUME,
	};
private:
	GOSettings& m_Settings;
	wxDirPickerCtrl* m_OrganPath;
	wxDirPickerCtrl* m_OrganPackagePath;
	wxDirPickerCtrl* m_SettingPath;
	wxDirPickerCtrl* m_AudioRecorderPath;
	wxDirPickerCtrl* m_MidiRecorderPath;
	wxDirPickerCtrl* m_MidiPlayerPath;
	wxSpinCtrl* m_MetronomeMeasure;
	wxSpinCtrl* m_MetronomeBPM;
	wxSpinCtrl* m_Volume;

public:
	SettingsDefaults(GOSettings& settings, wxWindow* parent);

	void Save();
};

#endif

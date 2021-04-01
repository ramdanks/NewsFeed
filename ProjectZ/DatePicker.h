#pragma once
#include <wx/wx.h>
#include <wx/calctrl.h>
#include <wx/datectrl.h>

class DatePicker : public wxDialog
{
public:
	DatePicker(wxWindow* parent);

	wxCalendarCtrl* GetCalendarCtrl() const;
	wxString GetISODate();

	void OnDateChanged(wxDateEvent& event);
	void OnCalendarChanged(wxCalendarEvent& event);

private:
	wxDatePickerCtrl* mDatePicker;
	wxCalendarCtrl* mCalendar;

	wxDECLARE_EVENT_TABLE();
};


#include "DatePicker.h"

wxBEGIN_EVENT_TABLE(DatePicker, wxDialog)
EVT_CALENDAR_SEL_CHANGED(wxID_ANY, DatePicker::OnCalendarChanged)
EVT_DATE_CHANGED(wxID_ANY, DatePicker::OnDateChanged)
wxEND_EVENT_TABLE()

DatePicker::DatePicker(wxWindow* parent)
	: wxDialog(parent, wxID_ANY, "Date Picker")
{
	auto* sizer = new wxBoxSizer(wxVERTICAL);
	auto* sizerTop = new wxBoxSizer(wxHORIZONTAL);
	
	mDatePicker = new wxDatePickerCtrl(this, wxID_ANY);
	auto* ok = new wxButton(this, wxID_OK, "OK");
	auto* cancel = new wxButton(this, wxID_CANCEL, "Cancel");
	sizerTop->Add(mDatePicker, 1);
	sizerTop->Add(ok, 0);
	sizerTop->Add(cancel, 0);

	mCalendar = new wxCalendarCtrl(this, wxID_ANY);
	mCalendar->SetForegroundColour(wxColour(240, 240, 240));
	mCalendar->SetBackgroundColour(wxColour(30, 30, 30));
	mCalendar->SetDate(mDatePicker->GetValue());
	
	sizer->Add(sizerTop);
	sizer->Add(mCalendar);
	this->SetSizer(sizer);
	sizer->SetSizeHints(this);
}

wxCalendarCtrl* DatePicker::GetCalendarCtrl() const
{
	return mCalendar;
}

wxString DatePicker::GetISODate()
{
	return mCalendar->GetDate().FormatISODate();
}

void DatePicker::OnDateChanged(wxDateEvent& event)
{
	auto* dateCtrl = (wxDatePickerCtrl*) event.GetEventObject();
	auto date = dateCtrl->GetValue();
	mCalendar->SetDate(date);
}

void DatePicker::OnCalendarChanged(wxCalendarEvent& event)
{
	auto* calCtrl = (wxCalendarCtrl*) event.GetEventObject();
	auto date = calCtrl->GetDate();
	mDatePicker->SetValue(date);
}

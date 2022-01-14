#include "funcitons.h"
#include <iomanip>
#include <map>
#include <string>
void functions::formatMeridiem (SYSTEMTIME & time_, std::string & meridiemMode_)
{
  if ((int) time_.wHour == 0)
  {
    time_.wHour = 12;
    meridiemMode_ = " AM";
  }
  else if ((int) time_.wHour == 12)
  {
    time_.wHour = time_.wHour;
    meridiemMode_ = " PM";
  }
  else if ((int)time_.wHour > 12)
  {
    time_.wHour = ((int)time_.wHour - 12);
    meridiemMode_ = " PM";
  }
  else
  {
    time_.wHour = time_.wHour;
    meridiemMode_ = " AM";
  }
}
void functions::formatDate (std::stringstream & ss_, SYSTEMTIME time_, std::string dateFormat_)
{
  std::map <const std::string, const int> DATE_FORMATS =
  {
    {"MDY", 0}, {"MYD", 1}, {"DMY", 2},
    {"DYM", 3}, {"YMD", 4}, {"YDM", 5}
  };
  switch (DATE_FORMATS[dateFormat_])
  {
  case (0):
    ss_ << time_.wMonth << '/' << time_.wDay << '/' << time_.wYear;
    break;
  case (1):
    ss_ << time_.wMonth << '/' << time_.wYear << '/' << time_.wDay;
    break;
  case (2):
    ss_ << time_.wDay << '/' << time_.wMonth << '/' << time_.wYear;
    break;
  case (3):
    ss_ << time_.wDay << '/' << time_.wYear << '/' << time_.wMonth;
    break;
  case (4):
    ss_ << time_.wYear << '/' << time_.wMonth << '/' << time_.wDay;
    break;
  case (5):
    ss_ << time_.wYear << '/' << time_.wDay << '/' << time_.wMonth;
    break;
  default:
    break;
  }
}
void functions::formatTime (std::string & string_, bool date_, bool time_, bool meridiem_, std::string dateFormat_)
{
  SYSTEMTIME time;
  GetLocalTime (&time);
  std::stringstream ss;
  string_ = "";
  std::string meridiemMode = "";
  if (meridiem_)
  {
    formatMeridiem (time, meridiemMode);
  }
  if (time_)
  {
    ss
      << time.wHour
      << std::setw (1) << ':'
      << std::setw (2) << std::setfill ('0') << time.wMinute
      << std::setw (1) << ':'
      << std::setw (2) << std::setfill ('0') << time.wSecond
      << std::setw (0) << meridiemMode;
  }
  if (time_ && date_)
  {
    ss << ' ';
  }
  if (date_)
  {
    formatDate (ss, time, dateFormat_);
  }
  string_ = ss.str ();
}
void functions::signal_control_c_handler (int signal_num)
{
  std::exit (0);
}
#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <sstream>
#include <Windows.h>
namespace functions
{
  void formatMeridiem (SYSTEMTIME & time_, std::string & meridiemMode_);
  void formatDate (std::stringstream & ss_, SYSTEMTIME time_, std::string dateFormat_);
  void formatTime (std::string& string_, bool date_, bool time_, bool meridiem_, std::string dateFormat_);
  void signal_control_c_handler (int signal_num);
};
#endif // !FUNCTIONS_H


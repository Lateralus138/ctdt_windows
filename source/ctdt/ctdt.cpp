//////////////////////////////////////////////////
// Console Title Date Time                      //
// Set the a Windows console's title to the     //
// current date and time on a loop. Use         //
// 'Start - Process -NoNewWindow ctdt'          //
// in PowerShell and                            //
// 'start /b ctdt'                              //
// in CMD to run this in the background.        //
// © 2021 Ian Pride - New Pride Software /      //
// Services                                     //
//////////////////////////////////////////////////
#include "ctdt.h"
#include "funcitons.h"

// TODO Possiby add /S,/SWITCH switch to change the display order.

//////////////////////////////////////////////////
// Main Program                                 //
//////////////////////////////////////////////////
int main (int argc, char * argv [])
{
  signal (SIGINT, functions::signal_control_c_handler);
  SetConsoleOutputCP (CP_UTF8);
  const std::regex RGX_HELP           ("^/([hH]|[hH][eE][lL][pP]|\\?)$");
  const std::regex RGX_DATE           ("^/([dD]|[dD][aA][tT][eE])$");
  const std::regex RGX_TIME           ("^/([tT]|[tT][iI][mM][eE])$");
  const std::regex RGX_MERIDIEM       ("^/([mM]|[mM][eE][rR][iI][dD][iI][eE][mM])$");
  const std::regex RGX_FORMAT         ("^/([fF]|[fF][oO][rR][mM][aA][tT])$");
  const std::regex RGX_PARAM_MDY_ALL  ("^([mM][dD][yY]|[mM][yY][dD]|[dD][mM][yY]|[dD][yY][mM]|[yY][mM][dD]|[yY][dD][mM])$");
  struct bools
  {
    bool
      date = true,
      time = true,
      meridiem = false;
  };
  struct strings
  {
    std::string
      dateFormat = "MDY",
      timeString = "";
  };
  struct ints
  {
    int delay = 1000000;
  };

  bools bools;
  strings strings;
  ints ints;
  if (argc > 1)
  {
    std::vector <std::string> args (argv + 1, argv + argc);
    argc--;
    bool skip = false;
    for (auto i = 0; i < argc; i++)
    {
      std::string this_arg = args [i];
      if (skip)
      {
        skip = false;
        continue;
      }
      if (std::regex_match (this_arg, RGX_HELP))
      {
        const std::vector <std::string> BOX =
        {
          u8"\u250C",
          u8"\u2500",
          u8"\u2510",
          u8"\u2502",
          u8"\u2514",
          u8"\u2518",
          u8"\u251C",
          u8"\u2524"
        };
        std::string box_line;
        for (auto i = 0; i < 48; ++i)
        {
          box_line += BOX [1];
        }
        std::string help_message;
        help_message.append
        (
          '\n' +
          BOX [0] + box_line                                            + BOX [2] + '\n' +
          BOX [3] + "            Console Title Date Time             "  + BOX [3] + '\n' +
          BOX [6] + box_line                                            + BOX [7] + '\n' +
          BOX [3] + " Set a console's title to the current date      "  + BOX [3] + '\n' +
          BOX [3] + " and/or time on a continous loop. It's best to  "  + BOX [3] + '\n' +
          BOX [3] + " run this in the background.                    "  + BOX [3] + '\n' +
          BOX [6] + box_line                                            + BOX [7] + '\n' +
          BOX [3] + " ctdt [/H] [/D] [/T] [/M] [/F format]           "  + BOX [3] + '\n' +
          BOX [3] + " Examples:                                      "  + BOX [3] + '\n' +
          BOX [3] + " CMD:                                           "  + BOX [3] + '\n' +
          BOX [3] + " start /B ctdt /m                               "  + BOX [3] + '\n' +
          BOX [3] + " PowerShell:                                    "  + BOX [3] + '\n' +
          BOX [3] + " Start-Process ctdt -NoNewWindow                "  + BOX [3] + '\n' +
          BOX [3] + "                    -ArgumentList '/m'          "  + BOX [3] + '\n' +
          BOX [6] + box_line                                            + BOX [7] + '\n' +
          BOX [3] + " /h,/HELP,/?     This help screen.              "  + BOX [3] + '\n' +
          BOX [3] + " /d,/DATE        Display the date only.         "  + BOX [3] + '\n' +
          BOX [3] + " /t,/TIME        Display the time only.         "  + BOX [3] + '\n' +
          BOX [3] + "                 What is displayed depends on   "  + BOX [3] + '\n' +
          BOX [3] + "                 which switch is passed last.   "  + BOX [3] + '\n' +
          BOX [3] + " /m,/MERIDIEM    12 Hour Meridiem time: AM/PM.  "  + BOX [3] + '\n' +
          BOX [3] + "                 Defaults to a 24 hour clock.   "  + BOX [3] + '\n' +
          BOX [3] + " /f,/FORMAT      The date's format. Defaults to "  + BOX [3] + '\n' +
          BOX [3] + "                 U.S. format M/D/Y, but all     "  + BOX [3] + '\n' +
          BOX [3] + "                 variations are possible in the "  + BOX [3] + '\n' +
          BOX [3] + "                 values of MDY,MYD,DMY,DYM,YMD, "  + BOX [3] + '\n' +
          BOX [3] + "                 and YDM.                       "  + BOX [3] + '\n' +
          BOX [4] + box_line                                            + BOX [5] + "\n\n"
        );
        std::cout << help_message;
        return 0;
      }
      if (std::regex_match (this_arg, RGX_DATE))
      {
        bools.date = true;
        bools.time = false;
        ints.delay = 1000000 * 60;
      }
      if (std::regex_match (this_arg, RGX_TIME))
      {
        bools.time = true;
        bools.date = false;
        ints.delay = 1000000;
      }
      if (std::regex_match(this_arg, RGX_MERIDIEM))
      {
        bools.meridiem = true;
      }
      if (std::regex_match (this_arg, RGX_FORMAT))
      {
        if ((i + 1) < argc)
        {
          std::string next_arg = args [i + 1];
          if (!std::regex_match (next_arg, RGX_PARAM_MDY_ALL))
          {
            std::cerr << "Not a valid argument for '" << this_arg << "'\n";
            return 2;
          }
          strings.dateFormat = next_arg;
        }
        else
        {
          std::cerr << "No argument provided for '" << this_arg << "'\n";
          return 1;
        }
        skip = true;
      }
    }
  }
  (void) argv;
  while (true)
  {
    auto start = std::chrono::high_resolution_clock::now ();
    functions::formatTime (strings.timeString, bools.date, bools.time, bools.meridiem, strings.dateFormat);
    SetConsoleTitleA (strings.timeString.c_str ());
    auto stop = std::chrono::high_resolution_clock::now ();
    auto duration = std::chrono::duration_cast <std::chrono::microseconds> (stop - start).count ();
    std::this_thread::sleep_for (std::chrono::microseconds ((static_cast <unsigned __int64> (ints.delay) - 10) - duration));
  }
}

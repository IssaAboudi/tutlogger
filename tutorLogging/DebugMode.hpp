//
// Created by ma422 on 11/27/2021.
//

#ifndef TUTORLOGGING_DEBUGMODE_HPP
#define TUTORLOGGING_DEBUGMODE_HPP
//TODO: Make this a settings window

#define OFF 0
#define ON 1
//-=-=-=-=-=-=-=-=-=-=-=//
//Quick Logging
#define LOGGING ON

//Release Mode toggle (Computer specific file paths)
#define RELEASE OFF


//Unit Test Mode toggle (Unit Test Function)
#define UNIT_TEST OFF

//-=-=-=-=-=-=-=-=-=-=-=//
#if LOGGING == ON
#define LOG(X) std::cout << X << std::endl
#elif LOGGING == OFF
#define LOG(X)
#endif

#define NUM_ACTIVE_STUDENTS 20
//Number of students that can be updated at a time before updating log file
// 20 probably more than needed but can be changed as needed
// TODO: check edge case (when reach limit)

//***************************//
//TODO: Figure out what colors to use
#define START_COLOR {0, 80, 0, 100}
#define STOP_COLOR {100, 0, 0, 100}
#define PRESSED_COLOR {0, 80, 20, 100}
//***************************//

#define SPACER() std::cout << std::endl

#endif //TUTORLOGGING_DEBUGMODE_HPP

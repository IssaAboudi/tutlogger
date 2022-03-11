//
// Created by ma422 on 11/27/2021.
//

#ifndef TUTORLOGGING_DEBUGMODE_HPP
#define TUTORLOGGING_DEBUGMODE_HPP

#define OFF 0
#define ON 1
//-=-=-=-=-=-=-=-=-=-=-=//
//Quick Logging
#define DEBUG ON

//Release Mode toggle (Computer specific file paths)
#define RELEASE OFF

//Unit Test Mode toggle (Unit Test Function)
#define UNIT_TEST OFF

//-=-=-=-=-=-=-=-=-=-=-=//
#if DEBUG == ON
#define LOG(X) std::cout << X << std::endl
#elif DEBUG == OFF
#define LOG(X)
#endif

#define SPACER() std::cout << std::endl

#endif //TUTORLOGGING_DEBUGMODE_HPP

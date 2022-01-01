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

//Release Mode toggle
#define RELEASE OFF

//Unit Test Mode toggle
#define UNIT_TEST ON

//-=-=-=-=-=-=-=-=-=-=-=//
#if DEBUG == ON
#define LOG(X) std::cout << X << std::endl
#define SPACER() std::cout << std::endl
#elif DEBUG == OFF
#define LOG(X)
#define SPACER()
#endif

#endif //TUTORLOGGING_DEBUGMODE_HPP

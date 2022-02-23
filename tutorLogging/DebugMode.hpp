//
// Created by ma422 on 11/27/2021.
//

#ifndef TUTORLOGGING_DEBUGMODE_HPP
#define TUTORLOGGING_DEBUGMODE_HPP

#define OFF 0
#define ON 1
//-=-=-=-=-=-=-=-=-=-=-=//
//Quick Logging
#define DEBUG OFF

//Release Mode toggle
#define RELEASE ON

//Unit Test Mode toggle
#define UNIT_TEST OFF

//-=-=-=-=-=-=-=-=-=-=-=//
#if DEBUG == ON
#define LOG(X) std::cout << X << std::endl
#elif DEBUG == OFF
#define LOG(X)
#endif

#define SPACER() std::cout << std::endl

#endif //TUTORLOGGING_DEBUGMODE_HPP
